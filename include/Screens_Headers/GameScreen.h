#pragma once

//-------------------------- Include section  ----------------------------
#include <iostream>
#include "Controller.h"
#include "Macros.h"
#include "CollisionHandling.h"
#include "Resources.h"
#include "Screens_Headers/MenuScreen.h"
#include "Screens_Headers/InstructionScreen.h"
#include "Screens_Headers/LodingScreen.h"
#include "Screens_Headers/EndGameScreen.h"
#include "MoveObjects_Headers/StoneArrow.h"
#include "MoveObjects_Headers/FireArrow.h"
#include "MoveObjects_Headers/Box.h"
#include "ScreenBase.h"


//-------------------------- Class GameScreen  ---------------------------
class GameScreen: public ScreenBase
{
public:
	
	// C-tor
	GameScreen(sf::RenderWindow&, Controller*);
	
	// D-tor
	virtual ~GameScreen() = default;

	// Intial req
	virtual void intialScreenSet() override;

	virtual void screenRun(sf::RenderWindow&,
		bool&, int&) override;

	// Draw
	virtual void draw(sf::RenderWindow&) override;

	void setBearObject(const sf::Vector2f&);

	void setCrowObject(const sf::Vector2f&);

	void setWolfObject(const sf::Vector2f&);

	void setPlayerObject(const sf::Vector2f&);

	void setBoxObejct(const sf::Vector2f&);

	void handleKeyPressed(const sf::Keyboard::Key&);

	void handleKeyReleased(const sf::Keyboard::Key&);

	void setStageBackground();

	void setStageSoundTrack();

protected:

	// Handle user hover mouse above buttons.
	virtual void handleHover(const  sf::Vector2f&,
		sf::RenderWindow&) override;

	// Handle user hover mouse above buttons.
	virtual void handleClick(const  sf::Vector2f&,
		bool&, int&) override;

private:

	void runGame();

	void onComplatedStage(bool&, int&);

	void draw(sf::Time&);

	void updateStatsToViewPosition();

	void drawGameStats(sf::Time&);

	void setTextData(sf::Text&, const int, const sf::Vector2f&,
		const std::string&, const int);

	void setTextData();

	void controlPlayer(const float&);

	void setPlayerData(const float&);

	void handlePlayerEvents();

	void controlMoveObjects(const float&);

	void setEnemyData(MoveObject*, const float&);

	void enemyHandleEvents(MoveObject* e);

	void updateTextInfo();

	void reloadMap();

	void setStage();

	void setIcons();

	void handlePlayerLost();

	void setSecondStageView(float );

	void setView();

	void deleteMoveObject();

	void moveEnemy(MoveObject*, const float&);

	void moveBox(MoveObject*);

	const bool allowMovment() const;

	void moveArrow(MoveObject*);

	void handleGameMovment(const float);

	void handlePausedGame();

	void handleGameOver();

	void setCurrentStageView(const float);

	void playerPreformShoot();

	int currentStage = STAGE_ONE,
		currentScreen = MENU;

	float stageTwoLoadTime = STAGE_TWO_LOAD_TIME;

	bool pauseGame = false;

	sf::RenderWindow* m_window;

	sf::View m_view;
	
	Controller* m_controller;

	Board m_world;

	// Static object used in the game.
	std::vector<std::unique_ptr<MoveObject>> m_moveObjects;

	Player* m_player = nullptr;

	sf::Clock gameMovementClock, animationTime;

	sf::RectangleShape
		playerIcon, scoreIcon, specailAbilityIcon,
		m_stageBackground, m_animatedBackground;

	sf::Text scoreGemsTxt, currentAbilityTxt,
		stageTwoStartText, pauseText;

	Animation m_scoreIconAnimation, m_stage2BackgroundAnim;
	
	bool toSwitchScreen = false,
		playerLost = false,
		stageTwoIntialWait = false;

	GameOverPopUp gameOverPopUp;
};