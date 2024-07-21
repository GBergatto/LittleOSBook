#ifndef INCLUDE_FRAMEBUFFER_H
#define INCLUDE_FRAMEBUFFER_H

#include "io.h"

/* I/O ports */
#define FB_COMMAND_PORT 0x3D4
#define FB_DATA_PORT 0x3D5

/* I/O port commands */
#define FB_HIGH_BYTE_COMMAND 14
#define FB_LOW_BYTE_COMMAND 15

/**
 * Moves the cursor of the framebuffer to the given position
 *
 * @param pos The new position of the cursor
 */
void fb_move_cursor(unsigned short pos);

#define FB_GREEN 2
#define FB_DARK_GREY 8
#define FRAMEBUFFER_ADDRESS 0x000B8000

/**
 * Writes a character with the given foreground and background to position i
 * in the framebuffer.
 *
 * @param i  The location in the framebuffer
 * @param c  The character
 * @param fg The foreground color
 * @param bg The background color
 */
void fb_write_cell(unsigned int i, char c, unsigned char fg, unsigned char bg);

/**
 * Writes the contents of the buffer of lenght len to the screen advancing the
 * cursor and moving to the next line if necessary
 *
 * @param buf
 * @param len
 * @return Number of characters written
 */
int fb_write(char *buf, unsigned int len);

#endif
