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
void move(Ennemi *e);
int collisionBB (SDL_Surface *p,SDL_Rect posp,Ennemi e); 
void moveAI(Ennemi *e,SDL_Rect pos);
