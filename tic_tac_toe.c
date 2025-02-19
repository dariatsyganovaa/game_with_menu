#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h> 
#include <locale.h>

#define SIZE 3

char field[SIZE][SIZE];

void input_field() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            field[i][j] = ' ';
        }
    }
}

void print_field() {
    printf("   1   2   3 \n");
    printf("  -------------\n");
    for (int i = 0; i < SIZE; i++) {
        printf("%d |", i + 1);
        for (int j = 0; j < SIZE; j++) {
            printf(" %c |", field[i][j]);
        }
        printf("\n  -------------\n");
    }
}

int start_toss(char* player_symbol, char* computer_symbol) {
    int chance = rand() % 100 + 1;
    if (chance < 50) {
        printf("Вы ходите первым! \n");
        *player_symbol = 'X';
        *computer_symbol = 'O';
        return 0;
    }
    else {
        printf("Вы ходите вторым! \n");
        *player_symbol = 'O';
        *computer_symbol = 'X';
        return 1;
    }
}

void start_user_move(char player_symbol) {
    int n, m;
    while (1) {
        printf("Ваш ход (введите номер строки и столбца через пробел): ");
        scanf_s("%d %d", &n, &m);
        n--; //приводим к правильным индексам массива
        m--;
        if (n >= 0 && n < SIZE && m >= 0 && m < SIZE && field[n][m] == ' ') {
            field[n][m] = player_symbol;
            break;
        }
        else {
            printf("Некорректный ход! Попробуйте снова! \n");
        }
    }
}
void start_computer_move(char computer_symbol) {
    printf("Компьютер думает, какой ход сделать следующим ... \n");
    Sleep(1000);
    if (field[1][1] == ' ') {
        field[1][1] = computer_symbol;
        return;
    }
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (field[i][j] == ' ') {
                field[i][j] = computer_symbol;
                if (check_win(computer_symbol)) return;
                field[i][j] = ' '; //возвращаем ячейку в исходное состояние, чтобы продолжить проверку других ячеек.
            }
        }
    }
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (field[i][j] == ' ') {
                field[i][j] = (computer_symbol == 'O' ? 'X' : 'O'); // симуляция хода пользователя (если компьютер — 'O', то ставим 'X', и наоборот) 
                if (check_win((computer_symbol == 'O' ? 'X' : 'O'))) { 
                    field[i][j] = computer_symbol; // заблокировать пользователя
                    return;
                }
                field[i][j] = ' ';
            }
        }
    }
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (field[i][j] == ' ') {
                field[i][j] = computer_symbol; 
                return;
            }
        }
    }
}

int check_win(char player_symbol) {
    for (int i = 0; i < SIZE; i++) { //проверка, заполнена ли текущая строка символом игрока
        if ((field[i][0] == player_symbol && field[i][1] == player_symbol && field[i][2] == player_symbol) ||
            (field[0][i] == player_symbol && field[1][i] == player_symbol && field[2][i] == player_symbol)) {
            return 1;
        }
    }
    if ((field[0][0] == player_symbol && field[1][1] == player_symbol && field[2][2] == player_symbol) ||
        (field[0][2] == player_symbol && field[1][1] == player_symbol && field[2][0] == player_symbol)) {
        return 1;
    }
    return 0;
}

int check_end() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (field[i][j] == ' ') {
                return 0; // если найдена пустая ячейка, игра не закончена
            }
        }
    }
    return 1;
}
