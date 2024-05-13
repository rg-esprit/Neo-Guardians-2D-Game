#ifndef PERSO_H
#define PERSO_H


#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

typedef struct {
    int up; // 1 if jumping, 0 otherwise
    int directions; // 0 for right, 1 for left, 2 for up (though 2 is not handled in main.c)
    double x, position_x, position_y, vitesse, acceleration, velocity_y;
    SDL_Surface *pes[20]; // Corrected from SDL_surface to SDL_Surface *
    int score, nb_vie, timing;
    int move_left, move_right, frame;
} Personne;

typedef struct {
    Personne* p;
    struct sp_port* port;
} ThreadParams;

void init(Personne *p, int numperso);
void initPerso(Personne *p);
void swapCharacter(Personne *p);
void afficherPerso(Personne *p, SDL_Surface *screen);
void movePerso(Personne *p);
void saut_Personnage(Personne *p, int posy_absolu);
void libererPerso(Personne *p);
void process_serial_data(const char *data);
void swapCharacter(Personne *p);


#endif
