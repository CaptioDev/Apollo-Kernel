# Makefile for Apollo Kernel

# Directories
SRCDIR = src
INCDIR = include
BUILDDIR = build
SCRIPTSDIR = scripts

# Compiler and tools
CC = i686-elf-gcc
LD = i686-elf-ld
OBJCOPY = i686-elf-objcopy
CFLAGS = -Wall -Wextra -nostdlib -ffreestanding -I$(INCDIR)
LDFLAGS = -T $(SCRIPTSDIR)/link.ld

# Output
KERNEL_ELF = $(BUILDDIR)/kernel.elf
KERNEL_BIN = $(BUILDDIR)/kernel.bin

# Source files
C_SOURCES = $(wildcard $(SRCDIR)/*.c)
ASM_SOURCES = $(wildcard $(SRCDIR)/*.asm)

# Object files
C_OBJECTS = $(patsubst $(SRCDIR)/%.c, $(BUILDDIR)/%.o, $(C_SOURCES))
ASM_OBJECTS = $(patsubst $(SRCDIR)/%.asm, $(BUILDDIR)/%.o, $(ASM_SOURCES))
OBJECTS = $(C_OBJECTS) $(ASM_OBJECTS)

# Targets
all: $(KERNEL_BIN)

$(KERNEL_BIN): $(KERNEL_ELF)
	$(OBJCOPY) -O binary $< $@

$(KERNEL_ELF): $(OBJECTS)
	$(LD) -o $@ $^ $(LDFLAGS)

$(BUILDDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILDDIR)/%.o: $(SRCDIR)/%.asm
	nasm -f elf $< -o $@

clean:
	rm -f $(BUILDDIR)/*.o $(KERNEL_ELF) $(KERNEL_BIN)

.PHONY: all clean
