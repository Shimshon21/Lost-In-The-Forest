#pragma once

//-------------------------- Include section  ----------------------------
#include "SFML/Graphics.hpp"
#include "MoveObjects_Headers/MoveObject.h"
#include "MoveObjects_Headers/Bear.h"
#include "MoveObjects_Headers/Crow.h"
#include "MoveObjects_Headers/Wolf.h"
#include "MoveObjects_Headers/Player.h"
#include "Board.h"
#include "HealthBar.h"
#include "Resources.h"
#include "Screens_Headers/ScreenBase.h"
#include "GameOverPopUp.h"


//-------------------------- class Controller  ---------------------------
class Controller
{
public:

	// c-tor
	Controller();

	// d-tor
	virtual ~Controller() = default;

	void run();

	void addCollectedStageGems(const int);

	void addExistedStageGems(const int);

	void addPlayerLostCount();

private:

	bool toSwitchScreen = false;

	// Each node reprasant the wanted screen to be shown
	// if no screen is 'true' play the game.
	std::vector<std::unique_ptr<ScreenBase>> m_screens;

	int currentScreen = MENU, overallScore = 0,
		amountOfGemsExisted = 0, playerLostCounter = 0;

	void switchScreens(bool&,int& wantedScreen);

	sf::RenderWindow m_window;

	void intilizeScreens();
};