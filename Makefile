# Define compiler
CC=gcc
# Define compiler flags
CFLAGS=-g -I./Menu
# Define linker flags
LDFLAGS=-lSDL -lSDL_ttf -lSDL_image -lSDL_mixer

# Define the executable output
EXEC=prog

# Define objects
OBJS=main.o Menu/main.o

# Rule to make the executable
$(EXEC): $(OBJS)
	$(CC) -o $(EXEC) $(OBJS) $(LDFLAGS)

# Rule to make main.o in the root directory
main.o: main.c
	$(CC) -c main.c -o main.o $(CFLAGS)

# Rule to make main.o in the Menu directory
Menu/main.o: Menu/main.c Menu/menu.h
	$(CC) -c Menu/main.c -o Menu/main.o $(CFLAGS)

# Clean objects in the project
clean:
	rm -f $(OBJS) $(EXEC)
