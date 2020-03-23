#include "AIBot.h"

AIBot::AIBot(Vector2 t_pos, int t_size, std::pair<int, int> t_cell, int t_mapSize, Map* t_map)
{
	m_bot.w = t_size;
	m_bot.h = t_size;
	m_bot.x = t_pos.x;
	m_bot.y = t_pos.y;
	m_cell = t_cell;
	m_mapSize = t_mapSize;
	m_map = t_map;
}

AIBot::~AIBot()
{
}

void AIBot::update(Vector2 t_playerpos, Vector2 t_pos)
{

	std::vector<Tile*> m_neighbours;

	for (int i = 0; i < 9; i++)
	{
		if (i == 4) continue;

		int n_row = m_cell.first + ((i % 3) - 1);
		int n_col = m_cell.second + ((i / 3) - 1);

		if (n_row >= 0 && n_row < m_mapSize && n_col >= 0 && n_col < m_mapSize && !m_map->m_map[n_row][n_col]->getWall())
		{
			m_map->m_map[n_row][n_col]->weight = getMag(t_playerpos, m_map->m_map[n_row][n_col]->getPosition());
			m_neighbours.push_back(m_map->m_map[n_row][n_col]);
		}
	}

	count++;

	if (count >= 10)
	{
		std::pair<int, int> m_target = findSmallestWeight(m_neighbours);
		m_cell.first = m_target.first;
		m_cell.second = m_target.second;

		m_pos = t_pos;
		m_bot.x = m_pos.x;
		m_bot.y = m_pos.y;

		count = 0;
	}
}

void AIBot::render(SDL_Renderer* t_window)
{
	SDL_SetRenderDrawColor(t_window, 255, 0, 0, 255);
	SDL_RenderFillRect(t_window, &m_bot);
}

float AIBot::getMag(Vector2 playerpos, Vector2 t_neighbourpos)
{
	float mag = sqrt((playerpos.x - t_neighbourpos.x) * (playerpos.x - t_neighbourpos.x) + (playerpos.y - t_neighbourpos.y) * (playerpos.y - t_neighbourpos.y));
	return mag;
}

std::pair<int, int> AIBot::findSmallestWeight(std::vector<Tile*> t_neighbours)
{
	float temp = t_neighbours[0]->weight;
	std::pair<int, int> smallest = t_neighbours[0]->m_cell;

	for (int i = 0; i < t_neighbours.size(); i++)
	{
		if (temp > t_neighbours[i]->weight)
		{
			temp = t_neighbours[i]->weight;
			smallest = t_neighbours[i]->m_cell;
		}
	}
	return smallest;
}
