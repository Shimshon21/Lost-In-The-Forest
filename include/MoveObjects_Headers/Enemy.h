#pragma once

//-------------------------- Include section  ----------------------------
#include "MoveObject.h"
#include "Enemy.h"
#include "Box.h"
#include "Animation.h"
#include "Player.h"
#include "Resources.h"

typedef Resources::movableDataAnime moveData;


//--------------------------- class Enemy  -------------------------------
class Enemy : public MoveObject
{
public:
	
	// c-tor
	Enemy(const sf::Vector2f&, const sf::Vector2f&, const AnimationData&);

	// d-tor
	virtual ~Enemy() = default;

	virtual void move(const sf::Vector2f&);

	virtual void handleCollision(Block&);

	virtual void handleCollision(Box&);

	void handleHit(Enemy&, const int);

	void setOperation(const Operation);

	void handleFall();

	bool isPlayerClose();

	bool isAlive();

	void hit(Enemy&);

	const int getDamagePoints() const;

protected:

	void scaleAccordingToPlayerPos();

	virtual void playDeathSound() const = 0;

	virtual void playHurtSound() const = 0;

	virtual void playAttackSound() const = 0;

	sf::Vector2f getMove();
	
	Animation m_animation;

	HealthBar m_health;

	int m_damagePoints = 0;

private:

	void setEventsClock();

	std::string m_kind = "";
};