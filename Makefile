TARGET = prog
OBJS = main.o Auth.o interface.o WebManager.o
CROSS-COMPILE = aarch64-elf-
CC = $(CROSS-COMPILE)gcc
LD = $(CROSS-COMPILE)ld
NM = $(CROSS-COMPILE)nm
OBJDUMP = $(CROSS-COMPILE)objdump
OBJCOPY = $(CROSS-COMPILE)objcopy
GDB = $(CROSS-COMPILE)gdb
MAKE = make
RM = rm -f
TOUCH = touch
CAT = cat
ECHO = echo
CP = cp
OPT = -O0 -g
GENDEPFLAGS = -MMD -MP
INCDIRS = -I.
CPU = -mcpu=cortex-a53 -mgeneral-regs-only
FLAGS = -Werror -Wall -Wunused $(CPU) $(GENDEPFLAGS)
CFLAGS = $(FLAGS) $(INCDIRS) $(OPT) -fno-strict-aliasing -
ffreestanding
CPPFLAGS = $(CFLAGS) -fno-rtti -fno-exceptions -fno-use-cxa-atexit
ASFLAGS = $(FLAGS)
LDFLAGS = -nostdlib -T ldscript.ld
LDFLAGS += -Wl,-Map=$(TARGET).map,--cref,--build-id=none
QEMU = qemu-system-aarch64
QEMU_OPTIONS = -machine
virt,secure="true",virtualization="true",gic-version="3"
QEMU_OPTIONS += -cpu cortex-a53 -m 256M -parallel none -nographic
QEMU_OPTIONS += -device virtio-net-device,netdev=br0
QEMU_OPTIONS += -netdev bridge,br=br0,id=br0
QEMU_OPTIONS += -device virtio-net-device,netdev=br1
QEMU_OPTIONS += -netdev bridge,br=br1,id=br1
all: build
build: $(TARGET)
$(TARGET): $(OBJS)
$(CC) -o $@ $^ $(LDFLAGS)
$(NM) -a -n -C $@ > $@.nm
$(OBJCOPY) --output-target binary $@ $@.bin
$(OBJDUMP) --disassemble --disassemble-zeroes --demangle $@ >
$@.lst
%.o : %.c
$(CC) -o $@ -c $< $(CFLAGS) $($(notdir $<)-FLAGS
%.o : %.sx
$(CC) -x assembler-with-cpp -o $@ -c $< $(ASFLAGS) $($(notdir
$<)-FLAGS)
clean:
$(RM) *.o *.d *.s *.ii $(TARGET) *.nm *.map *.bin *.lst
run: $(TARGET)
$(QEMU) $(QEMU_OPTIONS) -kernel $(TARGET)
-include $(wildcard *.d)
