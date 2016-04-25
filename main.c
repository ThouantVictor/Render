#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "render.h"

/***************************************
main.c
Fichier d'éxecution de l'application .
Il parse le fichier passé en argument 
et active la fenêtre graphique; 
 **************************************/
int
main(int argc, char **argv) {
  
  char *docname;
  if (argc <= 1) {
    printf("Usage: %s docname\n", argv[0]);   
    return(0);
  }
  
  printf("Usage: %s \n", argv[1]);
  docname = argv[1];
  int width=400;
  int height=700;
  parseDoc (docname,width,height);
  initRender(width,height);
  return (1);
}
