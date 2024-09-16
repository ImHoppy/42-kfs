# KFS - Kernel From Scratch

The **KFS** project is focused on writing a 32-bit kernel from scratch, with the final objective of creating a Unix-like system.
The project is broken down into several stages, each adding a critical component to the kernel.

## Project Stages

- [x] **KFS-1:** Boot with GRUB, handle keyboard input, and write to the VGA buffer.
- [ ] **KFS-2:** Implement a stack and integrate it with the Global Descriptor Table (GDT).
- [ ] **KFS-3:** Implement memory management, including paging, allocation, and free.
- [ ] **KFS-4:** Create and manage the Interrupt Descriptor Table (IDT) and handle interrupts.
- [ ] **KFS-5:** Develop process management, including the interpretation of the `:(){ :|:& }` command.
- [ ] **KFS-6:** Implement your own filesystem to manage storage in the kernel.
- [ ] **KFS-7:** Build syscalls, implement user accounts, sockets, and a Unix-like hierarchy.
- [ ] **KFS-8:** Create a module interface for your kernel to support modularity.
- [ ] **KFS-9:** Build an ELF parser and loader to handle executable files.
- [ ] **KFS-X:** Final stage – create a complete Linux-like environment. Optionally, name your kernel.

## References
# VGA Register
http://www.osdever.net/FreeVGA/vga/crtcreg.htm#0E