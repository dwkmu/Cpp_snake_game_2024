
#include "SnakeGame.h"

int maxheight, maxwidth;
int IsUserReady();
int AskUserToPlayAgain();
void ClearCentre();
int UserInput();

int main ()
{	
	if (IsUserReady() == 'y') 
	do {
		{
			SnakeGame NewSnake;
			NewSnake.PlayGame();
		}
	}
	while (AskUserToPlayAgain() == 'y');
	return 0;
}

void ClearCentre()
{
	clear(); 
	initscr(); 
	noecho();
	move((11), (25));
}

int UserInput()
{
	int UserInput = getch();
	refresh();
	endwin();
	clear();

	return UserInput;	
}

int IsUserReady() 
{
	ClearCentre();
	printw("GAME START (Y)\n");
	move((12), (27));
	printw("EXIT (N)");
	return UserInput();
}

int AskUserToPlayAgain()
{
	ClearCentre();
	printw("RESTART (Y)\n");
	move((12), (26));
	printw("EXIT (N)");


	return UserInput();
}
