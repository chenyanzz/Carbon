#include "../Include/Assert.h"
#include "../Include/KernelAssembly.h"
#include "../Include/Bootloader.h"
static elf_t kernel_elf;
void Assert(void *exp, void *file, unsigned int line) {
    printk("Assertion failed: %s, File: %s,Line: %d", exp, file, line);
    hlt();
}
void InitDebug() { kernel_elf = elf_from_multiboot(global_multiboot_ptr); }
void PrintStackTrace() {
    uint32_t *ebp, *eip;
    asm("mov %%ebp, %0" : "=r" (ebp));
    while (ebp) {
        eip = ebp + 1;
        printk("   [0x%x] %s\n", *eip, elf_lookup_symbol(*eip, &kernel_elf));
        ebp = (uint32_t *)*ebp;
    }
}