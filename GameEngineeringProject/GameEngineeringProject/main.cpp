#include <iostream>
#include <SDL_image.h>
#include <SDL.h>
#include "Game.h"
#include "SDL_thread.h"
#include <functional>
#include <queue>

#define DEBUG_MSG
using namespace std;
static SDL_mutex* aiMutex = SDL_CreateMutex();

//get update
class AI
{
public:
	unsigned int update(void* data)
	{
		Game* gameObj = static_cast<Game*>(data);
		gameObj->aiUpdate();
		return 0;
	}
};

//calls update ^^
class ProcessAI
{
public:
	static int run(void* data)
	{
		AI ai;
		unsigned int outcome = 0;

		Uint32 update, time = 0;
		update = 1000;

		while (true)
		{
			time = SDL_GetTicks();

			if (time >= update)
			{
				SDL_LockMutex(aiMutex);
				outcome = ai.update(data);
				SDL_UnlockMutex(aiMutex);
				time = 0;
			}
		}
		return outcome;
	}
};


int main(int argc, char* argv[])
{
	int size = 0;
	while (true)
	{
		std::cout << "Please choose between 30, 100 and 1000" << std::endl;
		std::cout << "Enter map size: ";
		std::cin >> size;

		if (size == 30 || size == 100 || size == 1000)
		{
			break;
		}
	}

	DEBUG_MSG("Game Object Created");
	Game* game = new Game();
	//FrameRate Capping 
	const int Fps = 60;
	const int frameDelay = 1000 / Fps;

	Uint32 framestart;

	int frameTime;

	SDL_DisplayMode DM;
	SDL_GetDesktopDisplayMode(0, &DM);
	auto Width = DM.w;
	auto Height = DM.h;

	game->init("GEProj", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1000, 1000, false, size);

	SDL_Thread* thread;
	thread = SDL_CreateThread(&ProcessAI::run, "thread", (void*)game);

	while (game->running() == true) {
		framestart = SDL_GetTicks();

		game->processEvents();
		game->update();
		game->render();

		frameTime = SDL_GetTicks() - framestart;
		if (frameDelay > frameTime)
		{
			SDL_Delay(frameDelay - frameTime);
		}
	}


	game->cleanUp();
	SDL_DestroyMutex(aiMutex);
	return 0;
}