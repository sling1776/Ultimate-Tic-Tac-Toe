#include<stdio.h>
#include<conio.h>

#include"ultimate.h"
#include"normal.h"

#define CURSUP "\033[A"
#define CURSDN "\033[B"
#define CURSRT "\033[C"
#define CURSLT "\033[D"

/*
begin game
initalize main grid
create all boards
display board
move cursor to correct position
	if first allow to move to any box
	else restrict within correct box.
get input
save location
change turns
display new grid

*/

void ultimate_game()
{
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
	
	char turn = 'x';
	char win = 0;
	int turn_count = 0;
	int position = 1;
	int okay, full;
	int* pos_p;
	pos_p = &position;
	initialize_ultimate_grid();
	
	
	/*First turn--Special--*/
	display_ultimate_grid();
	for (int i = 0; i < 15; i++)
	{
		printf(CURSUP);
	}
	printf("\r");
	for (int i = 0; i < 76; i++)
	{
		printf(CURSRT);
	}
	printf("It is player %c's Turn.", turn);
	move_curs_mmc();
	okay = get_position_ult_first(turn);
	if (okay != 0)														//if available
	{
		position = okay;														//change turn to  next player
		if (turn == 'x')
		{
			turn = 'o';
		}
		else
		{
			turn = 'x';
		}
		turn_count++;														//end one turn
	}


	/*continuing Game*/
	for (; turn_count < 81 && win == 0;)									//game loop
	{
		display_ultimate_grid();												//display grid
		for (int i = 0; i < 15; i++)
		{
			printf(CURSUP);
		}
		printf("\r");
		for (int i = 0; i < 76; i++)
		{
			printf(CURSRT);
		}
		printf("It is player %c's Turn.", turn);

		switch(position)
		{
			case 1:
				move_curs_tlc();
				full = is_full(1);
				break;
			case 2: 
				move_curs_tmc();
				full = is_full(2);
				break;
			case 3:
				move_curs_trc();
				full = is_full(3);
				break;
			case 4:
				move_curs_mlc();
				full = is_full(4);
				break;
			case 5:
				move_curs_mmc();
				full = is_full(5);
				break;
			case 6:
				move_curs_mrc();
				full = is_full(6);
				break;
			case 7:
				move_curs_blc();
				full = is_full(7);
				break;
			case 8:
				move_curs_bmc();
				full = is_full(8);
				break;
			case 9:
				move_curs_brc();
				full = is_full(9);
				break;
			default:
				printf("There was a position detection error in game loop.");
				exit (1);
		}
		if (full)
		{
			okay = get_position_ult_first(turn);
			for (int i = 1; i < 10; i++)
			{
				win = check_win_ult(i);
			}
		}
		else
		{
			okay = get_position_ult_norm(turn, position);											//get the desired position
		}
		if (okay != 0)														//if available
		{
			win = check_win_ult(position);									//check for a win
			position = okay;														
			if (turn == 'x')												//change turn to  next player
			{
				turn = 'o';
			}
			else
			{
				turn = 'x';
			}

			turn_count++;														//end one turn
			
		}												
		

	}
	display_ultimate_grid();
	for (int i = 0; i < 15; i++)
	{
		printf(CURSUP);
	}
	printf("\r");
	for (int i = 0; i < 76; i++)
	{
		printf(CURSRT);
	}
	printf("Player %c wins! ", win);
	getchar();
}

void initialize_ultimate_grid()
{
	int row = 0;  
	int col = 0;
	
	for (row = 0; row < 27; row++)
	{
		for (col = 0; col < 41; col++)
		{

			//first and last ultimate rows
			if (row == 0 || row == 18 || row == 9 || row == 26)
			{
				if (col == 13 || col == 27)
				{
					ultimate_grid[row][col] = '|';
				}
				else
				{
					ultimate_grid[row][col] = ' ';
				}
			}
			//ultimate full lines
			else if (row == 8 || row == 17)
			{
				if (col == 13 || col == 27)
				{
					ultimate_grid[row][col] = '|';
				}
				else
				{
					ultimate_grid[row][col] = '_';
				}
			}

			//inside lines
			else if (row == 2 || row == 5 || row == 11 || row == 14 || row == 20 || row == 23)
			{
				if (col == 0 || col == 12 || col == 14 || col == 26 || col == 28 || col == 40)
				{
					ultimate_grid[row][col] = ' ';
				}
				else if (col == 4 || col == 8 || col == 13 || col == 18 || col == 22 || col == 27 || col == 32 || col == 36)
				{
					ultimate_grid[row][col] = '|';
				}
				else
				{
					ultimate_grid[row][col] = '_';
				}
			}
			//remainder of lines
			else
			{
				if (col == 4 || col == 8 || col == 13 || col == 18 || col == 22 || col == 27 || col == 32 || col == 36)
				{
					ultimate_grid[row][col] = '|';
				}
			}
		}
		
	}
}

void display_ultimate_grid()
{
	int row, col;
	system("cls");
	printf("\n");
	for (row = 0; row < 27; row++)
	{
		printf("\t\t\t");
		for (col = 0; col < 41; col++)
		{
			printf("%c", ultimate_grid[row][col]);
		}
		printf("\n");
	}
	display_player_ul_pos();
}

void display_player_ul_pos()
{
	move_curs_tlc();
		move_curs_up();
		move_curs_left();
		print_players_ult(1);
	move_curs_tmc();
		move_curs_up();
		move_curs_left();
		print_players_ult(2);
	move_curs_trc();
		move_curs_up();
		move_curs_left();
		print_players_ult(3);
	move_curs_mlc();
		move_curs_up();
		move_curs_left();
		print_players_ult(4);
	move_curs_mmc();
		move_curs_up();
		move_curs_left();
		print_players_ult(5);
	move_curs_mrc();
		move_curs_up();
		move_curs_left();
		print_players_ult(6);
	move_curs_blc();
		move_curs_up();
		move_curs_left();
		print_players_ult(7);
	move_curs_bmc();
		move_curs_up();
		move_curs_left();
		print_players_ult(8);
	move_curs_brc();
		move_curs_up();
		move_curs_left();
		print_players_ult(9);
}

void move_curs_tlc()
{
	//move curs to top
	printf("\r");
	for (int i = 0; i < 1000; i++)
	{
		printf(CURSUP);
	}
	printf("\t\t\t");
	for (int i = 0; i < 5; i++)
	{
		printf(CURSDN);
	}
	for (int i = 0; i < 6; i++)
	{
		printf(CURSRT);
	}
}

void move_curs_tmc()
{
	//move curs to top
	printf("\r");
	for (int i = 0; i < 1000; i++)
	{
		printf(CURSUP);
	}
	printf("\t\t\t");
	for (int i = 0; i < 5; i++)
	{
		printf(CURSDN);
	}
	for (int i = 0; i < 20; i++)
	{
		printf(CURSRT);
	}
}

void move_curs_trc()
{
	//move curs to top
	printf("\r");
	for (int i = 0; i < 1000; i++)
	{
		printf(CURSUP);
	}
	printf("\t\t\t");
	for (int i = 0; i < 5; i++)
	{
		printf(CURSDN);
	}
	for (int i = 0; i <34 ; i++)
	{
		printf(CURSRT);
	}
}

void move_curs_mlc()
{
	//move curs to top
	printf("\r");
	for (int i = 0; i < 1000; i++)
	{
		printf(CURSUP);
	}
	printf("\t\t\t");
	for (int i = 0; i < 14; i++)
	{
		printf(CURSDN);
	}
	for (int i = 0; i < 6; i++)
	{
		printf(CURSRT);
	}
}

void move_curs_mmc()
{
	//move curs to top
	printf("\r");
	for (int i = 0; i < 1000; i++)
	{
		printf(CURSUP);
	}
	printf("\t\t\t");
	for (int i = 0; i < 14; i++)
	{
		printf(CURSDN);
	}
	for (int i = 0; i < 20; i++)
	{
		printf(CURSRT);
	}
}

void move_curs_mrc()
{
	//move curs to top
	printf("\r");
	for (int i = 0; i < 1000; i++)
	{
		printf(CURSUP);
	}
	printf("\t\t\t");
	for (int i = 0; i < 14; i++)
	{
		printf(CURSDN);
	}
	for (int i = 0; i < 34; i++)
	{
		printf(CURSRT);
	}
}

void move_curs_blc()
{
	//move curs to top
	printf("\r");
	for (int i = 0; i < 1000; i++)
	{
		printf(CURSUP);
	}
	printf("\t\t\t");
	for (int i = 0; i < 23; i++)
	{
		printf(CURSDN);
	}
	for (int i = 0; i < 6; i++)
	{
		printf(CURSRT);
	}
}

void move_curs_bmc()
{
	//move curs to top
	printf("\r");
	for (int i = 0; i < 1000; i++)
	{
		printf(CURSUP);
	}
	printf("\t\t\t");
	for (int i = 0; i < 23; i++)
	{
		printf(CURSDN);
	}
	for (int i = 0; i < 20; i++)
	{
		printf(CURSRT);
	}
}

void move_curs_brc()
{
	//move curs to top
	printf("\r");
	for (int i = 0; i < 1000; i++)
	{
		printf(CURSUP);
	}
	printf("\t\t\t");
	for (int i = 0; i < 23; i++)
	{
		printf(CURSDN);
	}
	for (int i = 0; i < 34; i++)
	{
		printf(CURSRT);
	}
}

void print_players_ult(int box)
{
	for (int j = 0; j < 3; j++)
	{
		for (int i = 0; i < 3; i++)
		{
			
			switch (box) {
			case 1: 
				{
					printf("%c", top_left[j][i]);
					printf("\b");
					move_curs_right();
					if (i == 2)
					{
						move_curs_down();
						move_curs_left();
						move_curs_left();
						move_curs_left();
					}

				}
			break;
			case 2:
				{
					printf("%c", top_middle[j][i]);
					printf("\b");
					move_curs_right();
					if (i == 2)
					{
						move_curs_down();
						move_curs_left();
						move_curs_left();
						move_curs_left();
					}
				}
			break;
			case 3:
				{
					printf("%c", top_right[j][i]);
					printf("\b");
					move_curs_right();
					if (i == 2)
					{
						move_curs_down();
						move_curs_left();
						move_curs_left();
						move_curs_left();
					}
				}
			break;
			case 4:
				{
					printf("%c", middle_left[j][i]);
					printf("\b");
					move_curs_right();
					if (i == 2)
					{
						move_curs_down();
						move_curs_left();
						move_curs_left();
						move_curs_left();
					}
				}
			break;
			case 5:
				{
					printf("%c", middle_middle[j][i]);
					printf("\b");
					move_curs_right();
					if (i == 2)
					{
						move_curs_down();
						move_curs_left();
						move_curs_left();
						move_curs_left();
					}
				}
			break;
			case 6:
				{
					printf("%c", middle_right[j][i]);
					printf("\b");
					move_curs_right();
					if (i == 2)
					{
						move_curs_down();
						move_curs_left();
						move_curs_left();
						move_curs_left();
					}
				}
			break;
			case 7:
				{
					printf("%c", bottom_left[j][i]);
					printf("\b");
					move_curs_right();
					if (i == 2)
					{
						move_curs_down();
						move_curs_left();
						move_curs_left();
						move_curs_left();
					}
				}
			break;
			case 8:
				{
					printf("%c", bottom_middle[j][i]);
					printf("\b");
					move_curs_right();
					if (i == 2)
					{
						move_curs_down();
						move_curs_left();
						move_curs_left();
						move_curs_left();
					}
				}
			break;
			case 9:
				{
					printf("%c", bottom_right[j][i]);
					printf("\b");
					move_curs_right();
					if (i == 2)
					{
						move_curs_down();
						move_curs_left();
						move_curs_left();
						move_curs_left();
					}
				}
			break;
			}
		}
	}
}

char get_position_ult_norm(char turn, int pos)
{
	char i = 0, check;
	int vert_pos, horiz_pos;
	int next_pos;

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
			if ((horiz_pos + 1) <= 2)
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
		check = check_grid_pos_ult(horiz_pos, vert_pos, 0, pos);
		if (check != 0)
		{
			switch (check)
			{
			case 1:
			{
				top_left[vert_pos][horiz_pos] = turn;
			}
			break;
			case 2:
			{
				top_middle[vert_pos][horiz_pos] = turn;
			}
			break;
			case 3:
			{
				top_right[vert_pos][horiz_pos] = turn;
			}
			break;
			case 4:
			{
				middle_left[vert_pos][horiz_pos] = turn;
			}
			break;
			case 5:
			{
				middle_middle[vert_pos][horiz_pos] = turn;
			}
			break;
			case 6:
			{
				middle_right[vert_pos][horiz_pos] = turn;
			}
			break;
			case 7:
			{
				bottom_left[vert_pos][horiz_pos] = turn;
			}
			break;
			case 8:
			{
				bottom_middle[vert_pos][horiz_pos] = turn;
			}
			break;
			case 9:
			{
				bottom_right[vert_pos][horiz_pos] = turn;
			}
			break;
			default: return 0;
			}
			next_pos = next_large_box(horiz_pos, vert_pos);
			return next_pos;
		}
		return 0;
	}
}

int get_position_ult_first(char turn)
{
	char i = 0, check;
	int vert_pos, horiz_pos;
	int next_pos;

	vert_pos = 5;
	horiz_pos = 5;

	for (; i != 13;)
	{
		i = get_input();

		if (i == 72)//up
		{
			if ((vert_pos - 1) >= 1)
			{
				vert_pos--;
				move_curs_up();
			}
		}
		if (i == 80)//down
		{
			if ((vert_pos + 1) <= 9)
			{
				vert_pos++;
				move_curs_down();
			}
		}
		if (i == 77)//right
		{
			if ((horiz_pos + 1) <= 9)
			{
				horiz_pos++;
				move_curs_right();
				if (horiz_pos == 7 || horiz_pos == 4)
				{
					printf(CURSRT);
					printf(CURSRT);
				}
			}
		}
		if (i == 75)//left
		{
			if ((horiz_pos - 1) >= 1)
			{
				horiz_pos--;
				move_curs_left();
				if (horiz_pos == 3 || horiz_pos == 6)
				{
					printf(CURSLT);
					printf(CURSLT);
				}
			}
		}
	}
	if (i == 13)
	{
		check = check_grid_pos_ult(horiz_pos, vert_pos, 1,0);
		if (check != 0)
		{
			switch (check)
			{
			case 1:
			{
				top_left[vert_pos - 1][horiz_pos - 1] = turn;
				next_pos = next_large_box(horiz_pos - 1, vert_pos - 1);
			}
			break;
			case 2:
			{
				top_middle[vert_pos - 1][horiz_pos - 4] = turn;
				next_pos = next_large_box(horiz_pos - 4, vert_pos - 1);
			}
			break;
			case 3:
			{
				top_right[vert_pos - 1][horiz_pos - 7] = turn;
				next_pos = next_large_box(horiz_pos - 7, vert_pos - 1);
			}
			break;
			case 4:
			{
				middle_left[vert_pos - 4][horiz_pos - 1] = turn;
				next_pos = next_large_box(horiz_pos - 1, vert_pos - 4);
			}
			break;
			case 5:
			{
				middle_middle[vert_pos - 4][horiz_pos - 4] = turn;
				next_pos = next_large_box(horiz_pos - 4, vert_pos - 4);
			}
			break;
			case 6:
			{
				middle_right[vert_pos - 4][horiz_pos - 7] = turn;
				next_pos = next_large_box(horiz_pos - 7, vert_pos - 4);
			}
			break;
			case 7:
			{
				bottom_left[vert_pos - 7][horiz_pos - 1] = turn;
				next_pos = next_large_box(horiz_pos - 1, vert_pos - 7);
			}
			break;
			case 8:
			{
				bottom_middle[vert_pos - 7][horiz_pos - 4] = turn;
				next_pos = next_large_box(horiz_pos - 4, vert_pos - 7);
			}
			break;
			case 9:
			{
				bottom_right[vert_pos - 7][horiz_pos - 7] = turn;
				next_pos = next_large_box(horiz_pos - 7, vert_pos - 7);
			}
			break;
			default: return 0;
			}
			return next_pos;
		}
		return 0;
	}
	return 0;
}


int check_grid_pos_ult(int horiz, int vert, int first, int pos)//returns the large box position
{
	if (first)
	{
		if ((horiz-1) / 3==0)//if left side
		{
			if ((vert - 1) / 3 == 0)//if top
			{
				if (top_left[vert - 1][horiz - 1] != 0)
					return 0;
				else
					return 1;
			}
			if((vert - 1) / 3 == 1)//if middle
			{
				if (middle_left[vert - 4][horiz - 1] != 0)
					return 0;
				else
					return 4;
			}
			if ((vert - 1) / 3 == 2)//if bottom
			{
				if (bottom_left[vert - 7][horiz - 1] != 0)
					return 0;
				else
					return 7;
			}
		}
		if ((horiz - 1) / 3 == 1)//if middle
		{
			if ((vert - 1) / 3 == 0)//if top
			{
				if (top_middle[vert - 1][horiz - 4] != 0)
					return 0;
				else
					return 2;
			}
			if ((vert - 1) / 3 == 1)//if middle
			{
				if (middle_middle[vert - 4][horiz - 4] != 0)
					return 0;
				else
					return 5;
			}
			if ((vert - 1) / 3 == 2)//if bottom
			{
				if (bottom_middle[vert - 7][horiz - 4] != 0)
					return 0;
				else
					return 8;
			}
		}
		if ((horiz - 1) / 3 == 2)//if right side
		{
			if ((vert - 1) / 3 == 0)//if top
			{
				if (top_right[vert - 1][horiz - 7] != 0)
					return 0;
				else
					return 3;
			}
			if ((vert - 1) / 3 == 1)//if middle
			{
				if (middle_right[vert - 4][horiz - 7] != 0)
					return 0;
				else
					return 6;
			}
			if ((vert - 1) / 3 == 2)//if bottom
			{
				if (bottom_right[vert - 7][horiz - 7] != 0)
					return 0;
				else
					return 9;
			}
		}
	}
	else {
		switch (pos) {
		case 1:
		{
			if (top_left[vert][horiz] != 0)
			{
				return 0;
			}
			return pos;
		}
		case 2:
		{
			if (top_middle[vert][horiz] != 0)
			{
				return 0;
			}
			return pos;
		}
		case 3:
		{
			if (top_right[vert][horiz] != 0)
			{
				return 0;
			}
			return pos;
		}
		case 4:
		{
			if (middle_left[vert][horiz] != 0)
			{
				return 0;
			}
			return pos;
		}
		case 5:
		{
			if (middle_middle[vert][horiz] != 0)
			{
				return 0;
			}
			return pos;
		}
		case 6:
		{
			if (middle_right[vert][horiz] != 0)
			{
				return 0;
			}
			return pos;
		}
		case 7:
		{
			if (bottom_left[vert][horiz] != 0)
			{
				return 0;
			}
			return pos;
		}
		case 8:
		{
			if (bottom_middle[vert][horiz] != 0)
			{
				return 0;
			}
			return pos;
		}
		case 9:
		{
			if (bottom_right[vert][horiz] != 0)
			{
				return 0;
			}
			return pos;
		}
		default: return 0;
		}
	}
	return 0;
}

int next_large_box(int hor, int vert)
{
	if (hor == 0)//if first col
	{
		switch (vert)
		{
		case 0:
			return 1;
		case 1://if second row
			return 4;
		case 2:
			return 7;

		default: return 0;
		}
	}
	if (hor == 1)//if second col
	{
		switch (vert)
		{
		case 0:
			return 2;
		case 1:
			return 5;
		case 2:
			return 8;
		default: return 0;
		}
	}
	if (hor == 2)//if third col
	{
		switch (vert)
		{
		case 0:
			return 3;
		case 1:
			return 6;
		case 2:
			return 9;
		default: return 0;
		}
	}
	return 0;
}

int is_full(int large_box_position)
{
	switch (large_box_position)
	{
	case 1:
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				if (top_left[i][j] == 0)
				{
					return 0;
				}
			}
		}
		break;
	case 2:
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				if (top_middle[i][j] == 0)
				{
					return 0;
				}
			}
		}
		break;
	case 3:
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				if (top_right[i][j] == 0)
				{
					return 0;
				}
			}
		}
		break;
	case 4:
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				if (middle_left[i][j] == 0)
				{
					return 0;
				}
			}
		}
		break;
	case 5:
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				if (middle_middle[i][j] == 0)
				{
					return 0;
				}
			}
		}
		break;
	case 6:
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				if (middle_right[i][j] == 0)
				{
					return 0;
				}
			}
		}
		break;
	case 7:
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				if (bottom_left[i][j] == 0)
				{
					return 0;
				}
			}
		}
		break;
	case 8:
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				if (bottom_middle[i][j] == 0)
				{
					return 0;
				}
			}
		}
		break;
	case 9:
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				if (bottom_right[i][j] == 0)
				{
					return 0;
				}
			}
		}
		break;
	}
	return 1;
}

char check_win_ult(int pos)
{
	char t = 0;
	check_win_individual_ult(pos);


	/******Horizontal Check******/
	if (ultimate_score[0][0] == ultimate_score[0][1])					//if 1 and 2 are same
		if (ultimate_score[0][1] == ultimate_score[0][2])					//if 2 and 3 are same
		{
			t = ultimate_score[0][0];
			if (t != 0)
			{
				return t;
			}
		}						//return winner
	if (ultimate_score[1][0] == ultimate_score[1][1])					//if 4 and 5 are same 
		if (ultimate_score[1][1] == ultimate_score[1][2])					//if 5 and 6 are same
		{
			t = ultimate_score[1][0];
			if (t != 0)
			{
				return t;
			}
		}							//return winner
	if (ultimate_score[2][0] == ultimate_score[2][1])					//if 7 and 8 are same
		if (ultimate_score[2][1] == ultimate_score[2][2])					//if 8 and 9 are same
		{
			t = ultimate_score[2][0];
			if (t != 0)
			{
				return t;
			}
		}							//return winner

	/******Vertical Check******/
	if (ultimate_score[0][0] == ultimate_score[1][0])					//if 1 and 4 are same
		if (ultimate_score[1][0] == ultimate_score[2][0])					//if 4 and 7 are same
		{
			t = ultimate_score[0][0];
			if (t != 0)
			{
				return t;
			}
		}						//return winner
	if (ultimate_score[0][1] == ultimate_score[1][1])					//if 2 and 5 are same
		if (ultimate_score[1][1] == ultimate_score[2][1])					//if 5 and 8 are same
		{
			t = ultimate_score[0][1];
			if (t != 0)
			{
				return t;
			}
		}						//return winner
	if (ultimate_score[0][2] == ultimate_score[1][2])					//if 3 and 6 are same
		if (ultimate_score[1][2] == ultimate_score[2][2])					//if 6 and 9 are same
		{
			t = ultimate_score[0][2];
			if (t != 0)
			{
				return t;
			}
		}								//return winner

	/******Diagonal Check******/
	if (ultimate_score[0][0] == ultimate_score[1][1])					//if 1 and 5 are same
		if (ultimate_score[1][1] == ultimate_score[2][2])					//if 5 and 9 are same
		{
			t = ultimate_score[0][0];
			if (t != 0)
			{
				return t;
			}
		}								//return winner
	if (ultimate_score[0][2] == ultimate_score[1][1])					//if 3 and 5 are same
		if (ultimate_score[1][1] == ultimate_score[2][0])					//if 5 and 7 are same
		{
			t = ultimate_score[0][2];
			if (t != 0)
			{
				return t;
			}
		}								//return winner

	return t;										//return the winner or 0 if none
}												//end

char check_win_individual_ult(int pos)
{
	char t = 0;	//declare winner variable
	int i = 0;
	switch (pos)
	{
	case 1://check for a win in the top left box
	{
		if (ultimate_score[0][0] != '\0')
		{
			return ultimate_score[0][0];
		}
		/******Horizontal Check******/
		if (top_left[0][0] == top_left[0][1])					//if 1 and 2 are same
			if (top_left[0][1] == top_left[0][2])					//if 2 and 3 are same
			{
				t = top_left[0][0];
				if (t != 0)
				{
					ultimate_score[0][0] = t;
					i = 3;
					ultimate_grid[0][i++] = t;
					ultimate_grid[0][i++] = ' ';
					ultimate_grid[0][i++] = 'W';
					ultimate_grid[0][i++] = 'I';
					ultimate_grid[0][i++] = 'N';
					ultimate_grid[0][i++] = 'S';
					ultimate_grid[0][i++] = '!';
					return t;
				}
			}						//return winner
		if (top_left[1][0] == top_left[1][1])					//if 4 and 5 are same 
			if (top_left[1][1] == top_left[1][2])					//if 5 and 6 are same
			{
				t = top_left[1][0];
				if (t != 0)
				{
					ultimate_score[0][0]=t;
					i = 3;
					ultimate_grid[0][i++] = t;
					ultimate_grid[0][i++] = ' ';
					ultimate_grid[0][i++] = 'W';
					ultimate_grid[0][i++] = 'I';
					ultimate_grid[0][i++] = 'N';
					ultimate_grid[0][i++] = 'S';
					ultimate_grid[0][i++] = '!';
					return t;
				}
			}							//return winner
		if (top_left[2][0] == top_left[2][1])					//if 7 and 8 are same
			if (top_left[2][1] == top_left[2][2])					//if 8 and 9 are same
			{
				t = top_left[2][0];
				if (t != 0)
				{
					ultimate_score[0][0]=t;
					i = 3;
					ultimate_grid[0][i++] = t;
					ultimate_grid[0][i++] = ' ';
					ultimate_grid[0][i++] = 'W';
					ultimate_grid[0][i++] = 'I';
					ultimate_grid[0][i++] = 'N';
					ultimate_grid[0][i++] = 'S';
					ultimate_grid[0][i++] = '!';
					return t;
				}
			}							//return winner

		/******Vertical Check******/
		if (top_left[0][0] == top_left[1][0])					//if 1 and 4 are same
			if (top_left[1][0] == top_left[2][0])					//if 4 and 7 are same
			{
				t = top_left[0][0];
				if (t != 0)
				{
					ultimate_score[0][0]=t;
					i = 3;
					ultimate_grid[0][i++] = t;
					ultimate_grid[0][i++] = ' ';
					ultimate_grid[0][i++] = 'W';
					ultimate_grid[0][i++] = 'I';
					ultimate_grid[0][i++] = 'N';
					ultimate_grid[0][i++] = 'S';
					ultimate_grid[0][i++] = '!';
					return t;
				}
			}						//return winner
		if (top_left[0][1] == top_left[1][1])					//if 2 and 5 are same
			if (top_left[1][1] == top_left[2][1])					//if 5 and 8 are same
			{
				t = top_left[0][1];
				if (t != 0)
				{
					ultimate_score[0][0]=t;
					i = 3;
					ultimate_grid[0][i++] = t;
					ultimate_grid[0][i++] = ' ';
					ultimate_grid[0][i++] = 'W';
					ultimate_grid[0][i++] = 'I';
					ultimate_grid[0][i++] = 'N';
					ultimate_grid[0][i++] = 'S';
					ultimate_grid[0][i++] = '!';
					return t;
				}
			}						//return winner
		if (top_left[0][2] == top_left[1][2])					//if 3 and 6 are same
			if (top_left[1][2] == top_left[2][2])					//if 6 and 9 are same
			{
				t = top_left[0][2];
				if (t != 0)
				{
					ultimate_score[0][0]=t;
					i = 3;
					ultimate_grid[0][i++] = t;
					ultimate_grid[0][i++] = ' ';
					ultimate_grid[0][i++] = 'W';
					ultimate_grid[0][i++] = 'I';
					ultimate_grid[0][i++] = 'N';
					ultimate_grid[0][i++] = 'S';
					ultimate_grid[0][i++] = '!';
					return t;
				}
			}			
		/******Diagonal Check******/
		if (top_left[0][0] == top_left[1][1])					//if 1 and 5 are same
			if (top_left[1][1] == top_left[2][2])					//if 5 and 9 are same
			{
				t = top_left[0][0];
				if (t != 0)
				{
					ultimate_score[0][0] = t;
					i = 3;
					ultimate_grid[0][i++] = t;
					ultimate_grid[0][i++] = ' ';
					ultimate_grid[0][i++] = 'W';
					ultimate_grid[0][i++] = 'I';
					ultimate_grid[0][i++] = 'N';
					ultimate_grid[0][i++] = 'S';
					ultimate_grid[0][i++] = '!';
					return t;
				}
			}								//return winner
		if (top_left[0][2] == top_left[1][1])					//if 3 and 5 are same
			if (top_left[1][1] == top_left[2][0])					//if 5 and 7 are same
			{
				t = top_left[0][2];
				if (t != 0)
				{
					ultimate_score[0][0] = t;
					i = 3;
					ultimate_grid[0][i++] = t;
					ultimate_grid[0][i++] = ' ';
					ultimate_grid[0][i++] = 'W';
					ultimate_grid[0][i++] = 'I';
					ultimate_grid[0][i++] = 'N';
					ultimate_grid[0][i++] = 'S';
					ultimate_grid[0][i++] = '!';
					return t;
				}
			}								//return winner

		ultimate_score[0][0] = t;
		return t;									//return the winner or 0 if none
	}												//end//return winner
	break;
	case 2: 
	{
		if (ultimate_score[0][1] != '\0')
		{
			return ultimate_score[0][1];
		}
	/******Horizontal Check******/
		if (top_middle[0][0] == top_middle[0][1])					//if 1 and 2 are same
			if (top_middle[0][1] == top_middle[0][2])					//if 2 and 3 are same
			{
				t = top_middle[0][0];
				if (t != 0)
				{
					ultimate_score[0][1]=t;
					i = 17;
					ultimate_grid[0][i++] = t;
					ultimate_grid[0][i++] = ' ';
					ultimate_grid[0][i++] = 'W';
					ultimate_grid[0][i++] = 'I';
					ultimate_grid[0][i++] = 'N';
					ultimate_grid[0][i++] = 'S';
					ultimate_grid[0][i++] = '!';
					return t;
				}
			}						//return winner
		if (top_middle[1][0] == top_middle[1][1])					//if 4 and 5 are same 
			if (top_middle[1][1] == top_middle[1][2])					//if 5 and 6 are same
			{
				t = top_middle[1][0];
				if (t != 0)
				{
					ultimate_score[0][1]=t;
					i = 17;
					ultimate_grid[0][i++] = t;
					ultimate_grid[0][i++] = ' ';
					ultimate_grid[0][i++] = 'W';
					ultimate_grid[0][i++] = 'I';
					ultimate_grid[0][i++] = 'N';
					ultimate_grid[0][i++] = 'S';
					ultimate_grid[0][i++] = '!';
					return t;
				}
			}							//return winner
		if (top_middle[2][0] == top_middle[2][1])					//if 7 and 8 are same
			if (top_middle[2][1] == top_middle[2][2])					//if 8 and 9 are same
			{
				t = top_middle[2][0];
				if (t != 0)
				{
					ultimate_score[0][1]=t;
					i = 17;
					ultimate_grid[0][i++] = t;
					ultimate_grid[0][i++] = ' ';
					ultimate_grid[0][i++] = 'W';
					ultimate_grid[0][i++] = 'I';
					ultimate_grid[0][i++] = 'N';
					ultimate_grid[0][i++] = 'S';
					ultimate_grid[0][i++] = '!';
					return t;
				}
			}							//return winner

		/******Vertical Check******/
		if (top_middle[0][0] == top_middle[1][0])					//if 1 and 4 are same
			if (top_middle[1][0] == top_middle[2][0])					//if 4 and 7 are same
			{
				t = top_middle[0][0];
				if (t != 0)
				{
					ultimate_score[0][1]=t;
					i = 17;
					ultimate_grid[0][i++] = t;
					ultimate_grid[0][i++] = ' ';
					ultimate_grid[0][i++] = 'W';
					ultimate_grid[0][i++] = 'I';
					ultimate_grid[0][i++] = 'N';
					ultimate_grid[0][i++] = 'S';
					ultimate_grid[0][i++] = '!';
					return t;
				}
			}						//return winner
		if (top_middle[0][1] == top_middle[1][1])					//if 2 and 5 are same
			if (top_middle[1][1] == top_middle[2][1])					//if 5 and 8 are same
			{
				t = top_middle[0][1];
				if (t != 0)
				{
					ultimate_score[0][1]=t;
					i = 17;
					ultimate_grid[0][i++] = t;
					ultimate_grid[0][i++] = ' ';
					ultimate_grid[0][i++] = 'W';
					ultimate_grid[0][i++] = 'I';
					ultimate_grid[0][i++] = 'N';
					ultimate_grid[0][i++] = 'S';
					ultimate_grid[0][i++] = '!';
					return t;
				}
			}						//return winner
		if (top_middle[0][2] == top_middle[1][2])					//if 3 and 6 are same
			if (top_middle[1][2] == top_middle[2][2])					//if 6 and 9 are same
			{
				t = top_middle[0][2];
				if (t != 0)
				{
					ultimate_score[0][1]=t;
					i = 17;
					ultimate_grid[0][i++] = t;
					ultimate_grid[0][i++] = ' ';
					ultimate_grid[0][i++] = 'W';
					ultimate_grid[0][i++] = 'I';
					ultimate_grid[0][i++] = 'N';
					ultimate_grid[0][i++] = 'S';
					ultimate_grid[0][i++] = '!';
					return t;
				}
			}								//return winner

		/******Diagonal Check******/
		if (top_middle[0][0] == top_middle[1][1])					//if 1 and 5 are same
			if (top_middle[1][1] == top_middle[2][2])					//if 5 and 9 are same
			{
				t = top_middle[0][0];
				if (t != 0)
				{
					ultimate_score[0][1]=t;
					i = 17;
					ultimate_grid[0][i++] = t;
					ultimate_grid[0][i++] = ' ';
					ultimate_grid[0][i++] = 'W';
					ultimate_grid[0][i++] = 'I';
					ultimate_grid[0][i++] = 'N';
					ultimate_grid[0][i++] = 'S';
					ultimate_grid[0][i++] = '!';
					return t;
				}
			}								//return winner
		if (top_middle[0][2] == top_middle[1][1])					//if 3 and 5 are same
			if (top_middle[1][1] == top_middle[2][0])					//if 5 and 7 are same
			{
				t = top_middle[0][2];
				if (t != 0)
				{
					ultimate_score[0][1]=t;
					i = 17;
					ultimate_grid[0][i++] = t;
					ultimate_grid[0][i++] = ' ';
					ultimate_grid[0][i++] = 'W';
					ultimate_grid[0][i++] = 'I';
					ultimate_grid[0][i++] = 'N';
					ultimate_grid[0][i++] = 'S';
					ultimate_grid[0][i++] = '!';
					return t;
				}
			}								//return winner

		ultimate_score[0][1]=t;										//return the winner or 0 if none
		return t;
	}												//end
	break;
	case 3:
	{
		if (ultimate_score[0][2] != '\0')
		{
			return ultimate_score[0][2];
		}
		/******Horizontal Check******/
		if (top_right[0][0] == top_right[0][1])					//if 1 and 2 are same
			if (top_right[0][1] == top_right[0][2])					//if 2 and 3 are same
			{
				t = top_right[0][0];
				if (t != 0)
				{
					ultimate_score[0][2]=t;
					i = 31;
					ultimate_grid[0][i++] = t;
					ultimate_grid[0][i++] = ' ';
					ultimate_grid[0][i++] = 'W';
					ultimate_grid[0][i++] = 'I';
					ultimate_grid[0][i++] = 'N';
					ultimate_grid[0][i++] = 'S';
					ultimate_grid[0][i++] = '!';
					return t;
				}
			}						//return winner
		if (top_right[1][0] == top_right[1][1])					//if 4 and 5 are same 
			if (top_right[1][1] == top_right[1][2])					//if 5 and 6 are same
			{
				t = top_right[1][0];
				if (t != 0)
				{
					ultimate_score[0][2]=t;
					i = 31;
					ultimate_grid[0][i++] = t;
					ultimate_grid[0][i++] = ' ';
					ultimate_grid[0][i++] = 'W';
					ultimate_grid[0][i++] = 'I';
					ultimate_grid[0][i++] = 'N';
					ultimate_grid[0][i++] = 'S';
					ultimate_grid[0][i++] = '!';
					return t;
				}
			}							//return winner
		if (top_right[2][0] == top_right[2][1])					//if 7 and 8 are same
			if (top_right[2][1] == top_right[2][2])					//if 8 and 9 are same
			{
				t = top_right[2][0];
				if (t != 0)
				{
					ultimate_score[0][2]=t;
					i = 31;
					ultimate_grid[0][i++] = t;
					ultimate_grid[0][i++] = ' ';
					ultimate_grid[0][i++] = 'W';
					ultimate_grid[0][i++] = 'I';
					ultimate_grid[0][i++] = 'N';
					ultimate_grid[0][i++] = 'S';
					ultimate_grid[0][i++] = '!';
					return t;
				}
			}							//return winner

		/******Vertical Check******/
		if (top_right[0][0] == top_right[1][0])					//if 1 and 4 are same
			if (top_right[1][0] == top_right[2][0])					//if 4 and 7 are same
			{
				t = top_right[0][0];
				if (t != 0)
				{
					ultimate_score[0][2]=t;
					i = 31;
					ultimate_grid[0][i++] = t;
					ultimate_grid[0][i++] = ' ';
					ultimate_grid[0][i++] = 'W';
					ultimate_grid[0][i++] = 'I';
					ultimate_grid[0][i++] = 'N';
					ultimate_grid[0][i++] = 'S';
					ultimate_grid[0][i++] = '!';
					return t;
				}
			}						//return winner
		if (top_right[0][1] == top_right[1][1])					//if 2 and 5 are same
			if (top_right[1][1] == top_right[2][1])					//if 5 and 8 are same
			{
				t = top_right[0][1];
				if (t != 0)
				{
					ultimate_score[0][2]=t;
					i = 31;
					ultimate_grid[0][i++] = t;
					ultimate_grid[0][i++] = ' ';
					ultimate_grid[0][i++] = 'W';
					ultimate_grid[0][i++] = 'I';
					ultimate_grid[0][i++] = 'N';
					ultimate_grid[0][i++] = 'S';
					ultimate_grid[0][i++] = '!';
					return t;
				}
			}						//return winner
		if (top_right[0][2] == top_right[1][2])					//if 3 and 6 are same
			if (top_right[1][2] == top_right[2][2])					//if 6 and 9 are same
			{
				t = top_right[0][2];
				if (t != 0)
				{
					ultimate_score[0][2]=t;
					i = 31;
					ultimate_grid[0][i++] = t;
					ultimate_grid[0][i++] = ' ';
					ultimate_grid[0][i++] = 'W';
					ultimate_grid[0][i++] = 'I';
					ultimate_grid[0][i++] = 'N';
					ultimate_grid[0][i++] = 'S';
					ultimate_grid[0][i++] = '!';
					return t;
				}
			}								//return winner

		/******Diagonal Check******/
		if (top_right[0][0] == top_right[1][1])					//if 1 and 5 are same
			if (top_right[1][1] == top_right[2][2])					//if 5 and 9 are same
			{
				t = top_right[0][0];
				if (t != 0)
				{
					ultimate_score[0][2]=t;
					i = 31;
					ultimate_grid[0][i++] = t;
					ultimate_grid[0][i++] = ' ';
					ultimate_grid[0][i++] = 'W';
					ultimate_grid[0][i++] = 'I';
					ultimate_grid[0][i++] = 'N';
					ultimate_grid[0][i++] = 'S';
					ultimate_grid[0][i++] = '!';
					return t;
				}
			}								//return winner
		if (top_right[0][2] == top_right[1][1])					//if 3 and 5 are same
			if (top_right[1][1] == top_right[2][0])					//if 5 and 7 are same
			{
				t = top_right[0][2];
				if (t != 0)
				{
					ultimate_score[0][2]=t;
					i = 31;
					ultimate_grid[0][i++] = t;
					ultimate_grid[0][i++] = ' ';
					ultimate_grid[0][i++] = 'W';
					ultimate_grid[0][i++] = 'I';
					ultimate_grid[0][i++] = 'N';
					ultimate_grid[0][i++] = 'S';
					ultimate_grid[0][i++] = '!';
					return t;
				}
			}								//return winner

		ultimate_score[0][2]=t;										//return the winner or 0 if none
		return t;
	}												//end
	break;
	case 4:
	{
		if (ultimate_score[1][0] != '\0')
		{
			return ultimate_score[1][0];
		}
		/******Horizontal Check******/
		if (middle_left[0][0] == middle_left[0][1])					//if 1 and 2 are same
			if (middle_left[0][1] == middle_left[0][2])					//if 2 and 3 are same
			{
				t = middle_left[0][0];
				if (t != 0)
				{
					ultimate_score[1][0]=t;
					i = 3;
					ultimate_grid[9][i++] = t;
					ultimate_grid[9][i++] = ' ';
					ultimate_grid[9][i++] = 'W';
					ultimate_grid[9][i++] = 'I';
					ultimate_grid[9][i++] = 'N';
					ultimate_grid[9][i++] = 'S';
					ultimate_grid[9][i++] = '!';
					return t;
				}
			}						//return winner
		if (middle_left[1][0] == middle_left[1][1])					//if 4 and 5 are same 
			if (middle_left[1][1] == middle_left[1][2])					//if 5 and 6 are same
			{
				t = middle_left[1][0];
				if (t != 0)
				{
					ultimate_score[1][0]=t;
					i = 3;
					ultimate_grid[9][i++] = t;
					ultimate_grid[9][i++] = ' ';
					ultimate_grid[9][i++] = 'W';
					ultimate_grid[9][i++] = 'I';
					ultimate_grid[9][i++] = 'N';
					ultimate_grid[9][i++] = 'S';
					ultimate_grid[9][i++] = '!';
					return t;
				}
			}							//return winner
		if (middle_left[2][0] == middle_left[2][1])					//if 7 and 8 are same
			if (middle_left[2][1] == middle_left[2][2])					//if 8 and 9 are same
			{
				t = middle_left[2][0];
				if (t != 0)
				{
					ultimate_score[1][0]=t;
					i = 3;
					ultimate_grid[9][i++] = t;
					ultimate_grid[9][i++] = ' ';
					ultimate_grid[9][i++] = 'W';
					ultimate_grid[9][i++] = 'I';
					ultimate_grid[9][i++] = 'N';
					ultimate_grid[9][i++] = 'S';
					ultimate_grid[9][i++] = '!';
					return t;
				}
			}							//return winner

		/******Vertical Check******/
		if (middle_left[0][0] == middle_left[1][0])					//if 1 and 4 are same
			if (middle_left[1][0] == middle_left[2][0])					//if 4 and 7 are same
			{
				t = middle_left[0][0];
				if (t != 0)
				{
					ultimate_score[1][0]=t;
					i = 3;
					ultimate_grid[9][i++] = t;
					ultimate_grid[9][i++] = ' ';
					ultimate_grid[9][i++] = 'W';
					ultimate_grid[9][i++] = 'I';
					ultimate_grid[9][i++] = 'N';
					ultimate_grid[9][i++] = 'S';
					ultimate_grid[9][i++] = '!';
					return t;
				}
			}						//return winner
		if (middle_left[0][1] == middle_left[1][1])					//if 2 and 5 are same
			if (middle_left[1][1] == middle_left[2][1])					//if 5 and 8 are same
			{
				t = middle_left[0][1];
				if (t != 0)
				{
					ultimate_score[1][0]=t;
					i = 3;
					ultimate_grid[9][i++] = t;
					ultimate_grid[9][i++] = ' ';
					ultimate_grid[9][i++] = 'W';
					ultimate_grid[9][i++] = 'I';
					ultimate_grid[9][i++] = 'N';
					ultimate_grid[9][i++] = 'S';
					ultimate_grid[9][i++] = '!';
					return t;
				}
			}						//return winner
		if (middle_left[0][2] == middle_left[1][2])					//if 3 and 6 are same
			if (middle_left[1][2] == middle_left[2][2])					//if 6 and 9 are same
			{
				t = middle_left[0][2];
				if (t != 0)
				{
					ultimate_score[1][0]=t;
					i = 3;
					ultimate_grid[9][i++] = t;
					ultimate_grid[9][i++] = ' ';
					ultimate_grid[9][i++] = 'W';
					ultimate_grid[9][i++] = 'I';
					ultimate_grid[9][i++] = 'N';
					ultimate_grid[9][i++] = 'S';
					ultimate_grid[9][i++] = '!';
					return t;
				}
			}								//return winner

		/******Diagonal Check******/
		if (middle_left[0][0] == middle_left[1][1])					//if 1 and 5 are same
			if (middle_left[1][1] == middle_left[2][2])					//if 5 and 9 are same
			{
				t = middle_left[0][0];
				if (t != 0)
				{
					ultimate_score[1][0]=t;
					i = 3;
					ultimate_grid[9][i++] = t;
					ultimate_grid[9][i++] = ' ';
					ultimate_grid[9][i++] = 'W';
					ultimate_grid[9][i++] = 'I';
					ultimate_grid[9][i++] = 'N';
					ultimate_grid[9][i++] = 'S';
					ultimate_grid[9][i++] = '!';
					return t;
				}
			}								//return winner
		if (middle_left[0][2] == middle_left[1][1])					//if 3 and 5 are same
			if (middle_left[1][1] == middle_left[2][0])					//if 5 and 7 are same
			{
				t = middle_left[0][2];
				if (t != 0)
				{
					ultimate_score[1][0]=t;
					i = 3;
					ultimate_grid[9][i++] = t;
					ultimate_grid[9][i++] = ' ';
					ultimate_grid[9][i++] = 'W';
					ultimate_grid[9][i++] = 'I';
					ultimate_grid[9][i++] = 'N';
					ultimate_grid[9][i++] = 'S';
					ultimate_grid[9][i++] = '!';
					return t;
				}
			}								//return winner

		ultimate_score[1][0]=t;										//return the winner or 0 if none
		return t;
}												//end
	break;
	case 5:
	{
		if (ultimate_score[1][1] != '\0')
		{
			return ultimate_score[1][1];
		}
		/******Horizontal Check******/
		if (middle_middle[0][0] == middle_middle[0][1])					//if 1 and 2 are same
			if (middle_middle[0][1] == middle_middle[0][2])					//if 2 and 3 are same
			{
				t = middle_middle[0][0];
				if (t != 0)
				{
					ultimate_score[1][1]=t;
					i = 17;
					ultimate_grid[9][i++] = t;
					ultimate_grid[9][i++] = ' ';
					ultimate_grid[9][i++] = 'W';
					ultimate_grid[9][i++] = 'I';
					ultimate_grid[9][i++] = 'N';
					ultimate_grid[9][i++] = 'S';
					ultimate_grid[9][i++] = '!';
					return t;
				}
			}						//return winner
		if (middle_middle[1][0] == middle_middle[1][1])					//if 4 and 5 are same 
			if (middle_middle[1][1] == middle_middle[1][2])					//if 5 and 6 are same
			{
				t = middle_middle[1][0];
				if (t != 0)
				{
					ultimate_score[1][1]=t;
					i = 17;
					ultimate_grid[9][i++] = t;
					ultimate_grid[9][i++] = ' ';
					ultimate_grid[9][i++] = 'W';
					ultimate_grid[9][i++] = 'I';
					ultimate_grid[9][i++] = 'N';
					ultimate_grid[9][i++] = 'S';
					ultimate_grid[9][i++] = '!';
					return t;
				}
			}							//return winner
		if (middle_middle[2][0] == middle_middle[2][1])					//if 7 and 8 are same
			if (middle_middle[2][1] == middle_middle[2][2])					//if 8 and 9 are same
			{
				t = middle_middle[2][0];
				if (t != 0)
				{
					ultimate_score[1][1]=t;
					i = 17;
					ultimate_grid[9][i++] = t;
					ultimate_grid[9][i++] = ' ';
					ultimate_grid[9][i++] = 'W';
					ultimate_grid[9][i++] = 'I';
					ultimate_grid[9][i++] = 'N';
					ultimate_grid[9][i++] = 'S';
					ultimate_grid[9][i++] = '!';
					return t;
				}
			}							//return winner

		/******Vertical Check******/
		if (middle_middle[0][0] == middle_middle[1][0])					//if 1 and 4 are same
			if (middle_middle[1][0] == middle_middle[2][0])					//if 4 and 7 are same
			{
				t = middle_middle[0][0];
				if (t != 0)
				{
					ultimate_score[1][1]=t;
					i = 17;
					ultimate_grid[9][i++] = t;
					ultimate_grid[9][i++] = ' ';
					ultimate_grid[9][i++] = 'W';
					ultimate_grid[9][i++] = 'I';
					ultimate_grid[9][i++] = 'N';
					ultimate_grid[9][i++] = 'S';
					ultimate_grid[9][i++] = '!';
					return t;
				}
			}						//return winner
		if (middle_middle[0][1] == middle_middle[1][1])					//if 2 and 5 are same
			if (middle_middle[1][1] == middle_middle[2][1])					//if 5 and 8 are same
			{
				t = middle_middle[0][1];
				if (t != 0)
				{
					ultimate_score[1][1]=t;
					i = 17;
					ultimate_grid[9][i++] = t;
					ultimate_grid[9][i++] = ' ';
					ultimate_grid[9][i++] = 'W';
					ultimate_grid[9][i++] = 'I';
					ultimate_grid[9][i++] = 'N';
					ultimate_grid[9][i++] = 'S';
					ultimate_grid[9][i++] = '!';
					return t;
				}
			}						//return winner
		if (middle_middle[0][2] == middle_middle[1][2])					//if 3 and 6 are same
			if (middle_middle[1][2] == middle_middle[2][2])					//if 6 and 9 are same
			{
				t = middle_middle[0][2];
				if (t != 0)
				{
					ultimate_score[1][1]=t;
					i = 17;
					ultimate_grid[9][i++] = t;
					ultimate_grid[9][i++] = ' ';
					ultimate_grid[9][i++] = 'W';
					ultimate_grid[9][i++] = 'I';
					ultimate_grid[9][i++] = 'N';
					ultimate_grid[9][i++] = 'S';
					ultimate_grid[9][i++] = '!';
					return t;
				}
			}								//return winner

		/******Diagonal Check******/
		if (middle_middle[0][0] == middle_middle[1][1])					//if 1 and 5 are same
			if (middle_middle[1][1] == middle_middle[2][2])					//if 5 and 9 are same
			{
				t = middle_middle[0][0];
				if (t != 0)
				{
					ultimate_score[1][1]=t;
					i = 17;
					ultimate_grid[9][i++] = t;
					ultimate_grid[9][i++] = ' ';
					ultimate_grid[9][i++] = 'W';
					ultimate_grid[9][i++] = 'I';
					ultimate_grid[9][i++] = 'N';
					ultimate_grid[9][i++] = 'S';
					ultimate_grid[9][i++] = '!';
					return t;
				}
			}								//return winner
		if (middle_middle[0][2] == middle_middle[1][1])					//if 3 and 5 are same
			if (middle_middle[1][1] == middle_middle[2][0])					//if 5 and 7 are same
			{
				t = middle_middle[0][2];
				if (t != 0)
				{
					ultimate_score[1][1]=t;
					i = 17;
					ultimate_grid[9][i++] = t;
					ultimate_grid[9][i++] = ' ';
					ultimate_grid[9][i++] = 'W';
					ultimate_grid[9][i++] = 'I';
					ultimate_grid[9][i++] = 'N';
					ultimate_grid[9][i++] = 'S';
					ultimate_grid[9][i++] = '!';
					return t;
				}
			}								//return winner

		ultimate_score[1][1]=t;										//return the winner or 0 if none
		return t;
	}												//end
	break;
	case 6:
	{
		if (ultimate_score[1][2] != '\0')
		{
			return ultimate_score[1][2];
		}
		/******Horizontal Check******/
		if (middle_right[0][0] == middle_right[0][1])					//if 1 and 2 are same
			if (middle_right[0][1] == middle_right[0][2])					//if 2 and 3 are same
			{
				t = middle_right[0][0];
				if (t != 0)
				{
					ultimate_score[1][2]=t;
					i = 31;
					ultimate_grid[9][i++] = t;
					ultimate_grid[9][i++] = ' ';
					ultimate_grid[9][i++] = 'W';
					ultimate_grid[9][i++] = 'I';
					ultimate_grid[9][i++] = 'N';
					ultimate_grid[9][i++] = 'S';
					ultimate_grid[9][i++] = '!';
					return t;
				}
			}						//return winner
		if (middle_right[1][0] == middle_right[1][1])					//if 4 and 5 are same 
			if (middle_right[1][1] == middle_right[1][2])					//if 5 and 6 are same
			{
				t = middle_right[1][0];
				if (t != 0)
				{
					ultimate_score[1][2]=t;
					i = 31;
					ultimate_grid[9][i++] = t;
					ultimate_grid[9][i++] = ' ';
					ultimate_grid[9][i++] = 'W';
					ultimate_grid[9][i++] = 'I';
					ultimate_grid[9][i++] = 'N';
					ultimate_grid[9][i++] = 'S';
					ultimate_grid[9][i++] = '!';
					return t;
				}
			}							//return winner
		if (middle_right[2][0] == middle_right[2][1])					//if 7 and 8 are same
			if (middle_right[2][1] == middle_right[2][2])					//if 8 and 9 are same
			{
				t = middle_right[2][0];
				if (t != 0)
				{
					ultimate_score[1][2]=t;
					i = 31;
					ultimate_grid[9][i++] = t;
					ultimate_grid[9][i++] = ' ';
					ultimate_grid[9][i++] = 'W';
					ultimate_grid[9][i++] = 'I';
					ultimate_grid[9][i++] = 'N';
					ultimate_grid[9][i++] = 'S';
					ultimate_grid[9][i++] = '!';
					return t;
				}
			}							//return winner

		/******Vertical Check******/
		if (middle_right[0][0] == middle_right[1][0])					//if 1 and 4 are same
			if (middle_right[1][0] == middle_right[2][0])					//if 4 and 7 are same
			{
				t = middle_right[0][0];
				if (t != 0)
				{
					ultimate_score[1][2]=t;
					i = 31;
					ultimate_grid[9][i++] = t;
					ultimate_grid[9][i++] = ' ';
					ultimate_grid[9][i++] = 'W';
					ultimate_grid[9][i++] = 'I';
					ultimate_grid[9][i++] = 'N';
					ultimate_grid[9][i++] = 'S';
					ultimate_grid[9][i++] = '!';
					return t;
				}
			}						//return winner
		if (middle_right[0][1] == middle_right[1][1])					//if 2 and 5 are same
			if (middle_right[1][1] == middle_right[2][1])					//if 5 and 8 are same
			{
				t = middle_right[0][1];
				if (t != 0)
				{
					ultimate_score[1][2]=t;
					i = 31;
					ultimate_grid[9][i++] = t;
					ultimate_grid[9][i++] = ' ';
					ultimate_grid[9][i++] = 'W';
					ultimate_grid[9][i++] = 'I';
					ultimate_grid[9][i++] = 'N';
					ultimate_grid[9][i++] = 'S';
					ultimate_grid[9][i++] = '!';
					return t;
				}
			}						//return winner
		if (middle_right[0][2] == middle_right[1][2])					//if 3 and 6 are same
			if (middle_right[1][2] == middle_right[2][2])					//if 6 and 9 are same
			{
				t = middle_right[0][2];
				if (t != 0)
				{
					ultimate_score[1][2]=t;
					i = 31;
					ultimate_grid[9][i++] = t;
					ultimate_grid[9][i++] = ' ';
					ultimate_grid[9][i++] = 'W';
					ultimate_grid[9][i++] = 'I';
					ultimate_grid[9][i++] = 'N';
					ultimate_grid[9][i++] = 'S';
					ultimate_grid[9][i++] = '!';
					return t;
				}
			}								//return winner

		/******Diagonal Check******/
		if (middle_right[0][0] == middle_right[1][1])					//if 1 and 5 are same
			if (middle_right[1][1] == middle_right[2][2])					//if 5 and 9 are same
			{
				t = middle_right[0][0];
				if (t != 0)
				{
					ultimate_score[1][2]=t;
					i = 31;
					ultimate_grid[9][i++] = t;
					ultimate_grid[9][i++] = ' ';
					ultimate_grid[9][i++] = 'W';
					ultimate_grid[9][i++] = 'I';
					ultimate_grid[9][i++] = 'N';
					ultimate_grid[9][i++] = 'S';
					ultimate_grid[9][i++] = '!';
					return t;
				}
			}								//return winner
		if (middle_right[0][2] == middle_right[1][1])					//if 3 and 5 are same
			if (middle_right[1][1] == middle_right[2][0])					//if 5 and 7 are same
			{
				t = middle_right[0][2];
				if (t != 0)
				{
					ultimate_score[1][2]=t;
					i = 31;
					ultimate_grid[9][i++] = t;
					ultimate_grid[9][i++] = ' ';
					ultimate_grid[9][i++] = 'W';
					ultimate_grid[9][i++] = 'I';
					ultimate_grid[9][i++] = 'N';
					ultimate_grid[9][i++] = 'S';
					ultimate_grid[9][i++] = '!';
					return t;
				}
			}								//return winner

		ultimate_score[1][2]=t;										//return the winner or 0 if none
		return t;
	}												//end
	break;
	case 7:
	{
		if (ultimate_score[2][0] != '\0')
		{
			return ultimate_score[2][0];
		}
		/******Horizontal Check******/
		if (bottom_left[0][0] == bottom_left[0][1])					//if 1 and 2 are same
			if (bottom_left[0][1] == bottom_left[0][2])					//if 2 and 3 are same
			{
				t = bottom_left[0][0];
				if (t != 0)
				{
					ultimate_score[2][0]=t;
					i = 3;
					ultimate_grid[18][i++] = t;
					ultimate_grid[18][i++] = ' ';
					ultimate_grid[18][i++] = 'W';
					ultimate_grid[18][i++] = 'I';
					ultimate_grid[18][i++] = 'N';
					ultimate_grid[18][i++] = 'S';
					ultimate_grid[18][i++] = '!';
					return t;
				}
			}						//return winner
		if (bottom_left[1][0] == bottom_left[1][1])					//if 4 and 5 are same 
			if (bottom_left[1][1] == bottom_left[1][2])					//if 5 and 6 are same
			{
				t = bottom_left[1][0];
				if (t != 0)
				{
					ultimate_score[2][0]=t;
					i = 3;
					ultimate_grid[18][i++] = t;
					ultimate_grid[18][i++] = ' ';
					ultimate_grid[18][i++] = 'W';
					ultimate_grid[18][i++] = 'I';
					ultimate_grid[18][i++] = 'N';
					ultimate_grid[18][i++] = 'S';
					ultimate_grid[18][i++] = '!';
					return t;
				}
			}							//return winner
		if (bottom_left[2][0] == bottom_left[2][1])					//if 7 and 8 are same
			if (bottom_left[2][1] == bottom_left[2][2])					//if 8 and 9 are same
			{
				t = bottom_left[2][0];
				if (t != 0)
				{
					ultimate_score[2][0]=t;
					i = 3;
					ultimate_grid[18][i++] = t;
					ultimate_grid[18][i++] = ' ';
					ultimate_grid[18][i++] = 'W';
					ultimate_grid[18][i++] = 'I';
					ultimate_grid[18][i++] = 'N';
					ultimate_grid[18][i++] = 'S';
					ultimate_grid[18][i++] = '!';
					return t;
				}
			}							//return winner

		/******Vertical Check******/
		if (bottom_left[0][0] == bottom_left[1][0])					//if 1 and 4 are same
			if (bottom_left[1][0] == bottom_left[2][0])					//if 4 and 7 are same
			{
				t = bottom_left[0][0];
				if (t != 0)
				{
					ultimate_score[2][0]=t;
					i = 3;
					ultimate_grid[18][i++] = t;
					ultimate_grid[18][i++] = ' ';
					ultimate_grid[18][i++] = 'W';
					ultimate_grid[18][i++] = 'I';
					ultimate_grid[18][i++] = 'N';
					ultimate_grid[18][i++] = 'S';
					ultimate_grid[18][i++] = '!';
					return t;
				}
			}						//return winner
		if (bottom_left[0][1] == bottom_left[1][1])					//if 2 and 5 are same
			if (bottom_left[1][1] == bottom_left[2][1])					//if 5 and 8 are same
			{
				t = bottom_left[0][1];
				if (t != 0)
				{
					ultimate_score[2][0]=t;
					i = 3;
					ultimate_grid[18][i++] = t;
					ultimate_grid[18][i++] = ' ';
					ultimate_grid[18][i++] = 'W';
					ultimate_grid[18][i++] = 'I';
					ultimate_grid[18][i++] = 'N';
					ultimate_grid[18][i++] = 'S';
					ultimate_grid[18][i++] = '!';
					return t;
				}
			}						//return winner
		if (bottom_left[0][2] == bottom_left[1][2])					//if 3 and 6 are same
			if (bottom_left[1][2] == bottom_left[2][2])					//if 6 and 9 are same
			{
				t = bottom_left[0][2];
				if (t != 0)
				{
					ultimate_score[2][0]=t;
					i = 3;
					ultimate_grid[18][i++] = t;
					ultimate_grid[18][i++] = ' ';
					ultimate_grid[18][i++] = 'W';
					ultimate_grid[18][i++] = 'I';
					ultimate_grid[18][i++] = 'N';
					ultimate_grid[18][i++] = 'S';
					ultimate_grid[18][i++] = '!';
					return t;
				}
			}								//return winner

		/******Diagonal Check******/
		if (bottom_left[0][0] == bottom_left[1][1])					//if 1 and 5 are same
			if (bottom_left[1][1] == bottom_left[2][2])					//if 5 and 9 are same
			{
				t = bottom_left[0][0];
				if (t != 0)
				{
					ultimate_score[2][0]=t;
					i = 3;
					ultimate_grid[18][i++] = t;
					ultimate_grid[18][i++] = ' ';
					ultimate_grid[18][i++] = 'W';
					ultimate_grid[18][i++] = 'I';
					ultimate_grid[18][i++] = 'N';
					ultimate_grid[18][i++] = 'S';
					ultimate_grid[18][i++] = '!';
					return t;
				}
			}								//return winner
		if (bottom_left[0][2] == bottom_left[1][1])					//if 3 and 5 are same
			if (bottom_left[1][1] == bottom_left[2][0])					//if 5 and 7 are same
			{
				t = bottom_left[0][2];
				if (t != 0)
				{
					ultimate_score[2][0]=t;
					i = 3;
					ultimate_grid[18][i++] = t;
					ultimate_grid[18][i++] = ' ';
					ultimate_grid[18][i++] = 'W';
					ultimate_grid[18][i++] = 'I';
					ultimate_grid[18][i++] = 'N';
					ultimate_grid[18][i++] = 'S';
					ultimate_grid[18][i++] = '!';
					return t;
				}
			}								//return winner

		ultimate_score[2][0]=t;										//return the winner or 0 if none
		return t;
	}												//end
	break;
	case 8:
	{
		if (ultimate_score[2][1] != '\0')
		{
			return ultimate_score[2][1];
		}
		/******Horizontal Check******/
		if (bottom_middle[0][0] == bottom_middle[0][1])					//if 1 and 2 are same
			if (bottom_middle[0][1] == bottom_middle[0][2])					//if 2 and 3 are same
			{
				t = bottom_middle[0][0];
				if (t != 0)
				{
					ultimate_score[2][1]=t;
					i = 17;
					ultimate_grid[18][i++] = t;
					ultimate_grid[18][i++] = ' ';
					ultimate_grid[18][i++] = 'W';
					ultimate_grid[18][i++] = 'I';
					ultimate_grid[18][i++] = 'N';
					ultimate_grid[18][i++] = 'S';
					ultimate_grid[18][i++] = '!';
					return t;
				}
			}						//return winner
		if (bottom_middle[1][0] == bottom_middle[1][1])					//if 4 and 5 are same 
			if (bottom_middle[1][1] == bottom_middle[1][2])					//if 5 and 6 are same
			{
				t = bottom_middle[1][0];
				if (t != 0)
				{
					ultimate_score[2][1]=t;
					i = 17;
					ultimate_grid[18][i++] = t;
					ultimate_grid[18][i++] = ' ';
					ultimate_grid[18][i++] = 'W';
					ultimate_grid[18][i++] = 'I';
					ultimate_grid[18][i++] = 'N';
					ultimate_grid[18][i++] = 'S';
					ultimate_grid[18][i++] = '!';
					return t;
				}
			}							//return winner
		if (bottom_middle[2][0] == bottom_middle[2][1])					//if 7 and 8 are same
			if (bottom_middle[2][1] == bottom_middle[2][2])					//if 8 and 9 are same
			{
				t = bottom_middle[2][0];
				if (t != 0)
				{
					ultimate_score[2][1]=t;
					i = 17;
					ultimate_grid[18][i++] = t;
					ultimate_grid[18][i++] = ' ';
					ultimate_grid[18][i++] = 'W';
					ultimate_grid[18][i++] = 'I';
					ultimate_grid[18][i++] = 'N';
					ultimate_grid[18][i++] = 'S';
					ultimate_grid[18][i++] = '!';
					return t;
				}
			}							//return winner

		/******Vertical Check******/
		if (bottom_middle[0][0] == bottom_middle[1][0])					//if 1 and 4 are same
			if (bottom_middle[1][0] == bottom_middle[2][0])					//if 4 and 7 are same
			{
				t = bottom_middle[0][0];
				if (t != 0)
				{
					ultimate_score[2][1]=t;
					i = 17;
					ultimate_grid[18][i++] = t;
					ultimate_grid[18][i++] = ' ';
					ultimate_grid[18][i++] = 'W';
					ultimate_grid[18][i++] = 'I';
					ultimate_grid[18][i++] = 'N';
					ultimate_grid[18][i++] = 'S';
					ultimate_grid[18][i++] = '!';
					return t;
				}
			}						//return winner
		if (bottom_middle[0][1] == bottom_middle[1][1])					//if 2 and 5 are same
			if (bottom_middle[1][1] == bottom_middle[2][1])					//if 5 and 8 are same
			{
				t = bottom_middle[0][1];

				if (t != 0)
				{
					ultimate_score[2][1]=t;
					i = 17;
					ultimate_grid[18][i++] = t;
					ultimate_grid[18][i++] = ' ';
					ultimate_grid[18][i++] = 'W';
					ultimate_grid[18][i++] = 'I';
					ultimate_grid[18][i++] = 'N';
					ultimate_grid[18][i++] = 'S';
					ultimate_grid[18][i++] = '!';
					return t;
				}
			}						//return winner
		if (bottom_middle[0][2] == bottom_middle[1][2])					//if 3 and 6 are same
			if (bottom_middle[1][2] == bottom_middle[2][2])					//if 6 and 9 are same
			{
				t = bottom_middle[0][2];
				if (t != 0)
				{
					ultimate_score[2][1]=t;
					i = 17;
					ultimate_grid[18][i++] = t;
					ultimate_grid[18][i++] = ' ';
					ultimate_grid[18][i++] = 'W';
					ultimate_grid[18][i++] = 'I';
					ultimate_grid[18][i++] = 'N';
					ultimate_grid[18][i++] = 'S';
					ultimate_grid[18][i++] = '!';
					return t;
				}
			}								//return winner

		/******Diagonal Check******/
		if (bottom_middle[0][0] == bottom_middle[1][1])					//if 1 and 5 are same
			if (bottom_middle[1][1] == bottom_middle[2][2])					//if 5 and 9 are same
			{
				t = bottom_middle[0][0];
				if (t != 0)
				{
					ultimate_score[2][1]=t;
					i = 17;
					ultimate_grid[18][i++] = t;
					ultimate_grid[18][i++] = ' ';
					ultimate_grid[18][i++] = 'W';
					ultimate_grid[18][i++] = 'I';
					ultimate_grid[18][i++] = 'N';
					ultimate_grid[18][i++] = 'S';
					ultimate_grid[18][i++] = '!';
					return t;
				}
			}								//return winner
		if (bottom_middle[0][2] == bottom_middle[1][1])					//if 3 and 5 are same
			if (bottom_middle[1][1] == bottom_middle[2][0])					//if 5 and 7 are same
			{
				t = bottom_middle[0][2];
				if (t != 0)
				{
					ultimate_score[2][1]=t;
					i = 17;
					ultimate_grid[18][i++] = t;
					ultimate_grid[18][i++] = ' ';
					ultimate_grid[18][i++] = 'W';
					ultimate_grid[18][i++] = 'I';
					ultimate_grid[18][i++] = 'N';
					ultimate_grid[18][i++] = 'S';
					ultimate_grid[18][i++] = '!';
					return t;
				}
			}								//return winner

		ultimate_score[2][1]=t;										//return the winner or 0 if none
		return t;
	}												//end
	break;
	case 9:
	{
		if (ultimate_score[1][0] != '\0')
		{
			return ultimate_score[1][0];
		}
		/******Horizontal Check******/
		if (bottom_right[0][0] == bottom_right[0][1])					//if 1 and 2 are same
			if (bottom_right[0][1] == bottom_right[0][2])					//if 2 and 3 are same
			{
				t = bottom_right[0][0];
				if (t != 0)
				{
					ultimate_score[2][2]=t;
					i = 31;
					ultimate_grid[18][i++] = t;
					ultimate_grid[18][i++] = ' ';
					ultimate_grid[18][i++] = 'W';
					ultimate_grid[18][i++] = 'I';
					ultimate_grid[18][i++] = 'N';
					ultimate_grid[18][i++] = 'S';
					ultimate_grid[18][i++] = '!';
					return t;
				}
			}						//return winner
		if (bottom_right[1][0] == bottom_right[1][1])					//if 4 and 5 are same 
			if (bottom_right[1][1] == bottom_right[1][2])					//if 5 and 6 are same
			{
				t = bottom_right[1][0];
				if (t != 0)
				{
					ultimate_score[2][2]=t;
					i = 31;
					ultimate_grid[18][i++] = t;
					ultimate_grid[18][i++] = ' ';
					ultimate_grid[18][i++] = 'W';
					ultimate_grid[18][i++] = 'I';
					ultimate_grid[18][i++] = 'N';
					ultimate_grid[18][i++] = 'S';
					ultimate_grid[18][i++] = '!';
					return t;
				}
			}							//return winner
		if (bottom_right[2][0] == bottom_right[2][1])					//if 7 and 8 are same
			if (bottom_right[2][1] == bottom_right[2][2])					//if 8 and 9 are same
			{
				t = bottom_right[2][0];
				if (t != 0)
				{
					ultimate_score[2][2]=t;
					i = 31;
					ultimate_grid[18][i++] = t;
					ultimate_grid[18][i++] = ' ';
					ultimate_grid[18][i++] = 'W';
					ultimate_grid[18][i++] = 'I';
					ultimate_grid[18][i++] = 'N';
					ultimate_grid[18][i++] = 'S';
					ultimate_grid[18][i++] = '!';
					return t;
				}
			}							//return winner

		/******Vertical Check******/
		if (bottom_right[0][0] == bottom_right[1][0])					//if 1 and 4 are same
			if (bottom_right[1][0] == bottom_right[2][0])					//if 4 and 7 are same
			{
				t = bottom_right[0][0];
				if (t != 0)
				{
					ultimate_score[2][2]=t;
					i = 31;
					ultimate_grid[18][i++] = t;
					ultimate_grid[18][i++] = ' ';
					ultimate_grid[18][i++] = 'W';
					ultimate_grid[18][i++] = 'I';
					ultimate_grid[18][i++] = 'N';
					ultimate_grid[18][i++] = 'S';
					ultimate_grid[18][i++] = '!';
					return t;
				}
			}						//return winner
		if (bottom_right[0][1] == bottom_right[1][1])					//if 2 and 5 are same
			if (bottom_right[1][1] == bottom_right[2][1])					//if 5 and 8 are same
			{
				t = bottom_right[0][1];
				if (t != 0)
				{
					ultimate_score[2][2]=t;
					i = 31;
					ultimate_grid[18][i++] = t;
					ultimate_grid[18][i++] = ' ';
					ultimate_grid[18][i++] = 'W';
					ultimate_grid[18][i++] = 'I';
					ultimate_grid[18][i++] = 'N';
					ultimate_grid[18][i++] = 'S';
					ultimate_grid[18][i++] = '!';
					return t;
				}
			}						//return winner
		if (bottom_right[0][2] == bottom_right[1][2])					//if 3 and 6 are same
			if (bottom_right[1][2] == bottom_right[2][2])					//if 6 and 9 are same
			{
				t = bottom_right[0][2];
				if (t != 0)
				{
					ultimate_score[2][2]=t;
					i = 31;
					ultimate_grid[18][i++] = t;
					ultimate_grid[18][i++] = ' ';
					ultimate_grid[18][i++] = 'W';
					ultimate_grid[18][i++] = 'I';
					ultimate_grid[18][i++] = 'N';
					ultimate_grid[18][i++] = 'S';
					ultimate_grid[18][i++] = '!';
					return t;
				}
			}								//return winner

		/******Diagonal Check******/
		if (bottom_right[0][0] == bottom_right[1][1])					//if 1 and 5 are same
			if (bottom_right[1][1] == bottom_right[2][2])					//if 5 and 9 are same
			{
				t = bottom_right[0][0];
				if (t != 0)
				{
					ultimate_score[2][2]=t;
					i = 31;
					ultimate_grid[18][i++] = t;
					ultimate_grid[18][i++] = ' ';
					ultimate_grid[18][i++] = 'W';
					ultimate_grid[18][i++] = 'I';
					ultimate_grid[18][i++] = 'N';
					ultimate_grid[18][i++] = 'S';
					ultimate_grid[18][i++] = '!';
					return t;
				}
			}								//return winner
		if (bottom_right[0][2] == bottom_right[1][1])					//if 3 and 5 are same
			if (bottom_right[1][1] == bottom_right[2][0])					//if 5 and 7 are same
			{
				t = bottom_right[0][2];
				if (t != 0)
				{
					ultimate_score[2][2]=t;
					i = 31;
					ultimate_grid[18][i++] = t;
					ultimate_grid[18][i++] = ' ';
					ultimate_grid[18][i++] = 'W';
					ultimate_grid[18][i++] = 'I';
					ultimate_grid[18][i++] = 'N';
					ultimate_grid[18][i++] = 'S';
					ultimate_grid[18][i++] = '!';
					return t;
				}
			}								//return winner

		ultimate_score[2][2]=t;										//return the winner or 0 if none
		return t;
	}												//end
	break;
	default: return 0;
	}
	return 0;
}

/*right now:

run test drive

*/