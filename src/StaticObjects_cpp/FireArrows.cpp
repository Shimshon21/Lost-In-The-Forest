//-------------------------- Include section  ----------------------------
#include "StaticObjects_Headers/SpecialAbilty_Headers/FireArrows.h"
#include "Resources.h"
#include "Macros.h"


// c-tor
FireArrows::FireArrows(const sf::Vector2f& pos) 
	: SpecialAbility({ BLOCK_SIZE / 2, BLOCK_SIZE / 2 }, pos,
	Resources::instance().
		animationWorldData(Resources::FIRE_ARROWS_ABILITY_DATA))
{}
