//-------------------------- Include section  ----------------------------
#include "Board.h"
#include <fstream>
#include <sstream> 
#include <iostream>
#include "Macros.h"
#include "Resources.h"
#include "Board.h"
#include "GameScreen.h"

// MoveObjects includes
#include "MoveObjects_Headers/Player.h"
#include "MoveObjects_Headers/Bear.h"
#include "MoveObjects_Headers/Crow.h"
#include "MoveObjects_Headers/Wolf.h"
#include "MoveObjects_Headers/Box.h"

// StaticObjects includes
#include "StaticObjects_Headers/Hurricane.h"
#include "StaticObjects_Headers/Door.h"
#include "StaticObjects_Headers/Key.h"
#include "StaticObjects_Headers/Door.h"
#include "StaticObjects_Headers/Block.h"
#include "StaticObjects_Headers/Gold.h"
#include "StaticObjects_Headers/SpecialAbilty_Headers/FireArrows.h"
#include "StaticObjects_Headers/SpecialAbilty_Headers/FastMoving.h"
#include "StaticObjects_Headers/SpecialAbilty_Headers/JumpBoost.h"
#include "StaticObjects_Headers/ExtraLife.h"
#include "StaticObjects_Headers/Spike.h"
#include "StaticObjects_Headers/Decoration.h"


//---------------------------- Constarctor -------------------------------
// Calls function to load and set all the objects of the game and their
// locations whithin the wold.
// Also, sets the size, position, and texture of the background.
//------------------------------------------------------------------------
Board::Board(GameScreen* controller)
	: m_background({ WINDOW_WIDTH,WINDOW_HEIGHT })
{
	m_controller = controller;

	m_background.setPosition(0, 0);
	m_background.setTexture(Resources::instance().
		getWindowObjectTexture(Resources::STAGE1_BACKGROUND));
	m_background.setSize({ WINDOW_WIDTH*1.5,WINDOW_HEIGHT*1.5 });

	setTextData();
}


//----------------------------- load_map ---------------------------------
// Load the map file according the name file given.
//------------------------------------------------------------------------
void Board::load_map(const int stageNum)
{
	m_goldCounter = 0;
	m_keyCounter = 0;
	std::string mapName;

	this->m_stageNum = stageNum;

	m_currentStage.clear();

	m_staticObjects.clear();

	switch (m_stageNum)
	{
	case STAGE_ONE:
		mapName = "stage1.txt";
		break;
	case STAGE_TWO:
		mapName = "stage2.txt";
		break;
	case STAGE_THREE:
		mapName = "stage3.txt";
		break;
	default:
		break;
	}

	std::ifstream m_stage(mapName);

	std::string fileLine;

	if (!(m_stage.is_open())) 
	{
		throw std::iostream::failure("File: " +
			mapName + "doesnt exist");
	}

	while (!m_stage.eof())
	{
		std::getline(m_stage, fileLine);
		m_currentStage.push_back(fileLine);
	}

	m_stage.close();

	setBoardObjects();
}


//---------------------------- setTextData -------------------------------
// Sets the text data.
//------------------------------------------------------------------------
void Board::setTextData()
{
	m_doorRequiredKeys.setFont(*Resources::instance().getArialfont());

	m_doorRequiredKeys.setCharacterSize(10);

	m_doorRequiredKeys.setString("Keys 0/0");

	m_doorRequiredKeys.setColor(sf::Color::White);

	m_doorRequiredKeys.setStyle(sf::Text::Bold | sf::Text::Underlined);

	m_doorRequiredKeys.setOrigin(m_doorRequiredKeys.
		getLocalBounds().width / 2,
		m_doorRequiredKeys.getLocalBounds().height / 2);
}


//---------------------------- setBoardObjects ---------------------------
// Store the Objects from the file to the relvents vectors whom stores
// the MoveObject and StaticObject
//------------------------------------------------------------------------
void Board::setBoardObjects()
{
	for (auto i = 0; i < m_currentStage.size(); i++)
	{
		for (auto j = 0; j < m_currentStage[i].size(); j++)
		{
			setObjectByIcon(m_currentStage[i][j], sf::Vector2f(j + 1.f, i));
		}
	}
}


//------------------------------ draw ------------------------------------
// Draws the static objects of the board upon the window.
// Runs over the static objects in the game and draws them upon the windw.
//------------------------------------------------------------------------
void Board::draw(sf::RenderWindow& window,sf::Time& deltaTime)
{
	for (auto i = m_staticObjects.begin(); i < m_staticObjects.end(); i++)
	{
		(*i)->update(deltaTime);
		(*i)->draw(window);
	}
	
	window.draw(m_doorRequiredKeys);
}


//-------------------------- setDoorKeyString ----------------------------
// Sets the doors key string. desplays how many keys have been collcted.
// The information is displayed follows: (number of key collcted) / (number
// of keys needed to open the door).
//------------------------------------------------------------------------
void  Board::setDoorKeyString(const int keyCollected)
{
	m_doorRequiredKeys.setString(std::to_string(keyCollected) +
		"/" + std::to_string(m_keyCounter));
}


//--------------------------- getStaticObjBegIt --------------------------
// Returns iterator to the begining of the vector that holds all the static
// objects of the game.
//------------------------------------------------------------------------
std::vector<std::unique_ptr<StaticObject>>::iterator Board::getStaticObjBegIt()
{
	return m_staticObjects.begin();
}


//--------------------------- getStaticObjEndIt --------------------------
// Returns iterator to the end of the vector that holds all the static
// objects of the game.
//------------------------------------------------------------------------
std::vector<std::unique_ptr<StaticObject>>::iterator Board::getStaticObjEndIt()
{
	return m_staticObjects.end();
}


//------------------------- clearStaticObjects ---------------------------
// Clears static objects from the vector that hold all the static objects
// of the game.
//------------------------------------------------------------------------
void Board::clearStaticObjects()
{	
	for (auto i = m_staticObjects.begin(); i != m_staticObjects.end(); i++)
	{
		if (i->get()->getDisapperStatus())
		{
			m_staticObjects.erase(i);	
			break;
		}
	}
}


//---------------------------- getGoldCounter ----------------------------
// Returns the number of gold existed
//------------------------------------------------------------------------
const int Board::getGoldCounter() const
{
	return m_goldCounter;
}


//--------------------------- getKeysCounter -----------------------------
// Returns the number of keys collected.
//------------------------------------------------------------------------
const int Board::getKeysCounter() const
{
	return m_keyCounter;
}


//------------------------------ reloadStage -----------------------------
//Reload the current stage data and objects.
//------------------------------------------------------------------------
void Board::reloadStage()
{
	m_goldCounter = 0;
	m_keyCounter = 0;
	m_staticObjects.clear();
	setBoardObjects();
}


//---------------------------- setObjectByIcon ---------------------------
// check the given icon and put the object accordingly:
// Put an object of type StaticObject into 
// vector of StaticObject that stored in Board.
// Put an object of type MoveObject into vector 
// of MoveObject that stord in Controller
// through access funtion.
//------------------------------------------------------------------------
void Board::setObjectByIcon(const char icon, sf::Vector2f pos)
{

	sf::Vector2f position = { pos.x * BLOCK_SIZE, pos.y * BLOCK_SIZE };
	switch (icon)
	{
	case PLAYER:
		m_controller->setPlayerObject(sf::Vector2f
		(pos.x * BLOCK_SIZE,pos.y * (BLOCK_SIZE)));
		break;

	case BEAR:
		m_controller->setBearObject
		(sf::Vector2f(pos.x * BLOCK_SIZE, pos.y * (BLOCK_SIZE)));
		break;

	case WOLF:
		m_controller->setWolfObject(sf::Vector2f
		(pos.x * BLOCK_SIZE, pos.y * (BLOCK_SIZE)+float(BLOCK_SIZE * 0.1)));
		break;

	case CROW:
		m_controller->setCrowObject(sf::Vector2f{ position });
		break;

	case BOX:
		m_controller->setBoxObejct(sf::Vector2f{ position });
		break;

	case HURRICANE:
		setStaticObject<Hurricane>(sf::Vector2f{ position });
		break;

	case DOOR:
		setStaticObject<Door>(sf::Vector2f
			{ position.x,position.y - BLOCK_SIZE*0.25f });
		m_doorRequiredKeys.setPosition(position.x + 0.4f * BLOCK_SIZE,
			position.y - BLOCK_SIZE * 1.2f);
		break;

	case FLOOR:
	case FLOOR_EDGE_LEFT:
	case FLOOR_EDGE_RIGHT:

	case WALL:
		setStaticObject<Block>(sf::Vector2f{position}, icon, m_stageNum);
		break;

	case KEY:
		m_keyCounter++;
		setStaticObject<Key>(sf::Vector2f{ position });
		break;

	case GOLD:
		setStaticObject<Gold>(sf::Vector2f{ position });
		m_goldCounter++;
		break;

	case LIFE:
		setStaticObject<ExtraLife>(sf::Vector2f{ position });
		break;

	case FIRE_ARROWS:
		setStaticObject<FireArrows>(sf::Vector2f{ position });
		break;

	case SPEED_BOOST:
		setStaticObject<FastMoving>(sf::Vector2f{ position });
		break;

	case JUMP_BOOST:
		setStaticObject<JumpBoost>(sf::Vector2f{ position });
		break;

	case SPIKE:
		setStaticObject<Spike>(sf::Vector2f{ position });
		break;
	case STAGE1_TREE:
	case STAGE1_LOG:
	case STAGE2_CRYSTAL1:
	case STAGE2_CRYSTAL2:
	case STAGE3_TREE:
	case STAGE3_BUSH:
		setStaticObject<Decoration>(sf::Vector2f{ position },
			icon, m_stageNum);
		break;
	}
}