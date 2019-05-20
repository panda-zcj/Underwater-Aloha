/**
 * 
 * Copyright (c) 2019 南京航空航天大学 航空通信网络研究室
 * 
 * @file     d:\code\matlab\Underwater Aloha\run.h
 * @author   詹长建 (2233930937@qq.com)
 * @date     2019-05
 * @brief    
 * @version  0.0.1
 * 
 * Last Modified:  2019-05-20
 * Modified By:    詹长建 (2233930937@qq.com)
 * 
 */
#ifndef SCHEDULE_H
#define SCHEDULE_H

#include "node.h"
#include "common.h"
#include "channel.h"
#include "mac.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 创建仿真的节点
 * 
 * @return int 创建成功返回 0
 */
int CreateNodes();

/**
 * @brief 模拟器运行主程序
 * 
 * @return double 返回归一化吞吐量
 */
double SimulatorRun(uint32_t simulation_time);

#ifdef __cplusplus
}
#endif

#endif //SCHEDULE_H