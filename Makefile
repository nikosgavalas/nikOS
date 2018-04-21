OBJECTS = loader.o kmain.o 
OBJECTS += lib/asm.o lib/logger.o 
OBJECTS += interrupt/handler.o interrupt/asm_int_handlers.o 
OBJECTS += drivers/framebuffer.o drivers/serial.o drivers/keyb.o drivers/pic.o
OBJECTS += descriptor_tables/gdt.o descriptor_tables/idt.o

CC = gcc
# remove the -g flag if no debugging is needed, because it makes the executable bigger
CFLAGS = -m32 -c -g -Iinclude
CFLAGS += -nostdlib -nostdinc -fno-builtin -fno-stack-protector -nostartfiles -nodefaultlibs
CFLAGS += -Wall -Wextra #-Werror

LD = ld
LDFLAGS = -T link.ld -melf_i386

AS = nasm
ASFLAGS = -f elf

QEMU = qemu-system-i386

all: kernel.elf

kernel.elf: $(OBJECTS)
	$(LD) $(LDFLAGS) $(OBJECTS) -o $@

os.iso: kernel.elf
	cp $< iso/boot/$<
	genisoimage -R \
		-b boot/grub/stage2_eltorito \
		-no-emul-boot \
		-boot-load-size 4 \
		-A os \
		-input-charset utf8 \
		-quiet \
		-boot-info-table \
		-o os.iso \
		iso

run: os.iso
	$(QEMU) -monitor stdio \
		-cdrom $? \
		-serial file:log.txt

# make sure to run $ make debug with the -g flag in the gcc
debug: os.iso debug.gdb
	$(QEMU) -S -s -cdrom $<

%.o: %.c
	$(CC) $(CFLAGS) $< -o $@

%.o: %.s
	$(AS) $(ASFLAGS) $< -o $@

clean:
	rm -rf *.o kernel.elf os.iso log.txt \
		drivers/*.o \
		descriptor_tables/*.o \
		interrupt/*.o \
		lib/*.o
