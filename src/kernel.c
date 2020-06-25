#include <stdint.h>
#include <stivale.h>
#include "vga.h"
#include "vga_out.h"
#include "terminal.h"
#include "types.h"
#include "gdt.h"

extern void kernel_main(struct stivale_struct* info)
{
    // QLoader does this, but do it just incase for extra big brain gain
    // TODO: PAGING
    asm volatile ("cli");
    //info.memory_map_addr;
    gdt_init();
    draw_menu();
    hide_cursor();
    
    for (int i = 0; i < 25 * 80; i++)
    {
        terminal_echo("_NUGGET_POOP_EGG___");
    }
    
    //TODO: (Active) Maybe do a terminal system?
    
    //TODO: Menu System
    //TODO: Cross-Compiler eventually
    
    asm volatile ("hlt");
}
