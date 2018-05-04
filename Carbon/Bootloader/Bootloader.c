#include "../Include/Bootloader.h"
#include "../Include/CarbonDefine.h"
#include "../Include/CarbonKernelIO.h"
#include "../Include/KernelAssembly.h"
typedef struct __multiboot_header__ {
    uint32_t magic;
    uint32_t flags;
    uint32_t checksum;
} MultibootHeader;
MultibootHeader mbr __attribute__((section(".init.text"))) = {
        .magic = 0x1BADB002,
        .flags = 0x00000003,
        .checksum = -(0x1BADB002 + 0x00000003),
};
uint32_t magic;
Multiboot *multiboot_ptr;
void BootEntry(void) {
    asm("movl %%eax,%0" : "=m"(magic));
    if (magic != 0x2BADB002) {
        printk("Error: Cannot loading kernel\n");
        return;
    }
    asm("movl %%ebx,%0" : "=m"(multiboot_ptr));
    cls();
    cli();
    printk("Booting...");
    KernelEntry();
    hlt();
}