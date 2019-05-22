/**
 * 
 * Copyright (c) 2019 南京航空航天大学 航空通信网络研究室
 * 
 * @file     d:\code\matlab\Underwater Aloha\mac.cpp
 * @author   詹长建 (2233930937@qq.com)
 * @date     2019-05
 * @brief    
 * @version  0.0.1
 * 
 * Last Modified:  2019-05-21
 * Modified By:    詹长建 (2233930937@qq.com)
 * 
 */
#include "mac.h"

uint32_t   Physical;  // 物理层头
uint32_t   Mac;       // MAC头
uint32_t   Payload;   // 数据负载
uint32_t   Rts;       // RTS帧
uint32_t   Cts;       // CTS帧
uint32_t   Ack;       // 应答帧

double    slot;   // 最小时隙单元
double    sifs;   // 接收状态和发送状态的切换时间
double    difs;   // 判断空闲的等待时间
uint32_t  cw_min; // 最小退避窗口
uint32_t  cw_max; // 最大退避窗口 
uint32_t  reTx_max;// 最大重发次数