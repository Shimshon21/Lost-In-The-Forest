#pragma once

//-------------------------- Include section  ----------------------------
#include "GameObject.h"
#include "StaticObjects_Headers/Block.h"
#include "EventClock.h"

typedef std::vector<std::unique_ptr<StaticObject>>::iterator mapIt;

//-------------------------- class MoveObject -----------------------------
class MoveObject : public GameObject
{
public:

	// c-tor
	MoveObject(const sf::Vector2f&, const sf::Vector2f&);

	// d-tor
	virtual ~MoveObject() = default;

	virtual void draw(sf::RenderWindow& window) override;

	virtual void move();

	// Handle collision with a block - move back 
	virtual void handleCollision(Block&);

	virtual void handleFall();

	void setMapIt(mapIt, mapIt);

	typedef std::vector<std::unique_ptr<MoveObject>>::iterator MoveObjectIt;

	void handleMoveObjects(MoveObjectIt, MoveObjectIt);

	void setPlayerPos(const sf::Vector2f&);

	const sf::Vector2f& getPlayerPos() const;

	virtual void update(sf::Time);

	void setDeltaTime(const float&);

	bool isHiting() const;
	
protected:
	
	void setEventsClock(const float);

	bool isEventDelayPassed(const int);

	void handleEvents();
	
	bool CollisionFromAboveFloor(GameObject&) const;

	bool CollisionFromAboveBox(GameObject&) const;
	
	bool collisionFromLeft(GameObject&) const;

	bool collisionFromRight(GameObject&) const;

	bool collisionFromBelow(GameObject&) const;
	
	// To follow acts of the object.
	bool
		onFloor = false,
		inHnaldeJump = false,
		inHandleFall = false,
		insideHurricane = false,
		m_hitingStatus = false,
		falling = false,
		mvUp = false,
		mvDown = false,
		mvRight = false,
		mvLeft = false;

	float m_deltaTime = 0;

private:

	std::vector<std::unique_ptr<EventClock>> m_eventsClock;

	mapIt getStaticBeg() const;

	mapIt getStaticEnd() const;

	sf::Vector2f m_playerPos;

	mapIt m_staticObjBeg, m_staticObjEnd;
};