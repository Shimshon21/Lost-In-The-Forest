//-------------------------- Include section  ----------------------------
#include "StaticObjects_Headers/Block.h"
#include "Resources.h"


//---------------------------- Constractor  ------------------------------
// Sets the blocks of the stages in the game.
//------------------------------------------------------------------------
Block::Block(sf::Vector2f pos, char type, const int stageNum)
	: StaticObject(sf::Vector2f(BLOCK_SIZE, BLOCK_SIZE), pos)
{
	auto size = sf::Vector2f(BLOCK_SIZE, BLOCK_SIZE);

	m_shape.setTexture(Resources::instance().
		getStaticObjectTexture(Resources::STATIC_ANIMATED));

	if(type==WALL)
	{
		m_rect = WALL_INRECT;
		m_shape.scale(-1, 1);
	}
	else
	{
		switch (stageNum) 
		{
		case STAGE_ONE:
			setFirstStage(type, size);
			break;
		case STAGE_TWO:
			setSecondStage(type, size);
			break;
		case STAGE_THREE:
			setThirdStage(type, size);
			break;
		}
	}
	
	m_shape.setTextureRect(m_rect);
	m_texture.setSmooth(true);
}


//--------------------------- setFirstStage  -----------------------------
// Sets the blocks of the first stage whithin the map.
// i.e. sets their position, size, scale.
//------------------------------------------------------------------------
void Block::setFirstStage(char type, const sf::Vector2f& size)
{
	if (type == FLOOR_EDGE_LEFT)
	{
		m_rect = FLOOR_INRECT_FIRST_STAGE;
		m_shape.setSize(sf::Vector2f{ size.x ,size.y / 2 });
	}
	else if (type == FLOOR_EDGE_RIGHT)
	{
		m_rect = FLOOR_INRECT_FIRST_STAGE;
		m_shape.setSize(sf::Vector2f{ size.x ,size.y / 2 });
		m_shape.scale(-1, 1);
	}
	else
	{
		m_rect = FLOOR_EDGE_FIRST_STAGE;
		m_shape.setSize(sf::Vector2f{ size.x ,size.y / 2 });
	}
}


//-------------------------- setSecondStage  -----------------------------
// Sets the blocks of the second stage whithin the map.
// i.e. sets their position, size, scale.
//------------------------------------------------------------------------
void Block::setSecondStage(char type, const sf::Vector2f& size)
{
	if (type == FLOOR_EDGE_LEFT)
	{
		m_rect = FLOOR_EDGE_INRECT_SECOND_STAGE;
		m_shape.setSize(sf::Vector2f{ size.x ,size.y / 2 });
	}
	else if (type == FLOOR_EDGE_RIGHT)
	{
		m_rect = FLOOR_EDGE_INRECT_SECOND_STAGE;
		m_shape.setSize(sf::Vector2f{ size.x ,size.y / 2 });
		m_shape.scale(-1, 1);
	}
	else
	{
		m_rect = FLOOR_INRECT_SECOND_STAGE;
		m_shape.setSize(sf::Vector2f{ size.x ,size.y / 2 });
	}
}


//--------------------------- setThirdStage  -----------------------------
// Sets the blocks of the third stage whithin the map.
// i.e. sets their position, size, scale.
//------------------------------------------------------------------------
void Block::setThirdStage(char type, const sf::Vector2f& size)
{
	if (type == FLOOR_EDGE_LEFT)
	{
		m_rect = FLOOR_EDGE_INRECT_THIRD_STAGE;
		m_shape.setSize(sf::Vector2f{ size.x ,size.y / 2 });
	}
	else if (type == FLOOR_EDGE_RIGHT)
	{
		m_rect = FLOOR_EDGE_INRECT_THIRD_STAGE;
		m_shape.setSize(sf::Vector2f{ size.x ,size.y / 2 });
		m_shape.scale(-1, 1);
	}
	else
	{
		m_rect = FLOOR_INRECT_THRID_STAGE;
		m_shape.setSize(sf::Vector2f{ size.x ,size.y / 2 });
	}
}