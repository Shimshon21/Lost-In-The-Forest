//-------------------------- Include section  ----------------------------
#include "MoveObjects_Headers/Player.h"
#include "Macros.h"
#include "CollisionHandling.h"
#include "GameObject.h"
#include "Resources.h"
#include "MoveObjects_Headers/Enemy.h"


//------------------------------- C-tor ----------------------------------
// Sets features using the base class constructor.
// Also, sets it's unique size and events clock.
//------------------------------------------------------------------------
Player::Player(const sf::Vector2f& size, const sf::Vector2f& pos)
	: MoveObject(size, pos), m_animation(Resources::instance().
		moveableAnimationsData(Resources::instance().PLAYER_DATA),
		Operation::Stay, m_shape, Resources::instance().
		getMovableObjectTexture(Resources::instance().PLAYER)),
	m_healthBar({ sf::Vector2f(sf::Vector2f(50.f, 8.f)),
		sf::Vector2f(5, 1) })
{
	m_shape.setSize({ m_shape.getSize() - sf::Vector2f{10, 10} });
	setEventsClock();
}


//------------------------------- move -----------------------------------
// Moves the player according to the players request.
// The player moves only if he is alive. Otherwise, the death animation
// is played.
// 
// the function works as follows:
// 1. Gets the next requested action(movement).
// 2. sets all the movement stats back to false.
// 3. Moves the shape of the player.
// 4. Handles all the possible events that can accure in the game.
//------------------------------------------------------------------------
void Player::move()
{
	if (m_healthBar.isAlive()) 
	{
		auto movement = getMovement();

		setMovementStatus(movement);

		moveShape(movement);

		MoveObject::handleEvents();
	}
	else
	{
		m_animation.operation(Operation::Dead);
	}
}


//------------------------- setMovementStatus ----------------------------
// Sets the movement status of the player and checks what is the new 
// movement the player preformed.
// Depending on the movement of the player, the function updates the
// data and presents the appropriate animation.
//------------------------------------------------------------------------
void Player::setMovementStatus(const sf::Vector2f& movement)
{
	doorCollide = insideHurricane = onFloor = mvRight = mvLeft = false;

	if (movement.x < ZERO)
	{
		setScale(SCALE_LEFT);
		mvLeft = true;
	}

	if (movement.x > ZERO)
	{
		setScale(SCALE_RIGHT);
		mvRight = true; 
	}

	playMovementAnimations();
}


//-------------------------- setExtraJumpStatus --------------------------
// Set the extra jump status.
// We enter this function if the player collects the extra jump boost gem.
//------------------------------------------------------------------------
void Player::setExtraJumpStatus()
{
	m_extraJumpBoost = JUMP_BOOST_BONUS;
}


//------------------------------------------------------------------------
// Checks if the player doesn't move. If he is not, plays the standing
// animation.
//------------------------------------------------------------------------
void Player::stayInPlaceAnimation(const sf::Vector2f& movement)
{
	if (movement == STAY_IN_PLACE &&
		m_animation.getOperation() != Operation::Hit &&
		m_animation.getOperation() != Operation::Shoot &&
		m_animation.getOperation() != Operation::Hurt &&
		!inHnaldeJump)
	{
		m_animation.operation(Operation::Stay);
	}
}


//------------------------------ moveShape -------------------------------
// Moves the shape of the obejct and saves the old position for handle
// collisions.
//------------------------------------------------------------------------
void Player::moveShape(const sf::Vector2f& movement)
{
	stayInPlaceAnimation(movement);
	m_oldPos = m_shape.getPosition();
	m_shape.move(movement);
}


//---------------------------- setEventsClock ----------------------------
// Set the extra jump status.
// We enter this function if the player collects the extra jump boost gem.
//------------------------------------------------------------------------
void Player::setEventsClock()
{
	MoveObject::setEventsClock(FIST_RATIO);
	MoveObject::setEventsClock(SHOOT_RATIO);
}


//------------------------- isInsideHurricane ----------------------------
// Returns if the player is inside a hurricane.
// We want to want accurate behavior so we calculate by the position of 
// the player whether he is really inside the hurricane and not just 
// collided with him
//------------------------------------------------------------------------
bool Player::isInsideHurricane(Hurricane& hurricane)
{
	return (m_shape.getPosition().x >= hurricane.getPosition().x
		- hurricane.getShape().x / 2 &&
		m_shape.getPosition().x <= hurricane.getPosition().x
		+ hurricane.getShape().x / 2);
}


//----------------------- playMovementAnimations -------------------------
// Plays the animation according to the situation in which the player is.
//------------------------------------------------------------------------
void Player::playMovementAnimations()
{
	if (mvRight || mvLeft)
	{
		if (!inHnaldeJump) 
		{
			if (m_animation.getOperation() != Operation::Hit &&
				m_animation.getOperation() != Operation::Hurt)
			{
				m_animation.operation(Operation::Right);
			}
		}
		else 
		{
			m_animation.operation(Operation::Jump);
		}
	}
	else if (inHnaldeJump)
	{
		m_animation.operation(Operation::Jump);
	}
}


//-------------------------- pushBackFromSpike ---------------------------
// Pushes the player backwards depending on the location of his collision
// with the spikes.
//------------------------------------------------------------------------
void Player::pushBackFromSpike(Spike& spike)
{
	if (collisionFromLeft(spike) && m_shape.getPosition().y +
		m_shape.getSize().y / 2 > spike.getPosition().y)
	{
		m_shape.move(-PUSH_FROM_SPIKE);
	}
	else if (collisionFromRight(spike) && m_shape.getPosition().y + 
		m_shape.getSize().y / 2 > spike.getPosition().y)
	{
		m_shape.move(PUSH_FROM_SPIKE);
	}
}


//---------------------------- getPosition -------------------------------
// Returns the position of the player.
//------------------------------------------------------------------------
const sf::Vector2f& Player::getPosition() const
{
	return m_shape.getPosition();
}


//------------------------------ handleFall ------------------------------
// Handle the fall of the player.
// Assume that the player is falling.
// Check what is the current position of the player.
// If the current position of the player is not in 
// the air ==> don't fall and exit.
// If the player is falling ==> move the player downwards.
//------------------------------------------------------------------------
void Player::handleFall()
{	
	if (!inHnaldeJump && !onFloor && !insideHurricane) 
	{
		inHandleFall = true;
		falling = true;
		
		move();
		
		if (!onFloor)
		{
			m_animation.operation(Operation::Fall);
		}

		inHandleFall = false;
	}
}


//---------------------------- keyToDirection ----------------------------
// Checks the key that the user has performed and returns the movement
// accordingly
//------------------------------------------------------------------------
const sf::Vector2f Player::keyToDirection() const
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		return LEFT_MOVEMENT;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		return RIGHT_MOVEMENT;
	}

	return STAY_IN_PLACE;
}


//----------------------------- getMovement ------------------------------
// Returns the next move depending on the situation.
// i.e. if the player is falling, return a downward movement, if the is
// jumping, return a movement upwards + the wanted direction the user 
// wants. If the player is neither falling or jumping, return the next
// movement the user wants to preform.
//------------------------------------------------------------------------
const sf::Vector2f Player::getMovement() 
{
	if (inHandleFall) 
	{
		return FALL_PUSH;
	}
	else if (inHnaldeJump)
	{
		return ((keyToDirection() + UP_MOVEMENT) * 
			m_deltaTime * HANDLE_JUMP_SPEED);
	}
	
	return keyToDirection() * m_deltaTime * (PLAYER_SPEED + m_extraSpeed);
}


//------------------------- setExtraSpeedStatus --------------------------
// Set the speed status of the player.
//------------------------------------------------------------------------
void Player::setExtraSpeedStatus()
{
 	m_extraSpeed = EXTRA_SPEED_BONUS;
}


//-------------------------- turnOnDamageBoost ---------------------------
// Turn on the damage bonus.
//------------------------------------------------------------------------
void Player::turnOnDamageBoost()
{
	m_damageBoost = true;
}


//----------------------------- pushFromBox ------------------------------
// Pushses the player from the box.
//------------------------------------------------------------------------
void Player::pushFromBox(Box& box, const sf::Vector2f& playerPush, 
	const sf::Vector2f& boxPush)
{
	if (box.isMoveAble())
	{
		box.move(boxPush);
	}
	else
	{
		m_shape.move(playerPush);
	}
}


//--------------------------- setPositionOnBox ---------------------------
// Sets the position of the player when he is above the box so that he
// will stand on it accurately.
//------------------------------------------------------------------------
void Player::setPositionOnBox(Box& box)
{
	m_shape.setPosition(m_shape.getPosition().x,
		box.getPosition().y - box.getShape().y / 2 - PUSH_FROM_BOX);
	falling = false;
	onFloor = true;
}


//---------------------------- getExtraSpeed -----------------------------
// Return the extra speed of the player.
// If the player didn't collected the extra speed gem, the extra speed 
// is by default zero.
//------------------------------------------------------------------------
const bool Player::getExtraSpeed() const
{
	return m_extraSpeed;
}


//---------------------------- getExtraJump ------------------------------
// Return the extra jump bonus.
//------------------------------------------------------------------------
const bool Player::getExtraJump() const
{
	return m_extraJumpBoost;
}


//-------------------------- hasSpecialArrow -----------------------------
// Return if the plyaer has a special arrow or not.
//------------------------------------------------------------------------
const bool Player::hasSpecialArrow() const
{
	return m_damageBoost;
}


//------------------------------- draw -----------------------------------
// Prints the player upon the window.
//------------------------------------------------------------------------
void Player::draw(sf::RenderWindow& window)
{
	m_healthBar.draw(window);

	auto temp_shape = m_shape;

	switch (m_animation.getOperation())
	{
	case Operation::Stay:
		temp_shape.setPosition(temp_shape.getPosition().x,
			temp_shape.getPosition().y +
			temp_shape.getOrigin().y / HALF_SIZE);
		break;

	case Operation::Right:
		temp_shape.scale(RIGHT_AND_LEFT_SCALE);
		temp_shape.setPosition(temp_shape.getPosition().x,
			temp_shape.getPosition().y +
			temp_shape.getOrigin().y / HALF_SIZE);
		break;

	case Operation::Fall:
	case Operation::Jump:
		temp_shape.scale(JUMP_SCALE);
		break;
	case Operation::Shoot:
		temp_shape.scale(SHOOT_SCALE);
		break;
	case Operation::Hurt:
		temp_shape.scale(HURT_SCALE);
	}
	window.draw(temp_shape);

}


//-------------------------- setSpecialAbility ---------------------------
// Set the appropriate ability according to the special ability that the
// player has collected.
//------------------------------------------------------------------------
void Player::setSpecialAbility(const std::string& specialAbility)
{
	m_damageBoost = m_extraJumpBoost = m_extraSpeed = ZERO;

	Resources::instance().playSound(COLLECT_ABILITY_SOUND);

	if (specialAbility == EXTRA_JUMP_ABILITY)
	{
		setExtraJumpStatus();
	}

	if (specialAbility == EXTRA_SPEED_ABILITY)
	{
		setExtraSpeedStatus();
	}

	if (specialAbility == FIRE_ARROWS_ABILITY)
	{
		turnOnDamageBoost();
	}
}


//-------------------------------- hit -----------------------------------
// The player reguests to attack. Therefore, we needed to update the
// status of the hit and display the hiting animation.
//------------------------------------------------------------------------
void Player::hit()
{
	if (m_healthBar.getHp() > ZERO && onFloor &&
		isEventDelayPassed(FIST_ATTACK))
	{
		Resources::instance().playSound(PLAYER_ATTACK_SOUND);
		m_hitingStatus = true;
		m_animation.operation(Operation::Hit);
	}
}


//----------------------------- handleJump -------------------------------
// handles the jump event.
// The player is shifted upwards with calling the function move that knows
// how to handle the various events that can happen during the jump and
// act accordingly.
// If the player has collected the jump bonus, the loop that calls the 
// move function will be summoned more times to elevate the player
// further upwards.
//------------------------------------------------------------------------
void Player::handleJump(bool jump)
{
	static int jumpCounter = ZERO;

	inHnaldeJump = true;
	if (jump && onFloor && jumpCounter == ZERO)
	{
		Resources::instance().playSound(JUMP_SOUND);
		falling = true;
		onFloor = false;
		jumpCounter = JUMP_COUNTER + m_extraJumpBoost;

	}

	if (jumpCounter != ZERO && !insideHurricane)
	{
		jumpCounter--;
		move();				// move the player upwards.
	}
	else
	{
		inHnaldeJump = false;
		jumpCounter = ZERO;
	}
}


//------------------------------- shoot ----------------------------------
// Plays the shoot animation.
//------------------------------------------------------------------------
void Player::shoot()
{
	m_animation.operation(Operation::Shoot);
}


//-------------------------- handleCollision -----------------------------
// Handles collision with hurricane.
// The hurricane lifst the player up (moves the player shape upwards).
// We Make an accurate calculation of the player's position within
// a hurricane to check if the player is really inside the hurricane.
// If the player is inside the hurricane, we update that the player is 
// not on floor. 
//------------------------------------------------------------------------
void Player::handleCollision(Hurricane& hurricane)
{
	if (m_shape.getPosition().y + m_shape.getSize().y / 2 <=
		hurricane.getPosition().y - hurricane.getShape().y * 2)
	{
		onFloor = true;
	}
	else if (isInsideHurricane(hurricane))
	{
		insideHurricane = true;
		m_shape.move(UP_MOVEMENT * (m_deltaTime * PLAYER_SPEED));
	}
	m_animation.operation(Operation::Fall);
}


//------------------------------ update ----------------------------------
// Update the animation.
//------------------------------------------------------------------------
void Player::update(sf::Time delta)
{
	m_animation.update(delta);
}


//-------------------------- handleCollision -----------------------------
// Handle collision with a box.
//------------------------------------------------------------------------
void Player::handleCollision(Box& box)
{
	if (collisionFromLeft(box) )
	{
		pushFromBox(box, -PUSH_FROM, PUSH_FROM);
	}
	else if (collisionFromRight(box))
	{
		pushFromBox(box, PUSH_FROM, -PUSH_FROM);
	}
	else if (CollisionFromAboveBox(box))
	{
		setPositionOnBox(box);
	}
}


//-------------------------- handleCollision -----------------------------
// Returns if the player collides with the door.
//------------------------------------------------------------------------
void Player::handleCollision(Door& door)
{
	doorCollide = true;
}


//-------------------------- handleCollision -----------------------------
// Handles collision with the enemy.
// If the enemy is dead, we do nothing.
// Absorbs the hit, player the hurt animation and updates his amount of
// life accordingly.
//------------------------------------------------------------------------
void Player::handleCollision(Enemy& e)
{
	if (e.isHiting() && e.isAlive()) 
	{
		Resources::instance().playSound(PLAYER_HURT_SOUND);
		m_healthBar.decreaseHealth(e.getDamagePoints());
		if (m_animation.getOperation() != Operation::Dead)
		{
			m_animation.operation(Operation::Hurt);
			m_shape.move(HIT_PUSH_BACK * m_shape.getScale().x, ZERO);
		}
	}

	if (!m_healthBar.isAlive()) 
	{
		m_animation.operation(Operation::Dead);
		Resources::instance().playSound(GAME_OVER_SOUND);
	}
}


//------------------------- handleCollision ------------------------------
// Handles collision with a spike object.
// Pushed back and absorbs the damage from the spikes.
//------------------------------------------------------------------------
void Player::handleCollision(Spike& spike)
{
	onFloor = true;

	pushBackFromSpike(spike);
	 
	if (isEventDelayPassed(ARROW_ATTACK))
	{
		m_healthBar.decreaseHealth(SPIKE_DAMAGE);
		m_animation.operation(Operation::Dead);
	}
}


//------------------------ setHealthBarPosition --------------------------
// Sets the position of the health bar
//------------------------------------------------------------------------
void Player::setHealthBarPosition(sf::Vector2f pos)
{
	m_healthBar.setPosition(pos);
}


//-------------------------- setHittingStatus ----------------------------
// Sets the hitting status of the player.
//------------------------------------------------------------------------
void Player::setHittingStatus(const bool status)
{
	m_hitingStatus = status;
}


//---------------------------- setKeyStatus ------------------------------
// Sets the key(key that opens the door) status.
//------------------------------------------------------------------------
void Player::setKeyStatus(const bool status)
{
	m_keyStatus = status;
}


//------------------------------- addKey ---------------------------------
// Increases the amount of keys collected by 1.
//------------------------------------------------------------------------
void Player::addKey()
{
	m_keysCount++;
}


//---------------------------- getKeyCount -------------------------------
// Returns the amount of keys collected.
//------------------------------------------------------------------------
const int Player::getKeyCount() const
{
	return m_keysCount;
}


//-------------------------- isFinishedLevel -----------------------------
// Returns if the current level has finished by checking if the player 
// collected keys equal to world existed keys and checking collison with
// door was occured.
//------------------------------------------------------------------------
bool Player::isFinishedLevel(const int worldKeys)
{
	if (m_keysCount == worldKeys && doorCollide)
	{
		return true;
	}

	return false;
}


//----------------------------- isAlive ----------------------------------
// Returns if the player is alive.
//------------------------------------------------------------------------
const bool Player::isAlive() const
{
	return m_healthBar.isAlive();
}


//------------------------------ incLife ---------------------------------
// Returns if the player is alive.
//------------------------------------------------------------------------
void Player::incLife()
{
	m_healthBar.increaseHealth(HEALTH_INC);
}


//----------------------------- isShootValid -----------------------------
// Returns if the time between shoots has passed.
//------------------------------------------------------------------------
bool Player::isShootValid() 
{
	return isEventDelayPassed(ARROW_ATTACK) && onFloor;
}


//--------------------------- increaseScore ------------------------------
// Increases the score by one.
//------------------------------------------------------------------------
void Player::increaseScore()
{
	++m_socore;
}


//----------------------------- getScore ---------------------------------
// Returns the score of the player. 
//------------------------------------------------------------------------
const int Player::getScore() const
{
	return m_socore;
}


//----------------------------- getScale ---------------------------------
// Returns the score of the player. 
//------------------------------------------------------------------------
const int Player::getScale() const
{
	return m_shape.getScale().x;
}
