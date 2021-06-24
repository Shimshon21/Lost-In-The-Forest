//-------------------------- Include section  ----------------------------
#include "StaticObjects_Headers/Door.h"
#include "Macros.h"


// C-tor
Door::Door(sf::Vector2f pos)
	: StaticObject({ BLOCK_SIZE * 1.5, BLOCK_SIZE * 1.5 }, pos)
{
	m_texture.loadFromFile(DOOR_FILE);
	m_shape.setTexture(&m_texture);
}
