
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
	int cou, cou2, cou3,cou4,cou5, del, maxwidth, maxheight;
	char direction, partchar, edgechar, Growthchar, poisonchar, gatechar;
	bool bEatsFruit, bEatsPoison;
	CharPosition Growth; 
	CharPosition poison;
	CharPosition gate1; //gate1 추가
	CharPosition gate2; //gate2 추가
	CharPosition temphead; //게이트 이동 위치
	CharPosition finish ; //마지막 이동지점 위치


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
	void makeGate1();
	void makeGate2();

	bool isPassed ;
	bool isPassing;


	int max_y;
	int max_x;
	void passing();

	void checkDirection(CharPosition temphead);

	

//아래는 5단계 추가내용임.

	void NextStage(); // 미션 성공 시 다음 스테이지 변경
	bool GameWin; // 게임 승리 종료

	void boardUpdate(); // 게임보드 업데이트
	int currentStage;
	void InitStage();


	bool gateMissionClear;
	bool poisonMissionClear;
	bool growthMissionClear;
	bool bodylenMissionClear;

	int poisonN;
	int growthN;
	int gateN;
	int bodylen;



public:
	SnakeGame();
	~SnakeGame();
	void PlayGame();

	//아래는 5단계 추가내용임.

	

};

#endif
