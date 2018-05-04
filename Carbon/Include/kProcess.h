#pragma once

#include "stddef.h"

#define MAX_PROCESSES 1000

extern int count_processes;///<存在的进程计数

struct PCB //process control block : 进程控制块
{
    id_t id;//从1开始，0表示无效

    //栈指针
    uint16_t ss;
    uint32_t esp;

    char name[31];

    bool isWaiting : 1;
    bool isEnd : 1;
    bool isPresent : 1;
};

///task state segment 任务状态段
struct TSS {

    ///上一个TSS的链接
    uint16_t back_link, RESERVED_1;

    /*堆栈指针*/
    uint32_t esp0;
    uint16_t ss0, RESERVED_2; ///< 0级堆栈指针，即Linux中的内核级
    uint32_t esp1;
    uint16_t ss1, RESERVED_3; ///< 1级堆栈指针，未用
    uint32_t esp2;
    uint16_t ss2, RESERVED_4; ///< 2级堆栈指针，未用

    /*特殊功能寄存器*/
    uint32_t cr3;
    uint32_t eip;
    uint32_t eflags;

    /*各种通用寄存器*/
    uint32_t eax, ecx, edx, ebx;
    uint32_t esp;
    uint32_t ebp;
    uint32_t esi;
    uint32_t edi;

    /*段寄存器*/
    uint16_t es, RESERVED_5;
    uint16_t cs, RESERVED_6;
    uint16_t ss, RESERVED_7;
    uint16_t ds, RESERVED_8;
    uint16_t fs, RESERVED_9;
    uint16_t gs, RESERVED_10;
    uint16_t ldt, RESERVED_11;

    bool isDebug:1;///<如果为1，则切换到这个task时会进入调试中断

    unsigned RESERVED_12:15;

    uint16_t IOMapBaseAddr;///<什么玩意
};

/**
 * 初始化进程
 */
bool init_process();

/**
 * 切换到指定进程
 * @param ppcb 新进程的PCB指针
 */
void switch_to(PCB *ppcb);

typedef void (*PROCESS_MAIN_PROC)();

/**
 * 创建进程
 * @param proc 新进程的主函数
 * @param name 进程名称，最大31字符
 * @param bWait 是否等待唤醒
 *          默认为false，立即进入可调度状态
 * @return 新进程的id

 */
id_t create_process(PROCESS_MAIN_PROC proc, char *name, bool bWait = false);

/**
 * 退出当前进程的函数
 * @param retCode 返回值
 */
void exit(int retCode = 0);

/**
 * 切换一次进程
 * 改变current指针
 * 如果没有可用进程则直接返回
 * @tip： 现在使用的是最简单的FIFO调度
 */
void schedule();

/**
 * 寻找isPresent=false的PCB并返回指针
 * @retval nullptr 如果没有空PCB
 */
PCB *findNewPCB();

/**
 * 将current进程删除
 * 再进程退出时被自动调用
 */
void deleteCurrentProcess();

/**
 * 根据id寻找PCB
 * @retval nullptr 未找到
 */
PCB *findPCBById(id_t id);

/**
 * 使当前进程睡眠，等待唤醒
 */
void sleep();

/**
 * 唤醒某进程
 */
void wake(id_t thread_id);

