#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#include"header.h"
#include "/home/rg/Desktop/Neo-Guardians/perso/perso.h"


void initBack(background *b) 
{
    Mix_Music *music;

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1) 
    {
        printf("Mix_OpenAudio error: %s\n", Mix_GetError());
        return;
    }

    // music = Mix_LoadMUS("background/map1.mp3");
    // if (!music) 
    // {
    //     printf("Mix_LoadMUS error: %s\n", Mix_GetError());
    //     return;
    // }

    // if (Mix_PlayMusic(music, -1) == -1) 
    // {
    //     printf("Mix_PlayMusic error: %s\n", Mix_GetError());
    //     return;
    // }

    char ch[50];
    int i, j;
    char chh[50];

    for (j = 1; j < 6; j++) 
    {
        sprintf(ch, "background/dhaw/%d.png", j);
        b->porte[j] = IMG_Load(ch);
        if (!b->porte[j]) 
        {
            printf("IMG_Load error for %s: %s\n", ch, IMG_GetError());
        }
    }

    for (i = 1; i < 12; i++) 
    {
        sprintf(chh, "background/owl2/%d.png", i);
        b->owl[i] = IMG_Load(chh);
        if (!b->owl[i]) 
        {
            printf("IMG_Load error for %s: %s\n", chh, IMG_GetError());
        }
    }

    b->calque_background = IMG_Load("background/masque.png");
    if (!b->calque_background) 
    {
        printf("IMG_Load error for background/masque.png: %s\n", IMG_GetError());
    }

    b->afficher_background = IMG_Load("background/map1.png");
    if (!b->afficher_background) 
    {
        printf("IMG_Load error for background/map1.png: %s\n", IMG_GetError());
    }

    b->aff = IMG_Load("background/map1.png");
    
    if (!b->aff) 
    {
        printf("IMG_Load error for background/map.png: %s\n", IMG_GetError());
    }

    b->pos_background.x = 0;
    b->pos_background.y = 0;
    b->pos_background2.x = 0;
    b->pos_background2.y = 0;
    b->pos_background2.h = 1080;
    b->pos_background2.w = 1920;
    b->port.x = 0;
    b->port.y = 0;
    b->owll.x = 0;
    b->owll.y = 0;

    b->nbVie = 3;
    b->heart = IMG_Load("background/heart.png");
    if (!b->heart) 
    {
        printf("IMG_Load error for background/heart.png: %s\n", IMG_GetError());
    }

    SDL_Rect hrect = {1560, 0, 0, 0};
    b->rectheart = hrect;
}

void afficherBack(background b, SDL_Surface *ecran) 
{
    SDL_Rect rect = {1560, 0, 0, 0};

    if (SDL_BlitSurface(b.afficher_background, &(b.pos_background2), ecran, &(b.pos_background)) < 0) 
    {
        printf("SDL_BlitSurface error: %s\n", SDL_GetError());
    }

    for (int i = 0; i < b.nbVie; i++) 
    {
        if (SDL_BlitSurface(b.heart, NULL, ecran, &rect) < 0) 
        {
            printf("SDL_BlitSurface error for heart: %s\n", SDL_GetError());
        }
        rect.x += 120;
    }
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

