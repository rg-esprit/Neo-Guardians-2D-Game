// serial_comm.c

#include "serial_comm.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <linux/uinput.h>
#include <unistd.h>
#include <pthread.h>
#include "perso.h"

#define KEY_RELEASE 0
#define KEY_PRESS 1

void trim_newline(char *str) {
    char *ptr;
    if ((ptr = strchr(str, '\n')) != NULL) {
        *ptr = '\0';
    }
    if ((ptr = strchr(str, '\r')) != NULL) {
        *ptr = '\0';
    }
}

void send_key_event(int fd, int keycode, int keyvalue) {
    struct input_event ev;
    memset(&ev, 0, sizeof(struct input_event));

    ev.type = EV_KEY;
    ev.code = keycode;
    ev.value = keyvalue;
    write(fd, &ev, sizeof(struct input_event));

    // Syn event to ensure the key event is processed
    ev.type = EV_SYN;
    ev.code = SYN_REPORT;
    ev.value = 0;
    write(fd, &ev, sizeof(struct input_event));
}

void setup_uinput_device(int *fd) {
    struct uinput_user_dev uidev;

    *fd = open("/dev/uinput", O_WRONLY | O_NONBLOCK);
    if (*fd < 0) {
        fprintf(stderr, "Failed to open uinput device\n");
        return;
    }

    ioctl(*fd, UI_SET_EVBIT, EV_KEY);
    ioctl(*fd, UI_SET_KEYBIT, KEY_LEFT);
    ioctl(*fd, UI_SET_KEYBIT, KEY_RIGHT);
    ioctl(*fd, UI_SET_KEYBIT, KEY_UP);

    memset(&uidev, 0, sizeof(uidev));
    snprintf(uidev.name, UINPUT_MAX_NAME_SIZE, "uinput-sample");
    write(*fd, &uidev, sizeof(uidev));

    if (ioctl(*fd, UI_DEV_CREATE) < 0) {
        fprintf(stderr, "Failed to create uinput device\n");
        close(*fd);
    }
}

void *serial_thread_func(void *arg) {
    ThreadParams* params = (ThreadParams*)arg;
    int uinput_fd;

    setup_uinput_device(&uinput_fd);

    struct sp_port* port = params->port;
    char buffer[1024];
    int left_pressed = 0;
    int right_pressed = 0;

    while (1) {
        int bytes_read = read_from_serial_port(port, buffer, sizeof(buffer));
        if (bytes_read > 0) {
            buffer[bytes_read] = '\0';
            trim_newline(buffer);

            if (strcmp(buffer, "Left") == 0) {
                if (!left_pressed) {
                    send_key_event(uinput_fd, KEY_LEFT, KEY_PRESS);
                    left_pressed = 1;
                }
            } else if (strcmp(buffer, "Right") == 0) {
                if (!right_pressed) {
                    send_key_event(uinput_fd, KEY_RIGHT, KEY_PRESS);
                    right_pressed = 1;
                }
            } else if (strcmp(buffer, "Up") == 0) {
                send_key_event(uinput_fd, KEY_UP, KEY_PRESS);
                send_key_event(uinput_fd, KEY_UP, KEY_RELEASE);
            } else if (strcmp(buffer, "C") == 0) {
                if (left_pressed) {
                    send_key_event(uinput_fd, KEY_LEFT, KEY_RELEASE);
                    left_pressed = 0;
                }
                if (right_pressed) {
                    send_key_event(uinput_fd, KEY_RIGHT, KEY_RELEASE);
                    right_pressed = 0;
                }
            }
        }
    }

    ioctl(uinput_fd, UI_DEV_DESTROY);
    close(uinput_fd);
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
    int bytes_read = sp_blocking_read(port, buf, buf_size - 1, 50);
    if (bytes_read > 0) {
        buf[bytes_read] = '\0'; // Null-terminate the string
    }
    return bytes_read;
}
