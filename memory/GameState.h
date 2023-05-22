#include "GameMode.h"
#include "CardValue.h"

#ifndef _GAMESTATE_H_
#define _GAMESTATE_H_

struct GameState {
	GameMode mode;
	Level level;
	int picks;
	int score;
	CardValue last_pick;
	int last_pick_index;
};

#endif