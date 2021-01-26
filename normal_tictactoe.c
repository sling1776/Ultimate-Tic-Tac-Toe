/*
Psudoecode:

Begin
	declare variables: create grid
	display grid
	declare player turn
	ask for location
	use arrow keys for input 27, 91 65(u,d,r,l)
	move cursor to location as inputed to correct location
	get new line character as entering input
	save location
	check for win
	if win:
		end game
	else:
		continue to next player's turn
*/

#include<conio.h>
#include<stdio.h>

#include"normal.h"

#define CURSUP "\033[A"
#define CURSDN "\033[B"
#define CURSRT "\033[C"
#define CURSLT "\033[D"

void normal_game()
{
	
	
	for (int j = 0; j < 3; j++)
	{
		for (int i = 0; i < 3; i++)
			x_o_normal_grid[j][i] = '\0';
	}
	
	char turn='x';
	char win = 0;
	int turn_count = 0;
	char okay;
	grid_normal_initializer();

	system("cls");


	for (; turn_count < 9 && win == 0;)									//game loop
	{
		print_normal_grid();												//display grid
		print_players();													//display positions of players
		printf("\r\n\n\n\n\n\n\nIt is Player %c's Turn.", turn);			//display players turn
		printf("\nplease select location.");								//give instructions
		curs_to_initial();													//move cursor to center

		okay = get_position(turn);											//get the desired position
		if (okay != 0)														//if available
		{
			turn = okay;														//change turn to  next player
			turn_count++;														//end one turn
		}
		win = check_win();													//check for a win
		

	}
	print_normal_grid();												 //display grid
	print_players();
	printf("\n\n\n\n\n\n\n");
	if (turn_count == 9 && win==0)
	{
		printf("cats game");
	}
	else
	{
		printf("player %c wins", win);
	}
	getchar();
}

void grid_normal_initializer()										//begin
{
	/*********make outline*********/
	for (int row = 0; row < 9; row++)									//begin outline row loop
	{
		for (int col = 0; col < 11; col++)									//begin outline column loop
		{
			if (row == 0 || row == 1 || row == 3 || row == 4 \
				|| row == 6 || row == 7 || row == 8)									//if row 0, 1, 3, 4, 6, 7, 8
			{
				if (col == 3 || col == 7)											//if column 3 or 7
				{
					grid_normal[row][col] = '|';											//place vertical bar
				}
				else 															//else
				{
					grid_normal[row][col] = ' ';												//fill with empty space
				}
			}
			if (row == 2 || row == 5)											//if row 2 or 5
			{
				if (col == 3 || col == 7)											//if column 3 or 7
				{
					grid_normal[row][col] = '|';												//place veritcal bar
				}
				else															//else
				{
					grid_normal[row][col] = '_';												//place horizontal bar
				}
			}
		}																//end outline column loop when last column reached
	}																//end outline row loop when last row reached
}

void print_normal_grid()												//begin
{
	system("cls");												//clean screen
	printf("\nEnter the number corresponding to the");				//display instructions
	printf(" box you would like to go in.\n\n");
	for (int i = 0; i < 9; i++)											//begin row print loop
	{
		printf("\t\t");													//indent row
		for (int j = 0; j < 11; j++)										//begin column print loop
		{
			printf("%c", grid_normal[i][j]);										//print column characters
		}																//end column print loop when last column reached
		printf("\n");													//go to next line
	}																//end row print loop when last row reached
}																//end

void print_players()
{
	curs_to_initial();
	move_curs_up();
	move_curs_left();

	for (int j = 0; j < 3; j++)
	{
		for (int i = 0; i < 3; i++)
		{
			printf("%c", x_o_normal_grid[j][i]);
			printf("\b");
			move_curs_right();
			if(i==2)
			{
				move_curs_down();
				move_curs_left();
				move_curs_left();
				move_curs_left();
			}
		}
	}
	curs_to_initial();
}

char get_input()
{
	char ch;

	while (1)
	{

		if (_kbhit)
		{

			// Stores the pressed key in ch 
			ch = _getch();
			//printf("%d", ch);
			// Terminates the loop 
			// when arrow key pressed 
			if ((ch) == -32)
			{
				ch = _getch();
				if (ch == 72)//up
				{
						break;
				}
				if (ch == 80)//down
				{
					break;
				}
				if (ch == 77)//right
				{
					break;
				}
				if (ch == 75)//left
				{
					break;
				}
			}
			if (ch == 13)
			{
				break;
			}
				

			//printf(" << \nKey pressed= %d ", ch);
		}
	}
	return ch;
}

char get_position(char turn)
{
	char i=0, check;
	int vert_pos, horiz_pos;

	vert_pos = 1;
	horiz_pos = 1;

	for (; i != 13;)
	{
		i = get_input();

		if (i == 72)//up
		{
			if ((vert_pos - 1) >= 0)
			{
				vert_pos--;
				move_curs_up();
			}
		}
		if (i == 80)//down
		{
			if ((vert_pos + 1) <= 2)
			{
				vert_pos++;
				move_curs_down();
			}
		}
		if (i == 77)//right
		{
			if((horiz_pos+1)<=2)
			{
				horiz_pos++;
				move_curs_right();
			}
		}
		if (i == 75)//left
		{
			if ((horiz_pos - 1) >= 0)
			{
				horiz_pos--;
				move_curs_left();
			}
		}
	}
	if (i == 13)
	{
		
		//
		
		check = check_grid_pos(horiz_pos, vert_pos);
		if (check)
		{
			x_o_normal_grid[vert_pos][horiz_pos] = turn;//save grid location
			if (turn == 'x')
			{
				turn = 'o';
			}
			else
			{
				turn = 'x';
			}
			return turn;
		}
		else {
			return 0;
		}
	}
}

char check_grid_pos(int hor, int vert)
{
	if (x_o_normal_grid[vert][hor]!=0)
	{
		return 0;
	}
	return 1;
}

void curs_to_initial()
{
	/*find the inital spot*/
	printf("\r");
	for (int i = 0; i < 100; i++)
	{
		printf(CURSUP);
	}

	/* move to center of grid*/
	printf("\n\n\n\n\n\n\n");
	for (int i = 0; i != 21; i++)
	{
		printf(CURSRT);
	}
}

void move_curs_up()
{
	for (int i = 0; i != 3; i++)
	{
		printf(CURSUP);
	}
}

void move_curs_down()
{
	for (int i = 0; i != 3; i++)
	{
		printf(CURSDN);
	}
}

void move_curs_right()
{
	for (int i = 0; i != 4; i++)
	{
		printf(CURSRT);
	}
}

void move_curs_left()
{
	for (int i = 0; i != 4; i++)
	{
		printf(CURSLT);
	}
}

char check_win()
{												//begin
	char t = 0;										//declare winner variable

	/******Horizontal Check******/
	if (x_o_normal_grid[0][0] == x_o_normal_grid[0][1])					//if 1 and 2 are same
		if (x_o_normal_grid[0][1] == x_o_normal_grid[0][2])					//if 2 and 3 are same
		{
			t = x_o_normal_grid[0][0];
			if (t != 0)
			{
				return t;
			}
		}						//return winner
	if (x_o_normal_grid[1][0] == x_o_normal_grid[1][1])					//if 4 and 5 are same 
		if (x_o_normal_grid[1][1] == x_o_normal_grid[1][2])					//if 5 and 6 are same
		{
			t = x_o_normal_grid[1][0];
			if (t != 0)
			{
				return t;
			}
		}							//return winner
	if (x_o_normal_grid[2][0] == x_o_normal_grid[2][1])					//if 7 and 8 are same
		if (x_o_normal_grid[2][1] == x_o_normal_grid[2][2])					//if 8 and 9 are same
		{
			t = x_o_normal_grid[2][0];
			if (t != 0)
			{
				return t;
			}
		}							//return winner

	/******Vertical Check******/
	if (x_o_normal_grid[0][0] == x_o_normal_grid[1][0])					//if 1 and 4 are same
		if (x_o_normal_grid[1][0] == x_o_normal_grid[2][0])					//if 4 and 7 are same
		{
			t = x_o_normal_grid[0][0];	
			if (t != 0)
			{
				return t;
			}
		}						//return winner
	if (x_o_normal_grid[0][1] == x_o_normal_grid[1][1])					//if 2 and 5 are same
		if (x_o_normal_grid[1][1] == x_o_normal_grid[2][1])					//if 5 and 8 are same
		{
			t = x_o_normal_grid[0][1];	
			if (t != 0)
			{
				return t;
			}
		}						//return winner
	if (x_o_normal_grid[0][2] == x_o_normal_grid[1][2])					//if 3 and 6 are same
		if (x_o_normal_grid[1][2] == x_o_normal_grid[2][2])					//if 6 and 9 are same
		{
			t = x_o_normal_grid[0][2];	
			if (t != 0)
			{
				return t;
			}
		}								//return winner

	/******Diagonal Check******/
	if (x_o_normal_grid[0][0] == x_o_normal_grid[1][1])					//if 1 and 5 are same
		if (x_o_normal_grid[1][1] == x_o_normal_grid[2][2])					//if 5 and 9 are same
		{
			t = x_o_normal_grid[0][0]; 
			if (t != 0)
			{
				return t;
			}
		}								//return winner
	if (x_o_normal_grid[0][2] == x_o_normal_grid[1][1])					//if 3 and 5 are same
		if (x_o_normal_grid[1][1] == x_o_normal_grid[2][0])					//if 5 and 7 are same
		{
			t = x_o_normal_grid[0][2];	
			if (t != 0)
			{
				return t;
			}
		}								//return winner

	return t;										//return the winner or 0 if none
}												//end