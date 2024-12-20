#ifndef INCLUDE_SERIAL_H
#define INCLUDE_SERIAL_H

/* I/O ports */
#define SERIAL_COM1_BASE 0x3F8

#define SERIAL_DATA_PORT(base) (base)
#define SERIAL_FIFO_COMMAND_PORT(base) (base + 2)
#define SERIAL_LINE_COMMAND_PORT(base) (base + 3)
#define SERIAL_MODEM_COMMAND_PORT(base) (base + 4)
#define SERIAL_LINE_STATUS_PORT(base) (base + 5)

/* I/O port commands */

/* Expect first the highest 8 bits on the data port, then the lowest 8 bits */
#define SERIAL_LINE_ENABLE_DLAB 0x80

typedef enum {DEBUG, INFO, ERROR} severity;

/**
 * Sets the speed of the data being sent. The default speed of a serial
 * port is 115200 bits/s. The argument is a divisor of that number, hence
 * the resulting speed becomes (115200 / divisor) bits/s.
 *
 * @param com The COM port to configure
 * @param divisor The divisor
 */
void serial_configure_baud_rate(unsigned short com, unsigned short divisor);

/**
 * Configures the line of the given serial port. The port is set to have a
 * data length of 8 bits, no parity bits, one stop bit and break control
 * disabled.
 *
 * @param com The serial port to configure
 */
void serial_configure_line(unsigned short com);

void serial_configure(unsigned short com, unsigned short divisor);

/**
 * Checks whether the transmit FIFO queue is empty or not for the given COM
 * port.
 *
 * @param  com The COM port
 * @return 0 if the transmit FIFO queue is not empty
 *         1 if the transmit FIFO queue is empty
 */
int serial_is_transmit_fifo_empty(unsigned int com);

/**
 * Writes the contents of the buffer of lenght len to the serial port
 *
 * @param buf
 * @param len
 * @return Number of characters written
 */
void serial_write(severity level, char *buf, unsigned int len);

#endif
