//--------------------------- Include section  ---------------------------
#include "MoveObjects_Headers\FireArrow.h"
#include "Resources.h"


//------------------------------- C-tor ----------------------------------
// Uses the base class constructor to the In order to initialize the
// fields.
//------------------------------------------------------------------------
FireArrow::FireArrow(const sf::Vector2f& size,const sf::Vector2f& pos,
	const int direction)
	: Arrow(size, pos, direction, Resources::instance().
		moveableAnimationsData(Resources::instance().FIRE_ARROWS_DATA))
{
	setDamage(FIRE_ARRROW_DMG);

	Resources::instance().playSound(FIRE_ATTACK_SOUND);
}