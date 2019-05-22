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
 * Last Modified:  2019-05-22
 * Modified By:    詹长建 (2233930937@qq.com)
 * 
 */
#ifndef COMMON_H
#define COMMON_H

#include <stdint.h>
#include <stdlib.h>
#include <vector>
#include <algorithm>

/**
 * @brief 是否向邻居传输数据
 * 
 */
enum TransitToNeighbor{ 
    No,  ///< 不传输数据
    Yes  ///< 传输数据
};

/**
 * @brief 数据包类型
 * 
 */
enum PacketType{
    RTS,
    CTS,
    DATA,
    ACK
};
/**
 * @brief 表示发送一个数据包所处的状态
 * 
 */
enum PacketState{
    Default,    ///< 生成一个数据包，等待接收端处理
    Success,    ///< 成功发送一个数据包
    Fail        ///< 失败发送一个数据包
};
/**
 * @brief 记录一个数据包消耗的资源
 * 
 */
struct Packet
{
    uint32_t id;       ///< 数据包的id号
    uint32_t from;     ///< 发送数据包的节点地址
    uint32_t to;       ///< 接收数据包的节点地址
    uint32_t type;     ///< 数据包类型  
    uint32_t state;    ///< 数据包所处状态
    uint32_t retransfer_number;///< 重发次数
    double   transmission;///< 传输时延
    double   arrive;   ///< 生成包的时间，即包到达时间
    double   tx_start; ///< 发包的开始时间
    double   tx_end;   ///< 发包的结束时间
    double   rx_start; ///< 收包的开始时间
    double   rx_end;   ///< 收包的结束时间
    double   delay;    ///< 传播时延
    double   energy;   ///< 消耗的能量
    Packet():id(0),from(0),
    to(0),type(DATA),state(Default),retransfer_number(0),
    transmission(0),tx_start(0),tx_end(0),rx_start(0),rx_end(0),delay(0)
    ,energy(0){
        /*code*/
    };
};
/**
 * @brief 水声节点位置
 * 
 */
struct NodeLocation
{
    uint32_t address;///<节点地址
    double   x_axis; ///<x轴坐标
    double   y_axis; ///<y轴坐标
    NodeLocation(uint16_t id , double x, double y ){
       address=id;
       x_axis=x;
       y_axis=y;
    }
    NodeLocation():address(0),x_axis(0),y_axis(0){
        /*code*/
    }
};
/**
 * @brief 记录对邻居节点的操作
 * 
 */
struct NeighborsNode
{
    // struct NodeLocation neighbor_position; ///<邻居节点位置
    uint32_t local_address;                ///<本节点地址 
    uint32_t neighbor_address;             ///<邻居节点地址
    double   neighbor_distance;            ///<与邻居节点的距离
    uint32_t transmission_state;           ///<是否向邻居节点开始传输
    // double   receive_start;                ///<邻居节点接收开始时间
    // double   receive_end;                  ///<邻居节点接收结束时间 
    std::vector<struct Packet> packetVector;///< 发包的集合

    NeighborsNode():
    // receive_start(0),receive_end(0),
    transmission_state(No){
        /*code*/
    } 
};


extern struct NodeLocation  nodes[50];  ///<所有节点的位置
extern struct NeighborsNode neighbor_node[50][50]; ///<邻居节点

extern uint32_t   node_number;      ///< 仿真的节点个数
extern double     simulation_time;  ///< 仿真时间
extern double     time_unit;        ///< 仿真运行基本时间单元


extern uint32_t   total_packets;    ///< 总的发包个数
extern double     throughput;       ///< 吞吐量
extern double     packet_loss_rate; ///< 丢包率
extern double     average_energy_consumption; ///< 能耗
extern double     average_delay;    ///< 平均时延

#ifdef __cplusplus
extern "C" {
#endif
/**
 * @brief 生成随机数
 * 
 */
uint32_t ulrand(void);
/**
 * @brief sort()函数的对比函数，这里为升序排序
 * sort()函数的对比函数，这里为升序排序。\a 和 \b 为两个比较大小的值
 * @return true \a 小于 \b
 * @return false \a 大于 \b
 */
bool AscendingOrder(const struct Packet &a , const struct Packet &b);
/**
 * @brief     统计所有节点生成的数据包
 * 
 * @param pac 节点生成的数据包
 * @return uint32_t 
 */
uint32_t PushPacket(const struct Packet &pac);

#ifdef __cplusplus
}
#endif

#endif //COMMON_H