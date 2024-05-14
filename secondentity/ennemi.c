#include "ennemi.h"

///////////////////////////

void initEnnemi(Ennemi *e){
  int i ;
  char ch[100]= "secondentity/ennemi/";
  char n [3],ch1[100];
  for(i=0;i<12;i++){
    strcpy (ch1,"");
    strcat (ch1,ch);

    sprintf (n, "%d" ,i);
    strcat (ch1,n);

    strcat (ch1, ".png");

    e->image[i]=IMG_Load(ch1); 
    if  (e->image[i]==NULL)
    {
      printf("Unable to load Ennemi %s\n" , IMG_GetError());
    }
    e->position.x =650;
    e->position.y =700;
    e->direction = 0;

    e->numIM = 0;
    e->status = 0;



  }


}
//////////////////////////////
void afficherEnnemi (Ennemi e,SDL_Surface *ecran){
  SDL_BlitSurface (e.image[e.numIM],NULL,ecran,&e.position);



}

////////////////////////////////
void animerEnnemi (Ennemi *e){
if(e->numIM%2==1) e->position.y=700;
else e->position.y=790;
  if(e->direction==0 && e->status ==0){ 
    e->numIM++;
    if (e->numIM>2) e->numIM=0;

  }
  if (e->direction==1 && e->status ==0)
  {
    e->numIM++;
    if (e->numIM>5) e->numIM=3;


  }

  ///////////////////////////////////
  if(e->direction==0 && e->status ==1){
    e->numIM++;
    if (e->numIM>8) e->numIM=6;

  }
  if(e->direction==1 && e->status ==1){
    e->numIM++;
    if (e->numIM>11) e->numIM=9;

  }



}
//////////////////////////////////
void move(Ennemi *e){
  if ((e->position.x>=300)&&(e->position.x<500)&&(e->direction==0)){
    
    e->position.x=e->position.x + 10; 
    animerEnnemi(e);
    if (e->position.x >= 500){
      e->direction = 1;//a gauche 
    }

  }
  if ((e->direction ==1)&&(e->position.x>300)){
    
    e->position.x=e->position.x - 10 ;
    animerEnnemi(e);
    if (e->position.x <=300)
    {
      e->direction=0;// adroite
    }

  }



}
/////////////////////////////////////////
int collisionBB (SDL_Rect posp,Ennemi e){
  if ((((posp.x+164) >= e.position.x)) && ((posp.x+164) <= (e.position.x+e.image[e.numIM]->w))&&((posp.y+256)>=e.position.y)){
    return 1;
  }
  if (((posp.x >= e.position.x)) && (posp.x <= (e.position.x+e.image[e.numIM]->w))&&((posp.y+256)>=e.position.y)){
    return 1;
  }

  return 0;
}

void moveAI(Ennemi *e,SDL_Rect pos){
  if (e->position.x-pos.x<100 && e->position.x>pos.x){ 
    e->status =1;//9rib
    e->direction = 1;//gauche
    e->numIM =9;
    e->position.x=e->position.x-4;
    animerEnnemi(e);
  }
  if ((e->position.x-pos.x)<300&&e->status ==0 &&e->position.x>pos.x){
    e->status = 0;
    e->direction = 1;
    e->position.x=e->position.x-4;
    animerEnnemi(e);

  }
  ////////////////////////
  if (pos.x-e->position.x<100 && e->position.x<pos.x){ 
    e->status =1;
    e->direction = 0;
    e->numIM =6;
    e->position.x=e->position.x+4;
    animerEnnemi(e);
  }
  if ((pos.x-e->position.x)<300&&e->status ==0 &&e->position.x<pos.x){
    e->status = 0;
    e->direction = 1;
    e->position.x=e->position.x+4;
    animerEnnemi(e);

  }


}

  
  











