
prog:main.o background.o collisionPP.o evan.o mouvment.o scrolling.o
	gcc  main.o background.o collisionPP.o evan.o mouvment.o scrolling.o -o prog -lSDL -lSDL_image -lSDL_ttf -lSDL_mixer -g
main.o:main.c 
	gcc -c main.c -lSDL -lSDL_image -lSDL_mixer -g
collisionPP.o:collisionPP.c 
	gcc -c collisionPP.c -lSDL -lSDL_image -lSDL_mixer -g
mouvment.o:mouvment.c 
	gcc -c mouvment.c -lSDL -lSDL_image -lSDL_mixer -g
evan.o:evan.c 
	gcc -c evan.c -lSDL -lSDL_image -lSDL_mixer -g
	
background.o:background.c
	gcc -c background.c -lSDL -lSDL_image -lSDL_mixer -g
	
scrolling.o:scrolling.c 
	gcc -c scrolling.c -lSDL -lSDL_image -lSDL_mixer -g


