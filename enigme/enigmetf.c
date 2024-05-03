#include "enigmetf.h"


void InitEnigme(Enigme *e)
{   
 
    // Utilisation de l'heure actuelle et de l'ID de processus comme graines


    //srand((unsigned int)(time(NULL) + getpid())); 



        e->pos_question.x=140;
	e->pos_question.y=220;
 
	e->pos_reponse1.x=375;//375
	e->pos_reponse1.y=522;


	e->pos_reponse2.x=177;
	e->pos_reponse2.y=648;

	e->pos_reponse3.x=566;
	e->pos_reponse3.y=651;

	e->pos_reponse1txt.x=e->pos_reponse1.x+50;
	e->pos_reponse1txt.y=522+30;

	e->pos_reponse2txt.x=177+50;
	e->pos_reponse2txt.y=648+30;

	e->pos_reponse3txt.x=566+50;
	e->pos_reponse3txt.y=651+30;
	
	
	(*e).image_clock=IMG_Load("clock1.png");  

	e->pos_image_clock.x=500;
	e->pos_image_clock.y=100;
	
	e->single_Clock.w=57;
	e->single_Clock.h=81;
	e->single_Clock.x=0;
	e->single_Clock.y=0;

	e->clock_num=0;

     	FILE *fquestion=NULL;
	FILE *freponse=NULL;
	FILE *fvraireponse=NULL;
	
	e->pos_selected=0;
	e->background= IMG_Load("img/background.png");
	e->button= IMG_Load("img/button.png");
	e->button_s= IMG_Load("img/button_s.png");

	TTF_Init();
	SDL_Color couleur; 
        couleur.r=0;
        couleur.g=0;
        couleur.b=0;

	e->police = TTF_OpenFont("arial.ttf", 30);
	e->police1 = TTF_OpenFont("arial.ttf", 20);
	  
	char questionn[100];
	


     e->num_question=1; //1234  

	 
	
        fquestion=fopen("questions.txt","r");
	if(fquestion!=NULL){

		int test=1;
		while (fgets(questionn,100, fquestion) &&(test!=e->num_question)){ 
			test++;
		}
		
		fclose(fquestion);
	}
	
	char reponse[100];

	int min,max;
   

if(e->num_question==1)
{
min=0;
max=2;
}
else if(e->num_question==2)
{
min=3;
max=5;
}
else
{
min=6;
max=8;
}
int try=1;

	freponse=fopen("reponses.txt","r");
	if(freponse!=NULL){

		int test=0;
		while (fgets((reponse),100, freponse) &&(test<max)){	//parcour
			
			if(test>=min){

                        if(try==1)
                              {
				e->rep1=TTF_RenderText_Blended(e->police1, reponse, couleur); 
                              try=0;
                              }                                                                                  
				e->reponse2=TTF_RenderText_Blended(e->police1, reponse, couleur); // e->reponses[2] = "2006" 


			}
			test++;
		}	
		
		fclose(freponse);
	}
	
 
	
e->positionVraiReponse=1;//1234 

	
	
	fvraireponse=fopen("vraireponses.txt","r+");
	if(fvraireponse!=NULL){
		
		int test=1;
		while (fgets((reponse),100, fvraireponse)){
			
			if(test==e->num_question){ 
				printf("%s\n",reponse);
				e->rep3=TTF_RenderText_Blended(e->police1, reponse, couleur); 
			}
			test++;
		}
		fclose(freponse);
	}




	
	printf("%d\n",e->positionVraiReponse);

	e->question = TTF_RenderText_Blended(e->police, questionn, couleur);

	

 

}

void afficherEnigme(Enigme e,SDL_Surface *ecran){

	
		
	SDL_BlitSurface(e.background, NULL, ecran, NULL);
 	SDL_BlitSurface(e.image_clock,&(e.single_Clock), ecran, &e.pos_image_clock);//&(e.single_Clock)
	SDL_BlitSurface(e.question, NULL, ecran, &e.pos_question);

	

	switch(e.positionVraiReponse){
		case 1:{

			switch(e.pos_selected){
			case 1:
			{
				SDL_BlitSurface(e.button_s, NULL, ecran, &e.pos_reponse1);
				SDL_BlitSurface(e.button, NULL, ecran, &e.pos_reponse2);
				SDL_BlitSurface(e.button, NULL, ecran, &e.pos_reponse3);


				SDL_BlitSurface(e.rep3, NULL, ecran, &e.pos_reponse1txt);

				SDL_BlitSurface(e.rep1, NULL, ecran, &e.pos_reponse2txt);

				SDL_BlitSurface(e.reponse2, NULL, ecran, &e.pos_reponse3txt);


			}
			break;
			case 2:
			{
				SDL_BlitSurface(e.button, NULL, ecran, &e.pos_reponse1);

				SDL_BlitSurface(e.button_s, NULL, ecran, &e.pos_reponse2);

				SDL_BlitSurface(e.button, NULL, ecran, &e.pos_reponse3);


				SDL_BlitSurface(e.rep3, NULL, ecran, &e.pos_reponse1txt);

				SDL_BlitSurface(e.rep1, NULL, ecran, &e.pos_reponse2txt);

				SDL_BlitSurface(e.reponse2, NULL, ecran, &e.pos_reponse3txt);

			
			}
			break;
			case 3:
			{
				SDL_BlitSurface(e.button, NULL, ecran, &e.pos_reponse1);

				SDL_BlitSurface(e.button, NULL, ecran, &e.pos_reponse2);

				SDL_BlitSurface(e.button_s, NULL, ecran, &e.pos_reponse3);


				SDL_BlitSurface(e.rep3, NULL, ecran, &e.pos_reponse1txt);

				SDL_BlitSurface(e.rep1, NULL, ecran, &e.pos_reponse2txt);

				SDL_BlitSurface(e.reponse2, NULL, ecran, &e.pos_reponse3txt);

	
			}
			break;
			default:
			{
				SDL_BlitSurface(e.button, NULL, ecran, &e.pos_reponse1);

				SDL_BlitSurface(e.button, NULL, ecran, &e.pos_reponse2);

				SDL_BlitSurface(e.button, NULL, ecran, &e.pos_reponse3);


				SDL_BlitSurface(e.rep3, NULL, ecran, &e.pos_reponse1txt);

				SDL_BlitSurface(e.rep1, NULL, ecran, &e.pos_reponse2txt);

				SDL_BlitSurface(e.reponse2, NULL, ecran, &e.pos_reponse3txt);

				}
			}	
			break;
		}
		case 2:{
			switch(e.pos_selected){
			case 1:
			{
				SDL_BlitSurface(e.button_s, NULL, ecran, &e.pos_reponse1);

				SDL_BlitSurface(e.button, NULL, ecran, &e.pos_reponse2);

				SDL_BlitSurface(e.button, NULL, ecran, &e.pos_reponse3);


				SDL_BlitSurface(e.rep1, NULL, ecran, &e.pos_reponse1txt);

				SDL_BlitSurface(e.rep3, NULL, ecran, &e.pos_reponse2txt);

				SDL_BlitSurface(e.reponse2, NULL, ecran, &e.pos_reponse3txt);


			}
			break;
			case 2:
			{
				SDL_BlitSurface(e.button, NULL, ecran, &e.pos_reponse1);

				SDL_BlitSurface(e.button_s, NULL, ecran, &e.pos_reponse2);

				SDL_BlitSurface(e.button, NULL, ecran, &e.pos_reponse3);


				SDL_BlitSurface(e.rep1, NULL, ecran, &e.pos_reponse1txt);

				SDL_BlitSurface(e.rep3, NULL, ecran, &e.pos_reponse2txt);

				SDL_BlitSurface(e.reponse2, NULL, ecran, &e.pos_reponse3txt);

			
			}
			break;
			case 3:
			{
				SDL_BlitSurface(e.button, NULL, ecran, &e.pos_reponse1);

				SDL_BlitSurface(e.button, NULL, ecran, &e.pos_reponse2);

				SDL_BlitSurface(e.button_s, NULL, ecran, &e.pos_reponse3);


				SDL_BlitSurface(e.rep1, NULL, ecran, &e.pos_reponse1txt);

				SDL_BlitSurface(e.rep3, NULL, ecran, &e.pos_reponse2txt);

				SDL_BlitSurface(e.reponse2, NULL, ecran, &e.pos_reponse3txt);


	
			}
			break;
			default:
			{
				SDL_BlitSurface(e.button, NULL, ecran, &e.pos_reponse1);

				SDL_BlitSurface(e.button, NULL, ecran, &e.pos_reponse2);

				SDL_BlitSurface(e.button, NULL, ecran, &e.pos_reponse3);


				SDL_BlitSurface(e.rep1, NULL, ecran, &e.pos_reponse1txt);

				SDL_BlitSurface(e.rep3, NULL, ecran, &e.pos_reponse2txt);

				SDL_BlitSurface(e.reponse2, NULL, ecran, &e.pos_reponse3txt);


				}
			}
			break;
		}
		case 3:{
			switch(e.pos_selected){
			case 1:
			{
				SDL_BlitSurface(e.button_s, NULL, ecran, &e.pos_reponse1);

				SDL_BlitSurface(e.button, NULL, ecran, &e.pos_reponse2);

				SDL_BlitSurface(e.button, NULL, ecran, &e.pos_reponse3);


				SDL_BlitSurface(e.rep1, NULL, ecran, &e.pos_reponse1txt);

				SDL_BlitSurface(e.reponse2, NULL, ecran, &e.pos_reponse2txt);

				SDL_BlitSurface(e.rep3, NULL, ecran, &e.pos_reponse3txt);


			}
			break;
			case 2:                       
			{
				SDL_BlitSurface(e.button, NULL, ecran, &e.pos_reponse1);

				SDL_BlitSurface(e.button_s, NULL, ecran, &e.pos_reponse2);

				SDL_BlitSurface(e.button, NULL, ecran, &e.pos_reponse3);


				SDL_BlitSurface(e.rep1, NULL, ecran, &e.pos_reponse1txt);

				SDL_BlitSurface(e.reponse2, NULL, ecran, &e.pos_reponse2txt);

				SDL_BlitSurface(e.rep3, NULL, ecran, &e.pos_reponse3txt);
			
			}
			break;
			case 3:
			{
				SDL_BlitSurface(e.button, NULL, ecran, &e.pos_reponse1);

				SDL_BlitSurface(e.button, NULL, ecran, &e.pos_reponse2);

				SDL_BlitSurface(e.button_s, NULL, ecran, &e.pos_reponse3);


				SDL_BlitSurface(e.rep1, NULL, ecran, &e.pos_reponse1txt);

				SDL_BlitSurface(e.reponse2, NULL, ecran, &e.pos_reponse2txt);

				SDL_BlitSurface(e.rep3, NULL, ecran, &e.pos_reponse3txt);

	
			}
			break;
			default:
			{
				SDL_BlitSurface(e.button, NULL, ecran, &e.pos_reponse1);

				SDL_BlitSurface(e.button, NULL, ecran, &e.pos_reponse2);

				SDL_BlitSurface(e.button, NULL, ecran, &e.pos_reponse3);


				SDL_BlitSurface(e.rep1, NULL, ecran, &e.pos_reponse1txt);

				SDL_BlitSurface(e.reponse2, NULL, ecran, &e.pos_reponse2txt);

				SDL_BlitSurface(e.rep3, NULL, ecran, &e.pos_reponse3txt);

				}
			}

			break;
		}
	}
		SDL_Flip(ecran);
	SDL_Delay(100);
}


void animerEnigme(Enigme *e){
		 	
	if (e->clock_num >=0 && e->clock_num <7) {
	e->clock_num++;
	e->single_Clock.x=e->clock_num * e->single_Clock.w;

	}
	
	if ( e->clock_num == 7) {
	e->clock_num=0;
	e->single_Clock.x=e->clock_num * e->single_Clock.w;

	}
 
	 
}

void winLost(Enigme e,SDL_Surface *ecran)
{

	SDL_Surface *win;
	SDL_Surface *lost;
SDL_Rect pos;//={160,330}; 
        pos.x=160;
       pos.y=330;
        win=IMG_Load("img/youwin.png");
	lost=IMG_Load("img/youlost.png");
if(e.win==1){
printf("You win\n");
SDL_BlitSurface(win, NULL, ecran,&pos);
							SDL_Flip(ecran);
							
							}else{	
							SDL_BlitSurface(lost, NULL, ecran, &pos);
							SDL_Flip(ecran);
							printf("You lost\n");	
							}
							SDL_Delay(2000);


}





























