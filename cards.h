#pragma once
void completion(char* user_field, char* game_field);
void text_win();
void text_lose();
void swap_cards(char* first_num, char* second_num);
void shuffle_cards(char* user_field, int size);
void generate_game_field(char* user_field, char* game_field, char* symbols, int size);
void print_field_cards(char* game_field, int size);
void count_time(int total_time, int attempts);
void main_rec(char* user_field, char* game_field, char* symbols, int* flag, int first_card, int second_card, int count_couple_cards, int* start_time, int* game_over);