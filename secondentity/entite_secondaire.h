#include "def.h"
typedef struct Ennemi
{
  SDL_Surface *image[12];
  SDL_Rect position;
  int direction;
  int numIM;
  int status;

}Ennemi;

void initEnnemi(Ennemi *e);
void afficherEnnemi (Ennemi e,SDL_Surface *ecran);
void animerEnnemi (Ennemi *e);
void deplacer(Ennemi *e);
int collision (SDL_Surface *p,SDL_Rect posp,Ennemi e);
void deplacerAI(Ennemi *e,SDL_Rect pos);
