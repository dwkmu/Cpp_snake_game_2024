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
	snake_map = new SnakeMap(0);
	map = snake_map->getCurrentMap();
	cou = 0;
	cou2 = 999999999;
	cou3 = 999999999;
	partchar = 'O'; 
	Growthchar = 'G';
	poisonchar = 'P';
	Growth.x = 0;
	Growth.y = 0;
	poison.x = 1;
	poison.y = 1;
	del = 250000;
	bool bEatsFruit = 0;
	bool bEatsPoison = 0;
	direction = 'l';
	srand(time(NULL));
	InitGameWindow();
	DrawWindow();
	DrawSnake();
	PositionGrowth();
	PositionPoison();

	refresh();	
}

SnakeGame::~SnakeGame()
{
	nodelay(stdscr, false);
	getch();
	endwin();
}

void SnakeGame::InitGameWindow() 
{ 
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
	initscr();
	start_color();
	init_pair(2, COLOR_GREEN, COLOR_GREEN);
	for (int i = 0; i < maxheight; i++)
	{
		for (int j = 0; j < maxwidth; j++)
		{
			move(i, j);
      if(map[i][j] == 1)
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
	return;
}

void SnakeGame::DrawSnake()
{
	
	for (int i = 0; i < 5; i++) 
	{
		snake.push_back(CharPosition(30+i, 15));
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
		if (map[tmpy][tmpx] == 1)
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
	init_pair(3, COLOR_BLUE, COLOR_BLACK);
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
		if (map[tmpy][tmpx] == 1)
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
	init_pair(4, COLOR_RED, COLOR_BLACK);
	attron(COLOR_PAIR(4));
	addch(poisonchar);
	attroff(COLOR_PAIR(4));
	refresh();

}

bool SnakeGame::FatalCollision()
{
	if (snake[0].x == 0 || snake[0].x == maxwidth-1 || snake[0].y == 0 || snake[0].y == maxheight-2)
	{
		return true;
	}
	if(map[snake[0].y][snake[0].x] == 1)
	{
		return true;
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
	}
	for (int i = 1; i<snake.size();i++){
		move(snake[i].y, snake[i].x);
		addch(partchar); 
		refresh();
	}
	return;
}

void SnakeGame::PlayGame()
{
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
