/* date = June 18th 2020 7:20 pm */
#include "vga.h"
#include "vga_out.h"

#ifndef TERMINAL_H
#define TERMINAL_H

// TODO: Themes?
void draw_menu()
{
    uint16_t *vga_buffer = (uint16_t*)VGA_ADDRESS;
    
    // Clear screen to specified color.
    for (int i = 0; i < 80 * 25; i++)
    {
        vga_buffer[i] = VGA_COLOR(' ', VGA_GRAY << 4);
    }
    // Top Section
    for (int i = 0; i < 80; i++)
    {
        vga_buffer[i] = VGA_COLOR(205, C(VGA_DARK_GRAY, VGA_GREEN));
    }
    // Top Corners
    vga_buffer[0] = VGA_COLOR(201, C(VGA_DARK_GRAY, VGA_GREEN));
    vga_buffer[79] = VGA_COLOR(187, C(VGA_DARK_GRAY, VGA_GREEN));
    
    // Left and right sides
    for (int i = 1; i < 24; i++)
    {
        vga_buffer[80 * i] = VGA_COLOR(186, C(VGA_DARK_GRAY, VGA_GREEN));
        vga_buffer[80 * i + 79] = VGA_COLOR(186, C(VGA_DARK_GRAY, VGA_GREEN));
    }
    // Bottom
    for (int i = 1; i < 79; i++)
    {
        vga_buffer[80 * 24 + i] = VGA_COLOR(205, C(VGA_DARK_GRAY, VGA_GREEN));
    }
    // Bottom Corners
    vga_buffer[80 * 24] = VGA_COLOR(200, C(VGA_DARK_GRAY, VGA_GREEN));
    vga_buffer[80 * 24 + 79] = VGA_COLOR(188, C(VGA_DARK_GRAY, VGA_GREEN));
    
    // Title "|MosqueOS|"
    int title_len = 10; 
    uint16_t title_offset = (79 - title_len) / 2;
    
    vga_buffer[title_offset] = VGA_COLOR(181, C(VGA_DARK_GRAY, VGA_GREEN));
    print_at_color(vga_buffer + title_offset + 1, "MosqueOS", VGA_DARK_GRAY, VGA_GREEN);
    vga_buffer[title_offset + 9] = VGA_COLOR(198, C(VGA_DARK_GRAY, VGA_GREEN));
}


#endif //TERMINAL_H
