#ifndef ENIGMETF_H_INCLUDED
#define ENIGMETF_H_INCLUDED
#define MAX_NUM_QUESTIONS 10 // ou une autre valeur appropriée


#include <stdio.h> 
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <time.h>
#include <unistd.h>


typedef struct{//type define structure 

	SDL_Surface *background;// l background ali besh nafficher fiha l question o les reponses 
	SDL_Surface *question;//l surface ali besh nafficher feha l question 
	SDL_Surface *rep1;//l surface ali besh nafficher feha les reponses 
	SDL_Surface *reponse2;//l surface ali besh nafficher feha les reponses 
	SDL_Surface *rep3;//l surface ali besh nafficher feha les reponses 
	SDL_Surface *button;// l button ali besh nenzl alih 
	SDL_Surface *button_s;

	int pos_selected;// 1 2 3 
	SDL_Rect pos_question;// l position mta3 l question 
	SDL_Rect pos_reponse1;// l position mta3 lreponse
	SDL_Rect pos_reponse2;// l position mta3 l reponse 
	SDL_Rect pos_reponse3;// l position mta3 l reponse 
	int num_question;
	
	SDL_Rect pos_reponse1txt;// l position mta3 l txt ali besh nhoto fouk l image ta3 l reponse 
	SDL_Rect pos_reponse2txt;// l position mta3 l txt ali besh nhoto fouk l image ta3 l reponse 
	SDL_Rect pos_reponse3txt;// l position mta3 l txt ali besh nhoto fouk l image ta3 l reponse 

	int positionVraiReponse;// l position mta3 l reponse l s7i7a o ali heya l position mta3 l image wel texte  
	TTF_Font *police; 
	TTF_Font *police1;
	
		
	SDL_Surface *image_clock;  
	SDL_Rect pos_image_clock;
	SDL_Rect single_Clock;
	int clock_num;
        int win;

}Enigme;
void InitEnigme(Enigme *e);
void afficherEnigme(Enigme e,SDL_Surface *ecran);
void animerEnigme(Enigme *e);
void winLost(Enigme e,SDL_Surface *ecran);
void GenererEnigmeAleatoire(Enigme *e);
void ChargerEnigme(Enigme *e);



#endif
