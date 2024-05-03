#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#include"header.h"
void scrolling (hero *evan,background *b,int co )
{
	
	switch(evan->mouvment)
	{

		case 1: 
			if (co!=1){ 
			if ((b->pos_background2.x<5500)&&(evan->pos_hero2.x>=800)) 
                		b->pos_background2.x=b->pos_background2.x+15;

			if (((evan->pos_hero2.x<800)||((b->pos_background2.x>=5500))&&(evan->pos_hero2.x<1700)))  
				evan->pos_hero2.x=evan->pos_hero2.x+10;
			
		}
		break;
		case 2:
		if (co!=1){
			if (b->pos_background2.x>0)
                		b->pos_background2.x=b->pos_background2.x-15;
	    		if (((b->pos_background2.x!=0)&&(evan->pos_hero2.x>=150))||((b->pos_background2.x==0)&&(evan->pos_hero2.x=50)))
				evan->pos_hero2.x=evan->pos_hero2.x-10;
			   
			}	
		break;
		case 3:

		if (evan->pos_hero2.y>50){
			if (b->pos_background2.x<5500)
				evan->pos_hero2.y=evan->pos_hero2.y-20;	
		}
                if ((evan->pos_hero2.y>750)&&(b->pos_background2.y>=0))
                b->pos_background2.y=b->pos_background2.y-5;
		break;
		case 4: 

		if ((evan->pos_hero2.y<600)&&(evan->pos_hero2.y!=810)&&(b->pos_background2.y<20))
                b->pos_background2.y=b->pos_background2.y+5;
		if ((co!=2)&&(co!=1))
		evan->pos_hero2.y=evan->pos_hero2.y+10;
		break;
                
		
	}
	if ((evan->mouvment!=3)&&(co!=2)&&(co!=1)) 
		evan->pos_hero2.y=evan->pos_hero2.y+5;
	
}


