/*
			SIMETRA 

		Some short of Alien Phobia clone

		Made by Mika Hynnä, igheax@gmail.com
		#unixgurut@QuakeNet ighea

		Special thanks to patson

		main.c
*/

//Becouse everyone does not use real operation systems..
#ifdef _WIN32
#pragma comment(lib, "SDLmain.lib")
#pragma comment(lib, "SDL.lib")
#include <windows.h>
#endif

#include <stdio.h>
#include <string.h>
#include <SDL/SDL.h>
#include <SDL/SDL_rotozoom.h>
#include <SDL/SDL_gfxPrimitives.h>
#include <SDL/SDL_ttf.h>
#include "defines.h"
#include "object.h"
#include "logics.h"
#include "sync.h"
#include "graphic.h"
#include "menu.h"
#include "otus.h"
#include "player.h"
#include "bullet.h"
#include "bonusbox.h"

void MainExit(SDL_Surface *ruutu, TTF_Font *font, int points);
void Events(t_object *player, int *lopetus);
void Credits(SDL_Surface *ruutu, TTF_Font *font_large, TTF_Font *font_medium);
int GameLoop(SDL_Surface *ruutu,TTF_Font *font_small,TTF_Font *font_medium,int otus_spawning_type);

void MainExit(SDL_Surface *ruutu, TTF_Font *font, int points) 
{
	char num[1000];
	strcpy(num, "");
	SDL_Surface *surface = NULL;

	surface = SDL_LoadBMP("game_exit.bmp");
	SDL_SetColorKey(surface, SDL_SRCCOLORKEY, SDL_MapRGB(surface->format, 255, 255, 255));
	sprintf(num, "Game Over\nKills: %i!\n", points);
	Menu(ruutu, surface, font, num, 2, 2, 245, 180, 150, 100, 0, 0);
	//Lets free the surface
	if (surface) SDL_FreeSurface(surface);
}



void Events(t_object *player, int *lopetus)
{
	SDL_Event tapahtuma;

	while ( SDL_PollEvent(&tapahtuma) )    {
		//Ikkunan ruksi
                if ( tapahtuma.type == SDL_QUIT )  {  *lopetus = 1;  }
                if ( tapahtuma.type == SDL_KEYDOWN )  {
	        	        if ( tapahtuma.key.keysym.sym == SDLK_ESCAPE ) {
                                        *lopetus = 1;
                                }
				if ( tapahtuma.key.keysym.sym == SDLK_UP ) { 
					player->eteen = 1; 
				}
                		if ( tapahtuma.key.keysym.sym == SDLK_DOWN ) { 
					player->taakse = 1; 
				}
                		if ( tapahtuma.key.keysym.sym == SDLK_LEFT ) { 
					player->vasemmalle = 1; 
				}
                		if ( tapahtuma.key.keysym.sym == SDLK_RIGHT ) { 
					player->oikealle = 1; 
				}
                 		if ( tapahtuma.key.keysym.sym == SDLK_LCTRL ) { 
					player->shoots = 1; 
				}
            		}
           		if ( tapahtuma.type == SDL_KEYUP)  {
                		if ( tapahtuma.key.keysym.sym == SDLK_UP ) { 
					player->eteen = 0; 
				}
            		
                		if ( tapahtuma.key.keysym.sym == SDLK_DOWN ) { 
					player->taakse = 0; 
				}
                		if ( tapahtuma.key.keysym.sym == SDLK_LEFT ) { 
					player->vasemmalle = 0; 
				}
                		if ( tapahtuma.key.keysym.sym == SDLK_RIGHT ) { 
					player->oikealle = 0; 
				}
            			if ( tapahtuma.key.keysym.sym == SDLK_LCTRL ) { 
					player->shoots = 0; 
				}
        		}
                }
}

void Credits(SDL_Surface *ruutu, TTF_Font *font_large, TTF_Font *font_medium)
{
	SDL_Event tapahtuma;
	int lopetus = 0;
	float level=480;

	while (lopetus == 0)
	{	
		level = level - 40*sync();
		if (level < -480) level = 480;
		SDL_FillRect(ruutu, NULL, SDL_MapRGB(ruutu->format, 20, 0, 0));
		DrawTeksti("CREDITS!", font_large, ruutu, 640/2-80, level);
		
		DrawTeksti("MadeBy:", font_medium, ruutu, 640/2-130, 100+level);
		
		DrawTeksti("Mika", font_large, ruutu, 640/2-50, 90+level);
		DrawTeksti("Hynnä", font_large, ruutu, 640/2+30, 100+level);
		DrawTeksti("igheax@gmail.com", font_medium, ruutu, 640/2-30, 135+level);
		
		DrawTeksti("JUST", font_large, ruutu, 640/2-110, 210+level);
		DrawTeksti("FOR", font_large, ruutu, 640/2-30, 200+level);
		DrawTeksti("FUN!?", font_large, ruutu, 640/2+40, 220+level);
		
		DrawTeksti("#unixgurut@QuakeNet", font_medium, ruutu, 640/2-90, 320+level);
		DrawTeksti("Special thanks to..", font_medium, ruutu, 640/2-90, 360+level);
		DrawTeksti("sieni_ & patson", font_medium, ruutu, 640/2-90, 380+level);
		

		SDL_Flip(ruutu);
		SDL_Delay(10);		
		while ( SDL_PollEvent(&tapahtuma))
		{

			if (tapahtuma.type == SDL_QUIT) { lopetus = 1;}
			if (tapahtuma.type == SDL_KEYDOWN)
			{
				lopetus = 1;
			}

		}		
	}

}



int GameLoop(SDL_Surface *ruutu, TTF_Font *font_small, TTF_Font *font_medium, int otus_spawning_type) 
{

	t_object player;
	int otus_max_count = 200;
	int otus_count = 0;
	int otus_spawn_rate = 1;
	t_object otus[otus_max_count];
	
	// OTUS SPAWN SPECIFICATIONS
	float spawn_more_calculator = 0;
	float spawn_more_interval = 5;
	float spawn_more_number = 0;

//	SDL_Surface *ruutu = NULL;
	SDL_Surface *blood = NULL;
	SDL_Surface *blood_surface = NULL;
	SDL_Surface *alien_blood = NULL;
	SDL_Rect blood_surface_alue;
	SDL_Surface *temp = NULL;
			

	int lopetus = 0;
	float synk;
	int i=0,j=0;
	int blood_fix=20;
	int FPS_counter=0;
	float FPS_calculator=0;

	char kuva[100] = "ukkoX.bmp";
	char otus_kuva[100] = "otusX.bmp";	
	char bullet_kuva[100] = "bulletX.bmp";
	char blood_kuva[100] = "blood.bmp";
	char blood_surface_kuva[100] = "ground.bmp";
	char alien_blood_kuva[100] = "alien_blood.bmp";
	char bonusbox_healkit_kuva[100] = "bonusbox_healkit.bmp";
	char bonusbox_shotgun_kuva[100] = "bonusbox_shotgun.bmp";
	char bonusbox_broken_kuva[100] = "bonusbox_broken.bmp";

	// BONUSBOX INIT
	
	SDL_Rect bonusbox_alue;
	SDL_Surface *bonusbox_healkit = NULL;
	SDL_Surface *bonusbox_shotgun = NULL;
	SDL_Surface *bonusbox_broken = NULL;
	int bonusbox_max_count = 10;
	t_object bonusbox[bonusbox_max_count];
	int bonusbox_interval = Random(5,15);
	float bonusbox_calculator = 0;
	int bonusbox_count = 0;
	Bonusbox_Init(bonusbox, bonusbox_max_count);
	bonusbox_healkit = SDL_LoadBMP(bonusbox_healkit_kuva);
	if (bonusbox_healkit == NULL) 
	{
		printf("%s\n", SDL_GetError());
	}
	SDL_SetColorKey(bonusbox_healkit, SDL_SRCCOLORKEY, SDL_MapRGB(bonusbox_healkit->format, 255, 255, 255));
	bonusbox_shotgun = SDL_LoadBMP(bonusbox_shotgun_kuva);
	if (bonusbox_shotgun == NULL) 
	{
		printf("%s\n", SDL_GetError());
	}
	SDL_SetColorKey(bonusbox_shotgun, SDL_SRCCOLORKEY, SDL_MapRGB(bonusbox_shotgun->format, 255, 255, 255));
	bonusbox_broken = SDL_LoadBMP(bonusbox_broken_kuva);
	if (bonusbox_broken == NULL) 
	{
		printf("%s\n", SDL_GetError());
	}
	SDL_SetColorKey(bonusbox_broken, SDL_SRCCOLORKEY, SDL_MapRGB(bonusbox_broken->format, 255, 255, 255));



	//RANDOMIZE TIMER INIT
	srand(SDL_GetTicks());

	//BLOOD init
	blood_surface_alue.x = 0;
	blood_surface_alue.y = 0;
	blood_surface_alue.h = 480;
	blood_surface_alue.w = 640;
	blood = SDL_LoadBMP(blood_kuva);
	if (blood == NULL) 
	{
		printf("%s\n", SDL_GetError());
	}
	SDL_SetColorKey(blood, SDL_SRCCOLORKEY, SDL_MapRGB(blood->format, 255, 255, 255));
	blood_surface = SDL_LoadBMP(blood_surface_kuva);
	if (blood_surface == NULL) 
	{
		printf("%s\n", SDL_GetError());
	}
	alien_blood = SDL_LoadBMP(alien_blood_kuva);
	if (alien_blood == NULL) 
	{
		printf("%s\n", SDL_GetError());
	}
	SDL_SetColorKey(alien_blood, SDL_SRCCOLORKEY, SDL_MapRGB(alien_blood->format, 255, 255, 255));


	//GUN RELATED
	char shotgun_shells[100];


	// BULLET init
	int bullet_max_count = 50;
	t_object bullet[bullet_max_count];
	int gun_shots = 0;
	float gun_firerate = 10.0;
	float gun_firerate_calculator = 0;
	/*for (i=0;i<bullet_max_count;i++)
	{
		bullet[i].spritecount = 1;
		bullet[i].eteen = 1;
		bullet[i].velocity = 400;
		bullet[i].damage = 50;
		bullet[i].hp = 0; //bullet is "dead"
		LoadSprites(&bullet[i], bullet_kuva);
	}*/

	//PLAYER init
	Player_Init(&player, kuva);

	//OTUS init
	Otus_Init(otus , otus_kuva,otus_max_count);


//
//			MAIN LOOP!!!!!
//
	printf("Main loop\n");
		//PLAYER init
	Player_Init(&player, kuva);
	//player.gun=1;

	//OTUS init
	Otus_Init(otus , otus_kuva,otus_max_count);

	Otus_SpawnNew(otus, &otus_count, otus_spawn_rate, otus_max_count);
	sync(); //Initializing sync

	Bullet_Init(bullet,bullet_kuva,bullet_max_count);

	while (lopetus == 0) {
		//Täytetään näyttö musta... tarpeeton v0.02 lähtien..		
		//SDL_FillRect(ruutu, NULL, SDL_MapRGB(ruutu->format, 0, 0, 0));

		synk = sync();

		//Piirretään veret näyttöön
		blood_surface_alue.x = 0;		
		blood_surface_alue.y = 0;
		blood_surface_alue.w = 640;
		blood_surface_alue.h = 480;
		SDL_BlitSurface(blood_surface, NULL, ruutu, &blood_surface_alue);			

		//if (synk > 1) synk = 1;


		//BONUSBOX
		bonusbox_calculator = bonusbox_calculator + 1*synk;
		if (bonusbox_calculator > bonusbox_interval)
		{
			bonusbox_calculator = 0;
			bonusbox_interval = Random(5,15);
			BonusboxNew(bonusbox, &bonusbox_count, bonusbox_max_count);
		}
		
		for (i=0; i<bonusbox_count; i++)
		{
			if (bonusbox[i].hp > 0)
			{
				
				bonusbox_alue.x = bonusbox[i].x - bonusbox_healkit->w/2;
				bonusbox_alue.y = bonusbox[i].y - bonusbox_healkit->h/2;
					
				if (bonusbox[i].bonus == BONUSBOX_HEALKIT)
				{
					temp = rotozoomSurface(bonusbox_healkit, bonusbox[i].kulma, 1, 1);
					SDL_BlitSurface(temp, NULL, ruutu, &bonusbox_alue);					
					if (temp != NULL) SDL_FreeSurface(temp);
				}			
				if (bonusbox[i].bonus == BONUSBOX_SHOTGUN)
				{
					temp = rotozoomSurface(bonusbox_shotgun, bonusbox[i].kulma, 1, 1);
					SDL_BlitSurface(temp, NULL, ruutu, &bonusbox_alue);					
					if (temp != NULL) SDL_FreeSurface(temp);
				}
			
				if (Tormays(&bonusbox[i], &player, 0) == 1 )
				{
					if (bonusbox[i].bonus == BONUSBOX_HEALKIT)
					{
						player.hp = player.hp + bonusbox[i].hp;
						if (player.hp > 100)
						{
							player.hp = 100;
						}
					}
					if (bonusbox[i].bonus == BONUSBOX_SHOTGUN)
					{
						player.gun = GUN_TYPE_SHOTGUN;
						player.bullets=player.bullets+bonusbox[i].bullets;
					}
					bonusbox[i].hp = 0;

					temp = rotozoomSurface(bonusbox_broken,bonusbox[i].kulma, 1 , 1);
					SDL_BlitSurface(temp , NULL, blood_surface, &bonusbox_alue);
					if (temp != NULL) SDL_FreeSurface(temp);
				}

			}
		}

		
		PlayerMovement(&player, synk);


		// OTUS HIT & RUN LOOP
		for (i=0;i<otus_count;i++)
		{
			//only if otus is "alive"
			otus[i].move = 0;
			if (otus[i].hp > 0) {
				//Does player collide with an otus??
				if (Tormays(&otus[i], &player, -5) == 1) {
					//Yes, we get some damage! Otus ain't moving.
					player.hp = player.hp - 1*synk;
					//NTS: siirrä verta otuksen suuntaan
					blood_surface_alue.x = player.x + Random(-blood_fix,blood_fix);		
					blood_surface_alue.y = player.y + Random(-blood_fix,blood_fix);
					SDL_BlitSurface(blood, NULL, blood_surface, &blood_surface_alue);
				}
				else
				{	
					//Otus vs. Otus Collision detection starts
					for (j=0;j<otus_count;j++)
					{
					//Am I me? 
					if (i == j)
					{
						//Yes, we shall move it baby!
						otus[i].move = 1;
					}
					else
					{
						//Do they collide?
						if (Tormays(&otus[j],&otus[i],5)==1)
						{
							//Collision! is the another one moving?
							if (otus[j].move == 1)
							{
								//if yes, we won't move
								otus[i].move = 0;
							}else {
								//if no, let us move then
								otus[j].move = 1;
							}
						}
					}
					}					
					//...and ends!


					if (otus[i].move == 1) 
					{
						OtusMovement(&otus[i], &player, synk);
					} else {
						otus[i].kulma = AngleTowards(&otus[i], &player);
					}									
				}
				Piirra(&otus[i], synk, ruutu, 1);
			}
		}


		DEBUG_OUT("Piirretään pelaaja...");
		Piirra(&player, synk, ruutu, 1);		
		DEBUG_OUT("..done!\n");
		
                //Tapahtumakäsittelijä
		Events(&player, &lopetus);		


//		SPAWN TIMER
		if (otus_spawning_type == OTUS_SPAWNING_TYPE_TIMED)
		{		
			spawn_more_calculator = spawn_more_calculator + 1*synk;
			if (spawn_more_calculator > spawn_more_interval) {
				spawn_more_calculator=0;
				otus_count = otus_count + otus_spawn_rate;			
				if (otus_count > otus_max_count) otus_count = otus_max_count;
			//SPawn half of "otus_count" more otuses every "spawn_more_interval"
				spawn_more_number += 1;
				Otus_SpawnNew(otus, &otus_count, spawn_more_number, otus_max_count);	
			}
		}

		//Ampuminen
		if (player.shoots == 1) 
		{	
			gun_firerate_calculator = gun_firerate_calculator + gun_firerate*synk;
			//Is it time to fire the gun?
			if (gun_firerate_calculator >= 1)
			{
				//Yes, clear the calculator:
				gun_firerate_calculator = 0;
				
				//Do we have a shotgun?
				if (player.gun == GUN_TYPE_SHOTGUN)
				{	
					//Yes, amount of bullets degreases!
					player.bullets = player.bullets - 1;
					if (player.bullets < 1)
					{
						//We run out of bullets, no more shotgun
						player.gun = GUN_TYPE_GENERAL;
					}
				}
				//Fire in the hole! New bullets on their way...
				NewBullets(&player,bullet, &gun_shots, bullet_max_count);
			}		
		}
		//Debug:
		if (player.bullets < 0) player.bullets = 0;

		// BULLET HIT & RUN LOOP
		for (i=0;i<bullet_max_count;i++) {
			if (bullet[i].hp > 0) 
			{				
				bullet[i].x = bullet[i].x + bullet[i].velocity*synk*cos((3.14/180)*bullet[i].kulma);
				bullet[i].y = bullet[i].y - bullet[i].velocity*synk*sin((3.14/180)*bullet[i].kulma);
				DEBUG_OUT2("Piirretään ammus %i",i);
				Piirra(&bullet[i], synk, ruutu, 0);
				DEBUG_OUT("..DONE!\n");				
				
				//Does bullet bullet[i] hit to an otus? Lets check it out!
				for (j=0;j<otus_count;j++)
				{
				if (otus[j].hp > 0 && bullet[i].hp > 0) 
				{
					//if Bullet hits
					if (Tormays(&bullet[i],&otus[j],5) == 1)
					{
					
						//Bullet is destroyed in collision
						bullet[i].hp--;
						//Bullet makes damage
						otus[j].hp = otus[j].hp - bullet[i].damage;
						//Blood's position...
						blood_surface_alue.x = otus[j].x;		
						blood_surface_alue.y = otus[j].y;
						//Lets draw some bloody mess!!! muahahaha
						temp = rotozoomSurface(alien_blood, Random(1,358),1,0);
						SDL_BlitSurface(temp, NULL, blood_surface, &blood_surface_alue);
						if (temp) SDL_FreeSurface(temp);
						// but if... if the otus dies? Sniff..
						if (otus[j].hp < 1) 
						{
							//Player scores! Yea!
							player.xp++;
							
							//Lets draw the alien on the ground...
							temp = rotozoomSurface(otus[j].sprite[0],otus[j].kulma-90,1,0);				
							blood_surface_alue.x = otus[j].x - temp->w/2;
							blood_surface_alue.y = otus[j].y - temp->h/2;

							SDL_BlitSurface(temp, NULL,blood_surface, &blood_surface_alue);		
							if (temp != NULL) SDL_FreeSurface(temp);
							
							//and blood over it...
							temp = rotozoomSurface(alien_blood, Random(1,358),1,0);
							blood_surface_alue.x = otus[j].x;
							blood_surface_alue.y = otus[j].y;
							SDL_BlitSurface(temp, NULL, blood_surface, &blood_surface_alue);
							if (temp) SDL_FreeSurface(temp);
							if (otus_spawning_type == OTUS_SPAWNING_TYPE_KILL)
							{
								Otus_SpawnNew(otus, &otus_count, otus_spawn_rate, otus_max_count);
							}
			
						}	
						//break;		
					}
				}				
				}		
			
			}
			//Ammus uusiokäyttöön ylitettyään näytön rajat
			if ((bullet[i].x > 640) || bullet[i].x < 0 || bullet[i].y < 0 || bullet[i].y > 480) 
			{
				bullet[i].hp = 0;			
			}		
		}


		//HP-palkki
		hlineColor(ruutu, 615,615-2*player.hp , 5, 0xff0000ff);
		hlineColor(ruutu, 413,617 , 7, 0xf0fffff0);
		vlineColor(ruutu, 617, 4 , 7,  0xf0fffff0);
		vlineColor(ruutu, 413, 4 , 7,  0xf0fffff0);


		DrawTeksti("HP", font_small, ruutu, 619,0);
		//DrawTeksti(48+player.xp, font, ruutu, 1,1);
		

		// SHOTGUN SHELLS
		sprintf(shotgun_shells, "Shotgun shells: %i", player.bullets);
		DrawTeksti(shotgun_shells, font_small, ruutu, 1,1);


		//Kuva näytölle
		SDL_Flip(ruutu);

		//Venaillaan millisekka ettei viedä kaikkea CPU-aikaa
		SDL_Delay(1);
		DEBUG_OUT2("Otus_count: %i\n",otus_count);

		// FPS
		FPS_calculator = FPS_calculator + synk;
		FPS_counter++;
		if (FPS_calculator >= 1)
		{
			printf("FPS: %i\n",FPS_counter);
			FPS_counter = 0;
			FPS_calculator = 0;		
		}	

		//PLAYER DIES & END OF GAME
		if (player.hp < 1) 
		{	
			MainExit(ruutu, font_medium, player.xp);
			lopetus = 1;
		}	



	}
	//GAME END: Reset:	
	lopetus = 0;
	if (player.hp > 0) MainExit(ruutu, font_medium, player.xp);
	otus_count = 0;
		
/*	//New bloody grounds:
	blood_surface = SDL_LoadBMP(blood_surface_kuva);
	if (blood_surface == NULL) 
	{
		printf("%s\n", SDL_GetError());
	}
*/	//Ready for menu

/// END OF MAIN LOOP!!	
	
	DEBUG_OUT("EXIT begin\n");

//Lets release some Surfaces

	DEBUG_OUT("Releasing memory... \n");
	DEBUG_OUT("blood \n");

	if (blood) SDL_FreeSurface(blood);
	DEBUG_OUT("blood_surface \n");
	if (blood_surface) SDL_FreeSurface(blood_surface);
	DEBUG_OUT("alien_blood \n");
	if (alien_blood) SDL_FreeSurface(alien_blood);
	DEBUG_OUT("temp \n");
	//if (temp) SDL_FreeSurface(temp);

	//bonusboxes..
	DEBUG_OUT("all  bonusboxes.. \n");
	
	if (bonusbox_shotgun != NULL) SDL_FreeSurface(bonusbox_shotgun);
	if (bonusbox_healkit != NULL) SDL_FreeSurface(bonusbox_healkit);
	if (bonusbox_broken != NULL) SDL_FreeSurface(bonusbox_broken);


	//Release all alien surfaces...
	for (i=0;i<otus_max_count;i++)
	{
		for (j=0;j<otus[i].spritecount;j++)
		{
			DEBUG_OUT3("otus[%i].sprite[%i]... \n",i,j);
	
			if (otus[i].sprite[j] != NULL) SDL_FreeSurface(otus[i].sprite[j]);
		}	
	}
	
	//..and all bullet surfaces...
	for (i=0;i<bullet_max_count;i++)
	{
		for (j=0;j<bullet[i].spritecount;j++)
		{
			DEBUG_OUT3("bullet[%i].sprite[%i]... \n",i,j);
			if (bullet[i].sprite[j] != NULL) SDL_FreeSurface(bullet[i].sprite[j]);
		}	
	}

	//Player's sprites..
	for (j=0;j<player.spritecount;j++)
	{
		DEBUG_OUT2("Player sprite %i...\n", j);
		if (player.sprite[j] != NULL) SDL_FreeSurface(player.sprite[j]);
	}	

	
//	if (player.hp > 0) MainExit(ruutu, font_medium, player.xp);

	DEBUG_OUT("All OK!\n");
	return 0;
}



int main (int argc, char *argv[]) 
{
	int points = 0;
	int otus_spawning_type = OTUS_SPAWNING_TYPE_TIMED;
	SDL_Surface *mainmenu_surface = NULL;
	SDL_Surface *ruutu = NULL;

	//SDL init
	SDL_Init(SDL_INIT_VIDEO);
	SDL_WM_SetCaption(VERSION, NULL); //Otsikko
	

	TTF_Font *font_small = NULL;
	TTF_Font *font_medium = NULL;
	TTF_Font *font_large = NULL;

	//TTF INIT
	if(TTF_Init()==-1) {
	    printf("TTF_Init: %s\n", TTF_GetError());
	    exit(2);
	}

	font_small=TTF_OpenFont("Vera.ttf", 10);
	if(!font_small) {
	   	printf("TTF_OpenFont: %s\n", TTF_GetError());
		exit(2);
	    // handle error
	}
	font_medium=TTF_OpenFont("Vera.ttf", 16);
	if(!font_medium) {
	    printf("TTF_OpenFont: %s\n", TTF_GetError());
		exit(2);
	    // handle error
	}
	font_large=TTF_OpenFont("Vera.ttf", 32);
	if(!font_large) {
	    printf("TTF_OpenFont: %s\n", TTF_GetError());
		exit(2);
	    // handle error
	}

	
	//MAIN MENU KUVA	
	char mainmenu_kuva[100] = "menu.bmp";
	int mainmenu_count = 4;
	char mainmenu_lista[100]; 
	mainmenu_surface = SDL_LoadBMP(mainmenu_kuva);
	if (mainmenu_surface == NULL) 
	{
		printf("%s\n", SDL_GetError());
	}
	int mainmenu_valinta = 0;


	//Set Video Mode
        ruutu = SDL_SetVideoMode(640, 480, 24, SDL_HWSURFACE|SDL_DOUBLEBUF);
	if (ruutu == NULL) 
	{
		printf("Could not set video mode 640x480 32bit: %s", SDL_GetError());
		exit(1);	
	}

	
	while (mainmenu_valinta != -1 && mainmenu_valinta != 3)
	{

		if (otus_spawning_type == OTUS_SPAWNING_TYPE_KILL)
		{
			strcpy(mainmenu_lista, "Start\nGame mode:KILL\nCredits\nQuit\n");
		}
		if (otus_spawning_type == OTUS_SPAWNING_TYPE_TIMED)
		{
			strcpy(mainmenu_lista, "Start\nGame mode:TIME\nCredits\nQuit\n");
		}

		//MAIN MENU
		mainmenu_valinta = Menu(ruutu, mainmenu_surface, font_large, mainmenu_lista, mainmenu_count, mainmenu_valinta, 0, 0, 640, 480, 1, 1);

		if (mainmenu_valinta == 0)
		{
			//GameLoop selected, returns the number of player's XP
			points = GameLoop(ruutu, font_small, font_medium, otus_spawning_type);
		}
		else if (mainmenu_valinta == 1)
		{
			//Game mode selection
			otus_spawning_type++;
			if (otus_spawning_type == OTUS_SPAWNING_TYPE_COUNT)
			{
				otus_spawning_type = 0;				
			} 		
			
		} 
		else if (mainmenu_valinta == 2)
		{
			//Credits? Anyone?
			Credits(ruutu, font_large, font_medium);
		} 
		else if (mainmenu_valinta == 3) 
		{
			//Quit game	
		}
	
	} 
	TTF_CloseFont(font_small);
	TTF_CloseFont(font_medium);
	TTF_CloseFont(font_large);
	TTF_Quit();

	SDL_Quit();
	printf("Exit_Success!\n");	
	return 0;
}

