//-------------------------- Include section  ----------------------------
#include "StaticObjects_Headers/Key.h"
#include "Resources.h"
#include "Macros.h"


// c-tor
Key::Key(sf::Vector2f pos)
	: StaticObject(sf::Vector2f(BLOCK_SIZE / 4,
		BLOCK_SIZE / 3), pos),
	m_animation(Resources::instance().
		animationWorldData(Resources::KEY_DATA)
		, Operation::Stay, m_shape,
		Resources::instance().
		getStaticObjectTexture(Resources::STATIC_ANIMATED))
{}


//----------------------------- update -----------------------------------
// Updates the animation depending on delta time.
//------------------------------------------------------------------------
void Key::update(const sf::Time& delta)
{
	m_animation.update(delta);
}

