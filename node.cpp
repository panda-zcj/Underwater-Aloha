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
 * Last Modified:  2019-05-27
 * Modified By:    詹长建 (2233930937@qq.com)
 * 
 */
#include "node.h"
#include <iostream>
#include <assert.h>
#include <time.h>


Node::Node()
{ 
    
	address_=0;        // 节点地址
	
    current_time_=0;   // 节点运行时钟
	alarm_time_=0;     // 定时器时钟

    cw_ =cw_min;       // 当前退避窗口
    cw_counter_=0;     // 当前退避计数器
    
	num=0;              // 当前正发送第n个包
    packet_counter_=0;  // 成功发送包的个数
    drop_counter_=0;    // 抛弃的包个数
	send_counter_=0;    // 发送的包个数
	send_energy_=0;     // 发送的能量
    receive_energy_=0;  // 接收的能量
	sequence_=0;        // 当前时间正接收第n个包

	// rx_start_=0;         // 接收开始时间
    // rx_end_=0;           // 接收结束时间
    // interfere_start_=0;  // 干扰开始时间
    // interfere_end_=0;    // 干扰结束时间
	
    work_state_=IdleState;     // 节点当前所处状态
	next_work_state_=IdleState;//节点下一个工作状态
	// channel_state_=Idle;      // 信道状态
	// timer_state_=Continue;    // 定时器所处状态
	timer_=Off;               // 定时器开关状态
    time_out_=INT32_MAX;      // ACK超时时间
}
Node::Node(uint32_t id)
{
    address_=id;         //节点地址

	current_time_=0;   // 节点运行时钟
	alarm_time_=0;     // 定时器时钟

    cw_ =cw_min;       // 当前退避窗口
    cw_counter_=0;     // 当前退避计数器
    
	num=0;              // 当前正发送第n个包
    packet_counter_=0;  // 成功发送包的个数
    drop_counter_=0;    // 抛弃的包个数
	send_counter_=0;    // 发送的包个数
	send_energy_=0;     // 发送的能量
    receive_energy_=0;  // 接收的能量
	sequence_=0;        // 当前时间正接收第n个包

	// rx_start_=0;         // 接收开始时间
    // rx_end_=0;           // 接收结束时间
    // interfere_start_=0;  // 干扰开始时间
    // interfere_end_=0;    // 干扰结束时间
	
    work_state_=IdleState;     // 节点当前所处状态
	next_work_state_=IdleState;//节点下一个工作状态
	// channel_state_=Idle;      // 信道状态
	// timer_state_=Continue;    // 定时器所处状态
	timer_=Off;               // 定时器开关状态
    // transmission_duration_=Payload/transmission_rate; // 传输数据持续的时间
    // transmission_start_=0; // 传输开始时间
    // transmission_end_=0;   // 传输结束时间
	time_out_=INT32_MAX;      // ACK超时时间
}

Node::~Node()
{
}

void Node::InitData(){
	tx_packet.id   =(++num)+address_*10000;
	tx_packet.from =address_;
	while (true){
		tx_packet.to =(ulrand() % node_number);
		if(tx_packet.to!=address_){
			break;
		}
	}
	#ifdef MY_DEBUG
        std::cout<<"DEBUG "<<__FILE__<<"/"<<__LINE__<<":"<<"初始化发送数据，时间为"
					<<current_time_<<" 从节点"<<tx_packet.from<<" 发往节点"<<tx_packet.to<<" 包id为"<<tx_packet.id<<std::endl;
    #endif
	tx_packet.type =DATA;
	tx_packet.state=Default;
	tx_packet.retransfer_number=0;
	tx_packet.transmission=(Mac+Physical+Payload)/transmission_rate;
	tx_packet.arrive=current_time_;
}
void Node::SendAck(){
	// send_counter_++; 
	struct Packet pac;
	pac.id   =rxpacketVector[address_][sequence_-1].id;
	pac.from =address_;
	pac.to   =rxpacketVector[address_][sequence_-1].from;
	pac.type =ACK;
	pac.state=Default;
	pac.retransfer_number=0;
	pac.transmission=(Ack)/transmission_rate;
	pac.arrive=current_time_;
	pac.tx_start=current_time_;
	pac.tx_end=pac.tx_start+pac.transmission;
	pac.delay=neighbor_node[pac.from][pac.to].neighbor_distance/propagate_speed;
	pac.rx_start=pac.tx_start+pac.delay;
	pac.rx_end=pac.rx_start+pac.transmission;
	pac.energy=propagate_power*pac.transmission;
	
	txpacketVector[pac.from].push_back(pac);//把ack压入发送数据包集合中
	PushPacket(pac);
	
	send_energy_+=pac.energy;// 统计所有发包能量消耗
}
void Node::SendData(){
	send_counter_++;
	if(tx_packet.state==Fail){
		if(tx_packet.retransfer_number < reTx_max){
			tx_packet.retransfer_number++;
		}else{
			InitData();
		}
	}
	tx_packet.tx_start=current_time_;
	tx_packet.tx_end=tx_packet.tx_start+tx_packet.transmission;
	tx_packet.delay=neighbor_node[address_][tx_packet.to].neighbor_distance/propagate_speed;
	tx_packet.rx_start=tx_packet.tx_start+tx_packet.delay;
	tx_packet.rx_end=tx_packet.rx_start+tx_packet.transmission;
	tx_packet.energy=propagate_power*tx_packet.transmission;
	PushPacket(tx_packet);

	send_energy_+=tx_packet.energy;// 统计所有发包能量消耗
}

void Node::SetAlarm(double time ,uint32_t state){
	timer_ = On;            //开启定时器
	alarm_time_  = time;    //超时的时刻
	next_work_state_=state; //超时后的状态
}
void Node::SetAlarm(double time){
	timer_ = On;            //开启定时器
	alarm_time_  = time;    //超时的时刻
}
void Node::Timer(){
	if( timer_==On && current_time_ >= alarm_time_){
		timer_=Off;                   //关闭定时器
		work_state_=next_work_state_; //节点的工作状态
	}
}
void Node::Run(double clock){
    current_time_ = clock;
	switch(timer_){
		case Off://定时器关闭
		{
			switch(work_state_){
				case IdleState:	
					// srand((uint32_t)time(NULL));
					cw_counter_ = ulrand() % cw_;
					InitData();
					SetAlarm(current_time_+difs,BackOffState);
					#ifdef MY_DEBUG
        			std::cout<<"DEBUG "<<__FILE__<<"/"<<__LINE__<<":"<<"选取退避值，时间为"
					<<current_time_<<" 退避值为"<<cw_counter_<<" 从节点"<<tx_packet.from<<" 发往节点"<<tx_packet.to<<" 包id为"<<tx_packet.id<<std::endl;
    				#endif
					break;
				case BackOffState:
					if(cw_counter_ <= 0){
						work_state_ = SendState;
					}else if (cw_counter_ > 0){
						cw_counter_--;
						SetAlarm(current_time_+slot,BackOffState);
					}
					break;
				case SendState:
					SendData();
					SetAlarm(current_time_+tx_packet.transmission,WaitAck);
					break;
				case ReceiveState:
					break;
				case CollsionState:
					break;
				case WaitAck:
					// SetAlarm(tx_packet.tx_end+2*propagate_range/propagate_speed+sifs+Ack/transmission_rate,IdleState);
					if(time_out_==INT32_MAX){
						timer_ = On;            //开启定时器
						time_out_=tx_packet.tx_end+2*propagate_range/propagate_speed+sifs+Ack/transmission_rate;
					}
					break;
			}
			break;
		}
		case On: //定时器开启
		{
			if(work_state_ == ReceiveState){
				if(rxpacketVector[address_][sequence_-1].type==RTS){
						/* code */
				}else if(rxpacketVector[address_][sequence_-1].type==CTS){
						/* code */
				}else if(rxpacketVector[address_][sequence_-1].type==DATA){
						if(current_time_ >= (rxpacketVector[address_][sequence_-1].rx_end + sifs) 
										&& rxpacketVector[address_][sequence_-1].state==Default){
							if( ulrand()%1000000 > propagate_error*1000000 ){
								SendAck();
								rxpacketVector[address_][sequence_-1].state=Success;
							}else{
								rxpacketVector[address_][sequence_-1].state=Fail;
							}	
						}			
				}else{
					// 接收ACK包
					if(current_time_ > rxpacketVector[address_][sequence_-1].rx_end && rxpacketVector[address_][sequence_-1].id==tx_packet.id){
							// rx_packet.state=Success;
							rxpacketVector[address_][sequence_-1].state=Success;
							packet_counter_++;
							tx_packet.state=Success;
							txpacketVector[address_].push_back(tx_packet);//记录成功发送的数据包
							timer_=Off;           //关闭定时
							work_state_=IdleState;//节点的工作状态
							time_out_=INT32_MAX;
					}
				}
			}
			if(current_time_ >= time_out_){//超时没有收到ack
				// rxpacketVector[address_][sequence_-1].state=Fail;
				drop_counter_++;
				tx_packet.state=Fail;
				time_out_=INT32_MAX;
				cw_counter_ = ulrand() % cw_; 
				next_work_state_=BackOffState;//直接进入backoffstate
			}
			this->Timer();
			break;
		}
		default:
			break;
	}
}