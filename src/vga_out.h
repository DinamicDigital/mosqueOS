/* date = June 18th 2020 7:12 pm */
#include "vga.h"

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
    uint16_t* vga = (uint16_t*)VGA_ADDRESS;
    
    for (int i = 0; i < length; i++)
    {
        vga[i] = VGA_COLOR(str[i], VGA_WHITE);
    }
}

void print_color(unsigned char* str, uint8_t bg, uint8_t fg)
{
    int length = strlen(str);
    uint16_t* vga = (uint16_t*)VGA_ADDRESS;
    
    for (int i = 0; i < length; i++)
    {
        vga[i] = VGA_COLOR(str[i], (bg << 4) | fg);
    }
}

void print_at_color(uint16_t* vga_mem, unsigned char* str, uint8_t bg, uint8_t fg)
{
    int length = strlen(str);
    uint16_t* vga = vga_mem;
    
    for (int i = 0; i < length; i++)
    {
        vga[i] = VGA_COLOR(str[i], (bg << 4) | fg);
    }
}


#endif //VGA_OUT_H
