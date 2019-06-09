// Base structure for all moveable objects: bullets, player character, etc...
typedef struct object_base {
	float x;
	float y;
	float velocity;
	float turn_speed;
	int hp;
	float anim;
	int spritecount;
	SDL_Surface *sprite[5];
	float kulma;
        SDL_Rect alue;
	int eteen;
	int taakse;
	int oikealle;
	int vasemmalle;
	int shoots;
	int damage;
	int xp;
	int bonus;
	int gun;
	char sprite_file[100];
	int bullets;
	int move; //0-1
} t_object;
