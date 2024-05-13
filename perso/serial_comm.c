// serial_comm.c

#include "serial_comm.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <pthread.h>
#include "perso.h"

void trim_newline(char *str) {
    char *ptr;
    if ((ptr = strchr(str, '\n')) != NULL) {
        *ptr = '\0';
    }
    if ((ptr = strchr(str, '\r')) != NULL) {
        *ptr = '\0';
    }
}

void *serial_thread_func(void *arg) {
    ThreadParams* params = (ThreadParams*)arg;
    Personne* p = params->p;
    struct sp_port* port = params->port;
    char buffer[1024];

    while (1) {
        int bytes_read = read_from_serial_port(port, buffer, sizeof(buffer));
        if (bytes_read > 0) {
            buffer[bytes_read] = '\0';
            trim_newline(buffer);
            
            // Print messages corresponding to received commands
            if (strcmp(buffer, "L") == 0) {
                p->directions = 1;
                p->move_left = 1;
                (*p).move_right = 0;
            } else if (strcmp(buffer, "R") == 0) {
                (*p).directions = 0;
                (*p).move_right = 1;
                p->move_left = 0;
            } else if (strcmp(buffer, "Up") == 0) {
                if (p->up == 0) {
                    p->up = 1;
                }
                
            } else if (strcmp(buffer, "C") == 0) {
                p->move_right = 0;
                p->move_left = 0;
            } else if (strcmp(buffer, "S") == 0) {
                swapCharacter(p);
            }
        }
    }

    return NULL;
}

int open_serial_port(const char *port_name, struct sp_port **port) {
    enum sp_return result = sp_get_port_by_name(port_name, port);
    if (result != SP_OK) {
        printf("Error finding serial port\n");
        return -1;
    }

    result = sp_open(*port, SP_MODE_READ);
    if (result != SP_OK) {
        printf("Error opening serial port\n");
        sp_free_port(*port);
        return -1;
    }

    // Set baud rate
    sp_set_baudrate(*port, 115200);
    return 0;
}

void close_serial_port(struct sp_port *port) {
    sp_close(port);
    sp_free_port(port);
}

int read_from_serial_port(struct sp_port *port, char *buf, int buf_size) {
    int bytes_read = sp_blocking_read(port, buf, buf_size - 1, 1);
    if (bytes_read > 0) {
        buf[bytes_read] = '\0'; // Null-terminate the string
    }
    return bytes_read;
}
