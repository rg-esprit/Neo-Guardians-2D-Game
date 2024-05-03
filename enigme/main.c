#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include "enigmetf.h"
#define TEMPS_LIMITE 10000 // Durée maximale de 10 secondes (exprimée en millisecondes)
int main()
{
	
	SDL_Surface * ecran=NULL;
	ecran = SDL_SetVideoMode(1000,1000, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
	int continuer=1;
	SDL_Event event;
   int var=0;
	SDL_Surface *win;
	SDL_Surface *lost;
	SDL_Rect pos;//={160,330}; 
        pos.x=160;
       pos.y=330;
	 Enigme e;
	InitEnigme(&e);
	win=IMG_Load("img/youwin.png");
	lost=IMG_Load("img/youlost.png");
Uint32 start_time; // Variable pour stocker le temps de début
    start_time = SDL_GetTicks(); // Enregistrer le temps de début



	while(continuer){
if(var==0){	
 		animerEnigme(&e);
 	
}

		afficherEnigme(e,ecran);
	
		while (SDL_PollEvent(&event)) //SDL_WaitEvent(&event)  
		{
			switch (event.type)
			{
				case SDL_QUIT:
				{	
                                   continuer=0;

				}
				case SDL_KEYDOWN:
				switch(event.key.keysym.sym)
				{	
					case SDLK_a:
					e.pos_selected=1;
					break ; 
					
					case SDLK_b:
					e.pos_selected=2;
					break ; 
					
					case SDLK_c:
					e.pos_selected=3;
					break ; 
					
					case SDLK_RETURN:

                                          winLost(e,ecran);
							
						return 0;
					break ; 

				}break;
				case SDL_MOUSEMOTION:
				{
					//printf("Souris en position %d %d\n",event.motion.x, event.motion.y);
				}
			case SDL_MOUSEBUTTONUP:
				{
					if((event.motion.x>375 && event.motion.x<375+321)&&(event.motion.y>520 && event.motion.y<520+91))
					{
						e.pos_selected=1;
						if (event.button.button == SDL_BUTTON_LEFT)
						{
							 winLost(e,ecran);
							return 0;
						} 	 
					}
					else if((event.motion.x>178 && event.motion.x<178+321)&&(event.motion.y>649 && event.motion.y<649+91))
					{
						e.pos_selected=2;
						if (event.button.button == SDL_BUTTON_LEFT)
						{	
 winLost(e,ecran);

							return 0;
						} 
					}
					else if((event.motion.x>568 && event.motion.x<568+321)&&(event.motion.y>656 && event.motion.y<656+91))
					{
						e.pos_selected=3;
						if (event.button.button == SDL_BUTTON_LEFT)
						{
							 winLost(e,ecran);
							return 0;
						} 					
					}
				}
				break;
			}
		}
		 
		if(e.positionVraiReponse==e.pos_selected)
		{
		e.win=1;
		}
		else
		{
		e.win=0;
		}

 // Si le temps est écoulé
    if (SDL_GetTicks() - start_time >= TEMPS_LIMITE)
    {
        var=1;
        SDL_BlitSurface(lost, NULL, ecran, &pos);
        SDL_Flip(ecran);
        printf("You lost, time's up!\n");
        SDL_Delay(1000);
return 0;
    }
		}

		
}



