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
 * Last Modified:  2019-05-20
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
    <<std::setw(24)<<"节点传播误码率"<<std::endl;
    out<<std::setw(17)<<node_number
    <<std::setw(17)<<propagate_range
    <<std::setw(17)<<transmission_rate
    <<std::setw(17)<<propagate_speed
    <<std::setw(17)<<propagate_power
    <<std::setw(17)<<propagate_error<<std::endl;

    out<<std::endl<<std::endl<<"节点传输负载大小"<<std::endl;
    out<<Payload<<std::endl;
    
    out<<std::endl<<std::endl<<"节点的位置坐标"<<std::endl
    <<std::setw(19)<<"节点ID"
    <<std::setw(23)<<"节点X轴坐标"
    <<std::setw(24)<<"节点Y轴坐标"<<std::endl;
    
    srand((uint32_t)time(NULL)); 
    for(uint32_t i=0; i < node_number; i++){
        for (; ;)
        {
            x=ulrand()%(uint32_t)(propagate_range*2);
            y=ulrand()%(uint32_t)(propagate_range*2);
            if(
                (x-propagate_range)*(x-propagate_range)
               +(y-propagate_range)*(y-propagate_range)
               < propagate_range*propagate_range
                ){
                break;
            }       
        }
        nodes[i].address=i;
        nodes[i].x_axis=x;
        nodes[i].y_axis=y;
        out<<std::setw(17)<<i<<std::setw(17)<<x<<std::setw(17)<<y<<std::endl;
    }
    
    out<<std::endl<<std::endl<<"节点之间的距离"<<std::endl<<std::setw(4)<<" ";
    for(uint32_t i=0;i<node_number;i++){
        out<<std::setw(12)<<i;
    }
    out<<std::endl;
    for(uint32_t i=0;i<node_number;i++){ 
        out<<std::setw(4)<<i;
        for(uint32_t j=0;j<node_number;j++){
            neighbor_node[i][j].neighbor_address=i;
            neighbor_node[i][j].neighbor_distance=sqrt(
                (nodes[i].x_axis-nodes[j].x_axis)*(nodes[i].x_axis-nodes[j].x_axis)
               +(nodes[i].y_axis-nodes[j].y_axis)*(nodes[i].y_axis-nodes[j].y_axis));
            neighbor_node[i][j].neighbor_position.x_axis=nodes[j].x_axis;
            neighbor_node[i][j].neighbor_position.y_axis=nodes[j].y_axis;
            out<<std::setw(12)<<neighbor_node[i][j].neighbor_distance;
        }
        out<<std::endl;
    }
    out<<std::endl<<std::endl;
    out.close();
   
    return EXIT_SUCCESS;
}

double SimulatorRun(uint32_t simulation_time){
    Node node[node_number];
    for(uint32_t i=0;i<node_number;i++){
        node[i].address_=nodes[i].address;         //节点地址
        node[i].position_.address=nodes[i].address;//节点坐标
        node[i].position_.x_axis=nodes[i].x_axis; 
        node[i].position_.y_axis=nodes[i].y_axis;
        std::cout<<nodes[i].address<<"\t"<<nodes[i].x_axis<<"\t"<<nodes[i].y_axis<<std::endl;
    }

    //todo
    //运行仿真
    return EXIT_SUCCESS;
}