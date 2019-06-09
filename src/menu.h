//MENU
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>

//Palauttaa valitun kohdan numeron 0 - n(<=0), ESC -> -1
//ruutu = näyttö
//menu_tausta = valikon taustakuva
//lista = lista valikon riveistä
//lista_count = valikon valintojen määrä
// x,y = vasen ylä nurkka
// h,w = koko
int Menu(SDL_Surface *ruutu, SDL_Surface *menu_tausta, TTF_Font *font, char *lista,int lista_count,int valinta, int x,int y,int w, int h, int versionnumber, int useable);
