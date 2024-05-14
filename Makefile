# Define the compiler
CC=gcc

# Define compiler flags, include directories for your headers
CFLAGS=-g -Wall -I$(CURDIR)/Menu -I$(CURDIR)/perso -I$(CURDIR)/background -I$(CURDIR)/minimap -I$(CURDIR)/secondentity


# Define linker flags, include libraries needed (SDL, pthread, and serialport)
LDFLAGS=-lSDL -lSDL_ttf -lSDL_image -lSDL_mixer -lpthread -lserialport -lm

# Define the executable output file
EXEC=prog

# Define all object files that are required for the final executable
OBJS=main.o \
     Menu/main.o \
     perso/main.o \
     perso/serial_comm.o \
     background/background.o \
     background/collisionPP.o \
     background/evan.o \
     background/mouvment.o \
	 secondentity/bonus.o \
	 secondentity/ennemi.o \
	 minimap/minimap.o \
     background/scrolling.o

# Rule to make the executable
$(EXEC): $(OBJS)
	$(CC) $(OBJS) -o $(EXEC) $(LDFLAGS)

# Rule for compiling the main.o in the root directory
main.o: main.c
	$(CC) $(CFLAGS) -c main.c -o main.o

# Rule for compiling main.o in the Menu directory
Menu/main.o: Menu/main.c Menu/menu.h
	$(CC) $(CFLAGS) -c Menu/main.c -o Menu/main.o

# Rules for perso
perso/main.o: perso/main.c perso/perso.h
	$(CC) $(CFLAGS) -c perso/main.c -o perso/main.o

perso/serial_comm.o: perso/serial_comm.c perso/serial_comm.h
	$(CC) $(CFLAGS) -c perso/serial_comm.c -o perso/serial_comm.o

# Rules for background
background/background.o: background/background.c background/header.h
	$(CC) $(CFLAGS) -c background/background.c -o background/background.o

background/collisionPP.o: background/collisionPP.c background/header.h
	$(CC) $(CFLAGS) -c background/collisionPP.c -o background/collisionPP.o

background/evan.o: background/evan.c background/header.h
	$(CC) $(CFLAGS) -c background/evan.c -o background/evan.o

background/mouvment.o: background/mouvment.c background/header.h
	$(CC) $(CFLAGS) -c background/mouvment.c -o background/mouvment.o

background/scrolling.o: background/scrolling.c background/header.h
	$(CC) $(CFLAGS) -c background/scrolling.c -o background/scrolling.o

minimap/minimap.o: minimap/minimap.c minimap/minimap.h
	$(CC) $(CFLAGS) -c minimap/minimap.c -o minimap/minimap.o

secondentity/ennemi.o: secondentity/ennemi.c secondentity/ennemi.h
	$(CC) $(CFLAGS) -c secondentity/ennemi.c -o secondentity/ennemi.o

secondentity/bonus.o: secondentity/bonus.c secondentity/bonus.h
	$(CC) $(CFLAGS) -c secondentity/bonus.c -o secondentity/bonus.o

# Clean rule to clean up object files and the executable
clean:
	rm -f $(OBJS) $(EXEC)
