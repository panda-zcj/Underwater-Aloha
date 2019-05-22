/**
 * 
 * Copyright (c) 2019 南京航空航天大学 航空通信网络研究室
 * 
 * @file     d:\code\matlab\Underwater Aloha\channel.h
 * @author   詹长建 (2233930937@qq.com)
 * @date     2019-05
 * @brief    
 * @version  0.0.1
 * 
 * Last Modified:  2019-05-21
 * Modified By:    詹长建 (2233930937@qq.com)
 * 
 */
#ifndef CHANNEL_H
#define CHANNEL_H

#include <stdint.h>

// 定义水声信道属性

extern double     transmission_rate;    ///< 传输速率
extern double     propagate_speed;      ///< 传播速度
extern double     propagate_range;      ///< 传播范围
extern double     propagate_power;      ///< 传播功率 
extern double     receive_power;        ///< 接收功率
extern double     propagate_error;      ///< 传播误码率
extern double     propagate_speed_jitter; ///< 传速度变化

#endif //CHANNEL_H