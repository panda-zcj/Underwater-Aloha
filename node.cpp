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
 * Last Modified:  2019-05-20
 * Modified By:    詹长建 (2233930937@qq.com)
 * 
 */
#include "node.h"
#include <iostream>


Node::Node()
{
    address_=0;        // 节点地址
    position_.address=0;//节点坐标
    position_.x_axis=0; 
    position_.y_axis=0;
    
    cw_ =cw_min;    // 当前退避窗口
    cw_counter_=0;  // 当前退避计数器
    
    packet_counter_=0; // 成功发送包的个数
    drop_counter_=0;   // 抛弃的包个数

    work_state_=IdleState;                  // 节点所处状态
    transmission_duration_=Payload/transmission_rate; // 传输数据持续的时间
    transmission_start_=0;        // 传输开始时间
    transmission_end_=0;          // 传输结束时间
    timer_state_=Off; // 定时器所处状态
}
Node::Node(uint32_t id, double x, double y)
{
    address_=id;        // 节点地址
    position_.address=id;//节点坐标
    position_.x_axis=x; 
    position_.y_axis=y;
    
    cw_ =cw_min;    // 当前退避窗口
    cw_counter_=0;  // 当前退避计数器
    
    packet_counter_=0; // 成功发送包的个数
    drop_counter_=0;   // 抛弃的包个数

    work_state_=IdleState;                  // 节点所处状态
    transmission_duration_=Payload/transmission_rate; // 传输数据持续的时间
    transmission_start_=0;        // 传输开始时间
    transmission_end_=0;          // 传输结束时间
    timer_state_=Off; // 定时器所处状态
}

Node::~Node()
{
}
void Node::Run(uint32_t clock_in,uint32_t flag_channel){

}
void Node::SetAlarm(uint32_t flag_channel){

}
void Node::Timer(uint32_t alarm_time){
    
}