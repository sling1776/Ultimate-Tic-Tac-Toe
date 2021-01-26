#pragma once
char grid_normal[9][11];

char get_position(char turn);

char get_input();

void normal_game();

void grid_normal_initializer();

void print_normal_grid();

char check_grid_pos(int hor, int vert);

void print_players();

void curs_to_initial();

void move_curs_up();

void move_curs_down();

void move_curs_right();

void move_curs_left();

char x_o_normal_grid[3][3];

char check_win();