#include <stdio.h>
#include <string.h>
#include <SDL/SDL.h>
#include <SDL/SDL_rotozoom.h>
#include <SDL/SDL_gfxPrimitives.h>
#include <SDL/SDL_ttf.h>
#include "object.h"
#include "sync.h"
#include "defines.h"

int NextFrame(t_object *player,float synk) 
{
		if ((player->eteen == 1 || player->taakse == 1) && player->spritecount != 1) {
			player->anim = player->anim + player->spritecount*synk;	
			if (player->anim >= player->spritecount ) {
				player->anim = 1;
			}
			return player->anim;
		} 
		else
		{
			return 0;
		}	
}


void Piirra(t_object *player,float synk, SDL_Surface *ruutu, int rotate) 
{

		SDL_Surface *temp = NULL;
		SDL_Rect ruutu_alue;
		SDL_Rect paikka;
		int frame = 0;
		paikka.x=0;
		paikka.y=0;
		frame = NextFrame(player, synk);

		DEBUG_OUT2("Piirto raamilla %i...\n",frame);

		if (rotate == 1)
		{
			DEBUG_OUT("rotozoomSurface..\n");
			temp = rotozoomSurface(player->sprite[ frame],((player->kulma-90)),1,1);
			if (temp == NULL)
			{
				DEBUG_OUT("Frame not found, this should not happen...\n");
				SDL_FreeSurface(temp);		
				return;
			}

			player->alue.w = temp->w;
			player->alue.h = temp->h;
		
			DEBUG_OUT("Asetetaan kuvan sijainti...\n");
			ruutu_alue.x = player->x - temp->w/2;		
			ruutu_alue.y = player->y - temp->h/2;

			DEBUG_OUT("Pyöritelty kuva näyttöön...\n");
			SDL_BlitSurface(temp, &player->alue, ruutu, &ruutu_alue); 
			DEBUG_OUT("Muistin vapautus..\n");
			if (temp != NULL) SDL_FreeSurface(temp);		
			DEBUG_OUT("OK!\n");
		}
		else
		{
			
			if (player->sprite[ frame ] == NULL)
			{
				DEBUG_OUT("Frame not found, this should not happen...\n");
				return;
			}
		
			ruutu_alue.x = player->x - player->alue.w/2;		
			ruutu_alue.y = player->y - player->alue.h/2;
			SDL_BlitSurface(player->sprite[ frame ], NULL, ruutu, &ruutu_alue); 
			
		}
	//if (temp != NULL) SDL_FreeSurface(temp);		
			
}



void DrawTeksti(char *teksti, TTF_Font *font, SDL_Surface *ruutu, int x, int y)
{

	SDL_Color color={0,0,255};
	SDL_Rect ruutu_paikka;
	SDL_Surface *text_surface = NULL;
	int i=0;
	char tmp[100];
	int paikkax = 0;
	int paikkay = 0;
	int tekstin_korkeus=0;

	while (teksti[i] != '\0')
	{
		
		if (text_surface == NULL)
		{
			if (i > 0)
			{
				paikkax = paikkax + tekstin_korkeus;			
			}	
			ruutu_paikka.x = x + paikkax;
		}
    		else 
		{
			tekstin_korkeus = text_surface->h/2;
			paikkax = paikkax + text_surface->w;
			ruutu_paikka.x = x + paikkax;
		}

    		ruutu_paikka.y = y + paikkay;
    		
		if (teksti[i] == '\n' && i != 0)
		{
			paikkay = paikkay + text_surface->h;
		}


		sprintf(tmp, "%c", teksti[i]);
		if (text_surface != NULL) SDL_FreeSurface(text_surface);
    		text_surface = TTF_RenderText_Blended(font, tmp , color);

    		if(text_surface == NULL) {
			DEBUG_OUT2("%s\n",TTF_GetError());
    			//handle error here, perhaps print TTF_GetError at least
	    		
		} else {
	    		SDL_BlitSurface(text_surface,NULL,ruutu, &ruutu_paikka);
	    		//perhaps we can reuse it, but I assume not for simplicity.
		}
		i++;
	}
	if (text_surface != NULL) SDL_FreeSurface(text_surface);
    		
}

void LoadSprites(t_object *player, char *kuva) {
	int k=0,j=0;	
	char ctmp[100] = "";

	for (k=0;k < player->spritecount;k++) {
		while (kuva[j] != '\0') {
			ctmp[j] = kuva[j];
			if (kuva[j] == 'X' ) {
				ctmp[j] = 48+k;
			}
			j++;
		}
		j=0;

		if (k<0 && player->spritecount != k-1)
		{
			player->sprite[k] = player->sprite[k-1];
		} else {		
		
			DEBUG_OUT2("Loading image %s...\n",ctmp);	
			player->sprite[k] = SDL_LoadBMP(ctmp);
			if (player->sprite[k] == NULL) 
			{
				printf("Error while loading image %s: %s\n",ctmp, SDL_GetError());
				exit(1);	
			}

			SDL_SetColorKey(player->sprite[k], SDL_SRCCOLORKEY, SDL_MapRGB(player->sprite[k]->format, 255, 255, 255));

		}
	}	
}

