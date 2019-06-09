#include <stdio.h>
#include <SDL/SDL.h>


float sync() 
{
        long int aika;
        float sync=0;
	long int tv;

	static long int atv;
	
	tv = SDL_GetTicks();
        aika = (tv - atv);
	if (aika < 0) 
	{
		aika = 0;
	}
        atv = SDL_GetTicks();
        
	sync = (aika/1000.0);

	return sync;
}




