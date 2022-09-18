# nikOS

Minimal hobby Operating System built from scratch, for learning purposes.

Resources I used:
- [LittleOSbook](https://littleosbook.github.io/)
- [OSDev Wiki](https://wiki.osdev.org/Expanded_Main_Page)

To use:
```
$ apt install qemu qemu-system nasm genisoimage build-essential
$ make run
```

## Roadmap:

- [x] Boot with GRUB
- [x] Set up a stack and call C
- [x] Load a Global Descriptor Table
- [x] Framebuffer driver
- [x] Serial comm driver
- [x] Debugging utilities and gdb
- [x] Interrupts
- [x] Keyboard driver
- [ ] Paging
- [ ] Shell
- [ ] Filesystem
- [ ] Utilities
- [ ] Scheduler
- [ ] Networking