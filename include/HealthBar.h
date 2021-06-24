#pragma once
#include "SFML/Graphics.hpp"


/*Health bar object to exhibit the movable 
object current health point he has	*/
class HealthBar
{
public:
	
	HealthBar(sf::Vector2f, sf::Vector2f);
	
	~HealthBar() = default;

	void draw(sf::RenderWindow&);

	void setHp(const int);

	void updateCurrentHealth();

	void decreaseHealth(const int);

	void increaseHealth(const int);

	void setPosition(sf::Vector2f);

	const int getHp() const;

	const bool isAlive()const;

private:

	int m_hp = 100;

	sf::RectangleShape
		m_fullSizeBackground,
		m_currentHealth,
		m_playerIcon;

	sf::Texture m_icon;
};