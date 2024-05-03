// serial_comm.h

#ifndef SERIAL_COMM_H
#define SERIAL_COMM_H

#include <libserialport.h>

int open_serial_port(const char *port_name, struct sp_port **port);
void close_serial_port(struct sp_port *port);
int read_from_serial_port(struct sp_port *port, char *buf, int buf_size);
void *serial_thread_func(void *arg);

#endif
