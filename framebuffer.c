#include "framebuffer.h"

unsigned short cursor_pos = 0;

void fb_move_cursor(unsigned short pos) {
  outb(FB_COMMAND_PORT, FB_HIGH_BYTE_COMMAND);
  outb(FB_DATA_PORT, ((pos >> 8) & 0x00FF));
  outb(FB_COMMAND_PORT, FB_LOW_BYTE_COMMAND);
  outb(FB_DATA_PORT, pos & 0x00FF);
}

void fb_write_cell(unsigned int i, char c, unsigned char fg, unsigned char bg) {
  char *fb = (char *)FRAMEBUFFER_ADDRESS;
  fb[i] = c;
  fb[i + 1] = ((fg & 0x0F) << 4) | (bg & 0x0F);
}

int fb_write(char *buf, unsigned int len) {
  for (unsigned int i = 0; i < len; i++) {
    fb_write_cell(2 * cursor_pos, buf[i], FB_GREEN, FB_DARK_GREY);
    fb_move_cursor(++cursor_pos);
  }
  return len;
}
