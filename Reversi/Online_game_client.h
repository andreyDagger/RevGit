#pragma once

#include <iostream>

#include "Online_game.h"

using namespace std;

class Online_game_client : public Online_game {
public:
	virtual string start_game();
};