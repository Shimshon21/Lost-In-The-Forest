#pragma once

//-------------------------- Include section  ----------------------------
#include "Enemy.h"
#include "MoveObjects_Headers/Wolf.h"
#include "Animation.h"
#include "HealthBar.h"
#include "MoveObjects_Headers/SmartEnemy.h"


//---------------------------- class Crow  -------------------------------
class Wolf : public SmartEnemy
{
public:

	// c-tor
	Wolf(const sf::Vector2f&, const sf::Vector2f&);

	// d-tor
	virtual ~Wolf() = default;

	virtual void update(sf::Time) override;

	virtual void draw(sf::RenderWindow&) override;

	virtual void move();

private:

	virtual void playHurtSound() const;

	virtual void playDeathSound() const;

	virtual void playAttackSound() const;
};
