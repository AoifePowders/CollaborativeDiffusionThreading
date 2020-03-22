#ifndef TILE_
#define TILE_

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include "Vector2.h"

class Tile
{
public:
	Tile(Vector2 t_size, Vector2 t_pos);
	~Tile();
	void render(SDL_Renderer* t_window);
	Vector2 getPosition();
	void setWall(bool status);
	bool getWall();
private:
	SDL_Rect m_tile;
	Vector2 m_size;
	Vector2 m_pos;
	bool m_wall = false;
};

#endif