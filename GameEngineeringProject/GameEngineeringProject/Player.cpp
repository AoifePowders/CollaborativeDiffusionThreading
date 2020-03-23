#include "Player.h"

Player::Player(Vector2 t_pos, int t_size, std::pair<int, int> t_cell, int t_mapSize)
{
	m_player.w = t_size;
	m_player.h = t_size;
	m_player.x = t_pos.x;
	m_player.y = t_pos.y;
	m_cell = t_cell;
	m_mapSize = t_mapSize;
}

Player::~Player()
{
}

void Player::update(Vector2 t_pos)
{
	m_pos = t_pos;
	m_player.x = m_pos.x;
	m_player.y = m_pos.y;
}

//change to move to each cell in the map insetad of moving around screen
void Player::Up()
{
	m_cell.first--;
}

void Player::Down()
{
	m_cell.first++;

}

void Player::Right()
{
	m_cell.second++;
}

void Player::Left()
{
	m_cell.second--;
}

void Player::render(SDL_Renderer* t_window)
{
	SDL_SetRenderDrawColor(t_window, 0, 0, 255, 255);
	SDL_RenderFillRect(t_window, &m_player);
}
