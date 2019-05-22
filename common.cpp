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
 * Last Modified:  2019-05-22
 * Modified By:    詹长建 (2233930937@qq.com)
 * 
 */
#include "common.h"
#include <iostream>

uint32_t ulrand(void) {
    return (
         (((uint32_t)rand()<<24)&0xFF000000)
        |(((uint32_t)rand()<<12)&0x00FFF000)
        |(((uint32_t)rand()    )&0x00000FFF)
        );
}
bool AscendingOrder(const struct Packet &a ,const struct Packet &b){
    return a.rx_start < b.rx_start;
}
uint32_t PushPacket(const struct Packet &pac){
    neighbor_node[pac.from][pac.to].packetVector.push_back(pac);
    std::sort(neighbor_node[pac.from][pac.to].packetVector.begin(),
    neighbor_node[pac.from][pac.to].packetVector.end(),
    AscendingOrder);
    // for(int j=0 ; j< neighbor_node[pac.from][pac.to].packetVector.size() ; j++){
    //     std::cout<<neighbor_node[pac.from][pac.to].local_address<<"  pac.from="<<pac.from
    //     <<neighbor_node[pac.from][pac.to].neighbor_address<<"  pac.to="<<pac.to<<std::endl
    //     <<neighbor_node[pac.from][pac.to].packetVector.at(j).rx_start<<"("
    //     <<neighbor_node[pac.from][pac.to].packetVector.at(j).rx_end<<")"<<"\t";
    // }
    // std::cout<<std::endl;
    return EXIT_SUCCESS;
}

struct NodeLocation  nodes[50]; // 所有节点的位置
struct NeighborsNode neighbor_node[50][50]; //邻居节点

uint32_t  node_number;      // 仿真的节点个数
double    simulation_time;  // 仿真时间
double    time_unit;        // 仿真运行基本时间单元

uint32_t  total_packets;    // 总的发包个数
double    throughput;       // 吞吐量
double    packet_loss_rate; // 丢包率
double    average_energy_consumption; // 能耗
double    average_delay;    // 平均时延

