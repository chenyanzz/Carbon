#ifndef INTERRUPTSERVICE_H
#define INTERRUPTSERVICE_H
#include "Gate.h"
#include "CarbonDefine.h"
#include "InterruptController.h"
#define INTERRUPT_GATE_COUNT 255
#define	IDT_DESC_P 1
#define	IDT_DESC_DPL0 0
#define	IDT_DESC_DPL3 3
#define	IDT_DESC_32_TYPE 0xE
#define	IDT_DESC_16_TYPE 0x6
#define	IDT_DESC_ATTR_DPL0 ((IDT_DESC_P << 7) + (IDT_DESC_DPL0 << 5) + IDT_DESC_32_TYPE)
#define	IDT_DESC_ATTR_DPL3 ((IDT_DESC_P << 7) + (IDT_DESC_DPL3 << 5) + IDT_DESC_32_TYPE)
typedef struct __interrupt_manager__ {
    Gate *g;
    int count;
} InterruptManager;
typedef struct __idt__ { Gate idt[INTERRUPT_GATE_COUNT]; } IDT;
typedef void(*intr_hander)();
void divide_error();
void single_step_exception();
void nmi();
void breakpoint_exception();
void overflow();
void bounds_check();
void inval_opcode();
void copr_not_available();
void double_fault();
void copr_seg_overrun();
void inval_tss();
void segment_not_present();
void stack_exception();
void general_protection();
void page_fault();
void copr_error();
void hwint00();
void hwint01();
void hwint02();
void hwint03();
void hwint04();
void hwint05();
void hwint06();
void hwint07();
void hwint08();
void hwint09();
void hwint10();
void hwint11();
void hwint12();
void hwint13();
void hwint14();
void hwint15();
void exception_handler(int vec_no, int err_code, int eip, int cs, int eflags);
void spurious_irq(int irq);
void keyboard_handler(int irq);
void interrupt_handler();
void ModifyGate(Gate *g, uint32_t offset, uint16_t selector, uint8_t dcount, uint8_t attr);
void SetIDT(int index, intr_hander function, uint16_t selector, uint8_t dcount, uint8_t attr);
void InitIDT();
void ShowIDTTable(int begin, int end);
#endif // INTERRUPTSERVICE_H