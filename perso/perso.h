#ifndef PERSO_H
#define PERSO_H


#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <stdbool.h>



typedef struct {
    int up; // 1 if jumping, 0 otherwise
    int directions; // 0 for right, 1 for left, 2 for up (though 2 is not handled in main.c)
    double x, position_x, position_y, vitesse, acceleration, velocity_y;
    SDL_Surface *pes[20]; // Corrected from SDL_surface to SDL_Surface *
    int score, nb_vie, timing;
    int move_left, move_right, frame;
    int niveau;
} Personne;

typedef struct {
    Personne* p;
    struct sp_port* port;
} ThreadParams;
#include "/home/rg/Desktop/Neo-Guardians/background/header.h"

void init(Personne *p, int numperso);
void initPerso(Personne *p);
void swapCharacter(Personne *p);
void afficherPerso(Personne *p, SDL_Surface *screen);
void movePerso(Personne *p, bool can_move_right, bool can_move_left);
void saut_Personnage(Personne *p, SDL_Surface *calque, SDL_Rect posmap);
void libererPerso(Personne *p);
void process_serial_data(const char *data);
void swapCharacter(Personne *p);

bool isOnGround(SDL_Surface *calque, SDL_Rect posperso, SDL_Rect posmap);


#endif
