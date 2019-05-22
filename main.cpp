/**
 * 
 * Copyright (c) 2019 南京航空航天大学 航空通信网络研究室
 * 
 * @file     d:\code\matlab\SimWiFi\DCF\CA\main.cpp
 * @author   詹长建 (2233930937@qq.com)
 * @date     2019-05
 * @brief    
 * @version  0.0.1
 * 
 * Last Modified:  2019-05-21
 * Modified By:    詹长建 (2233930937@qq.com)
 * 
 */
#include "run.h"
#include <iostream>
#include <fstream>
#include <getopt.h>       //命令行参数
#include <stdio.h>
#include <stdlib.h>       //某些结构体定义和宏定义，如EXIT_FAILURE、EXIT_SUCCESS 、atoi()函数
#include <stdarg.h>       //可变参数函数的宏的声明
#include <string.h>       //memset
#include <iomanip>

const char short_options[] = "n:m:t:r:s:a:p:e:j:l:u:d:S:D:h";
const struct option long_options[] = { 
    {"number", required_argument, NULL, 'n' },
    {"simulation", required_argument, NULL, 'm'},
    { "time" , required_argument, NULL, 't' },
    { "rate" , required_argument, NULL, 'r' },
    { "speed", required_argument, NULL, 's' },
    { "area" , required_argument, NULL, 'a' },
    { "power", required_argument, NULL, 'p' },
    { "error", required_argument, NULL, 'e' },
    {"jitter", required_argument, NULL, 'j' },
    { "lower", required_argument, NULL, 'l' },
    { "upper", required_argument, NULL, 'u' },
    { "delta", required_argument, NULL, 'd' },
    { "SIFS",  required_argument, NULL, 'S' },
    { "DIFS",  required_argument, NULL, 'D' },
    { "help" , no_argument,       NULL, 'h' }, 
    { 0, 0, 0, 0 } 
    };
void usage(FILE * fp, int argc, char ** argv) 
{
    fprintf(fp, "Usage: %s [options]\n\n"
        "Options:\n"
        "-n | --number     number of nodes\n"
        "-m | --simulation time of simulation\n"
        "-t | --time       time uint of simulation(second)\n"
        "-r | --rate       transmission rate\n"
        "-s | --speed      propagate speed\n"
        "-a | --area       propagate range\n"
        "-p | --power      propagate power\n"
        "-e | --error      propagate error\n"
        "-j | --jitter     propagate speed jitter\n"
        "-l | --lower      minimum of CW\n"
        "-u | --upper      maximum of CW\n"
        "-d | --delta      time unit of the mac \n"
        "-S | --SIFS       time of changing the state,transiting or receiving\n"
        "-D | --DIFS       waiting time  to judge the state of channel\n"
        "", argv[0]);
}

int main(int argc , char* argv[])
{ 
    // todo
    // 命令行添加
    // 接收功率
    // mac协议的各帧大小
    // 最大重发次数
    transmission_rate = 5000;    // 传输速率  5kb/s
    propagate_speed   = 1500;    // 传播速度  1500m/s
    propagate_range   = 500;     // 传播范围  500m
    propagate_power   = 10;      // 传播功率  10w
    receive_power     = 0.08;    // 接收功率  80mw
    propagate_error   = 0;       // 传播误码率
    propagate_speed_jitter=propagate_range/propagate_speed/29; //传速度变化

    Physical=16*8;  // 物理层头
    Mac=24*8;       // MAC头
    Payload=1024*8; // 数据负载
    Rts=20*8;       // RTS帧
    Cts=14*8;       // CTS帧
    Ack=14*8;       // 应答帧
    slot =0.2;      // 最小时隙单元
    sifs =0.1;      // 接收状态和发送状态的切换时间
    difs =0.2;      // 判断空闲的等待时间
    cw_min=31;      // 最小退避窗口
    cw_max=1023;    // 最大退避窗口 
    reTx_max=2;     // 最大重发次数
    
    node_number =10; // 仿真的节点个数
    simulation_time=600; // 仿真时间
    time_unit=0.001; // 仿真运行基本时间单元  1ms

    average_energy_consumption=0; // 能耗
    total_packets=0;    // 总的发包个数
    average_delay=0;    // 平均时延
    throughput=0;       // 吞吐量
    packet_loss_rate=0; // 丢包率
    
    for (;;) {
		int index;
		int c;
           /*
            *  
            * int getopt_long(int argc, char * const argv[],  const char *optstring, const struct option *longopts, int *longindex); 
            * 参数argc和argv从main()继承，
            * optsting：选项参数组成的字符串,包含下列元素:
            * 1.单个字符,表示选项,
            * 2.单个字符后接一个冒号:表示该选项后必须跟一个参数。参数紧跟在选项后或者以空格隔开,该参数的指针赋给optarg
            * 3.单个字符后跟两个冒号:表示该选项后可以有参数也可以没有参数。如果有参数,参数必须紧跟在选项后不能以空格隔开,该参数的指针赋给optarg
            * optstring是一个字符串,表示可以接受的参数。例如,"a:b:c:d:",表示可以接受的参数是a,b,c,d，其中，a和b参数后面跟有更多的参数值
            * (例如：-a host -b name)
            * longopts：其实是一个结构的实例：
            * struct option {
            * const char *name; //name表示的是长参数名
            * int has_arg; //has_arg有3个值，no_argument(或者是0)，表示该参数后面不跟参数值
            *              // required_argument(或者是1),表示该参数后面一定要跟个参数值
            *              // optional_argument(或者是2),表示该参数后面可以跟，也可以不跟参数值
            * int *flag;   //判断getopt_long()的返回值
            *              //flag为null,则函数会返回与该项option匹配的val值;
            *              //flag不是NULL,则将val值赋予flag所指向的内存,并且返回值设置为0
            * int val;     //和flag决定返回值
            * }
            * longindex:
            * longindex 非空,它指向的变量将记录当前找到参数符合longopts里的第几个元素的描述，即是longopts的下标值
           */
		c = getopt_long(argc, argv, short_options, long_options, &index);

		if (-1 == c) //跳出循环
			break;

		switch (c) {
		case 0: /* getopt_long() flag */
			break;
		case 'n':
            /*
                * 
                * atof()    将字符串转换为双精度浮点型值
                * atoi()    将字符串转换为整型值
                * atol()    将字符串转换为长整型值
                * strtod()  将字符串转换为双精度浮点型值，并报告不能被转换的所有剩余数字
                * strtol()  将字符串转换为长整值，并报告不能被转换的所有剩余数字
                * strtoul() 将字符串转换为无符号长整型值，并报告不能被转换的所有剩余数字
            */
            /*
                * 
                * itoa()   将整型值转换为字符串
                * ltoa()   将长整型值转换为字符串
                * ultoa()  将无符号长整型值转换为字符串
                * gcvt()   将浮点型数转换为字符串，取四舍五入
                * ecvt()   将双精度浮点型值转换为字符串，转换结果中不包含十进制小数点
                * fcvt()：指定位数为转换精度，其余同ecvt()
            */
            node_number=atol(optarg);
			break;
		case 'm':
            simulation_time=atof(optarg);
			break;
		case 't':
            time_unit=atof(optarg);
			break;
		case 'r':
            transmission_rate=atof(optarg);
			break;
		case 's':
            propagate_speed=atof(optarg);
			break;
	    case 'a':
            propagate_range=atof(optarg);
            break;
        case 'p':
            propagate_power=atof(optarg);
            break;
        case 'e':
            propagate_error=atof(optarg);
            break;
        case 'j':
            propagate_speed_jitter=atof(optarg);
            break;
        case 'l':
            cw_min=atol(optarg); 
            break;
        case 'u': 
            cw_max=atol(optarg); 
            break;
        case 'd':
            slot =atof(optarg);
            break;
        case 'S': 
            sifs =atof(optarg);
            break;
        case 'D':
            difs =atof(optarg);
            break;
        case 'h':
            usage(stderr,argc,argv);
            break;
		default:
		    usage(stderr,argc,argv);
			break;
		}
	}

    
    CreateNodes();
    for(uint32_t i=0;i<1;i++)
    {
        SimulatorRun(simulation_time);
    }
    
    //todo
    //仿真结束 添加吞吐量、丢包率、能耗(发包*发包个数)、仿真时间到文件"%d个节点配置.txt"

    char s[100];sprintf(s,"%d nodes of simulator.txt",node_number);
    std::ofstream out;
    out.setf(std::ios::fixed | std::ios::left);
    out.open(s, std::ios::app);
    if(out.is_open()){
        out<<"仿真结果"<<std::endl<<std::endl;
        out<<std::setw(18)<<"仿真时间"<<std::setw(18)<<"吞吐量"<<std::setw(18)<<"丢包率"<<std::setw(18)<<"能耗"<<std::endl;
        out<<std::setw(13)<<simulation_time
        <<std::setw(15)<<std::setprecision(2)/* 保留两位小数*/<<throughput
        <<std::setw(14)<<std::setprecision(2)<<packet_loss_rate
        <<std::setw(14)<<std::setprecision(2)<<average_energy_consumption;
        out.close();
    }
	return EXIT_SUCCESS;
}