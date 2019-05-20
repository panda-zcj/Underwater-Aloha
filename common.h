/**
 * 
 * Copyright (c) 2019 南京航空航天大学 航空通信网络研究室
 * 
 * @file     d:\code\matlab\Underwater Aloha\common.h
 * @author   詹长建 (2233930937@qq.com)
 * @date     2019-05
 * @brief    
 * @version  0.0.1
 * 
 * Last Modified:  2019-05-20
 * Modified By:    詹长建 (2233930937@qq.com)
 * 
 */
#ifndef COMMON_H
#define COMMON_H

#include <stdint.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 生成随机数
 * 
 */
uint32_t ulrand(void);

#ifdef __cplusplus
}
#endif

/**
 * @brief 水声节点位置
 * 
 */
struct NodeLocation
{
    uint32_t address;///<节点地址
    double x_axis;   ///<x轴坐标
    double y_axis;   ///<y轴坐标
    NodeLocation(uint16_t id ,double x,double y ){
       address=id;
       x_axis=x;
       y_axis=y;
    }
    NodeLocation():address(0),x_axis(0),y_axis(0){
        //tidi
    }
};
/**
 * @brief 记录对邻居节点的操作
 * 
 */
struct NeighborsNode
{
    struct NodeLocation neighbor_position;///<邻居节点位置
    double   neighbor_distance;    ///<与邻居节点的距离
    uint32_t neighbor_address;     ///<邻居节点地址
    uint32_t transmission_state;   ///是否向邻居节点开始传输
    double   receive_start;        ///<邻居节点接收开始时间
    double   receive_end;          ///<邻居节点接收结束时间 
    NeighborsNode(uint32_t addr):receive_start(0)
    ,receive_end(0)
    ,transmission_state(0){
        neighbor_address=addr;
    }
    NeighborsNode():receive_start(0)
    ,receive_end(0)
    ,transmission_state(0){
    } 
};
extern struct NodeLocation  nodes[100];  ///<所有节点的位置
extern struct NeighborsNode neighbor_node[100][100]; ///<邻居节点

extern uint32_t   node_number;      ///< 仿真的节点个数
extern double     simulation_time;  ///< 仿真时间
extern double     time_unit;        ///< 仿真运行基本时间单元
extern double     throughput;       ///< 吞吐量
extern double     packet_loss_rate; ///< 丢包率
extern double     average_energy_consumption; ///< 能耗

#endif //COMMON_H