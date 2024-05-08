CFLAGS = -no-pie

prog: main.o enigmetf.o
	gcc $(CFLAGS) main.o enigmetf.o -o prog -lSDL -lSDL_ttf -lSDL_mixer -lSDL_image

main.o: main.c
	gcc $(CFLAGS) -c main.c

enigmetf.o: enigmetf.c
	gcc $(CFLAGS) -c enigmetf.c

