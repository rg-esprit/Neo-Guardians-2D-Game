# Compiler and linker flags
CFLAGS=-c -fPIE
LDFLAGS=-pie

# Executable name
TARGET=prog

# Source files
SOURCES=main.c enigmetf.c
OBJECTS=$(SOURCES:.c=.o)

# Default target
all: $(TARGET)

# Linking the program
$(TARGET): $(OBJECTS)
	gcc $(LDFLAGS) $(OBJECTS) -o $(TARGET) -lSDL -lSDL_ttf -lSDL_mixer -lSDL_image

# Compiling source files
%.o: %.c
	gcc $(CFLAGS) $< -o $@

# Cleaning up
clean:
	rm -f $(OBJECTS) $(TARGET)
