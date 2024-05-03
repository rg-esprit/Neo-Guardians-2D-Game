# Compiler and linker configurations
CC = gcc
CFLAGS = -Wall -g
# Link against SDL, SDL_image, and libserialport
LDFLAGS = -lSDL -lSDL_image -lserialport -pthread


# Source files
SOURCES = main.c serial_comm.c
OBJECTS = $(SOURCES:.c=.o)
EXECUTABLE = game

# Default target
all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@ $(LDFLAGS)

# To obtain object files
%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

# Clean up
clean:
	rm -f $(OBJECTS) $(EXECUTABLE)

# Phony targets
.PHONY: all clean
