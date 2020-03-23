#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include "Vector2.h"
#include "Map.h"
#include "Tile.h"

class AIBot
{
public:
	AIBot(Vector2 t_pos, int t_size, std::pair<int, int> t_cell, int t_mapSize, Map* t_map);
	~AIBot();
	void update(Vector2 t_playerpos, Vector2 t_pos);

	void render(SDL_Renderer* t_window);
	float getMag(Vector2 playerpos, Vector2 t_neighbourpos);
	std::pair<int, int> findSmallestWeight(std::vector<Tile*> t_neighbours);

	std::pair<int, int> m_cell;
private:
	SDL_Rect m_bot;
	Vector2 m_size;
	Vector2 m_pos;
	int m_mapSize;
	Map* m_map;
	int count = 0;
};

