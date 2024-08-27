IMG = kernel
GRUB_IMG = kernel.iso

ASM_SRC = src/boot.asm \
src/syscall.asm

C_SRC = src/kernel.c \
src/vga.c

C_FLAGS = -fno-builtin -fno-exceptions -fno-stack-protector -nostdlib -nodefaultlibs # -fno-rtti

OBJ = $(ASM_SRC:.asm=.o) $(C_SRC:.c=.o)

.PHONY: all clean fclean re emu

all: $(IMG) $(GRUB_IMG)

$(GRUB_IMG): $(IMG)
	@if [ -z "$$(docker images -q grub-build 2> /dev/null)" ]; then \
		echo "Building Docker image grub-build..."; \
		docker build . --tag grub-build; \
	else \
		echo "Docker image grub-build already exists."; \
	fi
	docker run  -v .:/app grub-build ./grub.sh

$(IMG): $(OBJ)
	ld -m elf_i386 -T link.ld -o $(IMG) $(OBJ)

%.o: %.asm
	nasm -f elf32 $< -o $@

%.o: %.c
	gcc $(C_FLAGS) -m32 -c $< -o $@

clean:
	rm -f $(OBJ)
	rm -rf isodir

fclean: clean
	rm -f $(IMG) $(GRUB_IMG)

re: fclean all

emu:
	qemu-system-i386 -cdrom $(GRUB_IMG)
