#include <stdint.h>
#include <stivale.h>
#include "vga.h"
#include "vga_out.h"
#include "terminal.h"
#include "types.h"
/**
* Stack for bootstrapping the kernel
*/

static char stack[4096] = {0};

__attribute__((section(".stivalehdr"), used))
struct stivale_header header = {
    .stack = (uintptr_t)stack + sizeof(stack),
    .framebuffer_bpp = 0,
    .framebuffer_width = 0,
    .framebuffer_height = 0,
    .flags = 0,
    .entry_point = 0
};

static inline void outb(u16 port, u8 val)
{
    asm volatile ( "outb %1, %0" : : "a"(val), "Nd"(port) );
    /* There's an outb %al, $imm8  encoding, for compile-time constant port numbers that fit in 8b.  (N constraint).
     * Wider immediate constants would be truncated at assemble-time (e.g. "i" constraint).
     * The  outb  %al, %dx  encoding is the only option for all other cases.
     * %1 expands to %dx because  port  is a u16.  %w1 could be used if we had the port number a wider C type */
}

static inline u8 inb(u16 port)
{
    u8 ret;
    asm volatile ( "inb %0, %1"
                  : "=a"(ret)
                  : "Nd"(port) );
    return ret;
}

void hide_cursor()
{
    outb(0x3D4, 0x0A);
    outb(0x3D5, 0x20);
}

void enable_cursor (u8 scanline_start, u8 scanline_end)
{
    outb(0x3D4, 0x0A);
    outb(0x3D5, (inb(0x3D5) & 0xC0) | scanline_start);
    
    outb(0x3D4, 0x0B);
    outb(0x3D5, (inb(0x3D5) & 0xE0) | scanline_end);
}

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
    
    gdt_entries[1].limit       = 0;
    gdt_entries[1].base_low_16 = 0;
    gdt_entries[1].base_middle_8  = 0;
    gdt_entries[1].access      = 0b10010010;
    gdt_entries[1].granularity = 0b00000000;
    gdt_entries[1].base_high_8 = 0;
    
    gdt_pointer.size    = (uint16_t) (sizeof(gdt_entries) - 1);
    gdt_pointer.address = (uint64_t) (&gdt_entries);
    
    asm volatile (
                  "lgdtq %0;"
                  
                  // Long jump to set cs and ss.
                  "movq rax, rsp;"
                  "pushq %1;"
                  "pushq rax;"
                  "pushfq;"
                  "pushq %2;"
                  "pushq 1f;"
                  "iretq;"
                  
                  // Reload segments.
                  "1:;"
                  "movw ax, %1;"
                  "movw ds, ax;"
                  "movw es, ax;"
                  "movw fs, ax;"
                  "movw gs, ax;"
                  :
                  : "m" (gdt_pointer), "i" (DATA_SEGMENT), "i" (CODE_SEGMENT)
                  : "rax"
                  );
}

void _start(struct stivale_struct *bootloader_data) 
{
    // QLoader does this, but do it just incase for extra big brain gain
    asm volatile ("cli");
    gdt_init();
    
    hide_cursor();
    draw_menu();
    
    //TODO: GDT and other fancy stuff like that.
    //TODO: Maybe do a terminal system?
    //TODO: Cross-Compiler eventually
    asm volatile ("hlt");
}
