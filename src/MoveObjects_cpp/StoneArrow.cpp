//--------------------------- Include section  ---------------------------
#include "MoveObjects_Headers\StoneArrow.h"
#include "Resources.h"


//------------------------------- C-tor ----------------------------------
// Uses the base class constructor to the In order to initialize the
// fields.
//------------------------------------------------------------------------
StoneArrow::StoneArrow(const sf::Vector2f& size,const sf::Vector2f& pos,
	const int direction)
	: Arrow(size, pos, direction, Resources::instance().
	moveableAnimationsData(Resources::instance().STONE_ARROWS_DATA))
{
	setDamage(STONE_ARRROW_DMG);
	Resources::instance().playSound(ARROW_SOUND);
}