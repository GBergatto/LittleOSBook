#include "framebuffer.h"

int kmain() {
  char w[] = "Test";
  fb_write(w, 4);
  return 0;
}
