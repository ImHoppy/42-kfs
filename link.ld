OUTPUT_FORMAT(elf32-i386)
ENTRY(start)
SECTIONS
{
	. = 0x100000;
	.text : {
		*(.multiboot)	/* Multiboot header, must always be first */
		*(.text)
	}
	.data : {*(.data)}
	.bss  : {*(.bss)}
}
