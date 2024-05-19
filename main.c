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
#include "secondentity/ennemi.h"
#include "secondentity/bonus.h"
#include <stdbool.h>



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
        Ennemi enn;
        entite en;
        SDL_Rect posp;
        initEnnemi(&enn);
        init_entite(&en);
        int score=200;
        int c;
        // arduino
        struct sp_port *port;
        if (open_serial_port("/dev/ttyACM0", &port) != 0) {
            fprintf(stderr, "Failed to open serial port\n");
            return NULL; 
        }

        
        ThreadParams params;
        params.p = &p; 
        params.port = port; 

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

            bool can_move_right = true;
            bool can_move_left = true;

            // Check if moving right causes a collision
            if (p.move_right) {
                posp.x = p.position_x + p.vitesse;
                posp.y = p.position_y;
                int collision_right = collisionPP(b.calque_background, posp, b.pos_background2);
                //printf("Checking right collision: position_x = %d, collision = %d\n", posp.x, collision_right);
                if (collision_right != 0) {
                    can_move_right = false;
                }
            }

            // Check if moving left causes a collision
            if (p.move_left) {
                posp.x = p.position_x - p.vitesse;
                posp.y = p.position_y;
                int collision_left = collisionPP(b.calque_background, posp, b.pos_background2);
                //printf("Checking left collision: position_x = %d, collision = %d\n", posp.x, collision_left);
                if (collision_left != 0) {
                    can_move_left = false;
                }
            }

            if (p.move_left || p.move_right) {
                movePerso(&p, can_move_right, can_move_left);
            }
            if (p.up != 0) {
                saut_Personnage(&p, b.calque_background, b.pos_background2);
            }

            posp.x=p.position_x;
	        posp.y=p.position_y;

            afficherBack(b,screen);
            afficherPerso(&p, screen);
            scrolling(&p,&b,c);	
			
            MAJMinimap(&p, &minimap, resize, p.directions);
            blit_minimap(minimap,screen,p.niveau);

            afficherEnnemi(enn,screen);
            move(&enn);
            moveAI(&enn,posp);
            afficher_entite(en,screen);
            animer_entite(&en);
            afficher_score(score,screen);
            if (collisionTRI(en.pos,posp)) {if(en.affichage==1) score+=3; en.affichage=0;}
            SDL_Flip(screen);
            if (collisionBB(posp, enn) == 1) {
                score--;
                posp.x = 0;
                posp.y = 150;

                if (score == 0){
                    //gameRunning = 0;
                    printf("lost.");
                }
            }


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
