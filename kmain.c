#include "framebuffer.h"
#include "serial.h"

int kmain() {
  serial_configure(SERIAL_COM1_BASE, 3); /* 38400 baud */
  char w[] = "A\nB\nC\nD\nE\nF\nG\n";
  char a[] = "debug\n";
  char b[] = "info\n";
  char c[] = "error\n";

  fb_write(w, sizeof w);
  serial_write(DEBUG, a, sizeof a);
  serial_write(INFO, b, sizeof b);
  serial_write(ERROR, c, sizeof c);
  return 0;
}
