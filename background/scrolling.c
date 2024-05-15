#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#include"header.h"
#include "/home/rg/Desktop/Neo-Guardians/perso/perso.h"

void scrolling(Personne *p, background *b, int co) {
    // Forward movement
    if ((p->position_x > 1800) && (p->niveau == 1)) {
        b->pos_background2.x = 1920;
        p->position_x = 0;
        p->position_y = 420;  // Set y position for second screen
        p->niveau = 2;
    } else if ((p->position_x > 1800) && (p->niveau == 2)) {
        b->pos_background2.x = 3840;
        p->position_x = 0;
        p->position_y = 700;  // Set y position for third screen
        p->niveau = 3;
    }

    // Backward movement
    if ((p->position_x < 0) && (p->niveau == 2)) {
        b->pos_background2.x = 0;
        p->position_x = 1800;
        p->position_y = 630;  // Set y position for first screen
        p->niveau = 1;
    } else if ((p->position_x < 0) && (p->niveau == 3)) {
        b->pos_background2.x = 1920;
        p->position_x = 1800;
        p->position_y = 420;  // Set y position for second screen
        p->niveau = 2;
    }
}






