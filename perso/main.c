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
    p->pes[0] = IMG_Load("Perso.png");
    p->score = 0;
    p->nb_vie = 3;
}

void initPerso(Personne *p) {
    p->up = 0;
    p->directions = 0;
    p->x = 0;
    p->vitesse = 1;
    p->acceleration = 0;
    p->position_x = 0.0;
    p->position_y = 450.0;
    p->score = 0;
    p->nb_vie = 3;
    p->move_left = 0;
    p->move_right = 0;

    // Load images for pes array
    p->pes[0] = IMG_Load("img/jump/jump.png");
    p->pes[1] = IMG_Load("img/jump/Ljump.png");
    p->pes[2] = IMG_Load("img/run/Run1.png");
    p->pes[3] = IMG_Load("img/run/Run2.png");
    p->pes[4] = IMG_Load("img/run/LRun1.png");
    p->pes[5] = IMG_Load("img/run/LRun2.png");
    p->pes[6] = IMG_Load("Perso.png");
    p->pes[7] = IMG_Load("LPerso.png");

    // Check if any image failed to load
    for (int i = 0; i < 7; i++) {
        if (p->pes[i] == NULL) {
            fprintf(stderr, "Unable to load image: %s\n", IMG_GetError());
            // Handle error or exit the function
            return;
        }
    }
}


void afficherPerso(Personne p, SDL_Surface *screen) {
    SDL_Rect posecranimg;
    posecranimg.x = p.position_x;
    posecranimg.y = p.position_y;

    SDL_Surface *characterImage = NULL;
    if (p.up != 0) {
        if (p.directions == 0) {
            characterImage = p.pes[0];
        } else {
            characterImage = p.pes[1];
        }
    } else {
        if (p.move_left) {
            characterImage = (p.directions == 0) ? p.pes[2] : p.pes[4];
        } else if (p.move_right) {
            characterImage = (p.directions == 0) ? p.pes[3] : p.pes[5];
        } else {
            if (p.directions == 0) {
                characterImage = p.pes[6];
            } else {
                characterImage = p.pes[7];
            }            
        }
    }

    SDL_BlitSurface(characterImage, NULL, screen, &posecranimg);
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

int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        fprintf(stderr, "Unable to initialize SDL: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Surface *screen = SDL_SetVideoMode(800, 600, 32, SDL_SWSURFACE);
    if (screen == NULL) {
        fprintf(stderr, "Unable to set video mode: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    Personne p;
    initPerso(&p);
    // arduino
    struct sp_port *port;
    if (open_serial_port("/dev/ttyACM0", &port) != 0) {
        fprintf(stderr, "Failed to open serial port\n");
        return 1;
    }

    ThreadParams params;
    params.p = &p; // Assuming 'p' is initialized somewhere in your code
    params.port = port; // Assuming 'port' is initialized somewhere in your code

    // Create serial thread with params
    pthread_t serial_thread;
    if (pthread_create(&serial_thread, NULL, serial_thread_func, &params) != 0) {
        fprintf(stderr, "Failed to create the thread\n");
        close_serial_port(port);
        return 1;
    }

    // end code of arduino
    

    int gameRunning = 1;
    const int FPS = 60;
    const int frameDelay = 1000 / FPS;
    Uint32 frameStart;
    int frameTime;

    while (gameRunning) {
        frameStart = SDL_GetTicks();

        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            switch (e.type) {
                case SDL_QUIT:
                    gameRunning = 0;
                    break;
                case SDL_KEYDOWN:
                    switch (e.key.keysym.sym) {
                        case SDLK_RIGHT:
                            p.directions = 0;
                            p.move_right = 1;
                            
                            break;
                        case SDLK_LEFT:
                            p.directions = 1;
                            p.move_left = 1;
                            
                            break;
                        case SDLK_UP:
                            if (p.up == 0) {
                                p.up = 1;
                                printf("Jump now!\n");
                            }
                            break;
                    }
                    break;
                case SDL_KEYUP:
                    switch (e.key.keysym.sym) {
                        case SDLK_RIGHT:
                            p.move_right = 0;
                            break;
                        case SDLK_LEFT:
                            p.move_left = 0;
                            break;
                    }
                    break;
            }
        }

        if (p.move_left  || p.move_right){
            movePerso(&p);
        }
        if (p.up != 0) {
            saut_Personnage(&p, 450);
        }

        SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));
        afficherPerso(p, screen);
        SDL_Flip(screen);

        frameTime = SDL_GetTicks() - frameStart;
        if (frameDelay > frameTime) {
            SDL_Delay(frameDelay - frameTime);
        }
    }
    close_serial_port(port);
    libererPerso(&p);
    SDL_Quit();
    return 0;
}

// void process_serial_data(const char *data) {
//     printf("Processing received data: %s\n", data);
    
//     // Parse the received data and update player directions
//     if (strcmp(data, "LEFT_PRESS") == 0) {
//         p.directions = 1;
//         p.move_left = 1;
//     } else if (strcmp(data, "LEFT_RELEASE") == 0) {
//         p.move_left = 0;
//     } else if (strcmp(data, "RIGHT_PRESS") == 0) {
//         p.directions = 0;
//         p.move_right = 1;
//     } else if (strcmp(data, "RIGHT_RELEASE") == 0) {
//         p.move_right = 0;
//     } else if (strcmp(data, "UP_PRESS") == 0) {
//         if (p.up == 0) {
//             p.up = 1;
//             printf("Jump now!\n");
//         }
//     } else if (strcmp(data, "UP_RELEASE") == 0) {
//         // Handle UP release if needed
//     }
// }
