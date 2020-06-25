/* date = June 18th 2020 7:06 pm */

#ifndef VGA_H
#define VGA_H

#include "types.h"
#include "ports.h"

// Default VGA resolution is 80x25 (charaters)
#define VGA_ADDRESS 0xb8000
#define VGA_COLOR(character, color) (u16) character | (u16) (color) << 8
#define C(bg, fg) (bg << 4) | fg

// Colors
#define VGA_BLACK        0
#define VGA_BLUE         1
#define VGA_GREEN        2
#define VGA_CYAN         3
#define VGA_RED          4
#define VGA_PURPLE       5
#define VGA_BROWN        6
#define VGA_GRAY         7
#define VGA_DARK_GRAY    8
#define VGA_LIGHT_BLUE   9
#define VGA_LIGH_GREEN   10
#define VGA_LIGHT_CYAN   11
#define VGA_LIGHT_RED    12
#define VGA_LIGHT_PURPLE 13
#define VGA_YELLOW       14
#define VGA_WHITE        15


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


#endif //VGA_H
