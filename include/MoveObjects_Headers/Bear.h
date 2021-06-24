#pragma once

//-------------------------- Include section  ----------------------------
#include "Enemy.h"
#include "Animation.h"
#include "HealthBar.h"
#include "MoveObjects_Headers/Player.h"
#include "MoveObjects_Headers/Enemy.h"


//---------------------------- class Bear  -------------------------------
class Bear : public Enemy
{
public:

	// c-tor
	Bear(sf::Vector2f, sf::Vector2f);

	// d-tor
	virtual ~Bear() = default;

	// moves the Enemy - constant move 
	virtual void move();

	virtual void update(sf::Time) override;

	virtual void draw(sf::RenderWindow& window) override;

private:

	virtual void playHurtSound() const override;

	virtual void playDeathSound() const override;

	virtual void playAttackSound() const override;
};