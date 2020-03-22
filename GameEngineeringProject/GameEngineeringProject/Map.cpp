#include "Map.h"

Map::Map(int t_size)
{
	for (int y = 0; y < t_size; y++)
	{
		std::vector<Tile*> test;

		for (int x = 0; x < t_size; x++)
		{
			test.push_back(new Tile(Vector2(20, 20), Vector2(x * 20, y * 20)));
		}

		m_map.push_back(test);
	}
}

Map::~Map()
{
}

void Map::render(SDL_Renderer* t_window)
{
	for (int y = 0; y < m_map.size(); y++)
	{
		for (int x = 0; x < m_map.size(); x++)
		{
			m_map[x][y]->render(t_window);
		}
	}
}

Vector2 Map::getTilePosition(std::pair<int, int> t_pos)
{
	return m_map[t_pos.first][t_pos.second]->getPosition();
}
