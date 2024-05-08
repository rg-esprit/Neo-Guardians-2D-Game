#ifndef _BONUS_H_
#define _BONUS_H_
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

typedef struct
{
SDL_Rect pos;
SDL_Rect sprite;
SDL_Surface *image;
int sprite_n;
int d_h;
int d_v;
int speed;
int affichage;
}entite; 

void init_entite(entite *p);
void afficher_entite(entite p,SDL_Surface *screen);
void animer_entite(entite *p);
int collisionTRI(SDL_Rect x1,SDL_Rect x2);
void afficher_score(int score, SDL_Surface * screen);

#endif
