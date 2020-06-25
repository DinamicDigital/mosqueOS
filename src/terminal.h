/* date = June 18th 2020 7:20 pm */
#include "vga.h"
#include "vga_out.h"

#ifndef TERMINAL_H
#define TERMINAL_H

struct Terminal_Data {
    // TODO: Offscreen Buffer that gets drawn to VGA_ADDRESS
    // Cursor Data
    u32 cursor_row, cursor_col;
};

static struct Terminal_Data terminal = { .cursor_row = 1,  .cursor_col = 1 };

// TODO: (NOW) Make this actually work!
void terminal_echo(unsigned char* str)
{
    int len = strlen(str);
    u16* vga = (u16*)VGA_ADDRESS;
    for (int i = 0; i < len; i++)
    {
        if (str[i] == '\n')
        {
            terminal.cursor_row++;
            terminal.cursor_col = 1;
        }
        else {
            vga[80 * terminal.cursor_row + terminal.cursor_col] = VGA_COLOR(str[i], C(VGA_GRAY, VGA_BLACK));
            terminal.cursor_col++;
        }
    }
}

// TODO: Is draw_menu() logically supposed to be in this file?
// TODO: Themes?
void draw_menu()
{
    u16 *vga_buffer = (u16*)VGA_ADDRESS;
    
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
    u16 title_offset = (79 - title_len) / 2;
    
    vga_buffer[title_offset] = VGA_COLOR(181, C(VGA_DARK_GRAY, VGA_GREEN));
    print_at_color(vga_buffer + title_offset + 1, "MosqueOS", VGA_DARK_GRAY, VGA_GREEN);
    vga_buffer[title_offset + 9] = VGA_COLOR(198, C(VGA_DARK_GRAY, VGA_GREEN));
}


#endif //TERMINAL_H
