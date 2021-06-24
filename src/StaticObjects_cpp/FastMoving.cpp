//-------------------------- Include section  ----------------------------
#include "StaticObjects_Headers/SpecialAbilty_Headers/FastMoving.h"
#include "Resources.h"
#include "Macros.h"


// C-tor
FastMoving::FastMoving(const sf::Vector2f& pos) 
	: SpecialAbility({ BLOCK_SIZE / 2, BLOCK_SIZE / 2 }, pos,
	Resources::instance().
		animationWorldData(Resources::SPEED_ABILITY_DATA))
{}
