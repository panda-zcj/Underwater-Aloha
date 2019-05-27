/**
 * 
 * Copyright (c) 2019 南京航空航天大学 航空通信网络研究室
 * 
 * @file     d:\code\matlab\Underwater Aloha\run.cpp
 * @author   詹长建 (2233930937@qq.com)
 * @date     2019-05
 * @brief    
 * @version  0.0.1
 * 
 * Last Modified:  2019-05-27
 * Modified By:    詹长建 (2233930937@qq.com)
 * 
 */

#include "run.h"
#include <time.h>
#include <stdio.h>
#include <cmath>
#include <iostream>
#include <iomanip> //std::setw()
#include <fstream>

int CreateNodes(){
    double x,y;
    char s[100];sprintf(s,"%d nodes of simulator.txt",node_number);
    std::ofstream out;
    out.setf(std::ios::fixed | std::ios::left);
    out.open(s,std::ios::out | std::ios::trunc);

    /*
     * tips
     * 中文与英文对齐，则设其令中文字节宽度为a，英文字节宽度为b
     * 则a,b大致满足b=2a/3+1
     * 因为utf-8编码，一个中文为3个字节，英文为一个字节
     * windows系统，英文字符的长度约为中文字符的一半
     */
    out<<std::setw(24)<<"节点仿真个数"
    <<std::setw(24)<<"节点传播范围"
    <<std::setw(24)<<"节点传输速率"
    <<std::setw(24)<<"节点传播速度"
    <<std::setw(24)<<"节点传播功率"
    <<std::setw(24)<<"节点接收功率"
    <<std::setw(24)<<"节点传播误码率"<<std::endl;
    out<<std::setw(17)<<node_number
    <<std::setw(17)<<propagate_range
    <<std::setw(17)<<transmission_rate
    <<std::setw(17)<<propagate_speed
    <<std::setw(17)<<propagate_power
    <<std::setw(17)<<receive_power
    <<std::setw(17)<<propagate_error<<std::endl;

    out<<std::endl<<std::endl<<"节点传输负载大小"<<std::endl;
    out<<Payload<<std::endl;
    
    
    struct NodeLocation node_location;
    out<<std::endl<<std::endl<<"在半径为"<<propagate_range/2<<"m的范围内，节点的位置坐标"<<std::endl
    <<std::setw(19)<<"节点ID"
    <<std::setw(23)<<"节点X轴坐标"
    <<std::setw(24)<<"节点Y轴坐标"<<std::endl;
    srand((uint32_t)time(NULL)); 
    for(uint32_t i=0; i < node_number; i++){
        for (; ;)
        {
            x=ulrand()%(uint32_t)(propagate_range);
            y=ulrand()%(uint32_t)(propagate_range);
            if(
                (x-propagate_range/2)*(x-propagate_range/2)
               +(y-propagate_range/2)*(y-propagate_range/2)
               < propagate_range*propagate_range/4
                ){
                break;
            }       
        }
       
        node_location.address=i;
        node_location.x_axis =x;
        node_location.y_axis =y;
        nodes.push_back(node_location);
        out<<std::setw(17)<<i<<std::setw(17)<<x<<std::setw(17)<<y<<std::endl;
    }
    std::vector<struct NodeLocation> (nodes).swap(nodes); // 释放多余空间
    #ifdef MY_DEBUG
        std::cout<<"DEBUG "<<__FILE__<<"/"<<__LINE__<<":"<<"所有节点坐标占用的空间 "<<nodes.capacity()<<std::endl;
    #endif
    
    struct NeighborsNode temp;
    for(uint32_t i=0;i<node_number;i++){ 
        std::vector<struct NeighborsNode> neighbor;
        for(uint32_t j=0;j<node_number;j++){
            temp.local_address=i;
            temp.neighbor_address=j;
            temp.neighbor_distance=sqrt(
                (nodes.at(i).x_axis-nodes.at(j).x_axis)*(nodes.at(i).x_axis-nodes.at(j).x_axis)
               +(nodes.at(i).y_axis-nodes.at(j).y_axis)*(nodes.at(i).y_axis-nodes.at(j).y_axis));
            neighbor.push_back(temp);
        }
        std::vector<struct NeighborsNode> (neighbor).swap(neighbor); //释放多余的空间
        #ifdef MY_DEBUG
            std::cout<<"DEBUG "<<__FILE__<<"/"<<__LINE__<<":"<<"单个节点与邻居节点信息占用的空间 "<<neighbor.capacity()<<std::endl;
        #endif
        neighbor_node.push_back(neighbor);
    }
    std::vector<std::vector<struct NeighborsNode>> (neighbor_node).swap(neighbor_node); //释放多余的空间
    #ifdef MY_DEBUG
        std::cout<<"DEBUG "<<__FILE__<<"/"<<__LINE__<<":"<<"所有节点与邻居节点信息占用的空间 "<<neighbor_node.capacity()<<std::endl;
    #endif
    // 打印距离信息
    out<<std::endl<<std::endl<<"节点之间的距离"<<std::endl<<std::setw(4)<<" ";
    for(uint32_t j=0; j<node_number; j++){
        out<<std::setw(12)<<j;
    }
    out<<std::endl;
    for(uint32_t i=0;i<node_number;i++){ 
        out<<std::setw(4)<<i;
        for(uint32_t j=0;j<node_number;j++){
            out<<std::setw(12)<<neighbor_node[i][j].neighbor_distance;
        }
        out<<std::endl;
    }
    
    out<<std::endl<<std::endl;
    out.close();
    return EXIT_SUCCESS;
}

double SimulatorRun(double simulation_time){
    Node node[node_number];
    #ifdef MY_DEBUG
        std::cout<<"节点的坐标"<<std::endl;
    #endif
    std::vector<struct Packet> packet; //单个节点收到的数据包集合
    for(uint32_t i=0; i<node_number; i++){
        node[i].address_=nodes.at(i).address; //节点地址
        #ifdef MY_DEBUG
            std::cout<<nodes.at(i).address<<"\t"<<nodes.at(i).x_axis<<"\t"<<nodes.at(i).y_axis<<std::endl;
    	#endif
        rxpacketVector.push_back(packet);// 每个节点接收的数据包
        txpacketVector.push_back(packet);// 每个节点发送的数据包
    }
    std::vector<std::vector<struct Packet>> (rxpacketVector).swap(rxpacketVector);
    std::vector<std::vector<struct Packet>> (txpacketVector).swap(txpacketVector);

    #ifdef MY_DEBUG
        std::cout<<"DEBUG "<<__FILE__<<"/"<<__LINE__<<":"<<"所有节点接收的数据包集合占用的空间大小 "<<rxpacketVector.capacity()<<std::endl;
        std::cout<<"DEBUG "<<__FILE__<<"/"<<__LINE__<<":"<<"所有节点发送的数据包集合占用的空间大小 "<<txpacketVector.capacity()<<std::endl;
    #endif
    
    for(double bus_clock=time_unit; bus_clock < simulation_time ; bus_clock += time_unit){
        for(uint32_t i=0; i < node_number; i++){
            //rxpacketVector[i][j] 意为第i个节点，接收到的第j个数据包
            for( uint32_t j= node[i].sequence_ ; j < rxpacketVector[i].size() ; j++){
                if( bus_clock < rxpacketVector[i][j].rx_start){
                    break;
                }else if( bus_clock > rxpacketVector[i][j].rx_end){
                    break;
                }else{
                    switch (node[i].work_state_){
                        case IdleState:
                                if(rxpacketVector[i][j].to==i){
                                    // 接收自己的数据包，默认接收
                                    node[i].work_state_   =ReceiveState;
                                    node[i].SetAlarm(rxpacketVector[i][j].rx_end +sifs+Ack/transmission_rate,IdleState); //节点空闲状态，不会接收到发送到自己的ACK
                                }else{
                                    // 接收其它的数据包，默认导致冲突
                                    node[i].work_state_     =CollsionState;
                                    node[i].SetAlarm(rxpacketVector[i][j].rx_end,IdleState);
                                } 
                                node[i].receive_energy_+=receive_power*(rxpacketVector[i][j].rx_end-rxpacketVector[i][j].rx_start);
                                node[i].sequence_=j+1; //下一个处理的数据包序号
                                break;
                        case BackOffState:
                                if(rxpacketVector[i][j].to==i){
                                    // 接收自己的数据包，默认接收
                                    node[i].work_state_   =ReceiveState;
                                    node[i].SetAlarm(rxpacketVector[i][j].rx_end +sifs+Ack/transmission_rate,BackOffState);//节点退避状态，不会接收到发送到自己的ACK
                                }else{
                                    // 接收其它的数据包，默认导致冲突
                                    node[i].work_state_     =CollsionState;
                                    node[i].SetAlarm(rxpacketVector[i][j].rx_end,BackOffState);
                                } 
                                node[i].receive_energy_+=receive_power*(rxpacketVector[i][j].rx_end-rxpacketVector[i][j].rx_start);
                                node[i].sequence_=j+1;//下一个处理的数据包序号
                                break;
                        case ReceiveState:
                                if(rxpacketVector[i][j].rx_start >= rxpacketVector[i][j-1].rx_end){ 
                                    //成功接收之前的数据包，由于之后要回复ack，故之后的数据包都不能正确接收
                                    //为简化设计，我们这里规定发送ack的过程仍属于接收状态
                                    // rxpacketVector[i][j-1].state=Success; 考虑误码率和发送ack的时间
                                    if(rxpacketVector[i][j].to==i){
                                        rxpacketVector[i][j].state=Fail;  // 数据包接收失败(只记录发往接收节点的数据包是否成功接收)
                                    }
                                    // tips
                                    // 统计接收的能量消耗
                                }else{
                                    if(rxpacketVector[i][j].to==i){
                                        rxpacketVector[i][j-1].state=Fail;// 包接收失败(只记录发往接收节点的数据包是否成功接收)
                                        rxpacketVector[i][j].state=Fail; 
                                    }else{
                                        rxpacketVector[i][j-1].state=Fail; // 数据包接收失败(只记录发往接收节点的数据包是否成功接收)
                                    } 
                                    node[i].work_state_   =CollsionState;  // 冲突数据包不回复ack应答 
                                    node[i].receive_energy_+=receive_power*(rxpacketVector[i][j].rx_end-rxpacketVector[i][j-1].rx_end); 
                                }
                                node[i].SetAlarm(rxpacketVector[i][j].rx_end);
                                node[i].sequence_=j+1;
                                break;
                        case SendState:
                                break;
                        case CollsionState:
                                if(rxpacketVector[i][j].to==i){
                                    rxpacketVector[i][j].state=Fail; // 数据包接收失败(只记录发往接收节点的数据包是否成功接收)
                                }
                                node[i].work_state_   =CollsionState; //数据包冲突，不回复ack应答
                                node[i].SetAlarm(rxpacketVector[i][j].rx_end);
                                node[i].receive_energy_+=receive_power*(rxpacketVector[i][j].rx_end-rxpacketVector[i][j-1].rx_end);
                                node[i].sequence_=j+1;
                                break;
                        case WaitAck:
                                //发送数据包过程中，有数据包发送到当前节点，产生冲突（这里是处理发送状态下，接收到的数据包）
                                if(rxpacketVector[i][j].rx_start <= node[i].tx_packet.tx_end){ 
                                    if(rxpacketVector[i][j].to==i){
                                        rxpacketVector[i][j].state=Fail; // 数据包接收失败(只记录发往接收节点的数据包是否成功接收)
                                    }
                                    node[i].receive_energy_+=receive_power*(rxpacketVector[i][j].rx_end-node[i].tx_packet.tx_end);
                                    node[i].work_state_=CollsionState;
                                    node[i].SetAlarm(rxpacketVector[i][j].rx_end,WaitAck); 
                                }else{
                                    if(rxpacketVector[i][j].to==i){
                                        node[i].work_state_   =ReceiveState;
                                        node[i].SetAlarm(rxpacketVector[i][j].rx_end +sifs+Ack/transmission_rate,WaitAck);
                                    }else{
                                        node[i].work_state_   =CollsionState;
                                        node[i].SetAlarm(rxpacketVector[i][j].rx_end,WaitAck);
                                    }
                                    node[i].receive_energy_+=receive_power*(rxpacketVector[i][j].rx_end-rxpacketVector[i][j].rx_start);   
                                }    
                                node[i].sequence_=j+1;
                                break;
                        default:
                            break;
                    }                   
                }
            }
            node[i].Run(bus_clock);
        }
        printf("\rcurrent progress:%.2lf%%",bus_clock/simulation_time*100);
    }
        // extern double     energy_consumption;///< 总能耗
        // extern double     average_energy_consumption; ///< 能耗
        // extern double     average_delay;    ///< 平均时延
    for(uint32_t i=0; i< node_number; i++){
        total_packets+=node[i].send_counter_;
        packets+=node[i].packet_counter_;
        drop_packets+=node[i].drop_counter_;
        energy_consumption+=node[i].receive_energy_+node[i].send_energy_;
    }
    printf("Result:\n\t total_packets=%d packets=%d drop_packets=%d energy_consumption=\n",total_packets,packets,drop_packets,energy_consumption);
    packet_loss_rate=1.0*drop_packets/total_packets;//丢包率
    throughput=packets*Payload*1000.0/simulation_time;//总吞吐量
    char s[100];sprintf(s,"%d nodes of simulator.txt",node_number);
    std::ofstream out;
    out.setf(std::ios::fixed | std::ios::left);
    out.open(s, std::ios::app);
    if(out.is_open()){
        for(uint32_t i=0;i<node_number;i++){
            out<<std::endl<<"节点"<<i<<"收到的数据包"<<std::endl;
            out<<std::setw(20)<<"数据包ID"
             <<std::setw(24)<<"  源节点"
             <<std::setw(22)<<"目的节点"
             <<std::setw(22)<<"数据类型"
             <<std::setw(22)<<"接收状态"
             <<std::setw(24)<<"重传次数"
             <<std::setw(22)<<"传输时延"
             <<std::setw(24)<<"数据到达"
             <<std::setw(22)<<"传播开始"
             <<std::setw(24)<<"传播结束"
             <<std::setw(22)<<"接受开始"
             <<std::setw(22)<<"接收结束"
             <<std::setw(24)<<"传播时延"
             <<std::setw(20)<<"传播能量"<<std::endl;
            for(uint32_t j=0;j<rxpacketVector[i].size();j++){
               out<<std::setw(18)<<rxpacketVector[i][j].id
               <<std::setw(18)<<rxpacketVector[i][j].from
               <<std::setw(18)<<rxpacketVector[i][j].to
               <<std::setw(18)<<GetPacketType(rxpacketVector[i][j])
               <<std::setw(18)<<GetPacketState(rxpacketVector[i][j])
               <<std::setw(18)<<rxpacketVector[i][j].retransfer_number
               <<std::setw(18)<<rxpacketVector[i][j].transmission
               <<std::setw(18)<<rxpacketVector[i][j].arrive
               <<std::setw(18)<<rxpacketVector[i][j].tx_start
               <<std::setw(18)<<rxpacketVector[i][j].tx_end
               <<std::setw(18)<<rxpacketVector[i][j].rx_start
               <<std::setw(18)<<rxpacketVector[i][j].rx_end
               <<std::setw(18)<<rxpacketVector[i][j].delay
               <<std::setw(18)<<rxpacketVector[i][j].energy
               <<std::endl;
            }
            out<<std::endl<<"节点"<<i<<"发送的数据包"<<std::endl;
             out<<std::setw(20)<<"数据包ID"
             <<std::setw(24)<<"  源节点"
             <<std::setw(22)<<"目的节点"
             <<std::setw(22)<<"数据类型"
             <<std::setw(22)<<"发送状态"
             <<std::setw(24)<<"重传次数"
             <<std::setw(22)<<"传输时延"
             <<std::setw(24)<<"数据到达"
             <<std::setw(22)<<"传播开始"
             <<std::setw(24)<<"传播结束"
             <<std::setw(22)<<"接收开始"
             <<std::setw(22)<<"接收结束"
             <<std::setw(24)<<"传播时延"
             <<std::setw(20)<<"传播能量"<<std::endl;
            for(uint32_t j=0;j<txpacketVector[i].size();j++){
               out<<std::setw(18)<<txpacketVector[i][j].id
               <<std::setw(18)<<txpacketVector[i][j].from
               <<std::setw(18)<<txpacketVector[i][j].to
               <<std::setw(18)<<GetPacketType(txpacketVector[i][j])
               <<std::setw(18)<<GetPacketState(txpacketVector[i][j])
               <<std::setw(18)<<txpacketVector[i][j].retransfer_number
               <<std::setw(18)<<txpacketVector[i][j].transmission
               <<std::setw(18)<<txpacketVector[i][j].arrive
               <<std::setw(18)<<txpacketVector[i][j].tx_start
               <<std::setw(18)<<txpacketVector[i][j].tx_end
               <<std::setw(18)<<txpacketVector[i][j].rx_start
               <<std::setw(18)<<txpacketVector[i][j].rx_end
               <<std::setw(18)<<txpacketVector[i][j].delay
               <<std::setw(18)<<txpacketVector[i][j].energy
               <<std::endl;
            }
            out.flush();
        }  
        out.close();
    }
    return EXIT_SUCCESS;
}