#include "entite.h"

void init_entite(entite * p) //initialisation de tout les attributs
{
  ( * p).d_h = 0;
  ( * p).d_v = 0;
  ( * p).affichage = 1;
  ( * p).pos.x = 400;
  ( * p).pos.y = 0;
  ( * p).sprite.x = 0;
  ( * p).sprite.y = 0;
  ( * p).sprite_n = 0;
  ( * p).speed = 1;
  ( * p).image = IMG_Load("mini-coin.png");
  ( * p).pos.w = ( * p).image -> w/6;
  ( * p).pos.h = ( * p).image -> h;
  ( * p).sprite.w = ( * p).image -> w/6;
  ( * p).sprite.y = 0;
  ( * p).sprite.h = ( * p).image -> h;
}
void afficher_entite(entite p, SDL_Surface * screen) {
if (p.affichage == 1)
    SDL_BlitSurface(p.image, & p.sprite, screen, & p.pos);
//l image qu'on doit afficher, la partie qu'on va couper, surface sur la quelle on va afficher, dans quelle position
}
void animer_entite(entite * p) //change l image à afficher
{
    ( * p).sprite_n++;
    if (( * p).sprite_n >= 6) {
      ( * p).sprite_n = 0;
    }

    ( * p).sprite.x = ( * p).pos.w * ( * p).sprite_n;
}
void mouvement_aleatoire_entite(entite *p)
{
if (( * p).pos.x % 100<( * p).speed) ( * p).d_h=rand()%2;
if(( * p).pos.x<0) ( * p).d_h=0;
if(( * p).pos.x>500) ( * p).d_h=1;
if (( * p).d_h==1) ( * p).pos.x-=( * p).speed;
else ( * p).pos.x+=( * p).speed;

if (( * p).pos.y % 100<( * p).speed) ( * p).d_v=rand()%2;
if(( * p).pos.y<0) ( * p).d_v=0;
if(( * p).pos.y>220) ( * p).d_v=1;
if (( * p).d_v==1) ( * p).pos.y-=( * p).speed;
else ( * p).pos.y+=( * p).speed;
}

int collisionTRI(SDL_Rect x1,SDL_Rect x2)
{
int r1,r2;//rayons de x1 et x2
if (x1.w>x1.h) r1 = x1.w/2;
else r1 = x1.h/2;
if (x2.w>x2.h) r2 = x2.w/2;
else r2 = x2.h/2;
int distance = sqrt( (x2.y - x1.y)*(x2.y - x1.y) + (x2.x - x1.x)*(x2.x - x1.x) );
if(r1+r2>distance) return 1;
return 0;
}
