/* date = June 24th 2020 7:29 pm */

#ifndef PORTS_H
#define PORTS_H

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

#endif //PORTS_H
