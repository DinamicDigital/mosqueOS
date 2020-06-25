/* date = June 24th 2020 7:26 pm */

#ifndef GDT_H
#define GDT_H


struct GDT_Register {
    u16 size;
    u64 address;
} __attribute__((packed));

// An entry in the GDT is a GDT_Descriptor. 
struct GDT_Descriptor {
    
    u16 limit;
    
    u16 base_low_16;
    
    u8 base_middle_8; 
    
    u8 access;
    
    u8 granularity;
    
    u8 base_high_8;
    
} __attribute__((packed));

const int CODE_SEGMENT = 0x08;
const int DATA_SEGMENT = 0x10;


static struct GDT_Descriptor gdt_entries[3];
static struct GDT_Register gdt_pointer;

void gdt_init(void)
{
    // Null Descriptor
    gdt_entries[0].limit       = 0;
    gdt_entries[0].base_low_16 = 0;
    gdt_entries[0].base_middle_8  = 0;
    gdt_entries[0].access      = 0;
    gdt_entries[0].granularity = 0;
    gdt_entries[0].base_high_8 = 0;
    
    // Kernel Code
    gdt_entries[1].limit       = 0;
    gdt_entries[1].base_low_16 = 0;
    gdt_entries[1].base_middle_8  = 0;
    gdt_entries[1].access      = 0b10011010;
    gdt_entries[1].granularity = 0b00100000;
    gdt_entries[1].base_high_8 = 0;
    
    gdt_entries[2].limit       = 0;
    gdt_entries[2].base_low_16 = 0;
    gdt_entries[2].base_middle_8  = 0;
    gdt_entries[2].access      = 0b10010010;
    gdt_entries[2].granularity = 0b00000000;
    gdt_entries[2].base_high_8 = 0;
    
    gdt_pointer.size    = (uint16_t) (sizeof(gdt_entries) - 1);
    gdt_pointer.address = (uint64_t) (&gdt_entries);
    
    
    asm volatile (
                  "lgdt %0;"
                  :
                  : "m" (gdt_pointer)
                  :
                  );
}


#endif //GDT_H
