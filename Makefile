# http://www.nasm.us/doc/
NASM=nasm

# https://qemu.weilnetz.de/doc/qemu-doc.html#index-_002dserial
QEMU=qemu-system-i386

all: kernel.elf

kernel.elf: link.ld loader.o
	ld -T $< -melf_i386 loader.o -o $@
	mv $@ iso/boot/$@

loader.o: loader.s
	nasm -f elf32 $?

os.iso: kernel.elf
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

clean:
	rm *.o
	rm *.iso
	rm log/log.txt

