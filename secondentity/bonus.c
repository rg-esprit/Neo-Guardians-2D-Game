#include "bonus.h"

void init_entite(entite * p) 
{
  ( * p).d_h = 0;
  ( * p).d_v = 0;
  ( * p).affichage = 1;
  ( * p).pos.x = 200;
  ( * p).pos.y = 50;
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

}
void animer_entite(entite * p) 
{
    ( * p).sprite_n++;
    if (( * p).sprite_n >= 6) {
      ( * p).sprite_n = 0; 
    }

    ( * p).sprite.x = ( * p).pos.w * ( * p).sprite_n;
}

int collisionTRI(SDL_Rect x1,SDL_Rect x2) 
{
int r1,r2;
if (x1.w>x1.h) r1 = x1.w/2;
else r1 = x1.h/2;
if (x2.w>x2.h) r2 = x2.w/2;
else r2 = x2.h/2;
int distance = sqrt( (x2.y - x1.y)*(x2.y - x1.y) + (x2.x - x1.x)*(x2.x - x1.x) );
if(r1+r2>distance) return 1;
return 0;
}

void afficher_score(int score, SDL_Surface * screen) {
    TTF_Font * font = TTF_OpenFont("score.ttf", 75); 
    SDL_Color color = {255,255,255}; 
    SDL_Surface * text;
    char ch[15];
    sprintf(ch, "%d", score);
    text = TTF_RenderText_Solid(font, ch, color);
    SDL_BlitSurface(text, NULL, screen, NULL);
    TTF_CloseFont(font);
    font = NULL;
    SDL_FreeSurface(text);
    text = NULL;
}
