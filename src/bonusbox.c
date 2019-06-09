#include <stdio.h>
#include <string.h>
#include <SDL/SDL.h>
#include <SDL/SDL_rotozoom.h>
#include <SDL/SDL_gfxPrimitives.h>
#include <SDL/SDL_ttf.h>
#include "object.h"
#include "logics.h"
#include "graphic.h"

//BONUSBOX INIT
void Bonusbox_Init(t_object *bonusbox, int bonusbox_max_count)
{

	int i = 0;
	for (i=0; i < bonusbox_max_count; i++)
	{
		bonusbox[i].hp = 0;
		bonusbox[i].spritecount = 1;

	}

}

void BonusboxNew(t_object *bonusbox,int *bonusbox_count,int bonusbox_max_count)
{
	int i=0;
	int new=0;
	int max_new = 1;

	if (*bonusbox_count < bonusbox_max_count - 1)
	{
		*bonusbox_count = *bonusbox_count + 1;
	}	
	
	for (i=0;i<bonusbox_max_count;i++)
	{
		if (bonusbox[i].hp < 1 && new < max_new)
		{
			new++;
			bonusbox[i].x = Random(20,600);
			bonusbox[i].y = Random(20,440);
			bonusbox[i].hp = Random(30,100);
			bonusbox[i].bonus = Random(0,2);
			bonusbox[i].kulma = Random(0,359);
			bonusbox[i].bullets = Random(50,200);
		}
	}

}
