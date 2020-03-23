#include "Tile.h"

Tile::Tile(Vector2 t_size, Vector2 t_pos, std::pair<int, int> t_cell) :
	m_size(t_size),
	m_pos(t_pos)
{
	m_tile.w = m_size.x;
	m_tile.h = m_size.y;
	m_tile.x = (int)m_pos.x;
	m_tile.y = (int)m_pos.y;
	m_cell = t_cell;
}

Tile::~Tile()
{
}

void Tile::render(SDL_Renderer* t_window)
{
	SDL_SetRenderDrawColor(t_window, 255, 255, 255, 255);
	if (m_wall != true)
	{
		SDL_RenderDrawRect(t_window, &m_tile);
	}
	else
	{
		SDL_RenderFillRect(t_window, &m_tile);
	}
}

Vector2 Tile::getPosition()
{
	return m_pos;
}

void Tile::setWall(bool status)
{
	m_wall = status;
}

bool Tile::getWall()
{
	return m_wall;
}
