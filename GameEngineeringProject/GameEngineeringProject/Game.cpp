#include "Game.h"

Game::Game() 
{
	m_exitGame = false;
}


Game::~Game()
{
}

void Game::init(const char* title, int xPos, int yPos, int width, int height, bool fullscreen, int t_mapSize)
{
	mapSize = t_mapSize;
	int flags = 0;
	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		std::cout << "Subsystem Initialised!" << std::endl;

		window = SDL_CreateWindow(title, xPos, yPos, width, height, flags);
		if (window)
		{
			std::cout << "Window created!" << std::endl;
		}

		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			std::cout << "Renderer created!" << std::endl;
		}

		isRunning = true;
	}
	else {
		isRunning = false;
	}

	m_map = new Map(mapSize, Vector2(1000,1000));
	
	for (int i = 0; i < 25; i++)
	{
		m_map->m_map[i][6]->setWall(true);
	}

	for (int i = 5; i < 28; i++)
	{
		m_map->m_map[i][15]->setWall(true);
	}

	for (int i = 2; i < 26; i++)
	{
		m_map->m_map[i][24]->setWall(true);
	}

	m_player = new Player(m_map->m_map[0][0]->getPosition(),1000/mapSize,std::make_pair(0,0), mapSize);

	for (int i = 0; i < 5; i++)
	{
		m_bot.push_back(new AIBot(m_map->m_map[2 + (i* 4)][2 + (i*5)]->getPosition(), 1000 / mapSize, std::make_pair(2 + (i * 4), 2 + (i*5)), mapSize, m_map));
	}
}

/// handle user and system events/ input
void Game::processEvents()
{
	SDL_Event event;
	SDL_PollEvent(&event);

	switch (event.type)
	{
	case SDL_QUIT:
		isRunning = false;
		break;
	case SDL_KEYDOWN:
		switch (event.key.keysym.sym)
		{
		case SDLK_a:
			if (m_player->m_cell.second > 0)
			{
				if (!m_map->m_map[m_player->m_cell.first][m_player->m_cell.second - 1]->getWall())
				{
					m_player->Left();
				}
			}
			break;
		case SDLK_w:
			if (m_player->m_cell.first > 0)
			{
				if (!m_map->m_map[m_player->m_cell.first - 1][m_player->m_cell.second]->getWall())
				{
					m_player->Up();
				}
			}
			break;
		case SDLK_s:
			if (m_player->m_cell.first < mapSize - 1)
			{
				if (!m_map->m_map[m_player->m_cell.first + 1][m_player->m_cell.second]->getWall())
				{
					m_player->Down();
				}
			}
			break;
		case SDLK_d:
			if (m_player->m_cell.second < mapSize - 1)
			{
				if (!m_map->m_map[m_player->m_cell.first][m_player->m_cell.second + 1]->getWall())
				{
					m_player->Right();
				}
			}
			break;
		default:
			break;
		}
	default:
		break;
	}
}


/// Update the game world
void Game::update()
{
	m_player->update(m_map->getTilePosition(m_player->m_cell));
}

void Game::aiUpdate()
{
	if (!m_bot.empty())
	{
		for (int i = 0; i < m_bot.size(); i++)
		{
			m_bot[i]->update(m_player->m_pos, m_map->getTilePosition(m_bot[1]->m_cell));
		}
	}
}

/// draw the frame and then switch bufers
void Game::render()
{
	SDL_RenderClear(renderer);
	//add stuff to render
	m_map->render(renderer);
	m_player->render(renderer);
	for (int i = 0; i < m_bot.size(); i++)
	{
		m_bot[i]->render(renderer);
	}
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

	SDL_RenderPresent(renderer);
}

void Game::cleanUp()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);

	IMG_Quit();
	SDL_Quit();
	std::cout << "Game Cleaned" << std::endl;
}
