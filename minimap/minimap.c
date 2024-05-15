#include <SDL/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL_image.h>
#include "minimap.h"
#include "player.h"
#include <time.h>
#include <SDL/SDL_ttf.h>
#include "/home/rg/Desktop/Neo-Guardians/perso/perso.h"


void init_minimap(minimap* mp) {
    // Load the three minimap images
    mp->mini_maps[0] = IMG_Load("minimap/mini/1.png");
    mp->mini_maps[1] = IMG_Load("minimap/mini/2.png");
    mp->mini_maps[2] = IMG_Load("minimap/mini/3.png");

    // Set the positions for the three minimaps
    mp->pos_minimap[0].x = 400;
    mp->pos_minimap[0].y = 50;

    mp->pos_minimap[1].x = 400;
    mp->pos_minimap[1].y = 50;

    mp->pos_minimap[2].x = 400;
    mp->pos_minimap[2].y = 50;

    // Load the mini hero image
    mp->mini_hero = IMG_Load("minimap/mini_perso.png");

    // Set the position for the mini hero
    mp->pos_minihero.x = 100;
    mp->pos_minihero.y = 200;
}


void blit_minimap(minimap mp, SDL_Surface *screen, int level) {
    // Ensure the level is within valid range (0, 1, 2)
    if (level < 1 || level > 3) {
        printf("Invalid level: %d\n", level);
        return;
    }

    // Blit the appropriate minimap based on the level
    SDL_BlitSurface(mp.mini_maps[level - 1], NULL, screen, &mp.pos_minimap[level - 1]);
    
    // Blit the mini hero
    SDL_BlitSurface(mp.mini_hero, NULL, screen, &mp.pos_minihero);
}


void MAJMinimap(Personne *p, minimap *mp, int resize,int way){
    SDL_Rect tmp1;
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
// void free_minimap(minimap mp)
// {
// SDL_FreeSurface(mp.mini_map);
// SDL_FreeSurface(mp.mini_hero);
// }
