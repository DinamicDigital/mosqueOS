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
    asm volatile ("cli");
    gdt_init();
    u64 memory_length = 0;
    
    // TODO: PAGING
    u64* mmap_addr = (u64*)info->memory_map_addr;
    for(u64 i = 0; i < info->memory_map_entries; i++)
    {
        memory_length += *(mmap_addr + 8);
    }
    
    
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
