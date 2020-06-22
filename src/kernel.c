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

static inline void outb(uint16_t port, u8 val)
{
    asm volatile ( "outb %1, %0" : : "a"(val), "Nd"(port) );
    /* There's an outb %al, $imm8  encoding, for compile-time constant port numbers that fit in 8b.  (N constraint).
     * Wider immediate constants would be truncated at assemble-time (e.g. "i" constraint).
     * The  outb  %al, %dx  encoding is the only option for all other cases.
     * %1 expands to %dx because  port  is a uint16_t.  %w1 could be used if we had the port number a wider C type */
}

static inline u8 inb(uint16_t port)
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

struct gdtr {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed));

struct gdt_desc {
    
    uint16_t lim0_15;
    uint16_t base0_15;
    u8; 
    u8 access;
    u8 lim16_19 : 4;
    u8 other : 4;
    u8 base24_31;
    
} __attribute__((packed));

void init_gdt_desc(uint32_t base,  uint32_t limit, u8 access, u8 other, struct gdt_desc* desc)
{
    desc->lim0_15 = (limit & 0xffff);
    desc->base0_15 = (base & 0xffff);
    desc->base
}

void _start(struct stivale_struct *bootloader_data) 
{
    // QLoader does this, but do it just incase for extra big brain
    asm volatile ("cli");
    
    hide_cursor();
    draw_menu();
    
    //TODO: GDT and other fancy stuff like that.
    //TODO: Maybe do a terminal system?
    //TODO: Cross-Compiler eventually
    asm volatile ("hlt");
}
