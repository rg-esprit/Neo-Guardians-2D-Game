// main.c

#include "perso.h"
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>

void init(Personne *p, int numperso){
    p->up = 0;
    p->directions = 0;
    p->x = numperso;
    p->vitesse = 0.0;
    p->acceleration = 0.0;
    p->position_x = 0.0;
    p->position_y = 0.0;
    p->pes[0] = IMG_Load("perso/Perso.png");
    p->score = 0;
    p->nb_vie = 3;
}

void swapCharacter(Personne *p) {
    libererPerso(p);

    if (p->x == 0) {
        p->x = 1;
        p->vitesse = 9;  
        p->pes[0] = IMG_Load("perso/img2/jump/jump.png");
        p->pes[1] = IMG_Load("perso/img2/jump/Ljump.png");
        p->pes[2] = IMG_Load("perso/img2/run/Run1.png");
        p->pes[3] = IMG_Load("perso/img2/run/Run2.png");
        p->pes[4] = IMG_Load("perso/img2/run/LRun1.png");
        p->pes[5] = IMG_Load("perso/img2/run/LRun2.png");
        p->pes[6] = IMG_Load("perso/img2/Perso.png");
        p->pes[7] = IMG_Load("perso/img2/LPerso.png");
    } else {
        p->x = 0;
        p->vitesse = 5;  
        p->pes[0] = IMG_Load("perso/img/jump/jump.png");
        p->pes[1] = IMG_Load("perso/img/jump/Ljump.png");
        p->pes[2] = IMG_Load("perso/img/run/Run1.png");
        p->pes[3] = IMG_Load("perso/img/run/Run2.png");
        p->pes[4] = IMG_Load("perso/img/run/LRun1.png");
        p->pes[5] = IMG_Load("perso/img/run/LRun2.png");
        p->pes[6] = IMG_Load("perso/img/Perso.png");
        p->pes[7] = IMG_Load("perso/img/LPerso.png");
    }

    for (int i = 0; i < 8; i++) {
        if (p->pes[i] == NULL) {
            fprintf(stderr, "Unable to load image from set %f: %s\n", p->x, IMG_GetError());
            return;
        }
    }
}


void initPerso(Personne *p) {
    p->up = 0;
    p->directions = 0;
    p->x = 0;
    p->vitesse = 5;
    p->acceleration = 0;
    p->position_x = 0.0;
    p->position_y = 630.0;
    p->score = 0;
    p->nb_vie = 3;
    p->move_left = 0;
    p->move_right = 0;

    // Load images for pes array
    p->pes[0] = IMG_Load("perso/img/jump/jump.png");
    p->pes[1] = IMG_Load("perso/img/jump/Ljump.png");
    p->pes[2] = IMG_Load("perso/img/run/Run1.png");
    p->pes[3] = IMG_Load("perso/img/run/Run2.png");
    p->pes[4] = IMG_Load("perso/img/run/LRun1.png");
    p->pes[5] = IMG_Load("perso/img/run/LRun2.png");
    p->pes[6] = IMG_Load("perso/img/Perso.png");
    p->pes[7] = IMG_Load("perso/img/LPerso.png");

    // Check if any image failed to load
    for (int i = 0; i < 8; i++) { 
        if (p->pes[i] == NULL) {
            fprintf(stderr, "Unable to load image: %s\n", IMG_GetError());
            // Handle error or exit the function
            return;
        }
    }
}


void afficherPerso(Personne *p, SDL_Surface *screen) {
    SDL_Rect posecranimg;
    posecranimg.x = p->position_x;
    posecranimg.y = p->position_y;

    SDL_Surface *characterImage = NULL;

    if (p->up != 0) {
        // Handle jumping images
        if (p->directions == 0) {
            characterImage = p->pes[0];
        } else {
            characterImage = p->pes[1];
        }
    } else if (p->move_left) {
        int frameIndex = (p->frame / 30) % 2; // '5' can be adjusted to change animation speed
        if (frameIndex == 0) {
            characterImage = p->pes[5];
        } else {
            characterImage = p->pes[4];
        }
        p->frame++; // Increment frame count to advance animation
    } else if (p->move_right) {
        int frameIndex = (p->frame / 30) % 2; // '5' can be adjusted to change animation speed
        if (frameIndex == 0) {
            characterImage = p->pes[2];
        } else {
            characterImage = p->pes[3];
        }
        p->frame++;
    } else {
        // Handle static images when character is not moving
        if (p->directions == 0) {
            characterImage = p->pes[6];
        } else {
            characterImage = p->pes[7];
        }
    }

    // If a valid image is selected, blit it to the screen
    if (characterImage != NULL) {
        SDL_BlitSurface(characterImage, NULL, screen, &posecranimg);
    } else {
        // Log an error or handle cases where no valid image is found
        fprintf(stderr, "No valid character image found for rendering.\n");
    }
}




void libererPerso(Personne *p) {
    for (int i = 0; i < 7; i++) { 
        if (p->pes[i]) {
            SDL_FreeSurface(p->pes[i]);
            p->pes[i] = NULL;
        }
    }
}


void movePerso(Personne *p) {
    if (p->move_right) {
        p->position_x += p->vitesse;
    }
    if (p->move_left) {
        p->position_x -= p->vitesse;
    }
}



void saut_Personnage(Personne *p, int ground_level) {
    const float jump_velocity = 18.0;
    const float gravity_increment = 1.1;

    if (p->up == 1) {
        p->velocity_y = -jump_velocity;
        p->up = 2;
    }

    if (p->up == 2) {
        p->position_y += p->velocity_y;
        p->velocity_y += gravity_increment;

        if (p->velocity_y >= 0) {
            p->up = 3;
        }
    } else if (p->up == 3) {
        p->position_y += p->velocity_y;
        p->velocity_y += gravity_increment;

        if (p->position_y >= ground_level) {
            p->position_y = ground_level;
            p->up = 0;
        }
    }
}

#include "perso.h"
#include <stdio.h>
#include "serial_comm.h"
#include <pthread.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>

//int main(int argc, char* argv[]) {
    // if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
    //     fprintf(stderr, "Unable to initialize SDL: %s\n", SDL_GetError());
    //     return 1;
    // }

    // SDL_Surface *screen = SDL_SetVideoMode(1920, 1080, 32, SDL_SWSURFACE);
    // if (screen == NULL) {
    //     fprintf(stderr, "Unable to set video mode: %s\n", SDL_GetError());
    //     SDL_Quit();
    //     return 1;
    // }

    // Personne p;
    // initPerso(&p);
    // // arduino
    // struct sp_port *port;
    // if (open_serial_port("/dev/ttyACM0", &port) != 0) {
    //     fprintf(stderr, "Failed to open serial port\n");
    //     return NULL; 
    // }

    
    // ThreadParams params;
    // params.p = &p; // Assuming 'p' is initialized somewhere in your code
    // params.port = port; // Assuming 'port' is initialized somewhere in your code

    // // Create serial thread with params
    // pthread_t serial_thread;
    // if (pthread_create(&serial_thread, NULL, serial_thread_func, &params) != 0) {
    //     fprintf(stderr, "Failed to create the thread\n");
    //     close_serial_port(port);
    //     return 1;
    // }
    // // end code of arduino
    

    // int gameRunning = 1;
    // const int FPS = 60;
    // const int frameDelay = 1000 / FPS;
    // Uint32 frameStart;
    // int frameTime;

    // while (gameRunning) {
    //     frameStart = SDL_GetTicks();

    //     SDL_Event e;
    //     while (SDL_PollEvent(&e)) {
    //         switch (e.type) {
    //             case SDL_QUIT:
    //                 gameRunning = 0;
    //                 break;
    //             case SDL_KEYDOWN:
    //                 switch (e.key.keysym.sym) {
    //                     case SDLK_RIGHT:
    //                         p.directions = 0;
    //                         p.move_right = 1;
                            
    //                         break;
    //                     case SDLK_LEFT:
    //                         p.directions = 1;
    //                         p.move_left = 1;
                            
    //                         break;
    //                     case SDLK_UP:
    //                         if (p.up == 0) {
    //                             p.up = 1;
    //                         }
    //                         break;
    //                     case SDLK_s:
    //                         swapCharacter(&p);
    //                         break;
    //                 }
    //                 break;
    //             case SDL_KEYUP:
    //                 switch (e.key.keysym.sym) {
    //                     case SDLK_RIGHT:
    //                         p.move_right = 0;
    //                         break;
    //                     case SDLK_LEFT:
    //                         p.move_left = 0;
    //                         break;
    //                 }
    //                 break;
    //         }
    //     }

    //     if (p.move_left  || p.move_right){
    //         movePerso(&p);
    //     }
    //     if (p.up != 0) {
    //         saut_Personnage(&p, 450);
    //     }

    //     SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));
    //     afficherPerso(&p, screen);
    //     SDL_Flip(screen);

    //     frameTime = SDL_GetTicks() - frameStart;
    //     if (frameDelay > frameTime) {
    //         SDL_Delay(frameDelay - frameTime);
    //     }
    // }
    // close_serial_port(port);
    // libererPerso(&p);
    // SDL_Quit();
    // return 0;
//}


