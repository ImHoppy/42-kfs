
global load_gdt

load_gdt:
    ; get gdt entries on load it
    mov eax, [esp + 4]
    lgdt [eax]

    ; setup on Kernel Data Segment
    mov ax, 0x10
    mov ds, ax
    mov fs, ax
    mov gs, ax
    mov es, ax

    ; setup Stack Segment on Kernel Stack Segment
    mov ax, 0x18
    mov ss, ax

    ; setup CS on Kernel Code Segment
    jmp 0x08:.reload_cs

.reload_cs:
    ret