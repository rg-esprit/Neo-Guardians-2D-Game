#include "header.h"
#include <SDL/SDL_ttf.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL.h>
#include <SDL/SDL_main.h>
#include<SDL/SDL_keysym.h>
#include<string.h>
#include <stdbool.h>






int main(int argc, char* argv[]) {
    SDL_Surface* screen = NULL;
    if (init(&screen) == -1) {
        return 1;
    }
    SDL_Surface* x_img = NULL;
    SDL_Surface* o_img = NULL;
    SDL_Surface* bg_img = NULL;
    if (load_files(&x_img, &o_img, &bg_img) == -1) {
        clean_up(x_img, o_img, bg_img);
        return 1;
    }
    int board[9] = {0};
    int turn = 1;
    int quit = 0;
    while (!quit) {
        quit = handle_events(screen, x_img, o_img, bg_img, board, &turn);
        draw_board(screen, x_img, o_img, bg_img, board);
        int winner = check_win(board);
        if (winner != 0) {
            SDL_Delay(1000);
            char message[30];
            if (winner == 1) {
                sprintf(message, "X wins!");
            }
            else if (winner == 2) {
                sprintf(message, "O wins!");
            }
            else {
                sprintf(message, "Tie game!");
            }
            SDL_WM_SetCaption(message, NULL);
            SDL_Delay(2000);
            quit = 1;
        }
        if (SDL_Flip(screen) == -1) {
            quit = 1;
        }
    }
    clean_up(x_img, o_img, bg_img);
    return 0;
}

