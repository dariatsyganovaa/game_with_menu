#include "cards.h"
#include <time.h>

#define COUNT_OF_CARDS 16
#define COUPLE 8 
#define FIRST 1
#define SECOND 2

void completion(char* user_field, char* game_field) {
    for (int i = 0; i < COUNT_OF_CARDS; i++) {
        user_field[i] = ' ';
        game_field[i] = ' ';
    }
}
void text_win() {
    printf("Выбранные карты являются парой!");
    Sleep(1000);
    system("cls");
}
void text_lose() {
    printf("Выбранные карты не являются парой!\n");
    Sleep(1000);
    system("cls");
    for (int i = 1; i < 4; i++) {
        printf("Карты закроются через %d...\n", 4 - i);
        Sleep(1000);
        system("cls");
    }
}
void swap_cards(char* first_num, char* second_num) {
    char tmp = *first_num;
    *first_num = *second_num;
    *second_num = tmp;
}
void shuffle_cards(char* user_field, int size) {
    for (int i = 0; i < size; i++) {
        int rand_i = rand() % size;
        swap_cards(&user_field[i], &user_field[rand_i]);
    }
}
void generate_game_field(char* user_field, char* game_field, char* symbols, int size) {
    for (int i = 0, j = 0; i < size; i += 2, j++) {
        user_field[i] = symbols[j];
        user_field[i + 1] = symbols[j];
    }
    shuffle_cards(user_field, size);
}
void print_field_cards(char* game_field, int size) {
    printf("|  ");
    for (int i = 0; i < size; i++) {
        if (i == COUNT_OF_CARDS / 2) {
            printf(" |\n");
            printf("|   ---  ---  ---  ---  ---  ---  ---  ---  |\n");
            printf("|-------------------------------------------|\n");
            printf("|    9    10   11   12   13   14   15   16  |\n");
            printf("|   ---  ---  ---  ---  ---  ---  ---  ---  |\n");
            printf("|  ");
            printf(" |%c| ", game_field[i]);
        }
        else {
            printf(" |%c| ", game_field[i]);
        }
    }
    printf(" |\n");
}
void count_time(int total_time, int attempts) {
    double average_time = (double)total_time / attempts;

    printf("Время игры: %d секунд\n", total_time);
    printf("Среднее время на попытку: %.2f секунд\n", average_time);

    if (average_time < 5.0) {
        printf("Результат: Отлично\n");
    }
    else if (average_time < 10.0) {
        printf("Результат: Хорошо\n");
    }
    else {
        printf("Результат: Плохо\n");
    }
}
void main_rec(char* user_field, char* game_field, char* symbols, int* flag, int first_card, int second_card, int count_couple_cards, int* start_time, int* game_over) {
    static int attempts = 0; // Счетчик попыток
    system("cls");
    printf(" -------------------------------------------\n");
    printf("|    1    2    3    4    5    6    7    8   |\n");
    printf("|   ---  ---  ---  ---  ---  ---  ---  ---  |\n");
    print_field_cards(game_field, COUNT_OF_CARDS);
    printf("|   ---  ---  ---  ---  ---  ---  ---  ---  |\n");
    printf(" -------------------------------------------\n");

    if (*flag == 0) {
        printf("Введите номер первой карты: ");
        scanf_s("%d", &first_card);
        if (first_card > 0 && first_card <= COUNT_OF_CARDS) {
            if (game_field[first_card - 1] == ' ') {
                *flag = 1; // Изменяем значение по указателю
                game_field[first_card - 1] = user_field[first_card - 1];
                main_rec(user_field, game_field, symbols, flag, first_card, second_card, count_couple_cards, start_time, game_over);
            }
            else {
                printf("Некорректный номер карты, попробуйте снова! ");
                Sleep(3000);
            }
        }
        else {
            printf("Некорректный номер карты, попробуйте снова! ");
        }
    }
    if (*flag == 1) {
        *flag = 0; // Изменяем значение по указателю
        attempts++;
        printf("Введите номер второй карты: ");
        scanf_s("%d", &second_card);
        if (second_card > 0 && second_card <= COUNT_OF_CARDS) {
            if (game_field[second_card - 1] == ' ') {
                game_field[second_card - 1] = user_field[second_card - 1]; // Открываем вторую карту
                if (second_card == first_card) {
                    printf("Карта уже была открыта! Выберите другую! ");
                    Sleep(1000);
                    game_field[second_card - 1] = ' '; // Закрываем вторую карту
                }
                else if (game_field[second_card - 1] == game_field[first_card - 1]) {
                    count_couple_cards++;
                    // Проверка условия победы
                    if (count_couple_cards == COUPLE) { 
                        printf("Ура! Вы верно открыли все карточки!\n");

                        // Подсчет времени и вывод результатов
                        int total_time = (int)time(NULL) - *start_time; //текущее время - время начала игры
                        count_time(total_time, attempts);
                        system("pause");
                        *game_over = 1; // Устанавливаем флаг окончания игры
                        return; // Завершаем выполнение функции
                    }
                    else {
                        text_win();
                        main_rec(user_field, game_field, symbols, flag, first_card, second_card, count_couple_cards, start_time, game_over);
                    }
                }
                else {
                    *flag = 2; // Изменяем значение по указателю
                    main_rec(user_field, game_field, symbols, flag, first_card, second_card, count_couple_cards, start_time, game_over);
                }
            }
            else {
                printf("Некорректный номер карты, попробуйте снова! ");
                Sleep(3000);
                game_field[first_card - 1] = ' ';
            }
        }
        else {
            printf("Некорректный номер карты, попробуйте снова: ");
        }
    }
    if (*flag == 2) {
        text_lose();
        game_field[first_card - 1] = ' ';
        game_field[second_card - 1] = ' ';
        *flag = 0; // Изменяем значение по указателю
        main_rec(user_field, game_field, symbols, flag, first_card, second_card, count_couple_cards, start_time, game_over);
    }
}