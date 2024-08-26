IMG = kernel

ASM_SRC = src/boot.asm \
src/syscall.asm

C_SRC = src/kernel.c \
src/vga.c

C_FLAGS = -fno-builtin -fno-exceptions -fno-stack-protector -nostdlib -nodefaultlibs # -fno-rtti

OBJ = $(ASM_SRC:.asm=.o) $(C_SRC:.c=.o)

.PHONY: all clean fclean re emu

$(IMG): $(OBJ)
	ld -m elf_i386 -T link.ld -o kernel $(OBJ)

all: $(IMG)
	./grub.sh

%.o: %.asm
	nasm -f elf32 $< -o $@

%.o: %.c
	gcc $(C_FLAGS) -m32 -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f kernel

re: fclean all

emu:
	qemu-system-i386 -kernel kernel
