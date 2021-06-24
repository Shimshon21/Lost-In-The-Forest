//-------------------------- Include section  ----------------------------
#include "Spike.h"
#include "Macros.h"
#include "Resources.h"


//------------------------------ C-tor -----------------------------------
// Sets the position and size of the spike.
//------------------------------------------------------------------------
Spike::Spike(sf::Vector2f pos)
	: StaticObject(sf::Vector2f(BLOCK_SIZE, BLOCK_SIZE / 2), pos)
{
	m_shape.setPosition(m_shape.getPosition().x,
		m_shape.getOrigin().y + m_shape.getPosition().y);
	m_shape.setTexture(Resources::instance().
		getStaticObjectTexture(Resources::SPIKES));
}