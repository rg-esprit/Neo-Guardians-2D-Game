#include "enigmetf.h"


void InitEnigme(Enigme *e)
{   
 



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
	GenererEnigmeAleatoire(e);

	

 

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

void GenererEnigmeAleatoire(Enigme *e) {
    srand(time(NULL));

    
    e->num_question = rand() % MAX_NUM_QUESTIONS + 1;
    e->positionVraiReponse = rand() % 3 + 1;

    
    ChargerEnigme(e);
}
void ChargerEnigme(Enigme *e) {
    
    FILE *fquestion = fopen("questions.txt", "r");
    if (fquestion == NULL) {
        printf("Erreur : Impossible d'ouvrir le fichier des questions.\n");
        exit(1); 
    }

    
    int num_total_questions = 0;
    char questionn[100]; 

    while (fgets(questionn, sizeof(questionn), fquestion) != NULL) {
        num_total_questions++;
    }

    
    fclose(fquestion);

    
    srand(time(NULL));

    
    int num_question_aleatoire = rand() % num_total_questions + 1;


    fquestion = fopen("questions.txt", "r");
    if (fquestion == NULL) {
        printf("Erreur : Impossible d'ouvrir le fichier des questions.\n");
        exit(1); 
    }

  
    char question_aleatoire[100]; 
    char reponse1[100]; 
    char reponse2[100]; 
    char reponse3[100]; 

    // Lire les questions et réponses jusqu'à atteindre la question aléatoire
    int num_question_lue = 0;
    while (fgets(questionn, sizeof(questionn), fquestion) != NULL) {
        num_question_lue++;
        if (num_question_lue == num_question_aleatoire) {
            // Stocker la question lue
            strcpy(question_aleatoire, questionn);

            // Lire les réponses correspondant à cette question
            FILE *freponse = fopen("reponses.txt", "r");
            if (freponse == NULL) {
                printf("Erreur : Impossible d'ouvrir le fichier des réponses.\n");
                exit(1); // Quitter le programme avec code d'erreur
            }

            // Variables pour stocker les réponses
            char rep1[100]; // Assurez-vous que cette taille est suffisante pour vos réponses
            char rep2[100]; // Assurez-vous que cette taille est suffisante pour vos réponses
            char rep3[100]; // Assurez-vous que cette taille est suffisante pour vos réponses

            // Lire les réponses pour cette question
            while (fgets(rep1, sizeof(rep1), freponse) != NULL &&
                   fgets(rep2, sizeof(rep2), freponse) != NULL &&
                   fgets(rep3, sizeof(rep3), freponse) != NULL) {
                // Sortir de la boucle une fois que les réponses sont lues
                break;
            }

            // Fermer le fichier des réponses après lecture
            fclose(freponse);

            // Copier les réponses dans les variables définies dans la structure Enigme (e)
            strcpy(reponse1, rep1);
            strcpy(reponse2, rep2);
            strcpy(reponse3, rep3);

            // Sortir de la boucle une fois que la question et les réponses sont lues
            break;
        }
    }

    // Fermer le fichier des questions après lecture
    fclose(fquestion);

    // Maintenant, vous avez la question aléatoire dans question_aleatoire et les réponses dans reponse1, reponse2 et reponse3
    // Vous pouvez les utiliser pour initialiser les surfaces SDL dans votre structure Enigme (e)

    // Exemple d'utilisation pour initialiser la surface de la question
    SDL_Color couleur = {0, 0, 0}; // Couleur du texte en noir
    e->question = TTF_RenderText_Blended(e->police, question_aleatoire, couleur);
    // Faites de même pour les réponses et autres éléments nécessaires

    // Autres opérations de chargement
}




