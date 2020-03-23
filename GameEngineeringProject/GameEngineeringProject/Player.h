#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include "Vector2.h"
#include "Map.h"

class Player
{
public:
	Player(Vector2 t_pos,int t_size, std::pair<int,int> t_cell, int t_mapSize);
	~Player();
	void update(Vector2 t_pos);

	void Up();
	void Down();
	void Right();
	void Left();

	void render(SDL_Renderer* t_window);

	std::pair<int, int> m_cell;
	Vector2 m_pos;
private:
	SDL_Rect m_player;
	Vector2 m_size;
	int m_mapSize;
};

