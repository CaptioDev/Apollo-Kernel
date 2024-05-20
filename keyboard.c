// src/keyboard.c
#include <stdint.h>
#include "vga.h"
#include "keyboard.h"

#define KEYBOARD_DATA_PORT 0x60
#define KEYBOARD_STATUS_PORT 0x64
#define KEYBOARD_IRQ 1

// Keyboard Scancode Set 1
static const char scancode_set_1[128] = {
    0, 27, '1', '2', '3', '4', '5', '6', '7', '8', /* 9 */
    '9', '0', '-', '=', '\b', /* Backspace */
    '\t', /* Tab */
    'q', 'w', 'e', 'r', /* 19 */
    't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n', /* Enter key */
    0, /* 29   - Control */
    'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', /* 39 */
    '\'', '`', 0, /* Left shift */
    '\\', 'z', 'x', 'c', 'v', 'b', 'n', /* 49 */
    'm', ',', '.', '/', 0, /* Right shift */
    '*',
    0, /* Alt */
    ' ', /* Space bar */
    0, /* Caps lock */
    0, /* 59 - F1 key ... > */
    0, 0, 0, 0, 0, 0, 0, 0,
    0, /* < ... F10 */
    0, /* 69 - Num lock*/
    0, /* Scroll Lock */
    0, /* Home key */
    0, /* Up Arrow */
    0, /* Page Up */
    '-',
    0, /* Left Arrow */
    0,
    0, /* Right Arrow */
    '+',
    0, /* 79 - End key*/
    0, /* Down Arrow */
    0, /* Page Down */
    0, /* Insert Key */
    0, /* Delete Key */
    0, 0, 0,
    0, /* F11 Key */
    0, /* F12 Key */
    0, /* All other keys are undefined */
};

static inline uint8_t inb(uint16_t port) {
    uint8_t ret;
    __asm__ volatile ("inb %1, %0" : "=a"(ret) : "dN"(port));
    return ret;
}

static void keyboard_callback(void) {
    uint8_t scancode = inb(KEYBOARD_DATA_PORT);
    if (scancode & 0x80) {
        // Key released
    } else {
        // Key pressed
        char c = scancode_set_1[scancode];
        if (c) {
            char str[2] = {c, '\0'};
            vga_write(str);
        }
    }
}

// Placeholder for the IRQ handler setup. This depends on your interrupt handling code.
// For instance, in a real kernel, you might have something like:
// void irq_install_handler(int irq, void (*handler)(void));
// In this example, we're just setting it up statically for simplicity.
void irq_install_handler(int irq, void (*handler)(void));

void keyboard_initialize(void) {
    irq_install_handler(KEYBOARD_IRQ, keyboard_callback);
}
