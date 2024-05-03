#ifndef _ENTITE_H_
#define _ENTITE_H_
#include <SDL/SDL_image.h>
#include <SDL/SDL.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

typedef struct
{
SDL_Rect pos;
SDL_Rect sprite;
SDL_Surface *image;
int sprite_n;//current sprite
int d_h;//direction horizontale
int d_v;//direction verticale
int speed;
int affichage;//affichée ou non
}entite;

void init_entite(entite *p);
void afficher_entite(entite p,SDL_Surface *screen);
void animer_entite(entite *p);
void mouvement_aleatoire_entite(entite *p);
int collisionTRI(SDL_Rect x1,SDL_Rect x2);

#endif
