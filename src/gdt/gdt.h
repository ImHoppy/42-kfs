#ifndef GDT_H
#define GDT_H
#include <stdint.h>

#define GDT_ADDRESS 0x00000800
#define GDT_ENTRIES 7

// Access
#define SEG_PRES(x) (x << 7)            // Present (Must be set 1 for any valid segment)
#define SEG_PL(x) (x << 5)              // Set privilege level (0 - 3)
#define SEG_DESCTYPE(x) (x << 4)        // Descriptor type (0 for system, 1 for code/data)
#define SEG_CODE_EXRD (0b1000 | 0b0010) // Execute/Read
#define SEG_DATA_RDWR 0b0010            // Read/Write
#define SEG_DATA_RDWR 0b0010            // Read/Write
#define SEG_DATA_RDWREXPD 0b0110        // Read/Write, expand-down
// Access kernel
#define GDT_CODE_PL0 SEG_PRES(1) | SEG_PL(0) | SEG_DESCTYPE(1) | SEG_CODE_EXRD
#define GDT_DATA_PL0 SEG_PRES(1) | SEG_PL(0) | SEG_DESCTYPE(1) | SEG_DATA_RDWR
#define GDT_STACK_PL0 SEG_PRES(1) | SEG_PL(0) | SEG_DESCTYPE(1) | SEG_DATA_RDWREXPD
// Access User
#define GDT_CODE_PL3 SEG_PRES(1) | SEG_PL(3) | SEG_DESCTYPE(1) | SEG_CODE_EXRD
#define GDT_DATA_PL3 SEG_PRES(1) | SEG_PL(3) | SEG_DESCTYPE(1) | SEG_DATA_RDWR
#define GDT_STACK_PL3 SEG_PRES(1) | SEG_PL(3) | SEG_DESCTYPE(1) | SEG_DATA_RDWREXPD

// Flags
#define SEG_SIZE(x) (x << 2) // Size (0 for 16-bit, 1 for 32)
#define SEG_GRAN(x) (x << 3) // Granularity (0 for 1B - 1MB, 1 for 4KB - 4GB)
#define SEG_LONG(x) (x << 1) // Long mode

#define SEG_FLAG SEG_GRAN(1) | SEG_SIZE(1) | SEG_LONG(0)

typedef struct __attribute__((packed)) gdt_segment
{
    uint16_t limit_low;
    uint16_t base_low;
    uint8_t base_middle;
    uint8_t access_byte;
    uint8_t limit_high : 4;
    uint8_t flags : 4;
    uint8_t base_high;
} gdt_segment_t;

typedef struct __attribute__((packed)) gdt_ptr
{
    uint16_t size;
    uint32_t addr;
} gdt_ptr_t;

extern void load_gdt(uint32_t gdt_ptr);
void init_gdt(void);

#endif