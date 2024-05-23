#include "SnakeGame.h"
#include <unistd.h>
#include <ncurses.h>
#include <vector>


using namespace std;


CharPosition::CharPosition(int col, int row)
{
	x = col;
	y = row;
}

CharPosition::CharPosition()
{
	x = 0;
	y = 0;
}

SnakeGame::SnakeGame() :currentStage(0){
	snake_map = new SnakeMap(1);
	
	InitStage();

	
	


}

SnakeGame::~SnakeGame()
{
	nodelay(stdscr, false);
	getch();
	endwin();
}

void SnakeGame::InitGameWindow() 
{ 	//시작시 time
	initscr(); 
	nodelay(stdscr,TRUE);
	keypad(stdscr, true); 
	noecho(); 
	curs_set(0); 
	maxheight = 30;
	maxwidth = 60;
	


	//아래는 5단계 추가내용임.
	


	return; 
}








void SnakeGame::DrawWindow()
{	

	initscr();
	start_color();
	init_pair(2,COLOR_GREEN,COLOR_GREEN);
	for (int i = 0; i < maxheight; i++)
	{
		for (int j = 0; j < maxwidth; j++)
		{
			move(i, j);
      if(map[i][j] == 1 || map[i][j]==2) 
			{
				move(i,j);
				attron(COLOR_PAIR(2));
				addch(' ');
				attroff(COLOR_PAIR(2));
			}
			else
			{
        move(i,j);
        addch(' ');
      }
		}
	}
	
	refresh();



	return;
}

void SnakeGame::DrawSnake()
{
	
	for (int i = 0; i < 5; i++) 
	{
		snake.push_back(CharPosition(30+i, 10));
	}

	for (int i = 0; i < snake.size(); i++)
	{
		move(snake[i].y, snake[i].x);
		addch(partchar);
	}
	return;
}


void SnakeGame::PositionGrowth()
{
	cou2 = cou;
	while(1)
	{
		int tmpx = (rand()%maxwidth)+1; 
		int tmpy = (rand()%maxheight)+1;
		if (tmpx == 60 || tmpy == 30)
		{
			continue;
		}

		for (int i = 0; i < snake.size(); i++)
		{
			if (snake[i].x == tmpx && snake[i].y == tmpy)
			{
				continue; 
			}
		}
		if (tmpx == poison.x && tmpy == poison.y)
		{
			continue;
		}
		if (map[tmpy][tmpx] == 1 || map[tmpy][tmpx] == 2)
		{
			continue;
		}
		if (tmpx >= maxwidth-2 || tmpy >= maxheight-3)
		{
			continue; 
		}

		
		Growth.x = tmpx;
		Growth.y = tmpy;
	
		break;
	}

	move(Growth.y, Growth.x); 
	initscr();
	start_color();
	init_pair(3,COLOR_BLUE,COLOR_BLACK);
	attron(COLOR_PAIR(3));
	addch(Growthchar);
	attroff(COLOR_PAIR(3));

	refresh();


}

void SnakeGame::PositionPoison()
{
	cou3 = cou;
	while(1)
	{
		int tmpx = (rand()%maxwidth)+1; 
		int tmpy = (rand()%maxheight)+1;
		if (tmpx == 60 || tmpy == 30)
		{
			continue;
		}
		for (int i = 0; i < snake.size(); i++)
		{
			if (snake[i].x == tmpx && snake[i].y == tmpy)
			{
				continue;
			}
		}
		if (tmpx == Growth.x && tmpy == Growth.y)
		{
			continue;
		}
		if (map[tmpy][tmpx] == 1 || map[tmpy][tmpx] ==2)
		{
			continue;
		}
		if (tmpx >= maxwidth-2 || tmpy >= maxheight-3)
		{
			continue; 
		}

	
		poison.x = tmpx;
		poison.y = tmpy;
		break;
	}
	move(poison.y, poison.x); 
	initscr();
	start_color();
	init_pair(4,COLOR_RED,COLOR_BLACK);
	attron(COLOR_PAIR(4));
	addch(poisonchar);
	attroff(COLOR_PAIR(4));
	refresh();
	
}

bool SnakeGame::FatalCollision()
{
	if (snake[0].x == 0 || snake[0].x == maxwidth || snake[0].y == 0 || snake[0].y == maxheight)
	{
		return true;
	}
	if(map[snake[0].y][snake[0].x] == 1 || map[snake[0].y][snake[0].x]==2)
	{
		if (snake[0].x == temphead.x && snake[0].y ==temphead.y)
			{
				return false;
			}
		else{
			return true;
		}
	}
	if (snake.size() == 2)
	{
		return true;
	}
	for (int i = 2; i < snake.size(); i++)
	{
		if (snake[0].x == snake[i].x && snake[0].y == snake[i].y)
		{
			return true;
		}
	}

	return false;
}

bool SnakeGame::GetsGrowth()
{
	if (snake[0].x == Growth.x && snake[0].y == Growth.y)
	{
		PositionGrowth(); 
		growthN++;
		return bEatsFruit = true;
	}
	else 
	{
		return bEatsFruit = false;
	}
	return bEatsFruit;
}

bool SnakeGame::GetsPoison()
{
	if (snake[0].x == poison.x && snake[0].y == poison.y)
	{
		PositionPoison(); 
		poisonN++;
		return bEatsPoison = true;
	}
	else 
	{
		return bEatsPoison = false;
	}
	return bEatsPoison;
}


void SnakeGame::MoveSnake()
{	

	int KeyPressed = getch();
	switch(KeyPressed)
	{
		case KEY_LEFT:
			direction = 'l'; 
			break;
		case KEY_RIGHT:
			direction = 'r';
			break;
		case KEY_UP:
			direction = 'u';
			break;
		case KEY_DOWN:
			direction = 'd';
			break;
		case KEY_BACKSPACE:
			direction = 'q'; 
			break;
	}


	if (!bEatsFruit || snake.size() >10) // snake size 10으로 설정
	{
		move(snake[snake.size()-1].y, snake[snake.size()-1].x); 
		printw(" ");
		refresh();
		snake.pop_back(); 
	}
	if (bEatsPoison)
	{
		move(snake[snake.size()-1].y, snake[snake.size()-1].x); 
		printw(" "); 
		refresh();
		snake.pop_back(); 
	}

	if (direction == 'l')
	{
		snake.insert(snake.begin(), CharPosition(snake[0].x-1, snake[0].y)); 
		move(snake[0].y, snake[0].x);
		addch('<'); 
		refresh();

	} 
	else if (direction == 'r')
	{ 
		snake.insert(snake.begin(), CharPosition(snake[0].x+1, snake[0].y)); 		
		move(snake[0].y, snake[0].x);
		addch('>'); 
		refresh();		
	}
	else if (direction == 'u')
	{
		snake.insert(snake.begin(), CharPosition(snake[0].x, snake[0].y-1)); 
		move(snake[0].y, snake[0].x);
		addch('^'); 
		refresh();	
	}
	else if (direction == 'd')
	{ 
		snake.insert(snake.begin(), CharPosition(snake[0].x, snake[0].y+1)); 
		
		move(snake[0].y, snake[0].x);
		addch('v'); 
		refresh();		
	}
		for (int i = 1; i<snake.size();i++){
		move(snake[i].y, snake[i].x);
		addch(partchar); 
		refresh();
	}


	

	return;
}

void SnakeGame::boardUpdate()
{
	bodylen = snake.size();
	mvprintw(0, 60, "*-*-*-*-*-*-SCORE-BOARD*-*-*-*-*-*-*-*");
	mvprintw(1,60,"|");mvprintw(1,97,"|");
	mvprintw(2,60,"|");mvprintw(2,97,"|");
	mvprintw(3,60,"|");mvprintw(3,63, "B : "); mvprintw(3,67,"%d", bodylen); mvprintw(3,68," / 10");  ;  mvprintw(3,97,"|");
	mvprintw(4,60,"|");mvprintw(4,97,"|");
	mvprintw(5,60,"|");mvprintw(5,63, "+ : "); mvprintw(5,67,"%d", growthN);mvprintw(5,97,"|");
	mvprintw(6,60,"|");mvprintw(6,97,"|");
	mvprintw(7,60,"|");mvprintw(7,63, "- : "); mvprintw(7,67,"%d", poisonN);mvprintw(7,97,"|");
	mvprintw(8,60,"|");mvprintw(8,97,"|");
	mvprintw(9,60,"|");mvprintw(9,63, "GATE : "); mvprintw(9,70,"%d", gateN);mvprintw(9,97,"|");
	mvprintw(10,60,"|");mvprintw(10,97,"|");
	mvprintw(11,60,"|");mvprintw(11,97,"|");
	mvprintw(12,60,"|");mvprintw(12,97,"|");
	mvprintw(13,60,"|");mvprintw(13,97,"|");
	mvprintw(14,60,"|");mvprintw(14,97,"|");
	mvprintw(15, 60, "|-*-*-*-*-*-MISSION-BOARD-*-*-*-*-*-*|");
	
	mvprintw(16,60,"|");mvprintw(16,97,"|");
	mvprintw(17,60,"|");mvprintw(17,63, "B : 7 "); mvprintw(17,69,"("); mvprintw(17,71,")"); mvprintw(17,97,"|");
	mvprintw(18,60,"|");mvprintw(18,97,"|");
	mvprintw(19,60,"|");mvprintw(19,63, "+ : 4 ");mvprintw(19,69,"("); mvprintw(19,71,")");mvprintw(19,97,"|");
	mvprintw(20,60,"|");mvprintw(20,97,"|");
	mvprintw(21,60,"|");mvprintw(21,63, "- : 2 "); mvprintw(21,69,"("); mvprintw(21,71,")");mvprintw(21,97,"|");
	mvprintw(22,60,"|");mvprintw(22,97,"|");
	mvprintw(23,60,"|");mvprintw(23,63, "GATE : 3 "); mvprintw(23,72,"("); mvprintw(23,74,")");mvprintw(23,97,"|");
	mvprintw(24,60,"|");mvprintw(24,97,"|");
	mvprintw(25,60,"|");mvprintw(25,97,"|");
	mvprintw(26,60,"|");mvprintw(26,97,"|");
	mvprintw(27,60,"|");mvprintw(27,97,"|");
	mvprintw(28,60,"|");mvprintw(28,97,"|");
	mvprintw(29,60,"*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-");
	refresh();
	if(bodylen>=7){
		mvprintw(17,70,"v");
		bodylenMissionClear=true;
	}else{
		mvprintw(17,70," ");
		bodylenMissionClear=false;
	}
	if(growthN >= 4){
		mvprintw(19,70,"v");
		growthMissionClear=true;
	}else{
		mvprintw(19,70," ");
		growthMissionClear=false;
	}
	if(poisonN>=2){
		mvprintw(21,70,"v");
		poisonMissionClear=true;
	}else{
		mvprintw(21,70," ");
		poisonMissionClear=false;
	}
	if(gateN>=3){
		mvprintw(23,73,"v");
		gateMissionClear=true;
	}else{
		mvprintw(23,73," ");
		growthMissionClear=false;
	}


}
void SnakeGame::InitStage() {
    // 맵 초기화
    snake_map->setCurrentMap(currentStage);
    map = snake_map->getCurrentMap();
    
    cou = 0;
	cou2 = 999999999;
	cou3 = 999999999;
	cou4 = 999999999;
	

	partchar = 'O'; 
	edgechar = (char)219;
	
	Growthchar = 'G';
	poisonchar = 'P';
	gatechar = '@'; //gatechar 추가

	Growth.x = 0;
	Growth.y = 0;
	poison.x = 1;
	poison.y = 1;


	temphead.x=1; //게이트 이동지점 초기화
	temphead.y=1;

	finish.x=1;
	finish.y=1;
	
	GameWin=false;

	del = 100000;
	bool bEatsFruit = 0;
	bool bEatsPoison = 0;
	direction = 'l';
	srand(time(NULL));
	InitGameWindow();
	
	snake.clear();
	DrawWindow();
	DrawSnake();

	PositionGrowth();
	PositionPoison();

	isPassed = false;
	isPassing = false;


	gate1.x=2;
	gate1.y=1;
	gate2.x = 3;
	gate2.y =1;


	//5단계
	
	poisonN =0;
	gateN=0;
	growthN=0;
	bodylen = 4;
	gateMissionClear=false;
	poisonMissionClear=false;
	growthMissionClear=false;
	bodylenMissionClear=false;

	makeGate1();
	makeGate2();

}

void SnakeGame::NextStage()
{	

	if(bodylenMissionClear && gateMissionClear && poisonMissionClear&&growthMissionClear)
	{	
		if( currentStage==3)
		{
			GameWin=true;
			return;
		}
		currentStage++;
	
		
		
		InitStage();
		
		// 스테이지 이동 구현 및 윈도우 초기화
	}

}



void SnakeGame::makeGate1()
{
	cou4 =cou;

	
	while(1)
	{
		int gatex = (rand()%maxwidth); 
		int gatey = (rand()%maxheight);
		if (gatex == 60 || gatey == 30)
		{
			continue;
		}
		if (gate2.x == gatex && gate2.y ==gatey)
		{
			continue;
		}
		if (gatex >= maxwidth || gatey >= maxheight)
		{
			continue; 
		}
		if (map[gatey][gatex] == 1)
		{

		gate1.x = gatex;
		gate1.y = gatey;
		break;

		}

	
		
	}
	move(gate1.y, gate1.x); 
	addch(gatechar);
	refresh();

}
void SnakeGame::makeGate2()
{
	

	while(1)
		{
		


		int gatex = (rand()%maxwidth); 
		int gatey = (rand()%maxheight);
		if (gatex == 60 || gatey == 30)
		{
			continue;
		}
		if (gate1.x == gatex && gate1.y ==gatey)
		{
			continue;
		}
		if (gatex >= maxwidth || gatey >= maxheight)
		{
			continue; 
		}
		if (map[gatey][gatex] == 1)
		{

		gate2.x = gatex;
		gate2.y = gatey;
		break;

		}

	
		
	}
	move(gate2.y, gate2.x); 
	addch(gatechar);
	refresh();
}




void SnakeGame::checkDirection(CharPosition temphead)
{
	
	if (temphead.x ==0)
	{
		direction='r';
	}
	else if (temphead.x ==59)
	{
		direction='l';
	}
	else if (temphead.y ==0)
	{
		direction='d';
	
	}
	else if (temphead.y ==29)
	{
		direction='u';
	
	}
	else{
		if (direction =='l')
		{
			if (map[temphead.y][temphead.x-1]==0)
			{
				direction='l';
			}
			else if(map[temphead.y-1][temphead.x]==0)
			{
				direction = 'u';
			
			}
			else if (map[temphead.y+1][temphead.x] ==0)
			{
				direction = 'd';
			
			}
			else{
				direction = 'r';
			
			}
		}
		else if (direction == 'r')
		{
			if (map[temphead.y][temphead.x+1]==0)
			{
				direction='r';
			}
			else if(map[temphead.y+1][temphead.x]==0)
			{
				direction='d';
			
			}
			else if(map[temphead.y-1][temphead.x]==0)
			{
				direction='u';
				
			}
			else{
				direction='l';
							
			}
		}
		else if (direction== 'u')
		{
			if (map[temphead.y-1][temphead.x]==0)
			{
				direction='u';
			}
			else if(map[temphead.y][temphead.x+1]==0)
			{
				direction='r';
			
			}
			else if(map[temphead.y][temphead.x-1]==0)
			{
				direction='l';
			
			}
			else{
				direction='d';
						
			}
		}
		
		else if (direction == 'd')
		{
			if (map[temphead.y+1][temphead.x]==0)
			{
				direction='d';
			}
			else if(map[temphead.y][temphead.x-1]==0)
			{
				direction='l';
			
			}
			else if(map[temphead.y][temphead.x+1]==0)
			{
				direction='r';
		
			}
			else{
				direction='u';
							
			}
		}
		


	}

	


}

void SnakeGame::passing()
{	
	if(snake[0].x == gate1.x && snake[0].y == gate1.y)
	{
		isPassing=true;
		temphead.x = gate2.x;
		temphead.y = gate2.y;
		checkDirection(temphead); 
	if (direction == 'l')
	{
		snake.insert(snake.begin(), CharPosition(temphead.x-1, temphead.y)); 
		move(snake[0].y, snake[0].x);
		addch('<'); 
		refresh();

	} 
	else if (direction == 'r')
	{ 
		snake.insert(snake.begin(), CharPosition(temphead.x+1, temphead.y)); 		
		move(snake[0].y, snake[0].x);
		addch('>'); 
		refresh();		
	}
	else if (direction == 'u')
	{
		snake.insert(snake.begin(), CharPosition(temphead.x, temphead.y-1)); 
		move(snake[0].y, snake[0].x);
		addch('^'); 
		refresh();	
	}
	else if (direction == 'd')
	{ 
		snake.insert(snake.begin(), CharPosition(temphead.x, temphead.y+1)); 
		
		move(snake[0].y, snake[0].x);
		addch('v'); 
		refresh();		
	}

		finish.x = snake[0].x;
		finish.y = snake[0].y;

	move(snake[snake.size()-1].y, snake[snake.size()-1].x); 
	printw(" ");
	refresh();
	snake.pop_back(); 
	}

	else if(snake[0].x == gate2.x && snake[0].y == gate2.y)
	{
		isPassing=true;
		
		temphead.x = gate1.x;
		temphead.y = gate1.y;
		checkDirection(temphead); 
	if (direction == 'l')
	{
		snake.insert(snake.begin(), CharPosition(temphead.x-1, temphead.y)); 
		move(snake[0].y, snake[0].x);
		addch('<'); 
		refresh();

	} 
	else if (direction == 'r')
	{ 
		snake.insert(snake.begin(), CharPosition(temphead.x+1, temphead.y)); 		
		move(snake[0].y, snake[0].x);
		addch('>'); 
		refresh();		
	}
	else if (direction == 'u')
	{
		snake.insert(snake.begin(), CharPosition(temphead.x, temphead.y-1)); 
		move(snake[0].y, snake[0].x);
		addch('^'); 
		refresh();	
	}
	else if (direction == 'd')
	{ 
		snake.insert(snake.begin(), CharPosition(temphead.x, temphead.y+1)); 
		
		move(snake[0].y, snake[0].x);
		addch('v'); 
		refresh();		
	}

		finish.x = snake[0].x;
		finish.y = snake[0].y;

	move(snake[snake.size()-1].y, snake[snake.size()-1].x); 
	printw(" ");
	refresh();
	snake.pop_back(); 

	}

}




void SnakeGame::PlayGame()
{	
    while(1)
	{				
	
		if(cou == cou2+50)
				{
					move(Growth.y, Growth.x); 
					addch(' ');
					PositionGrowth();
				}
				if(cou == cou3+50)
				{
					move(poison.y, poison.x); 
					addch(' ');
					PositionPoison();
				}

				if (cou == cou4+100  && !isPassing)
				{	
					move(gate1.y,gate1.x);
					attron(COLOR_PAIR(2));
					addch(' ');
					attroff(COLOR_PAIR(2));
					makeGate1();
				
					move(gate2.y,gate2.x);
					attron(COLOR_PAIR(2));
					addch(' ');
					attroff(COLOR_PAIR(2));
					makeGate2();
				}
				if (isPassed  && !isPassing) 
				{	isPassed = false;
					move(gate1.y,gate1.x);
					attron(COLOR_PAIR(2));
					addch(' ');
					attroff(COLOR_PAIR(2));
					makeGate1();
				
					move(gate2.y,gate2.x);
					attron(COLOR_PAIR(2));
					addch(' ');
					attroff(COLOR_PAIR(2));
					
					makeGate2();
					
				}

				if(snake[snake.size()-1].x == finish.x && snake[snake.size()-1].y ==finish.y)
				{
					
					isPassing=false;
					isPassed=true;
					gateN++;
					
				}

		passing(); 	

        if (FatalCollision())
        {
            initscr();		
			start_color();
			init_pair(1, COLOR_RED, COLOR_WHITE);
			move((maxheight-2)/2,(maxwidth-8)/2);
			attron(COLOR_PAIR(1));
			printw("GAME OVER");
			attroff(COLOR_PAIR(1));
			break;
        }
		if(GameWin)
		{	initscr();
			start_color();
			init_pair(1, COLOR_BLUE, COLOR_YELLOW);
			move((maxheight-2)/2,(maxwidth-8)/2);
			attron(COLOR_PAIR(1));
			printw("!!!!YOU WIN!!!!");
			attroff(COLOR_PAIR(1));
			break;
		}

		
        GetsGrowth();
		GetsPoison();

		boardUpdate();
		
        MoveSnake();
		NextStage();



        if (direction=='q') 
        {
        	break;
        }

        usleep(del);
				cou += 1;
				
    }
}


