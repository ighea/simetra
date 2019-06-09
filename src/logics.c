#include <stdio.h>
#include <string.h>
#include <SDL/SDL.h>
#include <SDL/SDL_rotozoom.h>
#include <SDL/SDL_gfxPrimitives.h>
#include <SDL/SDL_ttf.h>
#include "object.h"
#ifdef _WIN32
#include <windows.h>
#endif


//Returns the angle in degree from object1 towards object2
float AngleTowards(t_object *from, t_object *to)
{
	float kulma=0;
	float x=0;
	float y=0;

	//Otuksen suunta kohti playeria	
	x = to->x - from->x;
	y = to->y - from->y;
	kulma = atan( y / x )*(180/3.14);
	if (x>0) kulma = -kulma;
	if (x<0) kulma = -kulma + 180;
		
	return kulma;
}


int Tormays(t_object *bullet, t_object *otus, int fix) 
{
	if ((otus->x + otus->alue.w/2 - fix > bullet->x ) && (otus->x - otus->alue.w/2 + fix < bullet->x)) 
	{
		if ((otus->y + otus->alue.h/2 - fix > bullet->y ) && (otus->y - otus->alue.h/2 + fix < bullet->y)) 
		{
			return 1;
		}
	}			
	
	return 0;
}


int Random(float min, float max)
{
	int luku=0;
	luku = min + (max * (rand() / (RAND_MAX + 1.0)));
	return luku;
}
