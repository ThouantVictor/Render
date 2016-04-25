#include "drawer.h"
#include "parser.h"

void initRender();
void printPt(SDL_Surface* scr, node* n, Uint32 col);
void printLine(SDL_Surface* scr, node* n1, node* n2, Uint32* col, int size); 
void printWy(SDL_Surface* scr, l_node* nds, Uint32* col, int size);
void printWys(SDL_Surface* scr,l_way* ways);
void printArea(SDL_Surface* scr,node* n1,node* n2,Uint32* col);
int pointOnLine(node* n1, node* n2,int rd);
