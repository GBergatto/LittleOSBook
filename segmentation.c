#include "segmentation.h"

#define GDT_SIZE 3

static segment_descriptor_t gdt[GDT_SIZE];

void init_descriptor(int index, unsigned int base, unsigned int limit,
                     char access_byte, char flags) {
  // Base
  gdt[index].base_low = base & 0xFFFF;
  gdt[index].base_middle = (base >> 16) & 0xFF;
  gdt[index].base_high = (base >> 24) & 0xFF;

  // Limit and Flags
  gdt[index].limit_low = limit & 0xFFFF;
  gdt[index].limit_and_flags = (limit >> 16) | (flags << 4);

  // Access Byte
  gdt[index].access_byte = access_byte;
}

void init_gdt() {
  gdt_t *p = (gdt_t *)gdt;
  p->address = (unsigned int)gdt;
  p->size = sizeof(segment_descriptor_t) * GDT_SIZE - 1;

  // https://wiki.osdev.org/GDT_Tutorial#Flat_/_Long_Mode_Setup
  init_descriptor(1, 0, 0xFFFFF, 0x9B, 0xC);
  init_descriptor(2, 0, 0xFFFFF, 0x92, 0xC);

  load_gdt(*p);
  load_segment_registers();
}
