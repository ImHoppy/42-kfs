#include "gdt.h"
#include "../uart/uart.h"

gdt_segment_t gdt_entries[GDT_ENTRIES];
gdt_ptr_t *gdt_ptr = (gdt_ptr_t *)GDT_ADDRESS;

static void create_segment(int num, unsigned int limit, unsigned int base, uint8_t access, uint8_t flags)
{
    gdt_entries[num].limit_low = limit & 0xFFFF;
    gdt_entries[num].limit_high = (limit >> 16) & 0xF;

    gdt_entries[num].base_low = base & 0xFFFF;
    gdt_entries[num].base_middle = (base >> 16) & 0xFF;
    gdt_entries[num].base_high = (base >> 24) & 0xFF;

    gdt_entries[num].access_byte = access;
    gdt_entries[num].flags = flags & 0xF;
}

void init_gdt()
{    
    gdt_ptr->size = (GDT_ENTRIES * sizeof(gdt_segment_t)) - 1; // gdt size is zero-based, the -1 is needed
    gdt_ptr->addr = ((uint32_t)(&gdt_entries));

    // NULL segment
    create_segment(0, 0, 0, 0, 0);
    // Kernel Code, Data, Stack
    create_segment(1, 0xFFFFF, 0, (uint8_t)(GDT_CODE_PL0), SEG_FLAG);
    create_segment(2, 0xFFFFF, 0, (uint8_t)(GDT_DATA_PL0), SEG_FLAG);
    create_segment(3, 0xFFFFF, 0, (uint8_t)(GDT_STACK_PL0), SEG_FLAG);
    // User Code, Data, Stack
    create_segment(4, 0xBFFFF, 0, (uint8_t)(GDT_CODE_PL3), SEG_FLAG);
    create_segment(5, 0xBFFFF, 0, (uint8_t)(GDT_DATA_PL3), SEG_FLAG);
    create_segment(6, 0xBFFFF, 0, (uint8_t)(GDT_STACK_PL3), SEG_FLAG);


    load_gdt((uint32_t)gdt_ptr);
}