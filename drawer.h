#ifndef __DRAWER_H__
#define __DRAWER_H__
#include <SDL.h>
#include <SDL_ttf.h>

enum {
  C_BLACK, C_DARK_BLUE, C_DARK_GREEN, C_DARK_CYAN, C_DARK_RED,
  C_DARK_MAGENTA, C_OCRE, C_GREY_CLAIR, C_GREY, C_BLUE, C_GREEN,
  C_CYAN, C_RED, C_MAGENTA, C_YELLOW, C_WHITE
};

Uint32 colors[16];
SDL_Color colors2[16];
SDL_Surface* screen;
SDL_Surface* texte;
TTF_Font* police;
SDL_Rect* pos;

void initColors();
void initColors2();
void init(int x, int y);
SDL_Surface* initScreen(int width,int heigh);
int waitKeyboard();
void update();
void updateScreen(SDL_Surface* scr);
void setPixel(SDL_Surface* screen, int x, int y, Uint32 col);
void setPixelSafe(SDL_Surface* screen, int x, int y, Uint32 col);
Uint32 getPixel(SDL_Surface *surface, int x, int y);
void fullLine(int x, int y, int w, int h, Uint32 col);
void deletScreen(SDL_Surface* scr);
void switchInt(int* x,int* y);
void line(SDL_Surface* scr,int x1, int y1, int x2, int y2, Uint32 col);
void circle(SDL_Surface* screen, int cx, int cy, int edge, int col);
void addText(SDL_Surface* screenText, char * text, char* plc, int size, int x, int y, SDL_Color col);
void proliferation(SDL_Surface* scr, int x, int y,Uint32 col);
#endif 
