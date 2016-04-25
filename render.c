#include "render.h"

/************************************
            Render.c 


 ************************************/


/*
  Initialise et execute l'affichage des chemins grace aux structures de données générées
  par parser.c tel que ways, la liste des chemins du fichier xml. 

  param: dimension de la fenêtre graphique à afficher
 */
void
initRender(int width, int height){
  int continu=1;
  SDL_Rect* pos=malloc( sizeof(pos) );
  init(width,height);

  SDL_FillRect(screen, NULL, colors[C_WHITE]);
 
  /* line(screen,15,50,100,150,colors[C_RED]);
  line(screen,100,150,100,50,colors[C_RED]);
  line(screen,100,50,5,45,colors[C_RED]);
  line(screen,5,45,15,50,colors[C_RED]);
  proliferation(screen, 80, 125,colors[C_RED]);
  update();*/

  printWys(screen,ways);
  update();
  
  while(continu){
    continu=waitKeyboard();
  }
  
  SDL_Quit();
  printf("Quiting....\n");

  //printWays(ways);

  SDL_FreeSurface(screen);
  freeNodes(nds);
  freeWays(ways);
  free(doc);
  free(cur);
}


/*
  Parcoure la liste de chemin et en fonction du type de chemin,associe une taille et une couleur
  pour l'affichage de celui-ci.
  param:la surface et la liste de chemin.
*/
void
printWys(SDL_Surface* scr,l_way* ways){
  int size=-1;
  
  while(ways->next != NULL){
    Uint32* col=malloc ( sizeof(Uint32) );
    switch (ways->cur->type){
    case 1 :
      //printf("Cas church");
      size=2;
      col=&colors[C_GREEN];
      break;
    case 2 :
      //printf("cas hotel");
      size=2;
      col=&colors[C_GREY];
      break;
    case 3 :
      //printf("Cas school");
      size=2;
      col=&colors[C_GREEN];
      break;
    case 4 :
      //printf("cas motorway");
      size=3;
      col=&colors[C_OCRE];
    case 5 :
      //printf("cas road");
      size=4;
      col=&colors[C_YELLOW];
      break;
      //Cas road
    case 6 :
      //printf("cas pedestrian ");
      size=2;
      col=&colors[C_OCRE];
      break;
    case 7 :
      //printf("cas river ");
      size=3;
      col=&colors[C_BLUE];
      break;
    case 8 :
      //printf("cas canal");
      size=4;
      col=&colors[C_DARK_BLUE];
      break;
    case 9 :
      //printf("cas natural water lac");
      size=4;
      col=&colors[C_DARK_BLUE];
      break;
    case 10 :
      //printf("cas coastline ");
      size=5;
      col=&colors[C_DARK_RED];
      break;
    case 11 :
      //printf("cas landuse=grass");
      size=1;
      col=&colors[C_DARK_GREEN];
      break;
    case 12 :
      //printf("cas landus=forest");
      size=1;
      col=&colors[C_DARK_GREEN];
      break;
    case 13 :
      //printf("cas leisure=park");
      size=2;
      col=&colors[C_DARK_GREEN];
      break;
    default:
      // printf("cas default");
      size=1;
      col=&colors[C_BLACK];
  
    }
    printWy(scr,ways->cur->lnode,col,size);//affichage du chemin courrant.
    /* if(ways->cur->area){
      printf("Dans affichage arrea\n");
      printArea(scr,ways->cur->lnode->cur,ways->cur->lnode->next->cur,col);
      printf("apre\n");
      }*/
    ways=ways->next;
  }
}

/*
  Parcour la liste de noed du chemin et "tire un trait" entre les deux.

  param:la surface , la liste de noed du chemin , une couleur et une taille  
 */
void
printWy(SDL_Surface* scr, l_node* nds,Uint32* col,int size){
  while(nds->next != NULL){
    if(nds->next->next!=NULL)
      printLine(scr, nds->cur, nds->next->cur, col, size);    
    nds=nds->next;
  }
}
/*
  Affiche un, point à l'ecran.

  param:la surface, le noeud et une couleur.
 */
void
printPt(SDL_Surface* scr, node* n, Uint32 col){
  setPixel(scr, n->p->x, n->p->y, col);
}

/*
  Affiche une ligne entre deux points.

  param:la surface, le noeud 1, le noeud 2, la couleur du trait et la taille du trait.
 */
void
printLine(SDL_Surface* scr, node* n1, node* n2, Uint32* col,int size){
  int i;
  line(scr, n1->p->x, (n1->p->y), n2->p->x, (n2->p->y), *col);
  for(i=1;i<=(size/2);i++){
    line(scr, n1->p->x, (n1->p->y)-i, n2->p->x, (n2->p->y)-i, *col);
    line(scr, n1->p->x, (n1->p->y)+i, n2->p->x, (n2->p->y)+i, *col);
  }
  //update();
}


/*
  Choisit un point juste à droite de la ligne et applique l'algorithme de remplissage de forme 
  Remarquez que pour cela on calcule l'équation de la droite puis on choisi un point aléatoire 
  de celle-ci et on le decale d'un pixel sur la droite.
 
  param:la surface, le noeud 1, le noeud 2, et la couleur pour le remplissage. 
 */
void
printArea(SDL_Surface* scr,node* n1,node* n2,Uint32* col){
  int randomX;
  if((n1->p->y)>(n2->p->y)){
    if((n1->p->x)>(n2->p->x)){
      randomX = rand() % (((n1->p->x)-1)+1-(n2->p->x)) + (n2->p->x) ; //random de x1-1 à x2
      proliferation(scr, randomX, pointOnLine(n1,n2,randomX)-1, *col);
    }
    else{
      randomX = rand() % ((n2->p->x)+1-((n1->p->x)+1)) + ((n1->p->x)+1); 
      proliferation(scr,randomX+1, pointOnLine(n1,n2,randomX),*col);
    }}
  else{
    if((n1->p->x)>(n2->p->x)){
      randomX = rand() % (((n1->p->x)-1)+1-(n2->p->x)) + ((n2->p->x));
      proliferation(scr, randomX, pointOnLine(n1,n2,randomX) -1,*col);
    }else{
      randomX = rand() % ((n2->p->x)+1-((n1->p->x)+1)) + ((n1->p->x)+1);
      proliferation(scr,randomX-1, pointOnLine(n1,n2,randomX),*col);     
    }
  }
}

/*
  Calcule l'equation de la droite et renvoie l'ordonnée associée à rd.
  param:noeud 1, noeud 2 et l'abcisse aléatoire rd.
 */
int
pointOnLine(node* n1, node* n2,int rd){
  double a= ((n2->p->y)-(n1->p->y))/ (n2->p->x)-(n2->p->x);// (y2-y1)/(x2-x1) on obtien a de y=ax+b
  double b= (n1->p->y)-(a*(n1->p->y));                  //on obtient b de y=ax+b
  return (int)a*rd+b;
    
}
