#ifndef LEVEL_H
#define LEVEL_H

#include "comet.h"
#include "convert.h"
#include "player.h"
#include "gamescreen.h"
#include "Entity.h"
#include <SDL_ttf.h>
#include <vector>
#include <fstream>
#include <sstream>

class Level : public IGameScreen {
public:
	Level(int levelNum);
	~Level();
	void Logic();
	void Handle_Events();
	void Draw();
	bool Load_Level();
protected:
	static int lineOffset;
	TTF_Font* f_HUD;
	SDL_Rect r_Formation;
	SDL_Surface* s_Background, *s_Score, *s_Lives;
	Entity* player, *comet/*, *ships*/;
	static const int ROWS=9, COLUMNS=6;
	int tileType, curr_x, curr_y, totalAlive, currLevel;
	std::vector<Entity*> enemyVec;	
	std::ifstream fl_currLevel;
	std::string line;
	std::stringstream ss;
};

#endif