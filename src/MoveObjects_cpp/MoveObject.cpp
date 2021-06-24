//-------------------------- Include section  ----------------------------
#include "MoveObjects_Headers/MoveObject.h"
#include "Macros.h"
#include "StaticObjects_Headers/Block.h"
#include "StaticObjects_Headers/Gold.h"
#include "CollisionHandling.h"


//------------------------------ C-tor -----------------------------------
// Uses the constructor of the base class to configure the moveable 
// objects characteristics.
//------------------------------------------------------------------------
MoveObject::MoveObject(const sf::Vector2f& size, const sf::Vector2f& pos)
	: GameObject(size, pos)
{}


//------------------------------- draw -----------------------------------
// Draws the object upon the world of the game.
//------------------------------------------------------------------------
void MoveObject::draw(sf::RenderWindow& window)
{
	GameObject::draw(window);
}


//-------------------------- handleCollision -----------------------------
// Handles collision with the floor.
// Pushes the moving object off the floor depending on the location of the
// collision.
//------------------------------------------------------------------------
void MoveObject::handleCollision(Block& floor)
{
	if (CollisionFromAboveFloor(floor))
	{
		m_shape.setPosition(m_oldPos);
		falling = false;
		onFloor = true;
	}
	else if (collisionFromLeft(floor))
	{
		m_shape.move(-PUSH_FROM);
	}
	else if (collisionFromRight(floor))
	{
		m_shape.move(PUSH_FROM);
	}
	else if (collisionFromBelow(floor))
	{
		m_shape.setPosition(m_oldPos);
	}
}


//----------------------------- setMapIt ---------------------------------
// Sets the map static obejcts iterators.
//------------------------------------------------------------------------
void MoveObject::setMapIt(mapIt it1, mapIt it2)
{
	m_staticObjBeg = it1;
	m_staticObjEnd = it2;	
}


//------------------------- handleMoveObjects ----------------------------
// Handles collision with moveable objects.
//------------------------------------------------------------------------
void MoveObject::handleMoveObjects(MoveObjectIt begin, MoveObjectIt end)
{
	for (auto i = begin; i != end; i++)
	{
		if (collide(*i->get()) && i->get() != this)
		{
			processCollision(*this, *i->get());
		}
	}
}


//--------------------------- collisionFromLeft --------------------------
// Returns if there was a collision from left side with a static object.
//------------------------------------------------------------------------
bool MoveObject::collisionFromLeft(GameObject& g) const
{
	return m_shape.getPosition().x < 
		(g.getPosition().x - g.getShape().x / 2);
}


//-------------------------- collisionFromRight ---------------------------
// Returns if there was a collision from right side with a static object.
//------------------------------------------------------------------------
bool MoveObject::collisionFromRight(GameObject& g) const
{
	return m_shape.getPosition().x > 
		(g.getPosition().x + g.getShape().x / 2);
}


//------------------------- collisionFromBelow ---------------------------
// Returns if there was a collision from below with a static object.
//------------------------------------------------------------------------
bool MoveObject::collisionFromBelow(GameObject& g) const
{
	return m_shape.getPosition().y > 
		(g.getPosition().y - g.getShape().y / 2);
}


//----------------------------- getStaticBeg -----------------------------
// Returns iterator to the begining of the static objects. 
//------------------------------------------------------------------------
mapIt MoveObject::getStaticBeg() const
{
	return m_staticObjBeg;
}


//----------------------------- getStaticEnd -----------------------------
// Returns iterator to the end of the static objects. 
//------------------------------------------------------------------------
mapIt MoveObject::getStaticEnd() const
{
	return m_staticObjEnd;
}


//----------------------------- setPlayerPos -----------------------------
// Sets the current player position.
//------------------------------------------------------------------------
void MoveObject::setPlayerPos(const sf::Vector2f& pos)
{
	m_playerPos = pos;
}


//---------------------------- getPlayerPos ------------------------------
// Returns the players position.
//------------------------------------------------------------------------
const sf::Vector2f& MoveObject::getPlayerPos() const
{
	return m_playerPos;
}


//----------------------- CollisionFromAboveFloor ------------------------
// Returns if there is collision from above with the floor.
//------------------------------------------------------------------------
bool MoveObject::CollisionFromAboveFloor(GameObject& floor) const
{
	return m_shape.getPosition().y + m_shape.getSize().x / 2.f <=
		(floor.getPosition().y - floor.getShape().y / 2) &&
		m_shape.getPosition().x >=
		(floor.getPosition().x - floor.getShape().x / 2) &&
		m_shape.getPosition().x <=
		(floor.getPosition().x + floor.getShape().x / 2);
}


//------------------------ CollisionFromAboveBox -------------------------
// Returns if there is collision from above with the box.
//------------------------------------------------------------------------
bool MoveObject::CollisionFromAboveBox(GameObject& box) const
{
	return m_shape.getPosition().y - m_shape.getSize().y / 2 <= 
		(box.getPosition().y - box.getShape().y / 2) &&
		m_shape.getPosition().x + HALF_SIZE >=
		(box.getPosition().x - box.getShape().x / 2) &&
		m_shape.getPosition().x - HALF_SIZE <=
		(box.getPosition().x + box.getShape().x / 2);
}


//----------------------------- setDeltaTime -----------------------------
// Sets delta time.
//------------------------------------------------------------------------
void MoveObject::setDeltaTime(const float& deltaTime)
{
	m_deltaTime = deltaTime;
}


//------------------------------ isHiting --------------------------------
// Returns if the current object is hiting.
//------------------------------------------------------------------------
bool MoveObject::isHiting() const
{
	return m_hitingStatus;
}


//--------------------------- setEventsClock -----------------------------
// Sets the event clock. needed to set a suitable timing for each moving
// object.
//------------------------------------------------------------------------
void MoveObject::setEventsClock(const float eventDelay)
{
	m_eventsClock.push_back(std::make_unique<EventClock>(eventDelay));
}


//------------------------- isEventDelayPassed ---------------------------
// Returns if the time of the delay between the events has passed.
//------------------------------------------------------------------------
bool MoveObject::isEventDelayPassed(const int i)
{
	return m_eventsClock[i]->delayTimePassed();
}


//---------------------------- handleEvents ------------------------------
// Runs over the static objects in the game and checks if there was a
// collision with them. 
//------------------------------------------------------------------------
void MoveObject::handleEvents()
{
	for (auto i = getStaticBeg(); i != getStaticEnd(); i++)
	{
		if (collide(*(i->get()))) 
		{
			processCollision(*this, *(i->get()));
		}
	}
}


void MoveObject::move() {}

void MoveObject::handleFall() {}

void MoveObject::update(sf::Time) {}