#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>


typedef struct hero
{
	int mouvment;
	SDL_Rect pos_hero[9];
	SDL_Surface *afficher_hero[9];
	SDL_Surface *afficher_herod[9];
	SDL_Rect pos_hero2;
	int farm;	
}hero;


typedef struct background{

	SDL_Surface *afficher_background;
	SDL_Surface *aff;
	SDL_Rect pos_background;
	SDL_Rect pos_background2;
	SDL_Surface *calque_background;
	SDL_Surface *porte[14];
	SDL_Surface *owl[14];
	SDL_Rect port;
	SDL_Rect owll;
}background;

 
	void initBack(background *b);
 	void afficherBack(background b,SDL_Surface *ecran);
	void initialiser_evan(hero *evan);
	void afficher_evan(hero evan,SDL_Surface *ecran);
	void animerBackground (background *b,SDL_Surface *ecran);
	void scrolling (hero *evan,background *b, int co);
	int mouvment(hero evan,SDL_Event *event);
	int collisionPP(SDL_Surface *calque,SDL_Surface *perso,SDL_Rect posperso,SDL_Rect posmap);
	SDL_Color GetPixel(SDL_Surface *surface,int x,int y);



#endif
