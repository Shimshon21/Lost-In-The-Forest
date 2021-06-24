//-------------------------- Include section  ----------------------------
#include "StaticObjects_Headers/Hurricane.h"
#include "Resources.h"
#include "Operation.h"
#include "Macros.h"


// c-tor
Hurricane::Hurricane(sf::Vector2f pos)
	: StaticObject(sf::Vector2f(BLOCK_SIZE, BLOCK_SIZE), pos),
	m_animation(Resources::instance().
		animationWorldData(Resources::HURRICANE_DATA),
		Operation::Stay, m_shape,
		Resources::instance().
		getStaticObjectTexture(Resources::STATIC_ANIMATED))
{
	m_shape.setPosition(m_shape.getPosition().x,
		m_shape.getPosition().y + m_shape.getSize().y / 2);
	m_shape.setOrigin(m_shape.getOrigin().x,
		m_shape.getOrigin().y + m_shape.getSize().y / 2);
	m_shape.scale(1, 2.2f);
}


//----------------------------- update -----------------------------------
// Updates the animation depending on delta time.
//------------------------------------------------------------------------
void Hurricane::update(const sf::Time& delta)
{
	m_animation.update(delta);
}
