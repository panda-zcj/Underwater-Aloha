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
 * Last Modified:  2019-05-20
 * Modified By:    詹长建 (2233930937@qq.com)
 * 
 */
#include "mac.h"

double    slot;   // 最小时隙单元
double    sifs;   // 接收状态和发送状态的切换时间
double    difs;   // 判断空闲的等待时间
uint32_t  cw_min; // 最小退避窗口
uint32_t  cw_max; // 最大退避窗口 