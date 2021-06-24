#pragma once
#include "ScreenBase.h"
#include "Animation.h"

class LoadingScreen: public ScreenBase
{
public:

	// c-tor
	LoadingScreen();

	// d-tor
	virtual ~LoadingScreen() = default;

	virtual void intialScreenSet() override;

	virtual void draw(sf::RenderWindow&) override;

	virtual void screenRun(sf::RenderWindow&, bool&, int&) override;

	void setPlayerBackgroundAnimation();

	void setLoadingBarAnimation(int& index);

protected:

	virtual void handleHover(const  sf::Vector2f&, sf::RenderWindow&);

	virtual void handleClick(const  sf::Vector2f&, bool&, int&);

private:

	void setLoadingBar();

	int loadingIndex = 0;

	sf::Clock loadTime,backgroundAnim,loadingBarAnim;

	sf::RectangleShape playerLoading,loadingBar;

	std::vector<sf::RectangleShape> m_loadingBar;

	sf::IntRect loadingRect;

	sf::CircleShape m_background;

	Animation m_playerAnimation;
};