学会使用消息队列这种进程间通信方式
实验要求：创建一消息队列，实现向队列中存放数据与读取数据
先运行msg1，在没有运行msg2向消息队列中添加消息时，msg1会阻塞在msgrcv函数上，直到添加的消息为“end”，程序结束。
