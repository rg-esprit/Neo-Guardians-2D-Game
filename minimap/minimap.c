#include <SDL/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL_image.h>
#include "minimap.h"
#include "player.h"
#include <time.h>
#include <SDL/SDL_ttf.h>
#include "/home/rg/Desktop/Neo-Guardians/perso/perso.h"


void init_minimap(minimap* mp){

  mp->mini_map =IMG_Load("minimap/minimap.png");
 mp->pos_minimap.x = 400;
 mp->pos_minimap.y = 50;


 mp->mini_hero = IMG_Load("minimap/mini_perso.png");
 mp->pos_minihero.x = 100;
 mp->pos_minihero.y = 200;

}

void blit_minimap(minimap mp,SDL_Surface *screen)
{

 SDL_BlitSurface(mp.mini_map,NULL,screen,&mp.pos_minimap);
 SDL_BlitSurface(mp.mini_hero,NULL,screen,&mp.pos_minihero);
}

void MAJMinimap(Personne *p, minimap *mp, int resize,int way){
    SDL_Rect tmp, tmp1;
    tmp1.x = (p->position_x * resize) / 100;
    tmp1.y = (p->position_y * resize) / 100;

    if (way == 0) {
        if (mp->pos_minihero.x <= 1500) {
            mp->pos_minihero.x = 400 + tmp1.x;
        }
    } else {
        if (mp->pos_minihero.x >= 400) {
            mp->pos_minihero.x = 400 + tmp1.x;
        }
    }

    // Limit the hero's x-coordinate within the range of 400 to 800
    if (mp->pos_minihero.x < 400)
        mp->pos_minihero.x = 400;
    else if (mp->pos_minihero.x > 1450)
        mp->pos_minihero.x = 1500;
}
void free_minimap(minimap mp)
{
SDL_FreeSurface(mp.mini_map);
SDL_FreeSurface(mp.mini_hero);
}
