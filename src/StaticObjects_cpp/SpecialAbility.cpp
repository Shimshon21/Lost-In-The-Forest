//-------------------------- Include section  ----------------------------
#include "StaticObjects_Headers/SpecialAbilty_Headers/SpecialAbility.h"
#include "Resources.h"


// C-tor
SpecialAbility::SpecialAbility(const sf::Vector2f& size,
	const sf::Vector2f& pos, const AnimationData& data)
	: Bonus(size, pos), m_animation(data, Operation::Stay,
		m_shape, Resources::instance().
		getStaticObjectTexture(Resources::STATIC_ANIMATED))
{}


//----------------------------- update -----------------------------------
// Updates the special ability's animation depending on delta time.
//------------------------------------------------------------------------
void SpecialAbility::update(const sf::Time& deltaTime)
{
	m_animation.update(deltaTime);
}
