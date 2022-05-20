# Process scheduler

## 目标
向系统中添加多个进程，并且通过时钟中断运行调度程序，让多个进程交替运行
### 描述进程的数据结构
1. task_struct
描述进程的数据结构，其中包括对内存的描述，对上下文的描述
2. cpu_context
描述进程在运行时的上下文，包括calle-saved寄存器（x19-x28），栈指针（x29），链接地址（fp，x30，pc)，栈指针寄存器（sp）
### 增加进程复制（fork）功能,向系统中添加线程的功能
1. 对系统中所有线程的管理
2. 对每个线程的栈内存的管理
3. fork功能的实现
    + 创建一个进程
    + 创建线程的标识符
    + 使创建的线程在退出时跳转到目标的函数执行
### 上下文切换
1. 保存当前线程的上下文
2. 恢复指定线程的上下文
3. 切换到指定线程的上下文
### 抢占功能的实现
1. 抢占计数器
2. 抢占点
3. 抢占规则
### 实现基础调度器，在时钟中断获得处理器控制权时，根据一定规则选择下一个运行的进程
1. 调度算法
2. 调度点

## 文件结构
* include
    * fork.h    
    fork函数原型
    * sched.h   
    进程描述数据结构定义（task_struct,cpu_context），调度函数原型(schedule)，抢占开关函数原型(preempt_enable/disable)，抢占点函数原型（timer_tick），进程切换函数原型(switch_to)，上下文切换函数原型(cpu_switch_to)，
    * mm.h  
    线程栈空间分配(get_free_page)，释放函数原型(free_page)
    * entry.h   
    上下文切换中，切换对应线程函数原型(ret_from_fork)
* src
    * entry.S   
    
    * fork.c
    * kernel.c
    * mm.c
    * sched.c
    * sched.S
    * timer.c
## 实现
### 进程描述符
### fork
### 上下文切换
### 抢占
### 核心调度算法（scheudle function）
