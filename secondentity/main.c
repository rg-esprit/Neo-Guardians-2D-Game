#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
int main()
{
Ennemi e;
entite en;
SDL_Rect pos,posp; 
SDL_Surface *ecran,*bg,*perso;
SDL_Event event;
int bfin = 0;
TTF_Init();
if (SDL_Init(SDL_INIT_VIDEO ) < 0)
	{
		fprintf(stderr, "Echec d'initialisation de SDL.\n");
		return 1;
	}
  printf("Bonjour le monde, SDL est initialise avec succes.\n");

  ecran = SDL_SetVideoMode(620, 250, 32, SDL_HWSURFACE);

  if ( ecran == NULL )
	{
		fprintf(stderr, "Echec de changement du mode video : %s.\n", SDL_GetError());
		return 1;
	}
  bg = IMG_Load("lvl1.png");
	perso= IMG_Load ("0.png");
	pos.x=0;
	pos.y=0;
	posp.x=0;
	posp.y=150;
	posp.w = perso->w;
	posp.h = perso->h;

  initEnnemi(&e);
  init_entite(&en);
  int score=0;

  while (!bfin){
    //SDL_WaitEvent(&event);
    SDL_PollEvent(&event);

    //while (SDL_PollEvent(&event)){
      switch(event.type)
      {
        case SDL_QUIT:
          bfin = 1;
          break;
				case SDL_KEYDOWN:
					switch(event.key.keysym.sym)
					{

						case SDLK_ESCAPE:
							bfin=1;
							break;
						case SDLK_UP:
							posp.y=posp.y-4;
							break;
						case SDLK_DOWN:
							posp.y=posp.y+4;
							break;
						case SDLK_RIGHT:
							posp.x=posp.x+4;
							break;
						case SDLK_LEFT:
							posp.x=posp.x-4;
							break;
					}

					break ;
      }
    //}


    SDL_BlitSurface(bg, NULL, ecran, &pos);
    afficherEnnemi(e,ecran);
    move(&e);
    moveAI(&e,posp);
    afficher_entite(en,ecran);
    animer_entite(&en);
    afficher_score(score,ecran);
	
	
if (collisionTRI(en.pos,posp)) {if(en.affichage==1) score+=3; en.affichage=0;}
		SDL_BlitSurface(perso, NULL, ecran, &posp);
    SDL_Flip(ecran);
		if (collisionBB(perso,posp,e)==1){
score--;
	posp.x=0;
	posp.y=150;
  	

if(score==0)bfin = 1 ;
		}

SDL_Delay(80); 

  }

  SDL_Quit();

  return 0;
}
