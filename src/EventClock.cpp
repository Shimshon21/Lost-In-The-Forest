
//-------------------------- Include section  ----------------------------
#include "EventClock.h"


// C-tor 
EventClock::EventClock(const float eventDelay) 
	: m_eventDelay(eventDelay)
{}


//--------------------------- delayTimePassed ----------------------------
// Returns if the time has elapsed between events.
//------------------------------------------------------------------------
bool EventClock::delayTimePassed() {

	if (firstTime) {
		firstTime = false;
		m_eventClock.restart();
		return true;
	}

	if (m_eventClock.getElapsedTime().asMilliseconds() >= m_eventDelay) {
		m_eventClock.restart();
		return true;
	}

	return false;
}