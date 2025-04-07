#ifndef GDT_H
#define GDT_H
#include <stdint.h>

#define GDT_ADDRESS 0x00000800 
#define GDT_ENTRIES 7 

#define GDT_CODE_PL0 0x9A
#define GDT_DATA_PL0 0x92
#define GDT_STACK_PL0 0x96
#define GDT_CODE_PL3 0xFA
#define GDT_DATA_PL3 0xF2
#define GDT_STACK_PL3 0xF6

#define FLAG_D_32 0xCF

__attribute__((packed))



typedef struct __attribute__((packed))  gdt_segment
{
    uint16_t limit_low;
    uint16_t base_low;
    uint8_t base_middle;
    uint8_t access_byte;
    uint8_t attributes;
    // uint8_t limit_high : 4;
    // uint8_t flags : 4;
    uint8_t base_high;
} gdt_segment_t;

typedef struct __attribute__((packed))  gdt_ptr {
    uint16_t size;
    uint32_t addr;
} gdt_ptr_t;

extern void load_gdt(uint32_t gdt_ptr);
void init_gdt(void);

#endif