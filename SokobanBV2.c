#include<stdio.h>
#include<stdlib.h>
#include<SDL.h>
#include<SDL_types.h>
#include<time.h>


#define LC 32

void dessine(SDL_Surface * f);

void dessineTJeu(char ** TJeu, int taille);

void pause(){
  int cont=1;
  SDL_Event event;
  while( cont){
    SDL_WaitEvent(&event);
    switch(event.type){
    case SDL_QUIT:
      cont=0;
      break;
    default:
      cont=1;
    }
  }
}



SDL_Surface * Brique = NULL;
SDL_Surface * Michel = NULL;
SDL_Surface * ON = NULL;
SDL_Surface * OFF = NULL;
SDL_Surface * MichelPoint = NULL;
SDL_Surface * Point = NULL;
SDL_Surface * ecran = NULL;
SDL_Surface * rectangle = NULL;
SDL_Surface * carre = NULL;
SDL_Rect position;

int main(int argc, char ** argv){
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


  SDL_FillRect(ecran,NULL,SDL_MapRGB(ecran->format,150,200,175));
  SDL_Flip(ecran);
  OFF =  SDL_LoadBMP("interrupteurOff.bmp");
  ON =  SDL_LoadBMP("interrupteurOn.bmp");
  Brique = SDL_LoadBMP("Bloc.bmp");
  Michel = SDL_LoadBMP("Michel2.bmp");
  MichelPoint = SDL_LoadBMP("MichelPoint.bmp");
  Point = SDL_LoadBMP("Point.bmp");
  
  // printf("0 : Tableau pre enregistré\n1 : CreeTab\n");
  //scanf("%d",&choixTab);

  // int  taille=4;
  char** TJeu =(char**) malloc(4*sizeof(char*));
  TJeu[0]="PpCc";
  TJeu[1]="#IIc";
  TJeu[2]="#c #";
  TJeu[3]="#PC#";
  //printf("Plateau = \n%s\n %s\n %s\n %s\n",TJeu[0],TJeu[1],TJeu[2],TJeu[3]);
  
  SDL_WM_SetCaption("SokobanBV",NULL);

  SDL_Flip(ecran);
  //SDL_Flip(ecran);
  dessineTJeu(TJeu,taille);

  
  TJeu[0]="PPPP";
  TJeu[1]="    ";
  TJeu[2]="##cC";
  TJeu[3]="pI  ";
  dessineTJeu(TJeu,taille);
  

  SDL_FreeSurface(ecran);
  
  SDL_Quit() ;
  
  /*for(int i=taille;i>0; i--){
  free(TJeu[i-1]);
  }
  free(): invalid pointer
  Abandon (core dumped)
*/
  
  free(TJeu);
  return EXIT_SUCCESS ;
}


  void dessine(SDL_Surface * s){
    // SDL_FillRect(ecran,NULL,SDL_MapRGB(ecran->format, 0,255,0) ) ;
    SDL_BlitSurface(s,NULL,ecran,&position) ;
    SDL_Flip(ecran) ;
  }



void dessineTJeu(char ** TJeu, int taille){

  for(int i=0 ; i<taille;i ++){
    position.y=i*LC;
    for(int j=0; j<taille; j++){
      position.x=j *LC;
      printf("%d %d\n",i,j);
      if(TJeu[i][j]=='#'){
	//SDL_BlitSurface(Brique,NULL,ecran,&position) ;
	dessine(Brique);}
      else if(TJeu[i][j]=='C'){
	//	SDL_BlitSurface(OFF,NULL,ecran,&position) ;}
	
	dessine(OFF);}
      else if(TJeu[i][j]=='c'){
	//SDL_BlitSurface(ON,NULL,ecran,&position) ;}
	dessine(ON);}
      else if(TJeu[i][j]=='P'){
	//SDL_BlitSurface(Michel,NULL,ecran,&position) ;}
	dessine(Michel);}
      else if(TJeu[i][j]=='p'){
	//SDL_BlitSurface(Michel,NULL,ecran,&position) ;}
	dessine(MichelPoint);}
      else if(TJeu[i][j]=='I'){
	//SDL_BlitSurface(Michel,NULL,ecran,&position) ;}
	dessine(Point);}
    }
  }

SDL_Flip(ecran);
pause();
}
