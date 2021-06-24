//-------------------------- Include section  ----------------------------
#include <iostream>
#include "Controller.h"
#include "Macros.h"
#include "CollisionHandling.h"
#include "Resources.h"

// Screens
#include "Screens_Headers/MenuScreen.h"
#include "Screens_Headers/InstructionScreen.h"
#include "Screens_Headers/LodingScreen.h"
#include "Screens_Headers/EndGameScreen.h"
#include "Screens_Headers/GameScreen.h"
#include "Screens_Headers/OptionsScreen.h"

// MoveObjects
#include "MoveObjects_Headers/StoneArrow.h"
#include "MoveObjects_Headers/FireArrow.h"


//----------------------------- Constractor ------------------------------
// intilizes the screens of the game and sets the fps limit to 60.
//------------------------------------------------------------------------
Controller::Controller()
    : m_window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), GAME_TITLE),
    m_screens(MAX_SCREENS)
{
    intilizeScreens();

    // sets fps limit to 60.
    m_window.setFramerateLimit(FPS_LIMIT);       
}


//--------------------------------- run ----------------------------------
// The main loop that turn on the game.
//------------------------------------------------------------------------
void Controller::run() try
{
    
    while (m_window.isOpen())
    { 
        m_window.clear();

        switchScreens(toSwitchScreen, currentScreen);

        if (currentScreen<MAX_SCREENS) 
        {
            m_screens[currentScreen]->draw(m_window);

            m_screens[currentScreen]->screenRun(m_window,
                toSwitchScreen, currentScreen);
        }

        m_window.display();
    }
}
catch (const std::exception& e) {
   std::cout << e.what();
}


//------------------------ addCollectedStageGems -------------------------
// Increases the number of collcted gems. 
//------------------------------------------------------------------------
void Controller::addCollectedStageGems(const int collectedGems)
{
    overallScore += collectedGems;
}


//------------------------ addExistedStageGems ---------------------------
// Increases the number of gems exsit. 
//------------------------------------------------------------------------
void Controller::addExistedStageGems(const int gems)
{
    amountOfGemsExisted += gems;
}


//------------------------- addPlayerLostCount ---------------------------
// Increases by 1 the number of the times that the player has lost. 
//------------------------------------------------------------------------
void Controller::addPlayerLostCount()
{
    playerLostCounter++;
}


//--------------------------- switchScreens ------------------------------
// Swiches between the diffrent screen hold in this game.
//------------------------------------------------------------------------
void Controller::switchScreens(bool& switchScreen, int& wantedScreen)
{
    if (switchScreen)
    {
        m_window.setView(m_window.getDefaultView());

        m_screens[wantedScreen]->intialScreenSet();

        if (wantedScreen == WIN) 
        {
            std::string 
                score(std::to_string(overallScore) + "/" +
                    std::to_string(amountOfGemsExisted)),
                lifesLosts(std::to_string(playerLostCounter));

            static_cast<EndGameScreen*>(m_screens[wantedScreen].
                get())->setEndGameData(score,lifesLosts);

            overallScore = 0;
            amountOfGemsExisted = 0;
            playerLostCounter = 0;

        }
        if (wantedScreen == EXIT)
            exit(EXIT_SUCCESS);
            
        switchScreen = false;
    }
}


//------------------------------ reloadMap -------------------------------
// Reloads the current level.
//------------------------------------------------------------------------
void Controller::intilizeScreens()
{
    m_screens[MENU] = (std::make_unique<MenuScreen>());
    m_screens[HELP] = (std::make_unique<InstructionScreen>());
    m_screens[LOADING] = (std::make_unique<LoadingScreen>());
    m_screens[OPTIONS] = (std::make_unique<OptionsScreen>());
    m_screens[WIN] = (std::make_unique<EndGameScreen>());
    m_screens[GAME] = (std::make_unique<GameScreen>(m_window, this));
}



