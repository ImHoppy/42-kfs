#!/bin/bash

if grub-file --is-x86-multiboot kernel; then
	echo multiboot confirmed
	mkdir -p isodir/boot/grub
	cp kernel isodir/boot/kernel
	cp grub.cfg isodir/boot/grub/grub.cfg
	grub-mkrescue -o kernel.iso isodir
else
  echo the file is not multiboot
fi
