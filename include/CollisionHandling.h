#pragma once

//--------------------------- Include section  ---------------------------
#include <map>
#include <string>
#include <typeinfo>
#include <typeindex>
#include "GameObject.h"


// search and activate the suitable function for the current collison.
void processCollision(GameObject&, GameObject&);