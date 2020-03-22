#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include "Map.h"
#include "Player.h"

class Game
{
public:
	Game();
	~Game();

	void init(const char* title, int xPos, int yPos, int width, int height, bool fullscreen);
	void update();

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
	int mapSize = 30;
};

#endif // !GAME_H
