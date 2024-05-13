#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#include"header.h"

void initialiser_evan(hero *evan) 
{		
		evan->afficher_hero[0]=NULL;
		evan->afficher_hero[0]=IMG_Load("background/1.png");
		evan->pos_hero2.x=120;
		evan->pos_hero2.y=675;
		evan->farm=0;
}


void afficher_evan(hero evan,SDL_Surface *ecran)
{
		SDL_BlitSurface(evan.afficher_hero[0],NULL,ecran,&(evan.pos_hero2));
}
