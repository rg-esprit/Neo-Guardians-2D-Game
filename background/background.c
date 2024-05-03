#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#include"header.h"


void initBack(background *b) 
{

	Mix_Music  *music; 
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1) 
    	{
        	printf("%s", Mix_GetError()); 
    	}
	music = Mix_LoadMUS("map1.mp3"); 	
	Mix_PlayMusic(music,-1) ; 

    char ch[50];
    int i,j;
    char chh[50];


	    for(j=1; j<10; j++) 
    {
        sprintf(ch,"../Background2/dhaw/%d.png",j);
        b->porte[j]=IMG_Load(ch);
    }
    for(i=1; i<12; i++)
    {
        sprintf(chh,"../Background2/owl2/%d.png",i);
        b->owl[i]=IMG_Load(chh);
    }

	b->calque_background=NULL;
	b->calque_background=IMG_Load("masque.png");  
	b->afficher_background=NULL;
	b->afficher_background=IMG_Load("map1.png");
	b->aff=NULL;
	b->aff=IMG_Load("map.png");
	b->pos_background.x=0;
	b->pos_background.y=0;
	b->pos_background2.x=0;
	b->pos_background2.y=0;
	b->pos_background2.h=1020;
	b->pos_background2.w=1920;
	b->port.x=  0 ;  //cor la fenêtre de visualisation 
        b->port.y=  0 ;
        b->owll.x=  0 ;
        b->owll.y=  0 ;
}


void afficherBack(background b,SDL_Surface *ecran) 
{	
	SDL_BlitSurface(b.afficher_background,&(b.pos_background2),ecran,&(b.pos_background)); 
}


void animerBackground (background *b,SDL_Surface *ecran) 
{   
    int j; 
    char ch[50]; 
    int i; 
    char chh[50];
     SDL_BlitSurface(b->aff,NULL,ecran,&(b->port));
    for(j=1; j<10; j++)
    {
        SDL_BlitSurface( b->porte[j], NULL,ecran,&(b->port));  
        SDL_Flip(ecran); 
        SDL_Delay(130);  
    }
SDL_Delay(1000);
SDL_BlitSurface(b->aff,NULL,ecran,&(b->port));
    for(j=1; j<12; j++)
    {
        SDL_BlitSurface( b->owl[j], NULL,ecran,&(b->owll));
        SDL_Flip(ecran);
        SDL_Delay(130);
    }
SDL_Delay(2000);
    for(j=1; j<12; j++)
    {
        SDL_BlitSurface( b->owl[j], NULL,ecran,&(b->owll));
        SDL_Flip(ecran);
        SDL_Delay(130);
    }

}

