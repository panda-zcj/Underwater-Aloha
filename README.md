# Underwater-Aloha

```flow
st=>start: 水下节点仿真
e=>end: 结束
op1=>operation: 创建并初始化水下节点
op2=>operation: 主时间轴，设定仿真时间
op3=>operation: 当前计算单元，根据信道状态计算节点的状态
并统计发送节点的个数
cond11=>condition: 发送节点个数是否为空
cond12=>condition: 信道是否忙碌
cond13=>condition: 节点的工作状态是空闲状态
cond21=>condition: 发送节点个数是否大于1
cond22=>condition: 信道是否空闲
op23=>operation: 计算出当前计算单元，哪个节点发送数据，
并在记录在当前发送节点表中，设置信道忙，
也设置节点工作状态为冲突状态，退避窗口扩大二倍
cond31=>condition: 信道是否空闲
op32=>operation: 计算出当前计算单元，
哪个节点发送数据，
并在记录在当前发送节点表中，
设置信道忙,


<!-- op4=>operation: 当前计算单元，根据信道状态计算节点的状态
根据节点的工作状态，计算信道状态 -->

<!-- io=>inputoutput: catch something...
para=>parallel: parallel tasks
sub1=>subroutine: My Subroutine -->

st->op1->op2->op3->cond11
cond11(no)->cond12
cond11(yes)->cond21
cond12(yes)->cond13
cond21(yes)->cond22
cond21(no)->cond31
cond22(yes)->op23
cond31(yes)->op32

<!-- ->cond1 -->
<!-- cond1(yes)->io->e
cond1(no)->para
para(path1, bottom)->sub1(right)->op1
para(path2, top)->op1 -->
```

