//-------------------------- Include section  ----------------------------
#include "Screens_Headers/ScreenBase.h"


//--------------------------- screenRun ----------------------------------
// Manages the screens of the game.
// The main loop is listening for events and handles them accordingly. 
//------------------------------------------------------------------------
void ScreenBase::screenRun(sf::RenderWindow& window,
    bool& toSwitchScreen, int& currentScreen)
{
    if (auto event = sf::Event{}; window.pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            window.close();
            break;

        case sf::Event::MouseButtonReleased:
            this->handleClick(window.mapPixelToCoords
            (sf::Mouse::getPosition(window)),
                toSwitchScreen, currentScreen);
            break;

        case sf::Event::MouseMoved:
            this->handleHover(window.mapPixelToCoords
            (sf::Mouse::getPosition(window)), window);
            break;
        }
    }
}
