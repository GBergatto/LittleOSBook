#include "framebuffer.h"
#include "serial.h"

int kmain() {
  char w[] = "Test\nAAA\n";
  fb_write(w, 4);
  serial_write(w, sizeof w);
  return 0;
}
