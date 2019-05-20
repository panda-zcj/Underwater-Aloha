/**
 * 
 * Copyright (c) 2019 南京航空航天大学 航空通信网络研究室
 * 
 * @file     d:\code\matlab\Underwater Aloha\mac.h
 * @author   詹长建 (2233930937@qq.com)
 * @date     2019-05
 * @brief    
 * @version  0.0.1
 * 
 * Last Modified:  2019-05-20
 * Modified By:    詹长建 (2233930937@qq.com)
 * 
 */
#ifndef MAC_H
#define MAC_H

#include <stdint.h>

// 定义水声MAC协议属性

#if 0
/**
 * @brief 数据在物理层的格式
 * 
 */
struct FrameFormat
{
    uint32_t  physical; ///< 物理层头
    uint32_t  mac;      ///< MAC头
    uint32_t  payload;  ///< 数据负载
    uint32_t  ack;      ///< 应答帧
    FrameFormat():
        physical(208),
        mac(224),
        payload(1500*8),
        ack(physical+112){
        //todo
    }
};
#else
const uint32_t  Physical=16*8;    ///< 物理层头
const uint32_t  Mac=24*8;         ///< MAC头
const uint32_t  Payload=1500*8;   ///< 数据负载
const uint32_t  Rts=20*8;         ///< RTS帧
const uint32_t  Cts=14*8;         ///< CTS帧
const uint32_t  Ack=14*8;         ///< 应答帧
#endif

extern double     slot;   ///< 最小时隙单元
extern double     sifs;   ///< 接收状态和发送状态的切换时间
extern double     difs;   ///< 判断空闲的等待时间
extern uint32_t   cw_min; ///< 最小退避窗口
extern uint32_t   cw_max; ///< 最大退避窗口

#endif //MAC_H