#pragma once

//-------------------------- Include section  ----------------------------
#include "SFML/Graphics.hpp"
#include "StaticObjects_Headers/StaticObject.h"
#include <vector>
#include <memory>	//Uniqe_ptr
#include <string>
class GameScreen;


//---------------------------- class Board  ------------------------------
class Board
{
public:

	// c-tor
	Board(GameScreen*);

	// c-tor
	Board() = default;

	// d-tor
	virtual ~Board() = default;

	void load_map(const int);

	void draw(sf::RenderWindow &, sf::Time&);

	void setDoorKeyString(const int);

	std::vector<std::unique_ptr<StaticObject>>::iterator getStaticObjBegIt();

	std::vector<std::unique_ptr<StaticObject>>::iterator getStaticObjEndIt();

	void clearStaticObjects();

	void reloadStage();

	const int getGoldCounter() const;

	const int getKeysCounter() const;


private:
	
	GameScreen* m_controller;

	int m_goldCounter = 0, m_stageNum = 0, m_keyCounter = 0;

	//Static object used in the game.
	std::vector<std::unique_ptr<StaticObject>> m_staticObjects;

	std::vector<std::string> m_currentStage;

	sf::RectangleShape m_background;

	sf::Text m_doorRequiredKeys;

	void setTextData();

	//Set board game objects from 'intialStage'
	void setBoardObjects();

	void setObjectByIcon(const char, sf::Vector2f);

	template <class OBJ>
	void setStaticObject(sf::Vector2f&&);

	template <class OBJ>
	void setStaticObject(sf::Vector2f&&, const char, const int);
};


template<class OBJ>
inline void Board::setStaticObject(sf::Vector2f&& pos)
{
	m_staticObjects.push_back(std::make_unique<OBJ>(pos));
}


template<class OBJ>
inline void Board::setStaticObject(sf::Vector2f&& pos, 
	const char type, const int m_stageNum)
{
	m_staticObjects.push_back(std::make_unique<OBJ>(pos, type, m_stageNum));
}
