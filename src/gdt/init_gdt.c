#include "gdt.h"
#include "../uart/uart.h"

gdt_segment_t gdt_entries[GDT_ENTRIES];
gdt_ptr_t *gdt_ptr = (gdt_ptr_t *)GDT_ADDRESS;

// static void create_segment(struct gdt_segment *entry, unsigned int limit, unsigned int base, uint8_t access, uint8_t flags)
// {
//     entry->limit_low = limit & 0xFFFF;
//     // entry->limit_high = (limit >> 16) & 0xF;

//     entry->base_low = base & 0xFFFF;
//     entry->base_middle = (base >> 16) & 0xFF;
//     entry->base_high = (base >> 24) & 0xFF;


//     // entry->access_byte = access;
//     // entry->flags = flags & 0xF;
// }

static void create_descriptor(int num, uint32_t base, uint32_t limit, uint8_t access, uint8_t flags)
{
	gdt_entries[num].limit_low = (limit & 0xFFFF);
	gdt_entries[num].base_low = (base & 0xFFFF);
	gdt_entries[num].base_middle = (base >> 16) & 0xFF;
	gdt_entries[num].access_byte = access;
	gdt_entries[num].attributes = (limit >> 16) & 0x0F;
	gdt_entries[num].attributes |= ((flags << 4) & 0xF0);
	gdt_entries[num].base_high = (base >> 24) & 0xFF;
}

// #define SEG_DESCTYPE(x) ((x) << 0x04)           /* Descriptor type (0 for system, 1 for code/data) */
// #define SEG_PRES(x) ((x) << 0x07)               /* Present */
// #define SEG_SAVL(x) ((x) << 0x0C)               /* Available for system use */
// #define SEG_LONG(x) ((x) << 0x0D)               /* Long mode */
// #define SEG_SIZE(x) ((x) << 0x0E)               /* Size (0 for 16-bit, 1 for 32) */
// #define SEG_GRAN(x) ((x) << 0x0F)               /* Granularity (0 for 1B - 1MB, 1 for 4KB - 4GB) */
// #define SEG_PRIV(x) (((x) &  0x03) << 0x05)     /* Set privilege level (0 - 3) */
 
// #define SEG_DATA_RD        0x00     /* Read-Only */
// #define SEG_DATA_RDA       0x01     /* Read-Only, accessed */
// #define SEG_DATA_RDWR      0x02     /* Read/Write */
// #define SEG_DATA_RDWRA     0x03     /* Read/Write, accessed */
// #define SEG_DATA_RDEXPD    0x04     /* Read-Only, expand-down */
// #define SEG_DATA_RDEXPDA   0x05     /* Read-Only, expand-down, accessed */
// #define SEG_DATA_RDWREXPD  0x06     /* Read/Write, expand-down */
// #define SEG_DATA_RDWREXPDA 0x07     /* Read/Write, expand-down, accessed */
// #define SEG_CODE_EX        0x08     /* Execute-Only */
// #define SEG_CODE_EXA       0x09     /* Execute-Only, accessed */
// #define SEG_CODE_EXRD      0x0A     /* Execute/Read */
// #define SEG_CODE_EXRDA     0x0B     /* Execute/Read, accessed */
// #define SEG_CODE_EXC       0x0C     /* Execute-Only, conforming */
// #define SEG_CODE_EXCA      0x0D     /* Execute-Only, conforming, accessed */
// #define SEG_CODE_EXRDC     0x0E     /* Execute/Read, conforming */
// #define SEG_CODE_EXRDCA    0x0F     /* Execute/Read, conforming, accessed */
// #define FLAT_MEMORY 0
// #define FLAGS 0xCF
// #define FLAG_D_32 0xCF

// /* 0x9A */
// #define GDT_CODE_PL0 SEG_DESCTYPE(1) | SEG_PRES(1) | SEG_SAVL(0) | \
//                      SEG_LONG(0)     | SEG_SIZE(1) | SEG_GRAN(1) | \
//                      SEG_PRIV(0)     | SEG_CODE_EXRD
 
// /* 0x92 */
// #define GDT_DATA_PL0 SEG_DESCTYPE(1) | SEG_PRES(1) | SEG_SAVL(0) | \
//                      SEG_LONG(0)     | SEG_SIZE(1) | SEG_GRAN(1) | \
//                      SEG_PRIV(0)     | SEG_DATA_RDWR

// /* 0x96 */
// #define GDT_STACK_PL0 SEG_DESCTYPE(1) | SEG_PRES(1) | SEG_SAVL(0) | \
//                      SEG_LONG(0)     | SEG_SIZE(1) | SEG_GRAN(1) | \
//                      SEG_PRIV(0)     | SEG_DATA_RDWREXPD

// /* 0xFA */
// #define GDT_CODE_PL3 SEG_DESCTYPE(1) | SEG_PRES(1) | SEG_SAVL(0) | \
//                      SEG_LONG(0)     | SEG_SIZE(1) | SEG_GRAN(1) | \
//                      SEG_PRIV(3)     | SEG_CODE_EXRD

// /* 0xF2 */
// #define GDT_DATA_PL3 SEG_DESCTYPE(1) | SEG_PRES(1) | SEG_SAVL(0) | \
//                      SEG_LONG(0)     | SEG_SIZE(1) | SEG_GRAN(1) | \
//                      SEG_PRIV(3)     | SEG_DATA_RDWR

// /* 0xF6 */
// #define GDT_STACK_PL3 SEG_DESCTYPE(1) | SEG_PRES(1) | SEG_SAVL(0) | \
//                      SEG_LONG(0)     | SEG_SIZE(1) | SEG_GRAN(1) | \
//                      SEG_PRIV(3)     | SEG_DATA_RDWREXPD




void init_gdt()
{    
    gdt_ptr->size = (GDT_ENTRIES * sizeof(gdt_segment_t)) - 1; // gdt size is zero-based, the -1 is needed
    gdt_ptr->addr = ((uint32_t)(&gdt_entries));

    create_descriptor(0, 0, 0, 0, 0);				// null
	create_descriptor(1, 0, 0xFFFFF, (uint8_t)(GDT_CODE_PL0),  FLAG_D_32);	// kernel code (kernel binary)
	create_descriptor(2, 0, 0xFFFFF, (uint8_t)(GDT_DATA_PL0),  FLAG_D_32);	// kernel data (kernel heap)
	create_descriptor(3, 0, 0xFFFFF, (uint8_t)(GDT_STACK_PL0), FLAG_D_32);	// kernel stack
	create_descriptor(4, 0, 0xBFFFF, (uint8_t)(GDT_CODE_PL3),  FLAG_D_32);	// user code (user-executed binaries)
	create_descriptor(5, 0, 0xBFFFF, (uint8_t)(GDT_DATA_PL3),  FLAG_D_32);	// user data (user heap)
	create_descriptor(6, 0, 0xBFFFF, (uint8_t)(GDT_STACK_PL3), FLAG_D_32);	// user stack

    load_gdt((uint32_t)gdt_ptr);
}