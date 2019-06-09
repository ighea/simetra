#include <stdio.h>
#include <string.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>


int Menu(SDL_Surface *ruutu, SDL_Surface *menu_tausta, TTF_Font *font, char *lista ,int lista_count,int valinta, int x,int y, int w, int h, int versionnumber, int useable)
{

	SDL_Event tapahtuma;
	SDL_Rect ruutu_alue;
	SDL_Rect valikko_alue;
	SDL_Surface *text_surface = NULL;
	SDL_Color color={0,0,255};
	SDL_Color color2={0,200,0};

	char teksti[100];

	int lopetus = 0;
//	int valinta = 0;
	int i=0,j=0,k=0,l=0;
//	int m=0;
//	int font_size = 17;
	/*
	for (m=0;m<100;m++)
	{
		teksti[h] = NULL;
	}
	m=0;
	*/
	ruutu_alue.x = x;
	ruutu_alue.y = y;
	ruutu_alue.w = w;
	ruutu_alue.h = h;

	while (lopetus == 0) {

		SDL_BlitSurface(menu_tausta,NULL, ruutu, &ruutu_alue);
		
		for (i=0;i<lista_count;i++)
		{
			
			while (l<i+1) {
				l++;
				for (j=0;lista[k] != '\n';j++)
				{
					teksti[j] = lista[k];
					k++;
				}
				k++;
			}
			k=0;
			l=0;
			teksti[j] = '\0';
			
	
			if (valinta == i)
			{
				text_surface = TTF_RenderText_Blended(font, teksti, color2);
			} else 
			{	
				text_surface = TTF_RenderText_Blended(font, teksti, color);
			}
			valikko_alue.y = y + h/2 - h/10 + text_surface->h*i;
			valikko_alue.x = x + w/2 - text_surface->w/2;
			SDL_BlitSurface(text_surface,NULL, ruutu, &valikko_alue);
			if (text_surface != NULL) SDL_FreeSurface(text_surface);		
		}
		
		//Piirretään versio näytölle		
		if (versionnumber == 1)
		{
/*			text_surface = TTF_RenderText_Solid(font, VERSION, color);
			valikko_alue.x = w - text_surface->w;
			valikko_alue.y = h - text_surface->h;
			SDL_BlitSurface(text_surface,NULL, ruutu, &valikko_alue);
			SDL_FreeSurface(text_surface);
*/			
		}
		
		SDL_Flip(ruutu);
		while ( SDL_PollEvent(&tapahtuma) )
		{	
			if (tapahtuma.type == SDL_QUIT)
			{
				lopetus = 1;
				valinta = -1;
			}
			if (tapahtuma.type == SDL_KEYDOWN)
			{
				if (tapahtuma.key.keysym.sym == SDLK_ESCAPE)
				{
					lopetus = 1;
					valinta = -1;
				}
				if (useable == 1 && tapahtuma.key.keysym.sym == SDLK_UP)
				{
					valinta--;
					if (valinta < 0) 
					{
						valinta = lista_count -1;					
					}
				}
				if (useable == 1 && tapahtuma.key.keysym.sym == SDLK_DOWN)
				{
					valinta++;
					if (valinta >= lista_count)
					{
						valinta = 0;
					}
				}
				if (tapahtuma.key.keysym.sym == SDLK_RETURN)
				{
					lopetus = 1;
				}
			}			
		}

		SDL_Delay(10);
	}
	//Lets release the used text surface...
	//if (text_surface != NULL) SDL_FreeSurface(text_surface);		

	return valinta;
}
