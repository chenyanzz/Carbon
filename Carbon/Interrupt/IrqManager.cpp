#include <PIT_timer.h>
#include <RTC_timer.h>
#include <keyboard.h>
#include "IrqManager.h"
#include "asm.h"
#include "IntPreProcess.h"

#define IRQ(n) (0x20 + (n))


#define P_PIC_MASTER (0x21)///< 控制是否接受某中断
#define P_PIC_SLAVE (0xA1)///< 控制是否接受某中断

#define P_PIC_MASTER_COMMAND    (0x20)
#define P_PIC_SLAVE_COMMAND    (0xA0)

#define PIC_EOI        0x20        /* End-of-interrupt command code */

void setup_irq() {
    stop_all_irq();

//	SetIDT(IRQ(APIC_TIMER_IRQ),deal_irq_0, KNL_PROGRAM_SEG,0,IDT_DESC_ATTR_DPL0);//ACPI时钟


    init_PIT_timer();
    SetIDT(IRQ(PIT_TIMER_IRQ), deal_irq_0, KNL_PROGRAM_SEG,0,IDT_DESC_ATTR_DPL0);//PIT时钟

    init_RTC_timer();
    SetIDT(IRQ(RTC_TIMER_IRQ), deal_irq_8, KNL_PROGRAM_SEG,0,IDT_DESC_ATTR_DPL0);//RTC实时时钟

    init_keyboard();
    SetIDT(IRQ(KEYBOARD_IRQ), deal_irq_1, KNL_PROGRAM_SEG,0,IDT_DESC_ATTR_DPL0);//键盘
}

uint16_t start_irq(uint8_t index) {
    uint8_t oldst_m = inb(P_PIC_MASTER);
    uint8_t oldst_s = inb(P_PIC_SLAVE);
    if (index < 8) {
        uint8_t st = oldst_m;
        clrb(st, index);
        outb(P_PIC_MASTER, st);
    } else {
        uint8_t st = oldst_s;
        clrb(st, index - 8);
        outb(P_PIC_SLAVE, st);
    }

    return (oldst_m << 8) + oldst_s;

}

uint16_t stop_irq(uint8_t index) {
    uint8_t oldst_m = inb(P_PIC_MASTER);
    uint8_t oldst_s = inb(P_PIC_SLAVE);
    if (index < 8) {
        uint8_t st = oldst_m;
        setb(st, index);
        outb(P_PIC_MASTER, st);
    } else {
        uint8_t st = oldst_s;
        setb(st, index - 8);
        outb(P_PIC_SLAVE, st);
    }

    return (oldst_m << 8) + oldst_s;
}

uint16_t stop_all_irq() {
    uint8_t oldst_m = inb(P_PIC_MASTER);
    uint8_t oldst_s = inb(P_PIC_SLAVE);
    outb(P_PIC_MASTER, 0b11111011);
    outb(P_PIC_SLAVE, 0b11111111);
    return (oldst_m << 8) + oldst_s;
}

uint16_t restore_irq(uint16_t mode) {

    uint8_t oldst_m = inb(P_PIC_MASTER);
    uint8_t oldst_s = inb(P_PIC_SLAVE);
    outb(P_PIC_MASTER, (uint8_t) mode >> 8);
    outb(P_PIC_SLAVE, (uint8_t) mode);
    return (oldst_m << 8) + oldst_s;
}

void accept_new_irq(int irq) {
    if(irq>=8) {
        outb(P_PIC_SLAVE_COMMAND, PIC_EOI);
    }
    outb(P_PIC_MASTER_COMMAND, PIC_EOI);
}

uint16_t start_all_irq() {
    uint8_t oldst_m = inb(P_PIC_MASTER);
    uint8_t oldst_s = inb(P_PIC_SLAVE);

    start_irq(SLAVE_IRQ);
    start_irq(KEYBOARD_IRQ);
    start_irq(PIT_TIMER_IRQ);
    start_irq(RTC_TIMER_IRQ);


    return ((oldst_m << 8)) + oldst_s;
}