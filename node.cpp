/**
 * 
 * Copyright (c) 2019 南京航空航天大学 航空通信网络研究室
 * 
 * @file     d:\code\matlab\SimWiFi\DCF\CA\node.cpp
 * @author   詹长建 (2233930937@qq.com)
 * @date     2019-05
 * @brief    
 * @version  0.0.1
 * 
 * Last Modified:  2019-05-22
 * Modified By:    詹长建 (2233930937@qq.com)
 * 
 */
#include "node.h"
#include <iostream>
#include <assert.h>


Node::Node()
{ 
	address_=0;        // 节点地址
	
    current_time_=0;   // 节点运行时钟
	alarm_time_=0;     // 定时器时钟

    cw_ =cw_min;    // 当前退避窗口
    cw_counter_=0;  // 当前退避计数器
    
    packet_counter_=0;  // 成功发送包的个数
    drop_counter_=0;    // 抛弃的包个数
	send_counter_=0;    // 发送的包个数
	// send_energy_=0;     // 发送的能量
    // receive_energy_=0;  // 接收的能量

    work_state_=IdleState; // 节点所处状态
	channel_state_=Idle;   // 信道状态
	timer_state_=Continue; // 定时器所处状态
	timer_=Off;            // 定时器开关状态
    // transmission_duration_=Payload/transmission_rate; // 传输数据持续的时间
    // transmission_start_=0; // 传输开始时间
    // transmission_end_=0;   // 传输结束时间
}
Node::Node(uint32_t id)
{
    address_=id;         //节点地址

	current_time_=0;   // 节点运行时钟
	alarm_time_=0;     // 定时器时钟
    
    cw_ =cw_min;    // 当前退避窗口
    cw_counter_=0;  // 当前退避计数器
    
    packet_counter_=0;  // 成功发送包的个数
    drop_counter_=0;    // 抛弃的包个数
	send_counter_=0;    // 发送的包个数
	// send_energy_=0;     // 发送的能量
    // receive_energy_=0;  // 接收的能量

    work_state_=IdleState; // 节点所处状态
	channel_state_=Idle;   // 信道状态
	timer_state_=Continue; // 定时器所处状态
	timer_=Off;            // 定时器开关状态
    // transmission_duration_=Payload/transmission_rate; // 传输数据持续的时间
    // transmission_start_=0; // 传输开始时间
    // transmission_end_=0;   // 传输结束时间
}

Node::~Node()
{
}
void Node::Run(uint32_t clock){

    current_time_ = clock;
	switch(timer_){
		case Off://定时器关闭
		{
			switch(work_state_){
				case IdleState:
                    #ifdef MY_DEBUG
					assert(cw_counter_ <= 0);
                    #endif
					cw_counter_ = ulrand() % cw_;
					work_state_ = BackOffState;
					timer_= On;
					packet.id   =++total_packets;
					packet.from =address_;
					while (true)
					{
						packet.to   =(ulrand() % node_number);
						if(packet.to!=address_){
							break;
						}
					}
					packet.type =DATA;
					packet.state=Default;
					packet.retransfer_number=0;
					packet.transmission=(Mac+Physical+Payload)/transmission_rate;
					packet.arrive=current_time_;
					break;
				case BackOffState:
					if(cw_counter_ <= 0){
						work_state_ = SendState;
					}else if (cw_counter_ > 0)
					{
						if(timer_state_ == Halt){
							SetAlarm(slot);
							timer_state_=Continue;
						}
						else if(timer_state_ == Continue){
							cw_counter_--; 
							SetAlarm(slot);
						}
					}
					switch (Channel(address_,current_time_))
					{
					case Idle:
						/*code*/
						timer_state_=Idle; // 重启定时计数器
						break;
					case Busy:
						timer_state_=Halt; // 挂起定时计数器
						break;
					default:
						break;
					}
					break;
				case SendState:
				
					send_counter_++;
					packet.tx_start=current_time_;
					packet.tx_end=packet.tx_start+packet.transmission;
					packet.delay=neighbor_node[address_][packet.to].neighbor_distance/propagate_speed;
					packet.rx_start=packet.tx_start+packet.delay;
					packet.rx_end=packet.rx_start+packet.transmission;
					packet.energy=propagate_power*packet.transmission;

					PushPacket(packet);
					
					SetAlarm(packet.tx_end+2*propagate_range/propagate_speed+sifs+Ack/transmission_rate);
					
					break;
				case ReceiveState:
                    if( ulrand()%1000000 > propagate_error*1000000 )
                    {
                        packet_counter_++;
				    }					
					cw_         = cw_min;
					work_state_ = IdleState;
					break;
				case CollsionState:
					transmission_duration_ = (Physical + Mac + Payload + Ack) / transmission_rate + sifs;
					SetAlarm(transmission_duration_);
					work_state_ = AckTimeoutState;
					break;
				case AckTimeoutState:
					work_state_ = IdleState;
					break;
			}
			break;
		}
		case On: //定时器开启
		{
			// this->Timer(channel_state_);
			switch (Channel(address_,current_time_))
			{
			case Idle:
				if(cw_counter_ > 0){
					cw_counter_--;
					SetAlarm(slot);
				}else if (cw_counter_==0){
					timer_state_=Off;
					work_state_=SendState;
				}else{
					/* code */
				}	
				break;
			case Busy:
				timer_state_=Halt; // 挂起定时计数器
				break;
			default:
				break;
			}
			
			break;
		}
			
		default:
			break;
	}
}
void Node::SetAlarm(uint32_t flag_channel){
	alarm_time_ = alarm_time_ + current_time_;
	timer_state_= On;
}
void Node::Timer(uint32_t alarm_time){
	// 节点所处工作状态
	if(work_state_ == BackOffState || work_state_ == IdleState){
		// 信道忙
		if(channel_state_ == Busy){
			alarm_time_ = 1+current_time_;
			timer_state_=Halt;
		}
	}
	// 超时
	if(current_time_>=alarm_time_){
		timer_state_=Off;
	}
}
uint32_t Node::Channel(const uint32_t address,const double current_time){

}