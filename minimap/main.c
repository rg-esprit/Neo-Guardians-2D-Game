#include <SDL/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL_image.h>
#include "minimap.h"
#include "background.h"
#include "player.h"
#include "timer.h"
#include <SDL/SDL_ttf.h>

int main(int argc, char* argv[])
{
 SDL_Init(SDL_INIT_VIDEO);
 SDL_Surface *screen;
 char ti[200]="";
 Time t;
 TTF_Init();
 SDL_Rect camera,pos_person;
 pos_person.x=0;
 pos_person.y=385;
 Background back1;
 player hero;
 minimap minimap1,minihero;
 int done=0,way,resize=20;
 screen=SDL_SetVideoMode(1200,800,32,SDL_HWSURFACE | SDL_DOUBLEBUF);
 

 if(!screen)
      {
             return 1;
      }
initback(&back1);
init_minimap(&minimap1);
init_minimap(&minihero);
initializerTime(&t);
initPlayer(&hero);
blit_minimap(minimap1,screen);
blit_minimap(minihero,screen);
displayback(back1,screen);
displayPlayer(hero,screen);
displayTime(&t,screen);
SDL_Flip(screen);
 while(done==0){
displayback(back1,screen);
displayTime(&t,screen);
MAJMinimap(pos_person,&minimap1,camera,resize,way);
blit_minimap(minimap1,screen);
//blit_minimap(minihero,screen);
displayPlayer(hero,screen);
//display_time(&tex,&t,screen);
SDL_Flip(screen);
  SDL_Event event;
  SDL_PollEvent(&event);


  switch (event.type)
			{
				case SDL_QUIT:
					done=1;
					break;
        case SDL_KEYDOWN:
                  switch(event.key.keysym.sym){
                   case SDLK_d:
                   displayback(back1,screen);
                   displayTime(&t,screen);
                   front(&hero);

                   pos_person.x+=30;
                   way=0;
                   MAJMinimap(pos_person,&minimap1,camera,resize,way);
                   blit_minimap(minimap1,screen);
                   displayPlayer(hero,screen);
                   SDL_Flip(screen);
                   SDL_Delay(50);
                   displayTime(&t,screen);
                   break;
                   case SDLK_q:
                    displayback(back1,screen);
                   displayTime(&t,screen);
                   back(&hero);

                   pos_person.x-=30;
                   way=1;
                   MAJMinimap(pos_person,&minimap1,camera,resize,way);
                   blit_minimap(minimap1,screen);
                   displayPlayer(hero,screen);
                   SDL_Flip(screen);
                   SDL_Delay(50);
                   //updatetime(&t);

                   break;
                   
                  }


}





  }
free_background(back1);
free_minimap(minimap1);
freePlayer(hero);
SDL_Quit();
return 0;
}
