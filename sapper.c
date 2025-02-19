#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include "sapper.h"

#define N 16
#define M 16
#define BOMB -1
#define PERSENT_BOMB 0.16

#ifdef DEBUG
//init_game_field(game_field);  
//print_game_field(game_field);
for (int i = 0; i < N; i++) {
    for (int j = 0; j < M; j++) {
        printf("| %c %c ", game_field[i][j], "|");
    }
    printf("\n");
}
#endif
int start_main_menu() {
    int user;
    int isExit = 0;
    printf("\t\t\t ДОБРО ПОЖАЛОВАТЬ В ИГРУ САПЕР !!! \n");
    print_main_menu_sapper();
    printf("Ваш выбор: ");
    scanf_s("%d", &user);
    switch (user) {
    case 1:
        start_game();
        break;
    case 0:
        isExit = 1;
        break;
    }
    return isExit;
}
void print_main_menu_sapper() {
    printf("1. Начать игру \n");
    printf("0. Выход \n");
}
void start_game() {
    system("cls");
    int game_field[N][M];
    char user_field[N][M];

    int i, j, open_cells = 0, flag = 0, correct = 0;
    int count = 0;

    init_game_field(game_field);
    init_user_field(user_field);

    while (1) {
        char key = input_keyboard(user_field, &i, &j, flag);
        if (key == 0) {
            printf("Вы вышли из игры! \n");
            return;
        }
        if (key == '\r') {
            if (opening_cell(i, j, game_field, user_field, &open_cells, &flag)) {
                for (int i = 0; i < N; i++) {
                    for (int j = 0; j < M; j++) {
                        if (game_field[i][j] == BOMB) {
                            user_field[i][j] = '*';
                        }
                    }
                }
                print_user_field(user_field);
                break;
            }
        }
        else {
            flags(&flag, user_field, i, j, game_field, &correct);
            if (user_field[i][j] == 3 && game_field[i][j] == BOMB) {
                count++;
            }
            if (count >= N * M * PERSENT_BOMB - 1) {
                printf("Вы верно расставили все флажки! \n");
                return;
            }
        }
        print_user_field(user_field);

        if (open_cells >= N * M - N * M * PERSENT_BOMB) {
            printf("Вы выиграли! \n");
            return;
        }
    }
}
char input_keyboard(char user_field[N][M], int* i, int* j, int flag) {
    char key = 0;
    *i = 0;
    *j = 0;

    while (key != '\r' && key != 'f') {
        char tmp = user_field[*i][*j];
        user_field[*i][*j] = '*';
        print_user_field(user_field);
        printf("Чтобы управлять игрой, используй клавиши w, a, s, d \n");
        printf("Чтобы подтвердить выбор, используй клавишу enter \n");
        printf("Чтобы поставить флаг, используй клавишу f \n");
        printf("Чтобы выйти из игры, используй клавишу esc \n");
        printf("Счётчик флагов: %d \n", flag);
        user_field[*i][*j] = tmp;
        key = _getch();
        system("cls");
        switch (key) {
        case('w'):
            if (*i > 0) {
                (*i)--;
            }
            break;
        case('s'):
            if (*i < N - 1) {
                (*i)++;
            }
            break;
        case('a'):
            if (*j > 0) {
                (*j)--;
            }
            break;
        case('d'):
            if (*j < M - 1) {
                (*j)++;
            }
            break;
        case 27: //esc
            return 0;
        }
    }
    return key;
}
void flags(int* flag, char user_field[N][M], int i, int j, int game_field[N][M], int* correct) {
    if (user_field[i][j] == 3) {
        user_field[i][j] = '-';
        (*flag)--;
        (*correct)--;
    }
    else {
        user_field[i][j] = 3;
        (*flag)++;

        if (game_field[i][j] == BOMB) {
            (*correct)++;
        }
    }

}
void init_user_field(char user_field[N][M]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            user_field[i][j] = '-';
        }
    }
}

void print_user_field(char user_field[N][M]) {
    printf("+");
    for (int m = 0; m < M; m++) {
        printf("---+");
    }
    printf("\n");

    for (int k = 0; k < N; k++) {
        for (int m = 0; m < M; m++) {
            printf("| %c ", user_field[k][m]);
        }
        printf("|\n");

        printf("+");
        for (int m = 0; m < M; m++) {
            printf("---+");
        }
        printf("\n");
    }
}
void init_game_field(int game_field[N][M]) {
    int bombs = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            game_field[i][j] = 0;
            bombs += 1;
            if (bombs <= PERSENT_BOMB * N * M - 1) {
                game_field[i][j] = BOMB;
            }
        }
    }
    shuffle_bombs(game_field);
    calculate_neighbours_bombs(game_field);
}
void print_game_field(int game_field[N][M]) {
    printf("+");
    for (int j = 0; j < M; j++) {
        printf("---+");
    }
    printf("\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            printf("| %d ", game_field[i][j]);
        }
        printf("|\n");
    }
    printf("+");
    for (int j = 0; j < M; j++) {
        printf("---+");
    }
    printf("\n");
}
int rand_generation(int min, int max) {
    return min + rand() % (max - min + 1);
}
void shuffle_bombs(int game_field[N][M]) {
    int rand_i, rand_j;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            rand_i = rand_generation(0, N - 1);
            rand_j = rand_generation(0, M - 1);
            int tmp = game_field[i][j];
            game_field[i][j] = game_field[rand_i][rand_j];
            game_field[rand_i][rand_j] = tmp;
        }
    }
}
void calculate_neighbours_bombs(int game_field[N][M]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            int bombs_count = 0;

            if (game_field[i][j] == BOMB) continue;

            if (i > 0 && game_field[i - 1][j] == BOMB) bombs_count++; //Проверяет верхнюю ячейку(i - 1, j). Условие i > 0 предотвращает выход за пределы массива.
            if (i > 0 && j < M - 1 && game_field[i - 1][j + 1] == BOMB) bombs_count++; //Проверяет верхнюю правую ячейку (i-1, j+1). Условия i > 0 и j < M - 1 предотвращают выход за границы массива.
            if (j < M - 1 && game_field[i][j + 1] == BOMB) bombs_count++; //Проверяет правую ячейку (i, j+1). Условие j < M - 1 предотвращает выход за границы.
            if (i < N - 1 && j < M - 1 && game_field[i + 1][j + 1] == BOMB) bombs_count++; //Проверяет нижнюю правую ячейку (i+1, j+1). Условие i < N - 1 и j < M - 1 предотвращает выход за границы.
            if (i < N - 1 && game_field[i + 1][j] == BOMB) bombs_count++; //Проверяет нижнюю ячейку (i+1, j). Условие i < N - 1 предотвращает выход за пределы.
            if (i < N - 1 && j > 0 && game_field[i + 1][j - 1] == BOMB) bombs_count++; //Проверяет нижнюю левую ячейку (i+1, j-1). Условия i < N - 1 и j > 0 помогают избежать выхода за границы.
            if (j > 0 && game_field[i][j - 1] == BOMB) bombs_count++; //Проверяет левую ячейку (i, j-1). Условие j > 0 предотвращает выход за пределы.
            if (i > 0 && j > 0 && game_field[i - 1][j - 1] == BOMB) bombs_count++; //Проверяет верхнюю левую ячейку (i-1, j-1). Условия i > 0 и j > 0 предотвращают выход за границы.

            game_field[i][j] = bombs_count;
        }
    }
}
int opening_cell(int i, int j, int game_field[N][M], char user_field[N][M], int* open_cells, int* flag) {
    if (user_field[i][j] == '-' || user_field[i][j] == 3) {
        if (game_field[i][j] == BOMB) {
            system("cls");
            printf("Игра окончена, вы попали на бомбу!\n");
            return 1;
        }
        if (game_field[i][j] == 0) {
            user_field[i][j] = game_field[i][j] + '0'; // Преобразование числа в символ
            if (i - 1 >= 0 && j - 1 >= 0 && (user_field[i - 1][j - 1] == '-' || user_field[i - 1][j - 1] == 3)) {
                if (user_field[i - 1][j - 1] == 3) { *flag += 1; }
                opening_cell(i - 1, j - 1, game_field, user_field, open_cells, flag);
            }
            if (i - 1 >= 0 && (user_field[i - 1][j] == '-' || user_field[i - 1][j] == 3)) {
                if (user_field[i - 1][j] == 3) { *flag += 1; }
                opening_cell(i - 1, j, game_field, user_field, open_cells, flag);
            }
            if (i - 1 >= 0 && j + 1 < N && (user_field[i - 1][j + 1] == '-' || user_field[i - 1][j + 1] == 3)) {
                if (user_field[i - 1][j + 1] == 3) { *flag += 1; }
                opening_cell(i - 1, j + 1, game_field, user_field, open_cells, flag);
            }
            if (j + 1 < N && (user_field[i][j + 1] == '-' || user_field[i][j + 1] == 3)) {
                if (user_field[i][j + 1] == 3) { *flag += 1; }
                opening_cell(i, j + 1, game_field, user_field, open_cells, flag);
            }
            if (i + 1 < M && j + 1 < N && (user_field[i + 1][j + 1] == '-' || user_field[i + 1][j + 1] == 3)) {
                if (user_field[i + 1][j + 1] == 3) { *flag += 1; }
                opening_cell(i + 1, j + 1, game_field, user_field, open_cells, flag);
            }
            if (i + 1 < M && (user_field[i + 1][j] == '-' || user_field[i + 1][j] == 3)) {
                if (user_field[i + 1][j] == 3) { *flag += 1; }
                opening_cell(i + 1, j, game_field, user_field, open_cells, flag);
            }
            if (i + 1 < M && j - 1 >= 0 && (user_field[i + 1][j - 1] == '-' || user_field[i + 1][j - 1] == 3)) {
                if (user_field[i + 1][j - 1] == 3) { *flag += 1; }
                opening_cell(i + 1, j - 1, game_field, user_field, open_cells, flag);
            }
            if (j - 1 >= 0 && (user_field[i][j - 1] == '-' || user_field[i][j - 1] == 3)) {
                if (user_field[i][j - 1] == 3) { *flag += 1; }
                opening_cell(i, j - 1, game_field, user_field, open_cells, flag);
            }
        }
        else {
            if (user_field[i][j] == 3) { *flag += 1; }
            user_field[i][j] = game_field[i][j] + '0';
        }
        (*open_cells) += 1;
    }
    return 0;
} 
