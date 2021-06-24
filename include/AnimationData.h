#pragma once

//-------------------------- Include section  ----------------------------
#include "Operation.h"

#include <SFML/Graphics.hpp>

#include <unordered_map>
#include <vector>


// Data structure of the animations.
struct AnimationData
{ 
    using ListType = std::vector<sf::IntRect>;

    // Data of the IntRect of the animation.
    using DataType = std::unordered_map<Operation, ListType>;

    // Time play of each frame in the animation.
    using TimeData = std::unordered_map<Operation, float>;

    // The frequancy the animation supposed to be played(Once or more).
    using PlayOnceData = std::unordered_map<Operation, bool>;

    DataType m_data;

    TimeData m_time;

    PlayOnceData playOnce;
};
