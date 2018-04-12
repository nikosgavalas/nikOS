OBJECTS = loader.o kmain.o drivers/io.o drivers/framebuffer.o drivers/serial.o
CC = gcc
# remove the -g flag if no debugging is needed, because it makes the executable bigger
CFLAGS = -m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector \
         -nostartfiles -nodefaultlibs -Wall -Wextra -Werror -c -g
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
		-serial file:log/log.txt

# make sure to run $ make debug with the -g flag in the gcc
debug: os.iso debug.gdb
	$(QEMU) -S -s -cdrom $<

%.o: %.c
	$(CC) $(CFLAGS) $< -o $@

%.o: %.s
	$(AS) $(ASFLAGS) $< -o $@

clean:
	rm -rf *.o drivers/*.o kernel.elf os.iso log/log.txt
