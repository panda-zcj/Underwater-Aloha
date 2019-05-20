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
 * Last Modified:  2019-05-20
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
    Off,  ///< 关闭定时器
    On,   ///< 开启定时器
    Halt  ///< 挂起定时器
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
 * @brief 是否向邻居传输数据
 * 
 */
enum TransitToNeighbor{ 
    No,  ///< 不传输数据
    Yes  ///< 传输数据
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
    struct NodeLocation position_;///< 节点坐标 
    uint32_t   address_;    ///< 节点地址
   
    uint32_t   cw_;         ///< 当前退避窗口
    uint32_t   cw_counter_; ///< 当前退避计数器
    
    uint32_t   packet_counter_; ///< 成功发送包的个数
    uint32_t   drop_counter_;   ///< 抛弃的包个数

    uint32_t   work_state_;  ///< 节点所处状态
    double     transmission_duration_;  ///< 传输数据持续的时间
    double     transmission_start_;     ///< 传输开始时间
    double     transmission_end_;       ///< 传输结束时间
    uint32_t   timer_state_; ///< 定时器所处状态
    
    // double Random_Num; ///< 随机选取的退避值 
    // double Prop_per;
    // double Prop_d;   
public:
    /**
     * @brief Construct a new Node object
     * 
     * @param id 节点地址
     * @param x  节点x轴坐标
     * @param y  节点y轴坐标
     */
    Node(uint32_t id, double x, double y);
    Node();
    virtual ~Node();

    
    //todo
    // 完成下列函数
	void Run(uint32_t clock_in,uint32_t flag_channel);
	void Timer(uint32_t flag_channel);
	void SetAlarm(uint32_t alarm_time);
};

#endif //NODE_H
