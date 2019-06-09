#include <stdio.h>
#include <string.h>
#include <SDL/SDL.h>
#include <SDL/SDL_rotozoom.h>
#include <SDL/SDL_gfxPrimitives.h>
#include <SDL/SDL_ttf.h>
#include "object.h"
#include "logics.h"
#include "graphic.h"
#ifdef _WIN32
#include <windows.h>
#endif

void OtusMovement(t_object *otus, t_object *player, float synk) 
{
/*	//Otuksen suunta kohti playeria	
	x = player->x - otus->x;
	y = player->y - otus->y;
	kulma = atan( y / x )*(180/3.14);
	if (x>0) kulma = -kulma;
	if (x<0) kulma = -kulma+180;
	otus->kulma = kulma;
*/
	//liikutus playerin suuntaan
	otus->kulma = AngleTowards(otus, player);	
	// lets move otus with speed of velocity towards player in to the direction of kulma
	otus->x = otus->x + otus->velocity*synk*cos((3.14/180)*otus->kulma);
	otus->y = otus->y - otus->velocity*synk*sin((3.14/180)*otus->kulma);
}


void Otus_SpawnNew(t_object *otus, int *otus_count, int otus_spawn_rate,int otus_max_count)
{
	int i = 0;
	int otus_sivu = 0;
	int spawned=0;

	*otus_count = *otus_count + otus_spawn_rate;
	if (*otus_count > otus_max_count) 
	{
		*otus_count = otus_max_count;	
	}

	for (i=0;i < *otus_count; i++)
	{		
		if (otus[i].hp < 1) 
		{
			otus_sivu = Random(1.0, 4.0);	
			if (otus_sivu == 1) 
			{	
				otus[i].x = Random(1.0, 640.0);
				otus[i].y = 0;
			}
			if (otus_sivu == 2) 
			{
				otus[i].x = Random(1.0, 640.0);
				otus[i].y = 480;
			}
			if (otus_sivu == 3)
			{		
				otus[i].y = Random(1.0, 480.0);
				otus[i].x = 0;
			}		
			if (otus_sivu == 4)
			{		
				otus[i].y = Random(1.0, 480.0);
				otus[i].x = 640;
			}		
			if (spawned <= otus_spawn_rate)
			{
				spawned++;
				otus[i].hp = 100;	
			}
		}		
	}
}

//Otus init
void Otus_Init(t_object *otus , char *kuva_tiedosto,int otus_max_count)
{
	int i=0;
	int otus_sivu=0;

	for (i=0;i<otus_max_count;i++) 
	{
		otus_sivu = 1 + (int) (4.0 * (rand() / (RAND_MAX + 1.0)));	
		otus[i].spritecount = 4;
		otus[i].anim = 0;
		if (otus_sivu == 1) 
		{	
			otus[i].x = 1 + (int) (640.0 * (rand() / (RAND_MAX + 1.0)));
			otus[i].y = 0;
		}
		if (otus_sivu == 2) 
		{
			otus[i].x = 1 + (int) (640.0 * (rand() / (RAND_MAX + 1.0)));
			otus[i].y = 480;
		}
		if (otus_sivu == 3)
		{		
			otus[i].y = 1+ (int) (480.0 * (rand() / (RAND_MAX + 1.0)));
			otus[i].x = 0;
		}		
		if (otus_sivu == 4)
		{		
			otus[i].y = 1+ (int) (480.0 * (rand() / (RAND_MAX + 1.0)));
			otus[i].x = 640;
		}		
		otus[i].velocity = 75;
		otus[i].turn_speed = 200;
		otus[i].kulma = 90;
		otus[i].hp = 100;
        	otus[i].alue.x = 0;
       		otus[i].alue.y = 0;
       		otus[i].alue.w = 32;
       		otus[i].alue.h = 32;
		otus[i].eteen = 1;
		otus[i].move = 1;
		LoadSprites(&otus[i], kuva_tiedosto);	
	}
}
