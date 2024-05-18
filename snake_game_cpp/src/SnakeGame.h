
#include <iostream>
#include <vector>
#include <ncurses.h>
#include <cstdlib>
#include <ctime>
#include "SnakeMap.h"
#ifndef SNAKEGAME_H
#define SNAKEGAME_H


struct CharPosition 
{
	int x, y;
	CharPosition(int col, int row);
	CharPosition();
};

class SnakeGame
{
private:
  SnakeMap* snake_map;
	int cou, cou2, cou3, del, maxwidth, maxheight;
	char direction, partchar, edgechar, Growthchar, poisonchar;
	bool bEatsFruit, bEatsPoison;
	CharPosition Growth; 
	CharPosition poison;
	std::vector<CharPosition> snake;
	std::vector<std::vector<int> > map;
	void InitGameWindow();
	void DrawWindow();  
	void DrawSnake();
	void PositionGrowth();
	void PositionPoison();
	bool FatalCollision();
	void MoveSnake();
	bool GetsGrowth();
	bool GetsPoison();

public:
	SnakeGame();
	~SnakeGame();
	void PlayGame();
};

#endif