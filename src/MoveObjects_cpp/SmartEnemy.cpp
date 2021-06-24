//-------------------------- Include section  ----------------------------
#include "MoveObjects_Headers/SmartEnemy.h"


//------------------------------- C-tor ----------------------------------
// Uses the base class constructor to initialize the fields.
//------------------------------------------------------------------------
SmartEnemy::SmartEnemy(const sf::Vector2f& size, const sf::Vector2f& pos,
	const AnimationData& data)
	: Enemy(size, pos, data)
{}


//------------------------------ getMove ---------------------------------
// Returns the next move that brings the enemy closer to the player.
//------------------------------------------------------------------------
const sf::Vector2f& SmartEnemy::getMove()
{
	// to hold the wanted movement and then
	// check if the movement is okay or not 
	mvUp = mvDown = mvLeft = mvRight = false;

	double
		// 1 - up
		d1 = getDistance(UP_MOVEMENT * PLAYER_SPEED),
		// 2 - down
		d2 = getDistance(DOWN_MOVEMENT * PLAYER_SPEED),
		// 3 - left
		d3 = getDistance(LEFT_MOVEMENT * PLAYER_SPEED),
		// 4 - right
		d4 = getDistance(RIGHT_MOVEMENT * PLAYER_SPEED);


	return getNextMove(minDistance(d1, d2, d3, d4));
}


//------------------------------- move -----------------------------------
// Moves the smart object.
// The function works as follows:
// Checking the player's current location.
// Depending on the position of the player, calculates with the the 
// Euclidean distance function all possible distances towards the player.
// After calculating all the distances, compares and returns the closest
// distance and then the enemy preforms that movement toward the player.
//------------------------------------------------------------------------
void SmartEnemy::move()
{
	auto speed = m_deltaTime * PLAYER_SPEED / 2.f;

	if (m_animation.getOperation() != Operation::Hit)
	{
		if (isPlayerClose() && !falling)
		{
			auto moveDir = getMove();

			Enemy::move(moveDir * speed);
		}
		else if (!falling)
		{
			Enemy::move(Enemy::getMove() * speed);
		}
	}
}


//---------------------------- getDistance -------------------------------
//   Return the distance between two given positions 
//------------------------------------------------------------------------
double SmartEnemy::getDistance(const sf::Vector2f& move)
{
	auto playerPos = getPlayerPos();
	auto enemyPos = m_shape.getPosition() + move;

	return sqrt(pow((playerPos.x - enemyPos.x), 2) +
		pow((playerPos.y - enemyPos.y), 2));
}


//---------------------------- minDistance -------------------------------
// Calculate which movement of the enemy returns the shortest distance
// between the player and the enemy.
//------------------------------------------------------------------------
int SmartEnemy::minDistance(const double& d1, const double& d2,
	const double& d3, const double& d4)
{
	// signal to move up
	if (d1 <= d2 && d1 <= d3 && d1 <= d4 ||
		m_shape.getPosition().y > getPlayerPos().y)
		return ONE;

	// signal to move down
	if (d2 <= d1 && d2 <= d3 && d2 <= d4)
		return TWO;

	// signal to move left
	if (d3 <= d1 && d3 <= d2 && d3 <= d4)
		return THREE;
	
	// signal to move right
	if (d4 <= d1 && d4 <= d2 && d4 <= d3)
		return FOUR;
	
	// default
	return ZERO;
}


//-------------------------- getNextMove ---------------------------------
// Return the next movement the tracking enemy should do.
// Calculates the next movement with the given params.
//------------------------------------------------------------------------
const sf::Vector2f SmartEnemy::getNextMove(const int type)
{
	switch (type)
	{
	case UP:    
		return UP_MOVEMENT;

	case DOWN:	
		return DOWN_MOVEMENT;

	case LEFT:
		mvLeft = true;
		m_shape.setScale(LEFT_SCALE);
		m_animation.operation(Operation::Right);
		return LEFT_MOVEMENT;

	case RIGHT:
		mvRight = true;
		m_shape.setScale(RIGHT_SCALE);
		m_animation.operation(Operation::Right);
		return RIGHT_MOVEMENT;
	}

	return STAY_IN_PLACE;
}
