// Copyright (c) 2024. All rights reserved.
// This source code is licensed under the CC BY-NC-SA
// (Creative Commons Attribution-NonCommercial-NoDerivatives) License, By Xiao Songtao.
// This software is protected by copyright law. Reproduction, distribution, or use for commercial
// purposes is prohibited without the author's permission. If you have any questions or require
// permission, please contact the author: 2207150234@st.sziit.edu.cn

/*****************************************************
 * @File name: C
 * @Author: edocsitahw
 * @Version: 1.1
 * @Date: 2024/05/29 下午3:31
 * @Commend:
 *******************************************************/

/**
 命令行中加入-omp选项，编译器会自动添加omp.h头文件，并将omp关键字识别为OpenMP关键字。
 #pragma omp 指导语句名 [子句, ...] 换行符
 子句:
     atomic: 定义一个必须被原子更新的内存区域
     barrier: 同步所有线程，直到所有线程都到达该语句
     critical: 定义一个临界区，同一时刻只能有一个线程执行
     flush: 同步指导语句,确保并行区域中的所有线程对内存中指定的对象有相同的取值
     for: 标明for循环中的迭代需要使用多个线程并行执行
     parallel: 定义一个由多个线程执行的并行代码区域,原线程成为主线程
     parallel do: 将循环迭代分配到多个线程
     parallel for: 类似于parallel do,但循环迭代的范围由用户指定

 编译指导语句:        子句:
     Parallel:
         Copying:
         default:
         firstprivate:
         private:
         shared:
         reduction:
     Section:
         firstprivate:
         Private:
         reduction:
         schedule:
         lastprivate:
     Sections:
         firstprivate:
         lastprivate:
         reduction:
         private:
     Critical:
         - 无
     Berrier:
         - 无
     Atomic:
         - 无
     Flush(List):
         - 无
     Ordered:
         - 无
     Threadadaptive:
         - 无

 default(模式): 控制变量默认的共享属性。模式可以是private,shared和none。
 shared(列表): 在parallel或者task编译指导语句产生的线程共享的列表条目,例如: #pragma omp parallel default(shared)
 copyin(列表): 将列表中列出的变量的值从主线程复制到工作线程
 num_threads(整数表达式): 设定线程数量

*/


/** CUDA C 语言拓展

 global void function(...): 定义在设备上运行的内核函数
 device int var: 存储在设备全局内存的变量
 shared int var: 存储在块共享内存中的变量
 local int var: 存储在块共享内存中的变量,只能在线程内使用
 constant int const: 存储在常数存储器中的常数

*/

/** 信号同步机制
	
	在多线程编程中，信号同步机制是用于协调和控制多个线程之间的执行顺序，以确保它们正确地访问和修改共享资源，从而避免数据竞争和不一致的状态。以下是多线程中常用的信号同步机制:
		
		1. **互斥锁(Mutex)**:
	- 互斥锁是最常用的同步机制之一，用于保护对共享资源的访问。当一个线程获取了互斥锁时，其他尝试获取该锁的线程将被阻塞，直到锁被释放。
	- 常见的互斥锁实现包括标准库中的`pthread_mutex_t`(POSIX线程)和`std::mutex`(C++11及以后版本)。

		2. **条件变量(Condition Variable)**:
	- 条件变量通常与互斥锁一起使用，用于允许线程等待某个条件成立。一个线程可以在条件变量上等待，直到另一个线程发出信号表明条件已经满足。
	- 条件变量在多线程编程中常用于实现生产者-消费者问题、线程池等场景。
	- 常见的条件变量实现包括`pthread_cond_t`(POSIX线程)和`std::condition_variable`(C++11及以后版本)。

		3. **读写锁(Read-Write Lock)**:
	- 读写锁允许多个线程同时读取共享资源，但只允许一个线程写入。这提高了读取操作的并发性，同时保证了写入操作的原子性。
	- 读写锁在实现读多写少的场景中特别有用。
	- 常见的读写锁实现包括`pthread_rwlock_t`(POSIX线程)和`std::shared_mutex`(C++17及以后版本)。

		4. **信号量(Semaphore)**:
	- 信号量是一个非负整数计数器，用于控制对共享资源的访问。线程可以通过增加或减少信号量的值来协调执行。
	- 信号量常用于实现资源池、限制并发访问数量等场景。
	- 常见的信号量实现包括`sem_t`(POSIX线程)和`std::counting_semaphore`(C++20及以后版本)。

		5. **栅栏(Barrier)**:
	- 栅栏是一种同步原语，它允许一组线程互相等待，直到所有线程都到达某个点。一旦所有线程都到达栅栏，它们可以继续执行。
	- 栅栏在实现并行算法、并行任务分割等场景中很有用。
	- 常见的栅栏实现包括`pthread_barrier_t`(POSIX线程)和`std::barrier`(C++20及以后版本)。

		6. **自旋锁(Spinlock)**:
	- 自旋锁是一种特殊的互斥锁，当线程尝试获取锁而失败时，它会在一个循环中持续尝试获取锁，而不是被阻塞或进入睡眠状态。
	- 自旋锁适用于锁持有时间非常短的场景，因为频繁地阻塞和唤醒线程会带来较大的开销。
	- 需要注意的是，自旋锁可能会导致CPU的忙等待，从而浪费计算资源。

		7. **事件(Event)**:
	- 事件是一种同步机制，允许一个线程向其他线程发送通知。当某个事件被触发时，等待该事件的线程可以继续执行。
	- 事件在实现异步编程、多线程通信等场景中很有用。
	- 不同的编程语言和库可能有不同的事件实现方式。

		在使用这些信号同步机制时，需要注意避免死锁、活锁和饥饿等问题。此外，还需要根据具体的应用场景和性能要求来选择合适的同步机制。

*/
