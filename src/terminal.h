/* date = June 18th 2020 7:20 pm */
#include "vga.h"
#include "vga_out.h"

#ifndef TERMINAL_H
#define TERMINAL_H

struct Terminal_Data {
    // TODO: Offscreen Buffer that gets drawn to VGA_ADDRESS
    // Cursor Data
    char ch_buffer[(80 * 24) - (80 + 80 + 25 + 25) - 4];
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
        if (terminal.cursor_row >= 23 && terminal.cursor_col >= 79)
        {
            // TODO: Scrolling
            terminal.cursor_row = 1; // Reset Cursor
            terminal.cursor_col = 1; 
        }
        if (str[i] == '\n')
        { // Set Cursor to next line.
            terminal.cursor_row++;
            terminal.cursor_col = 1; 
        }
        else {
            if (terminal.cursor_col >= 79)
            {
                terminal.cursor_row++;
                terminal.cursor_col = 1; 
            }
            vga[80 * terminal.cursor_row + terminal.cursor_col] = VGA_COLOR(str[i], C(VGA_GRAY, VGA_BLACK));
            terminal.cursor_col++;
        }
    }
}

// TODO: Is draw_menu() logically supposed to be in this file?
// TODO: Themes?
#define MENU_BORDER_BG VGA_DARK_GRAY
#define MENU_BORDER_FG VGA_GREEN

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
        vga_buffer[i] = VGA_COLOR(205, C(MENU_BORDER_BG, MENU_BORDER_FG));
    }
    // Top Corners
    vga_buffer[0] = VGA_COLOR(201, C(MENU_BORDER_BG, MENU_BORDER_FG));
    vga_buffer[79] = VGA_COLOR(187, C(MENU_BORDER_BG, MENU_BORDER_FG));
    
    // Left and right sides
    for (int i = 1; i < 24; i++)
    {
        vga_buffer[80 * i] = VGA_COLOR(186, C(MENU_BORDER_BG, MENU_BORDER_FG));
        vga_buffer[80 * i + 79] = VGA_COLOR(186, C(MENU_BORDER_BG, MENU_BORDER_FG));
    }
    // Bottom
    for (int i = 1; i < 79; i++)
    {
        vga_buffer[80 * 24 + i] = VGA_COLOR(205, C(MENU_BORDER_BG, MENU_BORDER_FG));
    }
    // Bottom Corners
    vga_buffer[80 * 24] = VGA_COLOR(200, C(MENU_BORDER_BG, MENU_BORDER_FG));
    vga_buffer[80 * 24 + 79] = VGA_COLOR(188, C(MENU_BORDER_BG, MENU_BORDER_FG));
    
    // Title "|MosqueOS|"
    int title_len = 10; 
    u16 title_offset = (79 - title_len) / 2;
    
    vga_buffer[title_offset] = VGA_COLOR(181, C(MENU_BORDER_BG, MENU_BORDER_FG));
    print_at_color(vga_buffer + title_offset + 1, "MosqueOS", MENU_BORDER_BG, MENU_BORDER_FG);
    vga_buffer[title_offset + 9] = VGA_COLOR(198, C(MENU_BORDER_BG, MENU_BORDER_FG));
}


#endif //TERMINAL_H
