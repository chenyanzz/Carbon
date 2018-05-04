#include <kProcess.h>
#include <time.h>
#include "../Include/Assert.h"
#include "../Include/Bootloader.h"
#include "../Include/CarbonDefine.h"
#include "../Include/CarbonELFDescriptor.h"
#include "../Include/CarbonKernelIO.h"
#include "../Include/CarbonStdArg.h"
#include "../Include/Descriptor.h"
#include "../Include/Gate.h"
#include "../Include/GlobalDescriptor.h"
#include "../Include/InterruptController.h"
#include "../Include/InterruptService.h"
#include "../Include/KernelAssembly.h"
#include "../Include/String.h"
int memory_size;
extern Multiboot *multiboot_ptr;
extern uint32_t kernel_start[];
extern uint32_t kernel_end[];
GDT gdt_table = { 0 };
Multiboot *global_multiboot_ptr = (void *)0;
void KernelEntry() {
    global_multiboot_ptr = multiboot_ptr;
    memory_size = global_multiboot_ptr->mem_upper * 1024;
    KernelMain();
}
void KernelMain() {
    InitDebug();
    cls();
    printk("Kernel is running...\n");
    printk("In the memory:\n");
    printk("Kernel in memory start: 0x%08X\n", kernel_start);
    printk("Kernel in memory end: 0x%08X\n", kernel_end);
    printk("Kernel in memory used: %d KB\n\n", (kernel_end - kernel_start) / 1024);
    // init_memory_manager(memory_size,(uint32_t)kernel_start,(uint32_t)kernel_end);
    InitGDT((uint32_t)&gdt_table);
    InitIDT();

    init_process();
    init_time();

    // init_kmemory();
    sti();
}
