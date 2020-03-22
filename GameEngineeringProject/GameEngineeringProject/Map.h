#ifndef MAP_
#define MAP_

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <vector>
#include "Vector2.h"
#include "Tile.h"

class Map
{
public:
	Map(int t_size);
	~Map();
	
	void render(SDL_Renderer* t_window);
	Vector2 getTilePosition(std::pair<int, int> t_pos);

	std::vector<std::vector<Tile*>> m_map;
};

#endif
