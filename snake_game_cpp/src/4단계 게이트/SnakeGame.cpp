#include "SnakeGame.h"
#include <unistd.h>
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

SnakeGame::SnakeGame()
{
	snake_map = new SnakeMap(1);
	snake_map->setCurrentMap(0);
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


	del = 100000;
	bool bEatsFruit = 0;
	bool bEatsPoison = 0;
	direction = 'l';
	srand(time(NULL));
	InitGameWindow();
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
	
	


	refresh();	
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
	return; 
}

void SnakeGame::DrawWindow()
{	
	for (int i = 0; i < maxheight; i++)
	{
		for (int j = 0; j < maxwidth; j++)
		{
			move(i, j);
      if(map[i][j] == 1 || map[i][j]==2) 
			{
				move(i,j);
				addch(edgechar);
			}
			else
			{
        move(i,j);
        addch(' ');
      }
		}
	}
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
	addch(Growthchar);
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
	addch(poisonchar);
	refresh();

}

bool SnakeGame::FatalCollision()
{
	if (snake[0].x == 0 || snake[0].x == maxwidth-1 || snake[0].y == 0 || snake[0].y == maxheight-2)
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


	if (!bEatsFruit)
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
	{ snake.insert(snake.begin(), CharPosition(snake[0].x-1, snake[0].y)); } 
	else if (direction == 'r')
	{ snake.insert(snake.begin(), CharPosition(snake[0].x+1, snake[0].y)); }
	else if (direction == 'u')
	{ snake.insert(snake.begin(), CharPosition(snake[0].x, snake[0].y-1)); }
	else if (direction == 'd')
	{ snake.insert(snake.begin(), CharPosition(snake[0].x, snake[0].y+1)); }


	

	move(snake[0].y, snake[0].x);
	addch(partchar); 
	refresh();
	return;
}

//아래 코드 추가
void SnakeGame::makeGate1()
{
	cou4 =cou;

	
	while(1)
	{
		int gatex = (rand()%maxwidth)+1; 
		int gatey = (rand()%maxheight)+1;
		if (gatex == 60 || gatey == 30)
		{
			continue;
		}
		if (gate2.x == gatex && gate2.y ==gatey)
		{
			continue;
		}
		if (gatex >= maxwidth-2 || gatey >= maxheight-3)
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
		


		int gatex = (rand()%maxwidth)+1; 
		int gatey = (rand()%maxheight)+1;
		if (gatex == 60 || gatey == 30)
		{
			continue;
		}
		if (gate1.x == gatex && gate1.y ==gatey)
		{
			continue;
		}
		if (gatex >= maxwidth-2 || gatey >= maxheight-3)
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
		checkDirection(temphead); // 가능한 방향 찾기 후 방향설정 , 해당 방향으로 이동 구현
		if (direction == 'l')
			{ snake.insert(snake.begin(), CharPosition(temphead.x-1, temphead.y)); } 
		else if (direction == 'r')
			{ snake.insert(snake.begin(), CharPosition(temphead.x+1, temphead.y)); }
		else if (direction == 'u')
			{ snake.insert(snake.begin(), CharPosition(temphead.x, temphead.y-1)); }
		else if (direction == 'd')
			{ snake.insert(snake.begin(), CharPosition(temphead.x, temphead.y+1)); }

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
		checkDirection(temphead); // 가능한 방향 찾기 후 방향설정

		if (direction == 'l')
	
			{ snake.insert(snake.begin(), CharPosition(temphead.x-1, temphead.y)); } 
		else if (direction == 'r')
			{ snake.insert(snake.begin(), CharPosition(temphead.x+1, temphead.y)); }
		else if (direction == 'u')
			{ snake.insert(snake.begin(), CharPosition(temphead.x, temphead.y-1)); }
		else if (direction == 'd')
			{ snake.insert(snake.begin(), CharPosition(temphead.x, temphead.y+1)); }

		finish.x = snake[0].x;
		finish.y = snake[0].y;

	move(snake[snake.size()-1].y, snake[snake.size()-1].x); 
	printw(" ");
	refresh();
	snake.pop_back(); 

	}

}




void SnakeGame::PlayGame()
{	makeGate1();
	makeGate2();
    while(1)
    {		
				if(cou == cou2+20)
				{
					move(Growth.y, Growth.x); 
					addch(' ');
					PositionGrowth();
				}
				if(cou == cou3+20)
				{
					move(poison.y, poison.x); 
					addch(' ');
					PositionPoison();
				}

				if (cou == cou4+100  && !isPassing)
				{	
					move(gate1.y,gate1.x);
					addch(edgechar);
					makeGate1();
				
					move(gate2.y,gate2.x);
					addch(edgechar);
					makeGate2();
				}
				if (isPassed  && !isPassing) //테스트 필요
				{	isPassed = false;
					move(gate1.y,gate1.x);
					addch(edgechar);
					makeGate1();
				
					move(gate2.y,gate2.x);
					addch(edgechar);
					makeGate2();
					
				}

				if(snake[snake.size()-1].x == finish.x && snake[snake.size()-1].y ==finish.y)
				{
					
					isPassing=false;
					isPassed=true;
					
				}

		passing(); //이동확인필요	

        if (FatalCollision())
        {
            move((maxheight-2)/2,(maxwidth-8)/2);
            printw("GAME OVER");
            break;
        }
		
        GetsGrowth();
		GetsPoison();

		
		
        MoveSnake();
	
        if (direction=='q') 
        {
        	break;
        }

        usleep(del);
				cou += 1;
				
    }
}



