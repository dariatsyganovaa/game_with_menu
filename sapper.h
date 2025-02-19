#pragma once
#define N 16 
#define M 16 

int start_main_menu();
void print_main_menu_sapper();
void start_game();
void init_game_field(int game_field[N][M]);
void init_user_field(char user_field[N][M]);
void print_user_field(char user_field[N][M]);
void print_game_field(int game_field[N][M]);
int rand_generation(int min, int max);
void shuffle_bombs(int game_field[N][M]);
void calculate_neighbours_bombs(int game_field[N][M]);
int opening_cell(int i, int j, int game_field[N][M], char user_field[N][M], int* open_cells, int* flag);
char input_keyboard(char user_field[N][M], int* i, int* j, int flag);
void flags(int* flag, char user_field[N][M], int i, int j, int game_field[N][M], int* correct);