#pragma once

//-------------------------- Include section  ----------------------------
#include "SFML/Graphics.hpp"


//------------------------- class EventClock  ----------------------------
class EventClock
{
public:

	// c-tor
	EventClock(const float);

	// d-tor
	virtual ~EventClock() = default;

	bool delayTimePassed();

private:

	bool firstTime = true;
	const float m_eventDelay;
	sf::Clock m_eventClock;
};