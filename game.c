#include<stdio.h>
#include<conio.h>

#include "normal.h"
#include "ultimate.h"

#define CURSUP "\033[A"
#define CURSDN "\033[B"
#define CURSRT "\033[C"
#define CURSLT "\033[D"

void basic_instructions();
void ultimate_instructions();
void align();
/*
Pseudocode:

Begin
	ask which version to play
	get version
	if normal: 
		run normal game
	if ultimate
		run ultimate game
	if quit:
		quit game
*/



int main()
{
	int end_game = 0;
	for (; end_game != 1;)
	{
		system("cls");
		printf("What would you like to do?\n\n");
		printf("- game of basic tic-tac-toe\n");
		printf("- game of ultimate tic-tac-toe\n");
		printf("- basic tic-tac-toe instructions\n");
		printf("- ultimate tic-tac-toe instructions\n");
		printf("- exit");

		for(int i=0; i<4; i++)
			printf(CURSUP);
		printf("\r");
	
	
		end_game = get_position_home_screen();
	}
	


	return 0;
}

int get_position_home_screen()
{
	int menu_item = 1;
	int i=0;

	for (; i != 13;)
	{
		i = get_input();

		if (i == 72)//up
		{
			if ((menu_item) > 1)
			{
				menu_item--;
				printf(CURSUP);
			}
		}
		if (i == 80)//down
		{
			if ((menu_item) < 5)
			{
				menu_item++;
				printf(CURSDN);
			}
		}
		if (i == 77)//right
		{
			if (menu_item < 5)
			{
				menu_item++;
				printf(CURSDN);
			}
		}
		if (i == 75)//left
		{
			if (menu_item > 1)
			{
				menu_item--;
				printf(CURSUP);
			}
		}
	}
	if (i == 13)
	{
		switch (menu_item)
		{
		case 1:
			system("cls");
			normal_game();
			return 0;
			break;
		case 2:
			system("cls");
			ultimate_game();
			return 0;
			break;
		case 3:
			system("cls");
			basic_instructions();
			return 0;
			break;
		case 4:
			system("cls");
			ultimate_instructions();
			return 0;
		default:
			system("cls");
			return 1;
		}
	}
}

void basic_instructions()
{
	
	grid_normal_initializer();
	print_normal_grid();
	for (int i = 0; i < 100; i++)
	{
		printf(CURSUP);
		printf(CURSLT);
	}
	printf("Players take turns placing thier symbol into one of nine squares in a grid:\n");
	printf("If a player gets three in a row, they win:                                                                  ");
	for (int j = 0; j < 3; j++)
	{
		for (int i = 0; i < 3; i++)
			x_o_normal_grid[j][i] = '\0';
	}
	x_o_normal_grid[0][0] = 'x';
	x_o_normal_grid[1][1] = 'x';
	x_o_normal_grid[2][2] = 'x';
	x_o_normal_grid[0][2] = 'o';
	x_o_normal_grid[1][0] = 'o';
	print_players();
	for (int i = 0; i < 5; i++)
	{
		printf(CURSDN);
	}
	printf("\r");
	printf("\npress enter to return to home screen.");
	getchar();
}

void ultimate_instructions()
{
	system("cls");
	initialize_ultimate_grid();
	for (int j = 0; j < 3; j++)//initialize small grids
	{
		for (int i = 0; i < 3; i++)
		{
			top_left[j][i] = '\0';
			top_middle[j][i] = '\0';
			top_right[j][i] = '\0';
			middle_left[j][i] = '\0';
			middle_middle[j][i] = '\0';
			middle_right[j][i] = '\0';
			bottom_left[j][i] = '\0';
			bottom_middle[j][i] = '\0';
			bottom_right[j][i] = '\0';
			ultimate_score[j][i] = '\0';
		}
	}
	display_ultimate_grid();
	for (int i = 0; i < 100; i++)
		printf(CURSUP);
	align();
	for (int i = 0; i < 10; i++)
	{
		printf(CURSDN);
	}
	printf("This is the Ultimate Tic-tac-toe board. "); printf(CURSDN); align();
	printf("The concept of tic-tac-toe is applied "); printf(CURSDN); align();
	printf("to Ultimate Tic - Tac - Toe.the object of "); printf(CURSDN); align();
	printf("the game is to get a tic - tac - toe in "); printf(CURSDN); align();
	printf("the large grid. You get large boxes by "); printf(CURSDN); align();
	printf("winning the tic - tac - toe inside of them. "); printf(CURSDN); align();
	printf("There is a catch though, whichever position "); printf(CURSDN); align();
	printf("in the small tic-tac-toe your opponent plays "); printf(CURSDN); align();
	printf("in, is the large box you are required to play "); printf(CURSDN); align();
	printf("in. Once a large box is won it can't be lost."); align();
	printf(CURSDN);
	printf(CURSDN);
	printf("press enter to return to the home screen.");
	getchar();
}

void align()
{
	printf("\r");
	for (int i = 0; i < 70; i++)
		printf(CURSRT);
}
/*
instant input from keyboard

char ch;
while (1) 
{

	if (_kbhit)
	{

		// Stores the pressed key in ch 
		ch = _getch();

		// Terminates the loop 
		// when escape is pressed 
		if ((ch) == 'a')
			break;

		printf(" << \nKey pressed= %c ", ch);
	}
}
Total code lines: 3468
*/
