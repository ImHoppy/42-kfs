#include "gdt.h"
#include "../uart/uart.h"

// Access
#define SEG_PRES(x) (x << 7)            // Present (Must be set 1 for any valid segment)
#define SEG_PL(x) (x << 5)              // Set privilege level (0 - 3)
#define SEG_DESCTYPE(x) (x << 4)        // Descriptor type (0 for system, 1 for code/data)
#define SEG_CODE_EXRD (0b1000 | 0b0100) // Execute/Read
#define SEG_DATA_RDWR 0b0100            // Read/Write
#define SEG_DATA_RDWREXPD 0b0110        // Read/Write, expand-down

// Flags
#define SEG_SIZE(x) (x << 2) // Size (0 for 16-bit, 1 for 32)
#define SEG_GRAN(x) (x << 3) // Granularity (0 for 1B - 1MB, 1 for 4KB - 4GB)
#define SEG_LONG(x) (x << 1) // Long mode

static void create_segment(struct gdt_segment *entry, unsigned int limit, unsigned int base, uint8_t access, uint8_t flags)
{
    entry->limit_low = limit & 0xFFFF;
    entry->limit_high = (limit >> 16) & 0xF;

    entry->base_low = base & 0xFFFF;
    entry->base_middle = (base >> 16) & 0xFF;
    entry->base_high = (base >> 24) & 0xFF;

    entry->access_byte = access;
    entry->flags = flags & 0xF;
}

void init_gdt(void)
{    
    struct gdt_segment gdt_entries[SEGMENTS_SIZE];
    struct gdt_ptr *gdt = (struct gdt_ptr *)GDT_ADDRESS;

    gdt->addr = (uint32_t)gdt_entries;
    gdt->size = (SEGMENTS_SIZE * sizeof(struct gdt_segment)) - 1; // gdt size is zero-based, the -1 is needed

    // NULL segment
    create_segment(&gdt_entries[0], 0, 0, 0, 0);
    // Kernel Code, Data, Stack
    create_segment(&gdt_entries[1], 0xFFFFF, 0, SEG_PRES(1) | SEG_PL(0) | SEG_DESCTYPE(1) | SEG_CODE_EXRD, SEG_GRAN(1) | SEG_SIZE(1) | SEG_LONG(0));
    create_segment(&gdt_entries[2], 0xFFFFF, 0, SEG_PRES(1) | SEG_PL(0) | SEG_DESCTYPE(1) | SEG_DATA_RDWR, SEG_GRAN(1) | SEG_SIZE(1) | SEG_LONG(0));
    create_segment(&gdt_entries[3], 0xFFFFF, 0, SEG_PRES(1) | SEG_PL(0) | SEG_DESCTYPE(1) | SEG_DATA_RDWR, SEG_GRAN(1) | SEG_SIZE(1) | SEG_LONG(0));
    // User Code, Data, Stack
    create_segment(&gdt_entries[4], 0xFFFFF, 0, SEG_PRES(1) | SEG_PL(3) | SEG_DESCTYPE(1) | SEG_CODE_EXRD, SEG_GRAN(1) | SEG_SIZE(1) | SEG_LONG(0));
    create_segment(&gdt_entries[5], 0xFFFFF, 0, SEG_PRES(1) | SEG_PL(3) | SEG_DESCTYPE(1) | SEG_DATA_RDWR, SEG_GRAN(1) | SEG_SIZE(1) | SEG_LONG(0));
    create_segment(&gdt_entries[6], 0xFFFFF, 0, SEG_PRES(1) | SEG_PL(3) | SEG_DESCTYPE(1) | SEG_DATA_RDWR, SEG_GRAN(1) | SEG_SIZE(1) | SEG_LONG(0));

    serial_putc(*((char *)GDT_ADDRESS + 16 )+  '0');

    load_gdt(gdt);
}