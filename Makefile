IMG = kernel
GRUB_IMG = kernel.iso
DISK = disk.img

ASM_SRC = src/boot.asm \
src/gdt/load_gdt.asm \
src/syscall.asm

C_SRC = src/gdt/init_gdt.c \
src/uart/uart.c \
src/kernel.c \
src/vga.c \
src/printf.c \
src/keyboard.c \
src/libft/ft_itoa.c src/libft/ft_atoi.c  src/libft/ft_char.c src/libft/str/ft_hextoint.c \
src/libft/ft_strlen.c  src/libft/ft_strrev.c src/libft/str/ft_strcmp.c src/libft/str/ft_strncmp.c \
src/libft/mem/ft_memchr.c  src/libft/mem/ft_memcmp.c  src/libft/mem/ft_memcpy.c  src/libft/mem/ft_memmove.c  src/libft/mem/ft_memset.c

C_FLAGS = -fno-builtin -fno-exceptions -fno-stack-protector -nostdlib -nodefaultlibs -Wall -Werror -Wextra # -fno-rtti

OBJ = $(ASM_SRC:.asm=.o) $(C_SRC:.c=.o)

.PHONY: all clean fclean re emu

all: $(IMG) $(GRUB_IMG) $(DISK)

$(GRUB_IMG): $(IMG)
	@if [ -z "$$(docker images -q grub-build 2> /dev/null)" ]; then \
		echo "Building Docker image grub-build..."; \
		docker build . --tag grub-build; \
	else \
		echo "Docker image grub-build already exists."; \
	fi
	@docker run  -v .:/app grub-build ./grub.sh 2> /dev/null

$(IMG): $(OBJ)
	@ld -m elf_i386 -T link.ld -o $(IMG) $(OBJ)

$(DISK):
	@dd if=/dev/zero of=$(DISK) bs=1M count=10 2> /dev/null

%.o: %.asm
	@nasm -f elf32 $< -o $@

%.o: %.c
	@gcc $(C_FLAGS) -m32 -c $< -o $@ -g3

clean:
	@rm -f $(OBJ)
	@rm -rf isodir

fclean: clean
	@rm -f $(IMG) $(GRUB_IMG) $(DISK)

re: fclean all

emu:
	@qemu-system-i386 -s -cdrom $(GRUB_IMG) -drive file=$(DISK),format=raw -serial mon:stdio
