/**
 * 
 * Copyright (c) 2019 南京航空航天大学 航空通信网络研究室
 * 
 * @file     d:\code\matlab\Underwater Aloha\common.cpp
 * @author   詹长建 (2233930937@qq.com)
 * @date     2019-05
 * @brief    
 * @version  0.0.1
 * 
 * Last Modified:  2019-05-20
 * Modified By:    詹长建 (2233930937@qq.com)
 * 
 */
#include "common.h"

uint32_t ulrand(void) {
    return (
         (((uint32_t)rand()<<24)&0xFF000000)
        |(((uint32_t)rand()<<12)&0x00FFF000)
        |(((uint32_t)rand()    )&0x00000FFF)
        );
}

struct NodeLocation  nodes[100]; // 所有节点的位置
struct NeighborsNode neighbor_node[100][100]; //邻居节点
uint32_t  node_number;      // 仿真的节点个数
double    simulation_time;  // 仿真时间
double    time_unit;        // 仿真运行基本时间单元
double    throughput;       // 吞吐量
double    packet_loss_rate; // 丢包率
double    average_energy_consumption; // 能耗

