/**
 * 
 * Copyright (c) 2019 南京航空航天大学 航空通信网络研究室
 * 
 * @file     d:\code\matlab\Underwater Aloha\demo.cpp
 * @author   詹长建 (2233930937@qq.com)
 * @date     2019-05
 * @brief    
 * @version  0.0.1
 * 
 * Last Modified:  2019-05-22
 * Modified By:    詹长建 (2233930937@qq.com)
 * 
 */
#include <vector>
#include <iostream>
#include <algorithm>
#include <time.h>
#include <stdio.h>

struct demo
{
    int    a;
    char   b;
    double c;
};

bool AscendingOrder(const struct demo &a,const struct demo &b){
    return a.a < b.a;
}
int main(int argc,char** argv){
    struct demo d;
    std::vector<struct demo> vec;
    srand((unsigned int)time(NULL));
    for(int i=0 ; i<10;i++){
        d.a=rand()%100;
        d.b=48+rand()%10;
        vec.push_back(d);
        std::sort(vec.begin(),vec.end(),AscendingOrder);
        for(int j=0 ; j< vec.size() ; j++){
            std::cout<<vec.at(j).a<<"("<<vec.at(j).b<<")"<<"\t";
        }
        std::cout<<std::endl; 
    }

    double e=1,f;
    for (size_t i = 0; i < 8; i++)
    {
        e=e/10;
        f=1+e;
        std::cout<<f<<std::endl;
        if(f==1){
            std::cout<<f<<"=1"<<std::endl;
            break;
        }
    }
    
    return 0;
}