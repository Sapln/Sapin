#include<stdio.h>
#include<stdlib.h>
#include<SDL.h>
#include<SDL_types.h>
#include<time.h>

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
void trouvePerso(char ** TJeu,int taille,position * perso);
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

  char** TJeu =(char**) malloc(4*sizeof(char*));
  TJeu[0]="    ";
  TJeu[1]="    ";
  TJeu[2]="    ";
  TJeu[3]="   P";

  position perso;
  perso.x=0;
  perso.y=0;
  printf("avant");
  pause();
  printf("apres");
  
  //  trouvePerso(TJeu,4,&perso);
  //  afficheTab2D(TJeu,4);
  // gauche();
  deplacement(TJeu,4);
  SDL_Quit();
  free(TJeu);
  
  return 0;}

void trouvePerso(char ** TJeu,int taille,position * perso){
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

/*void gauche(){
  SDL_Event event;
  int cont =1;
  while(cont){
    printf("a");
    SDL_WaitEvent(&event);
    switch(event.type){
    case SDL_QUIT:
      cont = 0;
      break;
    case SDL_KEYDOWN:
      cont = 0;
      break;
    default:
      cont=1;
    }}}
*/
	
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
  SDL_Event event ;
  position perso;
  trouvePerso(TJeu,taille,&perso);
  while(cont){
    printf("position=%d %d\n",perso.x,perso.y);
    event= pause();
    afficheTab2D(TJeu,taille);
    //    SDL_WaitEvent(&event) ;
    switch(event.type){
    case SDL_QUIT:
      cont=0;
      // printf("addddddddddddddddddddddddddddddddddd");
    case SDL_KEYDOWN:
      switch(event.key.keysym.sym){
      case SDLK_UP:
	if(perso.y>0 && ( TJeu[perso.y -1][perso.x] == 'I' || TJeu[perso.y-1][perso.x] == ' ')){
	  // TJeu[perso.y][perso.x]=' ';
	  
	  perso.y--;
	  //TJeu[perso.y][perso.x]='P';
	  //printf("aaaaaaaaaaaaaaaaaaaaaaaaaaa");
	  
	}
	//dessine(ecran) ;
	break ;
      case SDLK_DOWN:
	if(perso.y<taille-1 && ( TJeu[perso.y +1][perso.x] == 'I' || TJeu[perso.y+1][perso.x] == ' ')){
	  perso.y++;
	}
	//dessine(ecran) ;
	break ;

      case SDLK_LEFT :
	if(perso.x>0 && ( TJeu[perso.y][perso.x -1] == 'I' || TJeu[perso.y][perso.x-1] == ' ')){
	  perso.x--;
	}
	//dessine(ecran);
	break ;
      case SDLK_RIGHT:
	if(perso.x<taille-1 && ( TJeu[perso.y][perso.x +1] == 'I' || TJeu[perso.y][perso.x+1] == ' ')){
	  perso.x++;
	}
	//dessine(ecran) ;
	break ;
      case 'q':cont=0 ;
	break ;
      }
    }
  }

}

