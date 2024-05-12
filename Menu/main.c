#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>


void handleMouseHover(SDL_Surface *screen, SDL_Surface *image, SDL_Surface *hoverImage, SDL_Rect pos, int mouseX, int mouseY, int *soundPlayed, Mix_Chunk *sound);
void handleButtonClick(int mouseX, int mouseY, SDL_Rect pos_play, int play_w, int play_h,
                       SDL_Rect pos_settings, int settings_w, int settings_h,
                       SDL_Rect pos_exit, int exit_w, int exit_h, int* screen, SDL_Surface *background, SDL_Surface *ecran, int *choix);

int runMenu() {

    int choix = 0;
    SDL_Surface *ecran;
    SDL_Surface *background, *image_play, *image_settings, *image_exit, *image_play2, *image_settings2, *image_exit2, *new_game, *new_game2, *continuee, *continuee2, *home, *easy, *hard, *medium, *easy2, *hard2, *medium2, *up, *down;

    SDL_Rect pos_play, pos_settings, pos_exit;
    SDL_Event event;
    TTF_Font *font;
    SDL_Color textColor = {0, 0, 0};
    Mix_Music *musique;
    Mix_Chunk *soundEffect;

    int running = 1, screen = 0, soundPlayed = 0;

    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    TTF_Init();
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024);

    ecran = SDL_SetVideoMode(1920, 1080, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    if (!ecran) {
        fprintf(stderr, "Failed to create window: %s\n", SDL_GetError());
        return 1;
    }

    // Load images and audio
    background = IMG_Load("Menu/last.jpg");
    image_play = IMG_Load("Menu/img/play.png");
    image_play2 = IMG_Load("Menu/img/play_hover.png");
    image_settings = IMG_Load("Menu/img/settings.png");
    image_settings2 = IMG_Load("Menu/img/settings_hover.png");
    image_exit = IMG_Load("Menu/img/exit.png");
    image_exit2 = IMG_Load("Menu/img/exit_hover.png");
    new_game = IMG_Load("Menu/img/new_game.png");
    new_game2 = IMG_Load("Menu/img/new_game_hover.png");
    continuee = IMG_Load("Menu/img/continue.png");
    continuee2 = IMG_Load("Menu/img/continue_hover.png");
    home = IMG_Load("Menu/img/home.png");
    easy = IMG_Load("Menu/img/easy.png");
    hard = IMG_Load("Menu/img/hard.png");
    medium = IMG_Load("Menu/img/medium.png");
    easy2 = IMG_Load("Menu/img/easy_hover.png");
    hard2 = IMG_Load("Menu/img/hard_hover.png");
    medium2 = IMG_Load("Menu/img/medium_hover.png");
    up = IMG_Load("Menu/img/up.png");
    down = IMG_Load("Menu/img/down.png");

    font = TTF_OpenFont("Menu/arial.ttf", 20);
    musique = Mix_LoadMUS("Menu/song.mp3");
    soundEffect = Mix_LoadWAV("Menu/sound.wav");

    // Set initial positions
    pos_play.x = 900; pos_play.y = 150;
    pos_settings.x = 900; pos_settings.y = 350;
    pos_exit.x = 900; pos_exit.y = 550;

    // Blit the background once initially
    SDL_BlitSurface(background, NULL, ecran, NULL);

    while (running) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {

                case SDL_QUIT:
                    running = 0;
                    break;

                case SDL_KEYDOWN:
                    if (event.key.keysym.sym == SDLK_ESCAPE) {
                        running = 0;
                    }
                    break;

                case SDL_MOUSEMOTION:
                    handleMouseHover(ecran, screen == 0 ? image_play : (screen == 1 ? new_game : (screen == 2 ? easy : up)),
                                     screen == 0 ? image_play2 : (screen == 1 ? new_game2 : (screen == 2 ? easy2 : up)), 
                                     pos_play, event.motion.x, event.motion.y, &soundPlayed, soundEffect);

                    handleMouseHover(ecran, screen == 0 ? image_settings : (screen == 1 ? continuee : (screen == 2 ? medium : down)),
                                     screen == 0 ? image_settings2 : (screen == 1 ? continuee2 : (screen == 2 ? medium2 : down)), 
                                     pos_settings, event.motion.x, event.motion.y, &soundPlayed, soundEffect);

                    handleMouseHover(ecran, screen == 0 ? image_exit : home, 
                                     screen == 0 ? image_exit2 : home, 
                                     pos_exit, event.motion.x, event.motion.y, &soundPlayed, soundEffect);
                    break;

                case SDL_MOUSEBUTTONDOWN:
                    if (event.button.button == SDL_BUTTON_LEFT) { // Check if the left mouse button was pressed
                        handleButtonClick(event.button.x, event.button.y,
                                        pos_play, image_play->w, image_play->h,
                                        pos_settings, image_settings->w, image_settings->h,
                                        pos_exit, image_exit->w, image_exit->h,
                                        &screen, background, ecran, &choix);
                        if (screen == -1) {
                            running = 0; // Exit game if necessary
                        } else if (choix != 0) {
                            running = 0;
                        }
                    }
                    break;


            }
        }
        SDL_Flip(ecran);
    }

    // Clean up resources
    SDL_FreeSurface(background);
    SDL_FreeSurface(image_play);
    SDL_FreeSurface(image_settings);
    SDL_FreeSurface(image_exit);
    SDL_FreeSurface(image_play2);
    SDL_FreeSurface(image_settings2);
    SDL_FreeSurface(image_exit2);
    TTF_CloseFont(font);
    Mix_FreeMusic(musique);
    Mix_FreeChunk(soundEffect);
    Mix_CloseAudio();
    TTF_Quit();
    SDL_Quit();
    return choix;
}

void handleMouseHover(SDL_Surface *screen, SDL_Surface *image, SDL_Surface *hoverImage, SDL_Rect pos, int mouseX, int mouseY, int *soundPlayed, Mix_Chunk *sound) {
    if (mouseX >= pos.x && mouseX <= pos.x + image->w && mouseY >= pos.y && mouseY <= pos.y + image->h) {
        SDL_BlitSurface(hoverImage, NULL, screen, &pos);
        if (!*soundPlayed) {
            Mix_PlayChannel(-1, sound, 0);
            *soundPlayed = 1;
        }
    } else {
        SDL_BlitSurface(image, NULL, screen, &pos);
        *soundPlayed = 0;
    }
}


void handleButtonClick(int mouseX, int mouseY, SDL_Rect pos_play, int play_w, int play_h,
                                          SDL_Rect pos_settings, int settings_w, int settings_h,
                                          SDL_Rect pos_exit, int exit_w, int exit_h, int* screen, SDL_Surface *background, SDL_Surface *ecran, int *choix) {
    if (mouseX >= pos_play.x && mouseX <= pos_play.x + play_w &&
        mouseY >= pos_play.y && mouseY <= pos_play.y + play_h) {
        if (*screen == 0) {
            *screen = 1;  // Switch to game screen
        } else if (*screen == 1) {
            *screen = 2;
        }  else if (*screen == 2) {
            //*screen = 2;
            *choix = 1;
        }
        SDL_BlitSurface(background, NULL, ecran, NULL);
    } else if (mouseX >= pos_settings.x && mouseX <= pos_settings.x + settings_w &&
               mouseY >= pos_settings.y && mouseY <= pos_settings.y + settings_h) {
        if (*screen == 0) {
            *screen = 3;  // Switch to settings screen
        } else if (*screen == 2) {
            //*screen = 2;
            *choix = 2;
        }
        SDL_BlitSurface(background, NULL, ecran, NULL);
    } else if (mouseX >= pos_exit.x && mouseX <= pos_exit.x + exit_w &&
               mouseY >= pos_exit.y && mouseY <= pos_exit.y + exit_h) {
        if (*screen == 0) {
            *screen = -1; // Exit or go back to main menu, assuming -1 triggers exit elsewhere
        } else if (*screen == 1) {
            *screen = 0;
        }  else if (*screen == 3) {
            *screen = 0;
        } else if (*screen == 2) {
            *screen = 0;
        }
        SDL_BlitSurface(background, NULL, ecran, NULL);
    }
}