/**
 * 
 * Copyright (c) 2019 南京航空航天大学 航空通信网络研究室
 * 
 * @file     d:\code\matlab\Underwater Aloha\channel.cpp
 * @author   詹长建 (2233930937@qq.com)
 * @date     2019-05
 * @brief    
 * @version  0.0.1
 * 
 * Last Modified:  2019-05-21
 * Modified By:    詹长建 (2233930937@qq.com)
 * 
 */
#include "channel.h"

double    transmission_rate;    // 传输速率
double    propagate_speed;      // 传播速度
double    propagate_range;      // 传播范围
double    propagate_power;      // 传播功率
double    receive_power;        // 接收功率
double    propagate_error;      // 传播误码率
double    propagate_speed_jitter; // 传速度变化