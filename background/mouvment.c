#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#include"header.h"
 int mouvment(hero evan,SDL_Event *event) 
{

 	int mouvment;

 	SDL_PollEvent(event);
 	switch (event->type)
        {
   
        case SDL_KEYDOWN: 
            switch (event->key.keysym.sym)
            {
            case SDLK_RIGHT: 
                break;
            case SDLK_LEFT:
            	mouvment=2;
                break;
            case SDLK_UP: 
                mouvment=3;  
                 break;
            case SDLK_DOWN:
		mouvment=4;
                 break;
            }
            break;
             default: 	mouvment=9;
 }
 return mouvment;
}
