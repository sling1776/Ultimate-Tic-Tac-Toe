#pragma once
char ultimate_grid[27][41];

char ultimate_score[3][3];

void ultimate_game();

void display_ultimate_grid();

void initialize_ultimate_grid();

char top_left[3][3];

char top_middle[3][3];

char top_right[3][3];

char middle_left[3][3];

char middle_middle[3][3];

char middle_right[3][3];

char bottom_left[3][3];

char bottom_middle[3][3];

char bottom_right[3][3];

void display_player_ul_pos();

void move_curs_tlc();

void move_curs_tmc();

void move_curs_trc();

void move_curs_mlc();

void move_curs_mmc();

void move_curs_mrc();

void move_curs_blc();

void move_curs_bmc();

void move_curs_brc();

void print_players_ult(int box);

int get_position_ult_first(char turn);

char get_position_ult_norm(char turn, int pos);

int check_grid_pos_ult(int horiz, int vert, int first, int pos);

int next_large_box(int hor, int vert);

int is_full(int large_box_position);

char check_win_individual_ult(int pos);

char check_win_ult(int pos);