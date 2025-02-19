#pragma once
void input_field();
void print_field();
int start_toss(char* player_symbol, char* computer_symbol);
void start_user_move(char player_symbol);
void start_computer_move(char computer_symbol);
int check_win(char player);
int check_end();