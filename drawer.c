#include "drawer.h" 

/**************************************************
  drawer.c
 Fichier de gestion et création des primitives de dessin 

 **************************************************/

/*
  Active SDL et initialise la surface screen.
  Initialise également les couleurs de la structure enum du drawer.h

  param:les dimensions de l'écran.
 */
void
init(int width, int height) {
    
    printf("Initializing SDL.\n");
    
    if((SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO)==-1)) { 
        printf("Could not initialize SDL: %s.\n", SDL_GetError());
        exit(-1);
    }

     if((TTF_Init()==-1)){ 
        printf("Could not initialize TFF: %s.\n", SDL_GetError());
        exit(-1);
     }
    
    printf("SDL initialized.\n");
    
    screen = SDL_SetVideoMode(height, width, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    if ( screen == NULL ) {
        fprintf(stderr, "Couldn't set 640x480x8 video mode: %s\n",
                        SDL_GetError());
        exit(1);
    }
    printf("Set 640x480 at %d bits-per-pixel mode\n",
           screen->format->BitsPerPixel);    
    initColors();
}

/*
  Active SDL et initialise une surface et renvoit un pointeur sur celle-ci.
  Initialise également les couleurs de la structure enum du drawer.h
  
  param:les dimensions de l'écran.
 */
SDL_Surface*
initScreen(int width,int heigh){
  SDL_Surface* tmp;
  tmp = SDL_SetVideoMode(640, 480, 32, SDL_SWSURFACE|SDL_ANYFORMAT);
    if ( screen == NULL ) {
        fprintf(stderr, "Couldn't set 640x480x8 video mode: %s\n",
                        SDL_GetError());
        exit(1);
    }
    return tmp;
}

/*
  Boucle qui attend un event quelconque sur la fenêtre pour terminer. 
 */
int
waitKeyboard()
{
  SDL_Event event;
  while (event.type != SDL_QUIT && event.type != SDL_KEYDOWN){
    SDL_WaitEvent(&event);
  }
  return 0;
}

/*
  Actualise la surface screen global.
 */
void
update(){
  SDL_UpdateRect(screen, 0, 0, 0, 0);
}

/*
  Actualise une surface passé une argument.

  param:la surface.
 */
void
updateScreen(SDL_Surface* scr){
  SDL_UpdateRect(scr, 0, 0, 0, 0);
}

/*
  Modifie un pixel par une couleur.

  param:la surface, l'abcisse du pixel, l'ordonnée du pixel et sa couleur.
 */
void
setPixel(SDL_Surface* scr, int x, int y, Uint32 col){
  *((Uint32*)(scr->pixels) + x + y * screen->w) = col;
}

/*
  Modifie un pixel par une couleur et vérifie si celui-ci respecte bien dans les
  dimension de la surface

  param:la surface, l'abcisse du pixel, l'ordonnée du pixel et sa couleur.
 */
void
setPixelSafe(SDL_Surface* scr, int x, int y, Uint32 col)
{
  if (x >= 0 && x < scr->w &&
      y >= 0 && y < scr->h)
    setPixel(scr, x, y, col);
}

/*
  Initialise le tableau de couleur nomé colors.
 */
void initColors()
{
  colors[C_BLACK]         = SDL_MapRGB(screen->format, 0x00, 0x00, 0x00);
  colors[C_DARK_BLUE]     = SDL_MapRGB(screen->format, 0x00, 0x00, 0x80);
  colors[C_DARK_GREEN]    = SDL_MapRGB(screen->format, 0x00, 0x80, 0x00);
  colors[C_DARK_CYAN]     = SDL_MapRGB(screen->format, 0x00, 0x80, 0x80);
  colors[C_DARK_RED]      = SDL_MapRGB(screen->format, 0x80, 0x00, 0x00);
  colors[C_DARK_MAGENTA]  = SDL_MapRGB(screen->format, 0x80, 0x00, 0x80);
  colors[C_OCRE]          = SDL_MapRGB(screen->format, 0x80, 0x80, 0x00);
  colors[C_GREY_CLAIR]    = SDL_MapRGB(screen->format, 0xC0, 0xC0, 0xC0);
  colors[C_GREY]          = SDL_MapRGB(screen->format, 0x80, 0x80, 0x80);
  colors[C_BLUE]          = SDL_MapRGB(screen->format, 0x00, 0x00, 0xFF);
  colors[C_GREEN]         = SDL_MapRGB(screen->format, 0x00, 0xFF, 0x00);
  colors[C_CYAN]          = SDL_MapRGB(screen->format, 0x00, 0xFF, 0xFF);
  colors[C_RED]           = SDL_MapRGB(screen->format, 0xFF, 0x00, 0x00);
  colors[C_MAGENTA]       = SDL_MapRGB(screen->format, 0xFF, 0x00, 0xFF);
  colors[C_YELLOW]        = SDL_MapRGB(screen->format, 0xFF, 0xFF, 0x00);
  colors[C_WHITE]         = SDL_MapRGB(screen->format, 0xFF, 0xFF, 0xFF);
}

/*
void
initColors2(){
  colors2[C_BLACK]        = {0,0,0};
  colors2[C_DARK_BLUE]    = {0,0,128};
  colors2[C_DARK_GREEN]   = {0,128,0};
  colors2[C_DARK_CYAN]    = {0,128,128};
  colors2[C_DARK_RED]     = {128,0,0};
  colors2[C_DARK_MAGENTA] = {128,0,128};
  colors2[C_OCRE]         = {128,128,0};
  colors2[C_GREY_CLAIR]   = {192,192,192};
  colors2[C_GREY]         = {128,128,128};
  colors2[C_BLUE]         = {0,0,255};
  colors2[C_GREEN]        = {0,255,0};
  colors2[C_CYAN]         = {0,255,255};
  colors2[C_RED]          = {255,0,0};
  colors2[C_MAGENTA]      = {255,0,255};
  colors2[C_YELLOW]       = {255,255,0};
  colors2[C_WHITE]        = {255,255,255};
  }
*/

/*
  Fonction de récupération de la couleur d'un pixel.

  param:la surface, un abcisse, une ordonnée.
 */
Uint32 getPixel(SDL_Surface *surface, int x, int y)
{
  int bpp = surface->format->BytesPerPixel;
  Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;
  
  switch(bpp) {
  case 1:
    return *p;
    
  case 2:
    return *(Uint16 *)p;
    
  case 3:
    if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
      return p[0] << 16 | p[1] << 8 | p[2];
    else
      return p[0] | p[1] << 8 | p[2] << 16;
    
  case 4:
    return *(Uint32 *)p;
    
  default:
    return 0;      
    }
}

/*
  Fonction d'affichage d'un rectangle plein.

  param:un point, la largeur du rectangle, la longueur, la couleur.
 */
void fullLine(int x, int y, int w, int h, Uint32 col){
  SDL_Rect r; 
  r.x = x;
  r.y = y;
  r.w = w;
  r.h = h;
  SDL_FillRect(screen, &r, col);
}

/*
  Efface une surface

  param:la surface à effacer
 */
void deletScreen(SDL_Surface* scr){
  SDL_FillRect(scr, NULL, colors[C_BLACK]);
}

/*
  Inverse mutuelement deux valeurs 
 */
void switchInt(int* x, int* y)
{
  int t = *x;
  *x = *y;
  *y = t;
}

/*
  Affichage d'une ligne entre deux points.
  Algo basé sur des opérations elementaires et décalages de 
  bits, algorithme Bresenham.

  param:la surface,le point 1,le point 2, la couleur de la ligne 
*/
void line(SDL_Surface* scr, int x1, int y1, int x2, int y2, Uint32 col)
{
  int d, dx, dy, aincr, bincr, xincr, yincr, x, y;
 
  if (abs(x2 - x1) < abs(y2 - y1)) {
    /* parcours par l'axe vertical */
 
    if (y1 > y2) {
      switchInt(&x1, &x2);
      switchInt(&y1, &y2);
    }
    
    xincr = x2 > x1 ? 1 : -1;
    dy = y2 - y1;
    dx = abs(x2 - x1);
    d = 2 * dx - dy;
    aincr = 2 * (dx - dy);
    bincr = 2 * dx;
    x = x1;
    y = y1;
 
    setPixelSafe(scr,x, y, col);
 
    for (y = y1+1; y <= y2; ++y) {
      if (d >= 0) {
	x += xincr;
	d += aincr;
      } else
	d += bincr;
 
      setPixelSafe(scr,x, y, col);
    }
 
  } else {
    /* parcours par l'axe horizontal */
    
    if (x1 > x2) {
      switchInt(&x1, &x2);
      switchInt(&y1, &y2);
    }
 
    yincr = y2 > y1 ? 1 : -1;
    dx = x2 - x1;
    dy = abs(y2 - y1);
    d = 2 * dy - dx;
    aincr = 2 * (dy - dx);
    bincr = 2 * dy;
    x = x1;
    y = y1;
 
    setPixelSafe(scr, x, y, col);
 
    for (x = x1+1; x <= x2; ++x) {
      if (d >= 0) {
	y += yincr;
	d += aincr;
      } else
	d += bincr;
 
      setPixelSafe(scr, x, y, col);
    }
  }    
}

/*
  Affiche un cercle

  param:la surface, un point , le rayon et une couleur.
 */
void circle(SDL_Surface* scr, int cx, int cy, int edge, int col)
{
  int d, y, x;
  
  d = 3 - (2 * edge);
  x = 0;
  y = edge;
 
  while (y >= x) {
    setPixelSafe(scr, cx + x, cy + y, col);
    setPixelSafe(scr, cx + y, cy + x, col);
    setPixelSafe(scr, cx - x, cy + y, col);
    setPixelSafe(scr, cx - y, cy + x, col);
    setPixelSafe(scr, cx + x, cy - y, col);
    setPixelSafe(scr, cx + y, cy - x, col);
    setPixelSafe(scr, cx - x, cy - y, col);
    setPixelSafe(scr, cx - y, cy - x, col);
 
    if (d < 0)
      d = d + (4 * x) + 6;
    else {
      d = d + 4 * (x - y) + 10;
      y--;
    }
 
    x++;
  }
}

/*
  Affiche un texte sur une surface.

  param:la surface, le texte, la taille du texte, l'abcisse et l'ordonné de point d'affichage.
 */
void
addText(SDL_Surface* screenText, char * text,char* plc,int size ,int x ,int y,SDL_Color col){
  police = TTF_OpenFont(plc, size);
  screenText = TTF_RenderText_Blended(police, text, col);
  pos->x = x;
  pos->y = y;
  SDL_BlitSurface(screenText, NULL, screen, pos);
  SDL_Flip(screen);
}

/*
  Fonction de remplissage de forme

  param:la surface,un abcisse et une ordonnée de depart et la couleur.
 */
void
proliferation(SDL_Surface* scr, int x, int y,Uint32 col){

  if (x >= 2 && x < ((scr->w)-2) &&
      y >= 2 && y < ((scr->h)-2)){
    setPixel(scr,x,y,col);
    if(getPixel(scr,x+1,y)!=col)
      proliferation(scr, x+1, y, col);
    if(getPixel(scr,x-1,y)!=col)
      proliferation(scr, x-1, y, col);
    if(getPixel(scr,x,y+1)!=col)
      proliferation(scr, x,y+1,col);
    if(getPixel(scr,x,y-1)!=col)
      proliferation(scr, x,y-1,col); 
      }
}
