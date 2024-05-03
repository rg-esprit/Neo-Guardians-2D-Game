#include <stdio.h>
#include "SDL/SDL.h"
#include <string.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include"header.h"
int main()
{
	SDL_Surface *ecran =NULL;
	SDL_Surface *porte[10],*owl[12];
	SDL_Rect back,port,owll ;
        SDL_Event event;
	int continuer =1;
	int coe;
	int c,i,j;
	background b;
	hero evan ;
	evan.farm=0;
	Mix_Music *music=NULL;
   SDL_Init(SDL_INIT_VIDEO);
   ecran = SDL_SetVideoMode(1920, 1080, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
   initBack(&b);
   initialiser_evan(&evan);
   animerBackground (&b,ecran);
	
	while(continuer)
        {
			afficherBack(b,ecran);
			afficher_evan(evan,ecran);			
			SDL_Flip(ecran);
			evan.mouvment= mouvment(evan,&event);				
			scrolling(&evan,&b,c);	
			c=collisionPP(b.calque_background,evan.afficher_hero[evan.farm],evan.pos_hero2,b.pos_background2);		
	SDL_Delay(20);
	
	}
return 0;	
}
