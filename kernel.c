// src/kernel.c
#include "vga.h"
#include "gdt.h"
#include "keyboard.h"

void kernel_main() {
    gdt_initialize();
    vga_initialize();
    keyboard_initialize();

    vga_write("Apollo Kernel Initialized.\n");
}
