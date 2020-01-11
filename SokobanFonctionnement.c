#include<stdio.h>
#include<stdlib.h>
#include<SDL.h>
#include<SDL_types.h>
#include<time.h>
#include<string.h>

typedef struct position{
  int x;
  int y;
}position;

typedef struct player{
  position pos;
}player;

#define LC 32



SDL_Surface * ecran = NULL;

//void gauche();
SDL_Event pause();
void trouvePerso(char ** TJeu,int taille,position * perso,char* caseInit);
void afficheTab2D(char ** tab, int taille);
void deplacement(char** TJeu,int taille);

int main(){
  int taille = 4;
  int WIDTH =  taille * LC;
  int HEIGHT= taille * LC;
  if(SDL_Init(SDL_INIT_VIDEO) == 1){
    fprintf(stderr,"Erreur SDL : %s\n",SDL_GetError());
    return -1;
  }
  printf("oijdoiĵoi");

  if(( ecran = SDL_SetVideoMode(WIDTH,HEIGHT,32,SDL_HWSURFACE)) == NULL){
    fprintf(stderr,"Erreur VideoMode : %s\n",SDL_GetError());
    exit(EXIT_FAILURE);}

  char** TJeu =(char**) malloc(taille*sizeof(char*));
  TJeu[0]=   (char*) malloc((taille+1)*sizeof(char));
  TJeu[1]=  (char*) malloc((taille+1)*sizeof(char));
  TJeu[2]=   (char*) malloc((taille+1)*sizeof(char));
  TJeu[3]=  (char*) malloc((taille+1)*sizeof(char));
  int i,j;
  for(i = 0; i < taille; i++)
  {
    for(j = 0; j < taille; j++)
    {
       TJeu[i][j]=' ';
    }
  }
  TJeu[3][3]='P';
  TJeu[2][2]='I';

  
  deplacement(TJeu,taille);
  SDL_Quit();
  free(TJeu);
  
  return 0;}

void trouvePerso(char ** TJeu,int taille,position * perso,char* caseInit){
  // position perso;
  perso->x=0;
  perso->y=0;
  
  int i,j;
  for(i = 0; i < taille; i++)
  {
    for(j = 0; j < taille; j++)
      {
        if(TJeu[i][j]=='p' || TJeu[i][j]=='P'){
	  perso->x = j;
	  perso->y = i;
	}
      }
  }
  caseInit=&TJeu[perso->y][perso->x];
  //printf("position=%d %d\n",perso->x,perso->y);
}
    

void afficheTab2D(char ** tab, int taille)
{
  int i,j;
  for(i = 0; i < taille; i++)
  {
    printf("\n");
    for(j = 0; j < taille; j++)
    {
      printf("%c  ", tab[i][j]);
    }
    printf("\n");
  }
  printf("\n");
}


	
SDL_Event pause(){
  // printf("oijio");
  int cont=1;
  SDL_Event event;
  while( cont){
    SDL_WaitEvent(&event);
    switch(event.type){
    case SDL_QUIT:
      cont=0;
      break;
    case SDL_KEYDOWN:
      cont=0;
      break;
    default:
      cont=1;
    }
  }
  return(event);
}

void deplacement(char** TJeu,int taille){
  int cont=1 ;
  char* change= (char*) malloc((taille+1)*sizeof(char));
  SDL_Event event ;
  position perso;
  position posPrev;
  char nouvCase;
  char exCase;
  
  trouvePerso(TJeu,taille,&perso,&nouvCase);
  afficheTab2D(TJeu,taille);
  while(cont){
    posPrev= perso;
    exCase=nouvCase;
    printf("position=%d %d\n",perso.x,perso.y);
    printf("position=%d %d\n",posPrev.x,posPrev.y);
    event= pause();
    
    switch(event.type){
    case SDL_QUIT:
      cont=0;
    case SDL_KEYDOWN:
      switch(event.key.keysym.sym){
      case SDLK_UP:
	if(perso.y>0){
	  if( TJeu[perso.y -1][perso.x] == 'I'){
	    perso.y--;
	    nouvCase='p';
	  }
	  else if(TJeu[perso.y-1][perso.x] == ' '){
	  
	  perso.y--;
	  nouvCase='P';
	  }
	}
      
	break ;
      case SDLK_DOWN:
	if(perso.y<taille-1){
	  if( TJeu[perso.y +1][perso.x] == 'I'){
	    perso.y++;
	    nouvCase='p';}
	  else if(TJeu[perso.y+1][perso.x] == ' '){
	    perso.y++;
	    nouvCase='P';
	  }
	}
	break ;
	
      case SDLK_LEFT :
	if(perso.x>0){
	  if( TJeu[perso.y][perso.x -1] == 'I'){
	    
	    perso.x--;
	    nouvCase='p';}
	  
	  else if(TJeu[perso.y][perso.x-1] == ' '){
	  perso.x--;
	    nouvCase='P';
	  }
	}
	//dessine(ecran);
	break ;
      case SDLK_RIGHT:
	if(perso.x<taille-1){
	  if( TJeu[perso.y][perso.x +1] == 'I'){
	    perso.x++;
	    nouvCase='p';}
	  else if(TJeu[perso.y][perso.x+1] == ' '){
	    perso.x++;
	    nouvCase='P';
	  }
	}
	break ;
      case 'q':
	cont=0 ;
	break ;
      }
    }

    if(exCase =='P'){
      exCase=' ';}
    else{
      exCase='I';}
    
    
    strcpy(change,TJeu[posPrev.y]);
    change[posPrev.x]=exCase;  
    strcpy(TJeu[posPrev.y],change);

    
    strcpy(change,TJeu[perso.y]);
    change[perso.x]=nouvCase;  
    strcpy(TJeu[perso.y],change);

    
    afficheTab2D(TJeu,taille);
  }

}

