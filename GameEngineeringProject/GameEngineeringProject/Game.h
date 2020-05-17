#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include "Map.h"
#include "Player.h"
#include "AIBot.h"

class Game
{
public:
	Game();
	~Game();

	void init(const char* title, int xPos, int yPos, int width, int height, bool fullscreen, int t_mapSize);
	void update();
	void aiUpdate();

	void processEvents();
	void render();
	void cleanUp();

	bool running() { return isRunning; }


private:
	bool isRunning = false;
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;

	bool m_exitGame; // control exiting game
	Map* m_map;
	Player* m_player;
	std::vector<AIBot*> m_bot;

	//change the size of the map here, (30x30, 100x100, 1000x1000)
	int mapSize;
};

#endif // !GAME_H
