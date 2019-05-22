/**
 * 
 * Copyright (c) 2019 南京航空航天大学 航空通信网络研究室
 * 
 * @file     d:\code\matlab\SimWiFi\DCF\CA\node.h
 * @author   詹长建 (2233930937@qq.com)
 * @date     2019-05
 * @brief    
 * @version  0.0.1
 * 
 * Last Modified:  2019-05-22
 * Modified By:    詹长建 (2233930937@qq.com)
 * 
 */
#ifndef  NODE_H
#define  NODE_H

#include "common.h"
#include "channel.h"
#include "mac.h"
#include <stdint.h>


// 定义水声节点属性

/**
 * @brief 定时器状态
 * 
 */
enum TimerState{
    Halt,    ///< 挂起定时器
    Continue ///< 继续退避
};
/**
 * @brief 定时器开关
 * 
 */
enum Timer{
    Off,  ///< 关闭定时器
    On   ///< 开启定时器
};
/**
 * @brief 信道状态
 * 
 */
enum ChannelState{
    Idle, ///< 信道空闲
    Busy  ///< 信道忙碌
};
/**
 * @brief 节点所处状态
 * 
 */
enum NodeState{
    IdleState,    ///< 空闲状态
    BackOffState, ///< 退避状态
    SendState,    ///< 发送状态
    ReceiveState, ///< 接收状态
    CollsionState, ///< 冲突状态
    AckTimeoutState ///< 应答超时状态
};


/**
 * @brief 采用面向对象思想，定一个节点的所有属性和动作，简化仿真设计
 * 
 */
class Node
{
private:
    /* data */
public:

    uint32_t   address_;       ///< 节点地址
    
    uint32_t   current_time_;  ///< 节点运行时钟
	uint32_t   alarm_time_;    ///< 定时器时钟
    
    uint32_t   cw_;         ///< 当前退避窗口
    uint32_t   cw_counter_; ///< 当前退避计数器
    
    uint32_t   packet_counter_;   ///< 成功发送包的个数
    uint32_t   drop_counter_;     ///< 抛弃的包个数
    uint32_t   send_counter_;     ///< 发送的包个数
    struct Packet packet;         ///< 统计数据包操作记录

    // double     transmission_duration_;  ///< 传输数据持续的时间
    // double     transmission_start_;     ///< 传输开始时间
    // double     transmission_end_;       ///< 传输结束时间

    // uint32_t   send_energy_;      ///< 发送的能量
    // uint32_t   receive_energy_;   ///< 接收的能量

    uint32_t   work_state_;   ///< 节点所处状态
    uint32_t   channel_state_;///< 信道状态
    uint32_t   timer_state_;  ///< 定时器所处状态
    uint32_t   timer_;        ///< 定时器开关状态
public:
    /**
     * @brief Construct a new Node object
     * 
     * @param id 节点地址
     */
    Node(uint32_t id);
    Node();
    virtual ~Node();

    
    //todo
    // 完成下列函数
	void Run(uint32_t clock);
	void Timer(uint32_t flag_channel);
	void SetAlarm(uint32_t alarm_time);
    uint32_t Channel(const uint32_t address,const double current_time);
};

#endif //NODE_H
