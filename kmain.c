#include "framebuffer.h"
#include "serial.h"

int kmain() {
  char w[] = "A\nB\nC\nD\nE\nF\nG\n";

  fb_write(w, sizeof w);
  serial_write(w, sizeof w);
  return 0;
}
