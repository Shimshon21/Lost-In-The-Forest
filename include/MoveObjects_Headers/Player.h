#pragma once

//-------------------------- Include section  ----------------------------
#include "MoveObject.h"
#include <StaticObjects_Headers/Gold.h>
#include "Operation.h"
#include "StaticObjects_Headers/Hurricane.h"
#include "MoveObjects_Headers/Box.h"
#include "StaticObjects_Headers/Door.h"
#include "StaticObjects_Headers/Spike.h"
#include "HealthBar.h"
#include "EventClock.h"

class Enemy;

//--------------------------- class Player  ------------------------------
class Player : public MoveObject
{
public:

	// c-tor
	Player(const sf::Vector2f&, const sf::Vector2f&);

	// d-tor
	virtual ~Player() = default;

	virtual void move();

	virtual void update(sf::Time);

	void handleFall();
	
	void handleJump(bool);

	void shoot();

	void handleCollision(Hurricane&);

	void handleCollision(Box&);

	void handleCollision(Door&);

	void handleCollision(Enemy&);

	void handleCollision(Spike&);

	const sf::Vector2f& getPosition() const;

	const sf::Vector2f keyToDirection() const;

	const  sf::Vector2f getMovement();

	const bool getExtraSpeed()const;

	const bool getExtraJump() const;

	const bool hasSpecialArrow() const;

	virtual void draw(sf::RenderWindow&) override;

	void increaseScore();

	const int getScore() const;

	const int getScale() const;

	void setSpecialAbility(const std::string&);

	void hit();

	void setHealthBarPosition(sf::Vector2f);

	void setHittingStatus(const bool);

	void setKeyStatus(const bool);

	void addKey();

	const int getKeyCount() const;

	bool isFinishedLevel(const int);

	const bool isAlive() const;

	void incLife();

	bool isShootValid();

private:

	void moveShape(const sf::Vector2f&);

	void setEventsClock();

	bool isInsideHurricane(Hurricane&);

	void playMovementAnimations();

	void pushBackFromSpike(Spike&);

	void stayInPlaceAnimation(const sf::Vector2f&);

	void setMovementStatus(const sf::Vector2f&);

	void pushFromBox(Box&, const sf::Vector2f&, const sf::Vector2f&);
	
	void setExtraJumpStatus();

	void setExtraSpeedStatus();

	void turnOnDamageBoost();

	void setPositionOnBox(Box&);

	int m_socore = 0,
		m_extraSpeed = 0,
		m_extraJumpBoost = 0,
		m_keysCount = 0;

	bool m_levelFinishStatus = false,
		doorCollide = false,
		m_keyStatus = false,
		m_damageBoost = false;

	Animation m_animation;

	HealthBar m_healthBar;
};



