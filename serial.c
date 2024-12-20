#include "serial.h"
#include "io.h"

void serial_configure(unsigned short com, unsigned short divisor) {
  /* Set baud rate */
  outb(SERIAL_LINE_COMMAND_PORT(com), SERIAL_LINE_ENABLE_DLAB);
  outb(SERIAL_DATA_PORT(com), (divisor >> 8) & 0x00FF);
  outb(SERIAL_DATA_PORT(com), divisor & 0x00FF);
  /* Configure line, FIFO queue, and modem */
  outb(SERIAL_LINE_COMMAND_PORT(com), 0x03);
  outb(SERIAL_FIFO_COMMAND_PORT(com), 0xC7);
  outb(SERIAL_MODEM_COMMAND_PORT(com), 0x0B);
}

int serial_is_transmit_fifo_empty(unsigned int com) {
  /* Read bit 5 of the line status I/O port */
  return inb(SERIAL_LINE_STATUS_PORT(com)) & 0x20;
}

void serial_write(severity level, char *buf, unsigned int len) {
  char lvl_strings[3][10] = {"DEBUG: ", "INFO: ", "ERROR: "};
  unsigned int lvl_lens[3] = {7, 6, 7};

  for (unsigned int i = 0; i < lvl_lens[level] + len; i++) {
    while (!serial_is_transmit_fifo_empty(SERIAL_COM1_BASE))
      ;

    if (i < lvl_lens[level]) {
      outb(SERIAL_DATA_PORT(SERIAL_COM1_BASE), lvl_strings[level][i]);
    } else {
      outb(SERIAL_DATA_PORT(SERIAL_COM1_BASE), buf[i-lvl_lens[level]]);
    }
  }
}

// TODO: implement serial_prinft
