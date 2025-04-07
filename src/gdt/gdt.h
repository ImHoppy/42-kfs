#ifndef GDT_H
#define GDT_H
#include <stdint.h>

#define GDT_ADDRESS 0x00000800 
#define SEGMENTS_SIZE 7 

__attribute__((packed)) struct gdt_segment
{
    uint16_t limit_low;
    uint16_t base_low;
    uint8_t base_middle;
    uint8_t access_byte;
    uint8_t limit_high : 4;
    uint8_t flags : 4;
    uint8_t base_high;
};

__attribute__((packed)) struct gdt_ptr {

    uint16_t size;
    uint32_t addr;
};

extern void load_gdt(uint32_t* gdt_ptr);
void init_gdt(void);

#endif