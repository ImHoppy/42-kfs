global read_key

read_key:
	hlt
	in al, 0x64
	test al, 1
	jz read_key
	in al, 0x60
