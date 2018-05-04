#ifndef KERNELASSEMBLY_H
#define KERNELASSEMBLY_H
#include "CarbonDefine.h"
#include "Descriptor.h"
#define atomic(x) ({ asm volatile (x); })
uint8_t inb(uint32_t port);
uint16_t inw(uint32_t port);
uint32_t intdw(uint32_t port);
void outb(uint32_t port, uint8_t data);
void outw(uint32_t port, uint16_t data);
void outdw(uint32_t port, uint32_t data);
void cli();
void sti();
void hlt();
void sti_hlt();
uint32_t get_eflags();
void set_eflags(uint32_t eflages);
void set_ss(uint16_t data);
void set_ds(uint16_t data);
void set_es(uint16_t data);
void set_fs(uint16_t data);
void set_gs(uint16_t data);
uint16_t get_cs();
uint16_t get_ds();
uint16_t get_ss();
uint16_t get_es();
uint16_t get_fs();
uint16_t get_gs();


/* 一些函数的汇编宏实现 */

///压栈状态
#define push_reg()    \
    asm(            \
        "pushad;"    \
        "push ds;"    \
        "push es;"    \
        "push fs;"    \
        "push gs;"    \
        "pushf;"    \
    )


///出栈状态
#define pop_reg()    \
    asm(            \
        "popf;"        \
        "pop gs;"    \
        "pop fs;"    \
        "pop es;"    \
        "pop ds;"    \
        "popad;"    \
    )


/*位操作*/

///获取一位的值
#define bit(n, nb) (((n) & (1 << (nb))) != 0)

///设置一位=1
#define setb(n, nb) ((n) |= (1 << (nb)))

///设置一位=0
#define clrb(n, nb) ((n)&= ~(1<<(nb)))


/*一些底层宏定义*/

//将段号（0~2047）变成段选择符号
#define gknlseg(n) (uint32_t)(((n) << 3) + 0b000)
#define gusrseg(n) (uint32_t)(((n) << 3) + 0x011)

#define lknlseg(n) (uint32_t)(((n) << 3) + 0b100)
#define lusrseg(n) (uint32_t)(((n) << 3) + 0b111)

#define KNL_PROGRAM_SEG gknlseg(1)
#define KNL_DATA_SEG gknlseg(2)

///关闭中断和IRQ
#define close_int() //u16 irq_stat = stop_all_irq();


///开启中断和IRQ（必须先close_int）
///@todo start_int 会死机!!
#define start_int() //restore_irq(irq_stat);

#endif // KERNELASSEMBLY_H