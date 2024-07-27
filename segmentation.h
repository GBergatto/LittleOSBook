#ifndef INCLUDE_SEGMENTATION_H
#define INCLUDE_SEGMENTATION_H

typedef struct {
  unsigned short size;
  unsigned int address;
} __attribute__((packed)) gdt_t; // gdt_descriptor

/* Segment descriptor
 * https://wiki.osdev.org/Global_Descriptor_Table#Segment_Descriptor
 */
typedef struct {
  unsigned short limit_low;
  unsigned short base_low;
  unsigned char base_middle;
  unsigned char access_byte;
  unsigned char limit_and_flags;
  unsigned char base_high;
} __attribute__((packed)) segment_descriptor_t;

void load_gdt(gdt_t gdt);
void load_segment_registers();

#endif
