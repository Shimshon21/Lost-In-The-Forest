//-------------------------- Include section  ----------------------------
#include "StaticObjects_Headers/Gold.h"
#include "Resources.h"
#include "Macros.h"


// C-tor
Gold::Gold(const sf::Vector2f& pos)
	: Bonus({ BLOCK_SIZE / 3, BLOCK_SIZE / 3 }, pos),
	m_animation(Resources::instance().
		animationWorldData(Resources::GOLD_DATA),
		Operation::Stay, m_shape, Resources::instance().
		getStaticObjectTexture(Resources::STATIC_ANIMATED))
{}


//----------------------------- update -----------------------------------
// Updates the animation depending on delta time.
//------------------------------------------------------------------------
void Gold::update(const sf::Time& delta)
{
	m_animation.update(delta);
}
