#pragma once

//-------------------------- Include section  ----------------------------
#include "SFML/Graphics.hpp"


//------------------------- class GameObject -----------------------------
class GameObject
{
public:

	// c-tor
	GameObject() = default;

	// d-tor
	virtual ~GameObject() = default;
	
	GameObject(const sf::Vector2f&, const sf::Vector2f&);

	virtual void draw(sf::RenderWindow&);

	bool collide(GameObject& b) const;

	const sf::Vector2f getPosition() const;

	const sf::Vector2f getShape() const;

	void setDisappear(bool);

	const bool getDisapperStatus() const;

protected:

	void setScale(const sf::Vector2f&);

	//Temporary
	sf::Texture m_texture;

	// Holds the previous position of the player.
	// Needed for collision handling.
	sf::Vector2f m_oldPos;

	sf::RectangleShape m_shape;

private:

	bool m_disappear = false;
};