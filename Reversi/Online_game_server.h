#pragma once

#include "Online_game.h"

using namespace std;

class Online_game_server : public Online_game {
public:
	virtual string start_game();
};