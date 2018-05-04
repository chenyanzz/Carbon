#ifndef GLOBALDESCRIPTOR_H
#define GLOBALDESCRIPTOR_H
#include "Bootloader.h"
#include "CarbonDefine.h"
#include "Descriptor.h"
#define GDT_COUNT 8192
typedef struct __descriptor_manager__ {
    Descriptor *desc;
    int count;
} DescriptorManager;
typedef struct __gdt__ {
    Descriptor desc[GDT_COUNT];
} GDT;
void ModifyDescriptor(Descriptor *desc, uint32_t limit, uint32_t base, uint32_t attr);
uint32_t GetGDTBase(int index);
uint32_t GetGDTLimit(int index);
uint32_t GetGDTAttribute(int index);
void SetGDT(int index, uint32_t size, uint32_t base, uint32_t attr);
void InitGDT(uint32_t address);
#endif // GLOBALDESCRIPTOR_H
