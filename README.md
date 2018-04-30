# nikOS

Minimal hobby Operating System built from scratch, for learning purposes.

[LittleOSbook](https://littleosbook.github.io/) helped me get started. It's a good resource, even if it has some errors and doesn't mention at all certain important things...which I later found on the awesome [OSDev Wiki](https://wiki.osdev.org/Expanded_Main_Page).

To use:
```
$ apt install qemu nasm genisoimage build-essential
$ make run
```

## Status:

- [x] Boot with GRUB
- [x] Set up a stack and call C
- [x] Load a Global Descriptor Table
- [x] Framebuffer driver
- [x] Serial comm driver
- [x] Debugging utilities and gdb
- [x] Interrupts
- [x] Keyboard driver
- [ ] Paging
- [ ] Userspace
- [ ] Filesystem
- [ ] Syscalls
- [ ] StdLib
- [ ] Scheduler
- [ ] Networking