#include "framebuffer.h"

#define FB_LINE_LEN 80

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
    switch (buf[i]) {
    case '\0':
      break;
    case '\n': {
      // move cursor to the start of the next line
      int steps = FB_LINE_LEN - (cursor_pos % FB_LINE_LEN);
      for (int i = 0; i < steps; i++) {
        fb_write_cell(2 * cursor_pos, ' ', FB_BLACK, FB_BLACK);
        fb_move_cursor(++cursor_pos);
      }
      break;
    }
    case '\t':
      // move the cursor forward by 3 pos
      for (int i = 0; i < 3; i++) {
        fb_write_cell(2 * cursor_pos, ' ', FB_BLACK, FB_BLACK);
        fb_move_cursor(++cursor_pos);
      }
      break;
    default:
      fb_write_cell(2 * cursor_pos, buf[i], FB_GREEN, FB_DARK_GREY);
      fb_move_cursor(++cursor_pos);
      break;
    }
  }
  return len;
}
