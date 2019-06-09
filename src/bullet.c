#include <stdio.h>
#include <string.h>
#include <SDL/SDL.h>
#include <SDL/SDL_rotozoom.h>
#include <SDL/SDL_gfxPrimitives.h>
#include <SDL/SDL_ttf.h>
#include "object.h"
#include "defines.h"
#include "graphic.h"

void Bullet_Init(t_object *bullet, char *bullet_kuva, int bullet_max_count)
{
	int i=0;

	for (i=0;i<bullet_max_count;i++)
	{
		bullet[i].spritecount = 1;
		bullet[i].eteen = 0;
		bullet[i].velocity = 400;
		bullet[i].damage = 50;
		bullet[i].hp = 0; //bullet is "dead"
		LoadSprites(&bullet[i], bullet_kuva);
	}
}

void NewBullets(t_object *player, t_object *bullet, int *gun_shots, int  bullet_max_count)
{
	int new_shots = 1;
	int shooted = 0;
	int i=0;
	int kulma_fix=0;

	if (player->gun == GUN_TYPE_SHOTGUN) new_shots +=2;
	
	if (*gun_shots < bullet_max_count) *gun_shots = *gun_shots + 1;
	for (i=0;i<*gun_shots;i++)
	{
		if (bullet[i].hp < 1 && shooted < new_shots)
		{
			shooted++;
			bullet[i].hp = 1;
			if (player->gun == GUN_TYPE_SHOTGUN)
			{
				// Shotgun shells has more power!
				bullet[i].hp++;
			}			
			
			bullet[i].x = player->x + (player->alue.w/2)*cos((3.14/180)*(player->kulma+45));
			bullet[i].y = player->y - (player->alue.w/2)*sin((3.14/180)*(player->kulma+45));

			if (shooted == 2) kulma_fix = -20;
			if (shooted == 3) kulma_fix = 20;

			bullet[i].kulma = player->kulma + 45 + kulma_fix;
		}
	}
}
