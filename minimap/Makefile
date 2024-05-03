prog:main.o minimap.o background.o player.o time.o 
	gcc main.o minimap.o background.o player.o time.o -o prog -lSDL -lSDL_ttf -g -lSDL_image -lSDL_mixer
main.o:main.c
	gcc -c main.c -g
minimap.o:minimap.c
	gcc -c minimap.c -g
background.o:background.c
	gcc -c background.c -g
player.o:player.c
	gcc -c player.c -g
time.o:time.c
	gcc -c time.c -g

