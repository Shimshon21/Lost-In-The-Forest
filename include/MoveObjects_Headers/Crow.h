 #pragma once

//-------------------------- Include section  ----------------------------
#include "MoveObjects_Headers/Crow.h"
#include "MoveObjects_Headers/Enemy.h"
#include "MoveObjects_Headers/SmartEnemy.h"
#include "Animation.h"
#include "HealthBar.h"


//---------------------------- class Crow  -------------------------------
class Crow : public SmartEnemy
{
public:

	// c-tor
	Crow(sf::Vector2f, sf::Vector2f);

	// d-tor
	virtual ~Crow() = default;

	virtual void update(sf::Time)override;

	virtual void draw(sf::RenderWindow&)override;

	virtual void move();

	virtual void handleFall();

	virtual void handleCollision(Block&);

private:

	virtual void playHurtSound() const override;

	virtual void playDeathSound() const override;

	virtual void playAttackSound() const override;
};

