#include <stdio.h>
#include "SDL/SDL.h"
#include <string.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#include"header.h"

int main()
{
	SDL_Surface *ecran =NULL;
	SDL_Surface *porte[10],*owl[12];
	SDL_Rect back,port,owll ;
        SDL_Event event;



	
	TTF_Init();
	TTF_Font*police=TTF_OpenFont("arial.ttf",40);
	int score=0;







	char scoreTxt[20];
	printf("%s\n",TTF_GetError());
	SDL_Color color={255,255,255};
	SDL_Surface * text;
	SDL_Rect scoreRect={0,0,0,0};















	int continuer =1;
	int coe;
	int c,i,j;
	background b;
	hero evan ;
	evan.farm=0;
	Mix_Music *music=NULL;
   SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER);
   ecran = SDL_SetVideoMode(1920, 1080, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
   initBack(&b);
   initialiser_evan(&evan);


	FILE*fl=NULL;
	fl=fopen("neo.txt","r");
	if(fl!=NULL){
		if(fscanf(fl,"%d\n",&score)!=0){
			fscanf(fl,"%d\n",&b.nbVie);
		}
		fclose(fl);
	}


	sprintf(scoreTxt,"score: %d",score);
	text=TTF_RenderText_Blended(police,scoreTxt,color);
	SDL_BlitSurface(text,NULL,ecran,&scoreRect);

/*
	Uint32 prev=SDL_GetTicks();
	Uint32 current;
*/


   //animerBackground (&b,ecran);
	while(continuer){	
		/*
		current=SDL_GetTicks();
		if(current-prev>=2000){
			prev=current;
			score+=5;
			sprintf(scoreTxt,"score: %d",score);
			text=TTF_RenderText_Blended(police,scoreTxt,color);
		}
		*/
		


        	while(SDL_PollEvent(&event)){
        	switch(event.type){
        		case SDL_QUIT:
        			continuer=0;
        			break;
        		case SDL_KEYDOWN:

					score+=5;
					sprintf(scoreTxt,"score: %d",score);
					text=TTF_RenderText_Blended(police,scoreTxt,color);
        			switch(event.key.keysym.sym){

						case SDLK_x:
							continuer=0;

							FILE*f=NULL;
							f=fopen("neo.txt","w");
							if(f!=NULL){
								fprintf(f,"%d\n",score);
								fprintf(f,"%d\n",b.nbVie);
								fclose(f);
							}

							break;

        				case SDLK_k:
        					b.nbVie--;
							afficherBack(b,ecran);
							SDL_Flip(ecran);
							if(b.nbVie==0){
								continuer=0;
								remove("neo.txt");
							}
        					break;

						case SDLK_c:
							remove("neo.txt");
							score=0;
							sprintf(scoreTxt,"score: %d",score);
							text=TTF_RenderText_Blended(police,scoreTxt,color);
							break;
        			}
        			break;
        		}
		}
			afficherBack(b,ecran);







			SDL_BlitSurface(text,NULL,ecran,&scoreRect);



			afficher_evan(evan,ecran);		
			evan.mouvment= mouvment(evan,&event);				
			scrolling(&evan,&b,c);	
			c=collisionPP(b.calque_background,evan.afficher_hero[evan.farm],evan.pos_hero2,b.pos_background2);
			
			SDL_Flip(ecran);
	//SDL_Delay(20);
	
	}
return 0;	
}
