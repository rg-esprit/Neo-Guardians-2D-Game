#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#include <stdio.h>
#include <pthread.h>
#include "Menu/menu.h"
#include "perso/perso.h"
#include "background/header.h"
#include "perso/serial_comm.h"
#include "minimap/minimap.h"

int main() {
    int choix = runMenu();
    printf("%d", choix);
    
    if (choix == 1 || choix == 2){
        if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
            fprintf(stderr, "Unable to initialize SDL: %s\n", SDL_GetError());
            return 1;
        }
        SDL_Surface *screen = SDL_SetVideoMode(1920, 1080, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
        if (screen == NULL) {
            fprintf(stderr, "Unable to set video mode: %s\n", SDL_GetError());
            SDL_Quit();
            return 1;
        }
        background b;
        initBack(&b);
        Personne p;
        initPerso(&p);
        int resize=20;
        minimap minimap;
        init_minimap(&minimap);
        // arduino
        struct sp_port *port;
        if (open_serial_port("/dev/ttyACM0", &port) != 0) {
            fprintf(stderr, "Failed to open serial port\n");
            return NULL; 
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
                                }
                                break;
                            case SDLK_s:
                                swapCharacter(&p);
                                break;
                            default:
                                
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
                            default:
                                
                                break;
                        }
                        break;
                }
            }

            if (p.move_left  || p.move_right){
                movePerso(&p);
            }
            if (p.up != 0) {
                saut_Personnage(&p, 630);
            }

            //SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));
            afficherBack(b,screen);
            afficherPerso(&p, screen);
            MAJMinimap(&p, &minimap, resize, p.directions);
            blit_minimap(minimap,screen);
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


    return 0;
}
