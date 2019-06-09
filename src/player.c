#include <stdio.h>
#include <string.h>
#include <SDL/SDL.h>
#include <SDL/SDL_rotozoom.h>
#include <SDL/SDL_gfxPrimitives.h>
#include <SDL/SDL_ttf.h>
#include "object.h"
#include "graphic.h"

void Player_Init(t_object *player , char *kuva_tiedosto)
{
	//PLAYER INIT
	player->spritecount = 3;
	player->anim = 0;	
	player->x = 320;
	player->y = 220;
	player->velocity = 100;
	player->turn_speed = 200;
	player->kulma = 90;
	player->hp = 100;
        player->alue.x = 0;
        player->alue.y = 0;
        player->alue.w = 32;
        player->alue.h = 32;
	player->eteen = 0;
	player->vasemmalle = 0;
	player->oikealle = 0;
	player->taakse = 0;
	player->shoots = 0;
	player->xp = 0;
	player->bullets = 0;

	LoadSprites(player, kuva_tiedosto);

}

void PlayerMovement(t_object *player, float synk) {
	if (player->eteen == 1) {
		player->x = player->x + player->velocity*synk*cos((3.14/180)*player->kulma);
		player->y = player->y - player->velocity*synk*sin((3.14/180)*player->kulma);
	}
	if (player->taakse == 1) {
		player->x = player->x - player->velocity*synk*cos((3.14/180)*player->kulma);
		player->y = player->y + player->velocity*synk*sin((3.14/180)*player->kulma);
	}
	if (player->vasemmalle == 1) {
		player->kulma = player->kulma + synk*player->turn_speed;
		if (player->kulma > 360) player->kulma = 0;
	}
	if (player->oikealle == 1) {
		player->kulma = player->kulma - synk*player->turn_speed;
		if (player->kulma < 0) player->kulma = 360;
	}

	if (player->x < 0) player->x = 0;
	if (player->x > 640) player->x = 640;
	if (player->y < 0) player->y = 0;
	if (player->y > 480) player->y = 480;
}
