/* date = June 18th 2020 7:12 pm */
#include "vga.h"
#include "types.h"

#ifndef VGA_OUT_H
#define VGA_OUT_H


// TODO: Maybe this isnt optimized?
int strlen(unsigned char* str)
{
    int len = 0;
    while(*str != 0)
    {
        len++;
        str++;
    }
    return len;
}

void print(unsigned char* str)
{
    int length = strlen(str);
    u16* vga = (u16*)VGA_ADDRESS;
    
    for (int i = 0; i < length; i++)
    {
        vga[i] = VGA_COLOR(str[i], VGA_WHITE);
    }
}

void print_color(unsigned char* str, u8 bg, u8 fg)
{
    int length = strlen(str);
    u16* vga = (u16*)VGA_ADDRESS;
    
    for (int i = 0; i < length; i++)
    {
        vga[i] = VGA_COLOR(str[i], (bg << 4) | fg);
    }
}

void print_at_color(u16* vga_mem, unsigned char* str, u8 bg, u8 fg)
{
    int length = strlen(str);
    u16* vga = vga_mem;
    
    for (int i = 0; i < length; i++)
    {
        vga[i] = VGA_COLOR(str[i], (bg << 4) | fg);
    }
}


#endif //VGA_OUT_H
