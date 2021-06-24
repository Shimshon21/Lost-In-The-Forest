#pragma once

//-------------------------- Include section  ----------------------------
#include "Enemy.h"

//------------------------- class SmartEnemy  -----------------------------
class SmartEnemy : public Enemy
{
public:

	// c-tor
	SmartEnemy(const sf::Vector2f&, const sf::Vector2f&, const AnimationData&);

	// d-tor
	virtual ~SmartEnemy() = default;

protected:

	const sf::Vector2f& getMove();
	
	void move();

private:

	double getDistance(const sf::Vector2f&);

	int minDistance(const double&, const double&,
		const double&, const double&);

	const sf::Vector2f getNextMove(const int);
};