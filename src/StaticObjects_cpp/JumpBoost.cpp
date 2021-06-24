//-------------------------- Include section  ----------------------------
#include "StaticObjects_Headers/SpecialAbilty_Headers/JumpBoost.h"
#include "Resources.h"
#include "Macros.h"


// C-tor
JumpBoost::JumpBoost(const sf::Vector2f& pos)
	: SpecialAbility(sf::Vector2f(BLOCK_SIZE / 2, BLOCK_SIZE / 2), pos,
		Resources::instance().
		animationWorldData(Resources::JUMP_ABILITY_DATA))
{}
