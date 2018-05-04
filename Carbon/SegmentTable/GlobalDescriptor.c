#include "../Include/GlobalDescriptor.h"
#include "../Include/KernelAssembly.h"
#include "../Include/CarbonDefine.h"
GDT *gdt;
void ModifyDescriptor(Descriptor *desc, uint32_t limit, uint32_t base, uint32_t attr) {
    desc->limit1 = limit & 0xFFFF;
    desc->base1 = base & 0xFFFF;
    desc->base2 = base >> 16 & 0xFF;
    desc->attrandlimit2 = (limit >> 8 & 0x0F00) | (attr & 0xF0FF);
    desc->base3 = base >> 24 & 0xFF;
}
uint32_t GetGDTBase(int index) {
    uint64_t gdt_operand = 0;
    atomic("sgdt %0":"=m"(gdt_operand));
    uint32_t tmppp = (uint32_t)(gdt_operand >> 16);
    Descriptor *tmp = (Descriptor *)tmppp;
    tmp = tmp + index;
    return (tmp->base3 << 24) | (tmp->base2 << 16) | tmp->base1;
}
uint32_t GetGDTLimit(int index) {
    uint64_t gdt_operand = 0;
    atomic("sgdt %0":"=m"(gdt_operand));
    uint32_t tmppp = (uint32_t)(gdt_operand >> 16);
    Descriptor *tmp = (Descriptor *)tmppp;
    tmp = tmp + index;
    return ((tmp->attrandlimit2 & 0x0F00) << 8) | tmp->limit1;
}
uint32_t GetGDTAttribute(int index) {
    uint64_t gdt_operand = 0;
    atomic("sgdt %0":"=m"(gdt_operand));
    uint32_t tmppp = (uint32_t)(gdt_operand >> 16);
    Descriptor *tmp = (Descriptor *)tmppp;
    tmp = tmp + index;
    return tmp->attrandlimit2 & 0xF0FF;
}
void SetGDT(int index, uint32_t size, uint32_t base, uint32_t attr) {
    Descriptor *tmp;
    tmp = (Descriptor *)gdt;
    tmp = tmp + index;
    ModifyDescriptor(tmp, size, base, attr);
}
void InitGDT(uint32_t address) {
    gdt = (GDT *)address;
    int i = 0;
    for (; i < GDT_COUNT; i++) { SetGDT(i, 0x0, 0x0, 0); }
    int d_tmp;
    d_tmp = get_cs() >> 3;
    SetGDT(d_tmp, GetGDTLimit(d_tmp), GetGDTBase(d_tmp), GetGDTAttribute(d_tmp));
    d_tmp = get_ds() >> 3;
    SetGDT(d_tmp, GetGDTLimit(d_tmp), GetGDTBase(d_tmp), GetGDTAttribute(d_tmp));
    uint32_t tmp = (uint32_t)gdt;
    uint64_t gdt_operand = ((sizeof(GDT) - 1) | ((uint64_t)tmp << 16));
    atomic("lgdt %0"::"m"(gdt_operand));
}