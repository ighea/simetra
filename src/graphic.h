int NextFrame(t_object *player,float synk); 
void LoadSprites(t_object *player, char *kuva);
void DrawTeksti(char *teksti, TTF_Font *font, SDL_Surface *ruutu, int x, int y);
void Piirra(t_object *player, float synk, SDL_Surface *ruutu, int rotate);
