#include <stdio.h>
#include <stdlib.h> 
#include <locale.h>
#include <time.h>
#include <Windows.h>
#include <conio.h>
#include "tic_tac_toe.h" 
#include "sapper.h" 
#include "cards.h"

#define RUS

#define COUNT_OF_CARDS 16
#define COUPLE 8 
#define FIRST 1
#define SECOND 2

void print_main_menu() {
    system("cls");
#ifdef RUS
    printf("ГЛАВНОЕ МЕНЮ \n");
    printf("0 - выход из игры \n");
    printf("1 - играть \n");
    printf("2 - настройки \n");
    printf("Ваш выбор: \n");
#else
    printf("MAIN MENU \n");
    printf("0 - exit \n");
    printf("1 - game \n");
    printf("2 - settings \n");
    printf("Your choose: \n");
#endif
}

void print_game_menu() {
    system("cls");
#ifdef RUS
    printf("0 - выход из игры \n");
    printf("1 - сюжетная игра \n");
    printf("2 - угадайка \n");
    printf("3 - крестики-нолики \n");
    printf("4 - сапёр \n");
    printf("5 - пары \n");
    printf("<любая другая цифра> - назад \n");
    printf("Ваш выбор: \n");
#else
    printf("0 - exit \n");
    printf("1 - story game \n");
    printf("2 - guess game \n");
    printf("3 - tic-tac-toe \n");
    printf("4 - sapper \n");
    printf("5 - cards \n");
    printf("<any another key> - back \n");
    printf("Your choose: \n");
#endif
}

void print_settings_menu() {
    system("cls");
#ifdef RUS
    printf("НАСТРОЙКИ МЕНЮ \n");
    printf("0 - выход из меню настроек \n");
    printf("1 - изменить цвет \n");
    printf("2 - изменить размер \n");
    printf("Ваш выбор: \n");
#else
    printf("SETTINGS MENU \n");
    printf("0 - exit \n");
    printf("1 - change color\n");
    printf("2 - change size\n");
    printf("Your choose: \n");
#endif
}

void press_for_continue() {
#ifdef RUS
    printf("Чтобы продолжить игру, нажмите на любую клавишу... \n");
#else
    printf("For continue, press any key... \n");
#endif
    getchar(); getchar();
}

int start_game_menu() {
    int user, _isExit, isBack;
    while (1) {
        print_game_menu();
        scanf_s("%d", &user);
        isBack = 0, _isExit = 0;
        switch (user) {
        case 1:
            start_story_game();
            break;
        case 2:
            start_guess_game();
            break;
        case 3:
            start_tic_tac_toe();
            break;
        case 4:
            start_sapper();
            break;
        case 5:
            start_cards();
            break;
        case 0:
            _isExit = 1;
            break;
        default:
            isBack = 1;
            break;
        }
        if (_isExit || isBack) { break; }
        press_for_continue(); 
    }
    return _isExit;
}

int start_settings_menu() {
    int user, _isExit = 0, isBack = 0;
#ifdef RUS
    setlocale(LC_ALL, "rus");
#endif
    srand(time(0));

    while (1) {
        print_settings_menu();
        scanf_s("%d", &user);
        switch (user) {
        case 1:
            color_change();
            break;
        case 2:
            size_change();
            break;
        case 0:
            _isExit = 1;
            break;
        default:
            isBack = 1;
            break;
        }
        if (_isExit || isBack) break;
    }
    return 0;
}

int color_change() {
    int a, b, c;

    system("cls");
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

    printf("Введите значения цвета для шрифта и фона: \n");
    scanf_s("%d %d %d", &a, &b, &c);
    SetConsoleTextAttribute(console, a * b + c);
   
    system("cls");
    system("pause");

    getchar(); getchar();
    
    return 0;
}
void print_size() {
    system("cls");
#ifdef RUS
    printf("НАСТРОЙКИ РАЗМЕРА \n");
    printf("0 - выход \n");
    printf("1 - маленький \n");
    printf("2 - средний \n");
    printf("3 - большой \n");
    printf("Ваш выбор: \n");
#else
    printf("SETTINGS SIZE \n");
    printf("0 - exit \n");
    printf("1 - small\n");
    printf("2 - medium \n");
    printf("3 - big\n");
    printf("Your choose: \n");
#endif
}
int size_change() {
    system("cls");
    int diff_size;
    print_size();
    scanf_s("%d", &diff_size);

    switch (diff_size) {
    case 1:
        choice_size(50, 25);
        system("cls");
        break;
    case 2:
        choice_size(80, 40);
        system("cls");
        break;
    case 3:
        choice_size(100, 50);
        system("cls");
        break;
    }
    return 0;
}
void resetBuffer() {
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

    COORD size;
    size.X = 0;
    size.Y = 0;
    SetConsoleScreenBufferSize(console, size);

    SMALL_RECT rect;
    rect.Right = 0;
    rect.Bottom = 0;
    rect.Left = 0;
    rect.Top = 0;
    SetConsoleWindowInfo(console, TRUE, &rect);
}
int choice_size(int size_x, int size_y) {
    resetBuffer(); //сбрасывает размеры консоли
    system("title Arcade Game");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD size;
    size.X = size_x;
    size.Y = size_y;

    SMALL_RECT rect;
    rect.Right = size.X - 1;
    rect.Bottom = size.Y - 1;
    rect.Left = rect.Top = 0;

    SetConsoleScreenBufferSize(console, size);
    SetConsoleWindowInfo(console, TRUE, &rect);
}

int generate_rand_chance() {
    return 1 + rand() % 100;
}
void print_bonus_image()
{
    printf(" ______      ________     _        _   _        _      ______ \n");
    printf("|      |    /        \\    |\\       |  |          |    /      \n");
    printf("|      |   /          \\   | \\      |  |          |    |       \n");
    printf("|     /    |          |   |  \\     |  |          |    |        \n");
    printf("|____/     |          |   |   \\    |  |          |     \\_____        \n");
    printf("|     \\    |          |   |    \\   |  |          |           \\ \n");
    printf("|      \\   |          |   |     \\  |  |          |            |\n");
    printf("|      /    \\        /    |      \\ |   \\        /             |\n");
    printf("|_____/      \\______/     |       \\|    \\______/      _______/\n");
}
void print_goodbye() {

    printf("\t ______     _       _   ______    \n");
    printf("\t|      |    \\      /   |                \n");
    printf("\t|      |     \\    /    |            \n");
    printf("\t|     /       \\  /     |             \n");
    printf("\t|____/         \\/      |_____ \n");
    printf("\t|     \\        |       |               \n");
    printf("\t|      \\       |       |              \n");
    printf("\t|      /       |       |             \n");
    printf("\t|_____/        |       |______  \n");
}
void print_two_doors() {
#ifdef RUS
    printf(" \t \t Какую пещеру ты выберешь, чтобы вернуться домой? \n");
#else
    printf("\t\t Which cave will you choose to return home to? \n");
#endif
    printf("                ____                                        ____ \n");
    printf("               (    )                                      (    ) \n");
    printf("              /      \\                                    /      \\ \n");
    printf("             |        |                                  |        | \n");
    printf("            /          \\                                /          \\ \n");
    printf("           |            |                              |            | \n");
    printf("          /              \\                            /              \\ \n");
    printf("         |                |                          |                | \n");
    printf("        /        / \\       \\                        /        / \\       \\ \n");
    printf("       |       _| 1 |_      |                      |       _| 2 |_      | \n");
    printf("      /      (|      |)      \\                    /      (|      |)      \\ \n");
    printf("     |       (|      |)       |                  |       (|      |)       | \n");
    printf("    /        (|      |)        \\                /        (|      |)        \\ \n");
    printf("   |         (|      |)         |              |         (|      |)         | \n");
    printf("  /          (|      |)          \\            /          (|      |)          \\ \n");
    printf(" |===========(|______|)===========|          |===========(|______|)===========|  \n");
}
void print_choice() {
#ifdef RUS
    printf("\t Вы уверены ? Нажми 'a' или 'r'. \n ");
    printf("\t \t Ваш выбор: ");
#else
    printf("\t Are you sure ? Press 'a' or 'r'. \n ");
    printf("\t\t is your choice:");
#endif
}
void print_monster() {
#ifdef RUS
    printf("\t Ты забрел в пещеру к монстру. \n");
#else
    printf("\t You wandered into the cave of a monster. \n");
#endif
    printf("\t     ^    (#)    ^   \n");
    printf("\t    (    > W <    )    \n");
    printf("\t     / >        < \\    \n");
    printf("\t     \\            /     \n");
    printf("\t       `'--'||--'` \n");
}
void print_exit() {
#ifdef RUS
    printf("Ты нашёл секретный тоннель, позволяющий избежать столкновения с монстром. Беги! \n");
#else
    printf("You have found a secret tunnel that allows you to avoid a collision with a monster. Run! \n");
#endif
    printf("\t          _-_-_-_-_-_\n");
    printf("\t         |'         '|\n");
    printf("\t        (             )\n");
    printf("\t       /'             '\\ \n");
    printf("\t      (                 )\n");
    printf("\t     /        (@)        \\ \n");
    printf("\t    (        (   )        )\n");
    printf("\t   ||       (     )       || \n");
    printf("\t   (       (       )       )\n");
    printf("\t  /|_-_-_-_-_-_-_-_-_-_-_-_|\\ \n");
}
void print_fight() {
#ifdef RUS
    printf("\t Ты нанес удар по монстру. Так держать! \n");
#else
    printf("\t You hit the monster. Keep it up ! \n");
#endif
    printf("\t \t           _ \n");
    printf("\t \t       _  / \\  _\n");
    printf("\t \t   _  / \\|   |/ \\\n");
    printf("\t \t  / \\|   |   |   ||\\\n");
    printf("\t \t |   |   |   |   | \\>\n");
    printf("\t \t |   |   |   |   |   \\\n");
    printf("\t \t | -   -   -   - |)   )\n");
    printf("\t \t |                   /\n");
    printf("\t \t \\                  /\n");
    printf("\t \t  \\                /\n");
    printf("\t \t   \\              /\n");
    printf("\t \t    \\            /\n");
}
void print_kill_monster() {
#ifdef RUS
    printf("\t Поздравляю! Ты убил монстра, жившего в этой пещере. \n");
#else
    printf("\t Congratulations! You killed the monster that lived in this cave. \n"); 
#endif
    printf("\t     ^    (#)    ^   \n");
    printf("\t    (    X _ X    )    \n");
    printf("\t     / >        < \\    \n");
    printf("\t     \\            /     \n");
    printf("\t       `'--'||--'` \n");
}

int start_story_game() {

    int open, chance, gold, hp_people, hp_monster, count;
    char action;

    open = 0, chance = 0, gold = 15, count = 0, hp_people = 5, hp_monster = 3;
    action = ' ';

    system("cls");
    setlocale(LC_ALL, "rus");
    srand(time(0));

    printf("\t \t \t \tДобро пожаловать!  \n");

    while (hp_people > 1) { 
        while (1) {
            print_two_doors();
            printf("\t \t \t Уже определились? Ваш выбор:");
            scanf_s("%d", &open);
            system("cls");

            chance = generate_rand_chance();
            if (chance <= 50) {
                print_choice();
                getchar();
                action = getchar();
                if (action == 'a') {
                    hp_people--;
                    system("cls");
                    print_monster();
                    printf("\t Теперь твоё здоровье: %d \n", hp_people);
                }
                if (hp_people < 1) {
                    system("cls"); 
                    printf(" К сожалению, тебя убил монстр, живущий в этой пещере. \n"); 
                    print_goodbye();  
                    return 0;
                    break;
                }
                if (action == 'r') {
                    hp_monster--; 
                    system("cls"); 
                    print_fight(); 
                    printf("\t Теперь здоровье монстра: %d \n", hp_monster);
                }
                if (hp_monster < 1) {
                    system("cls"); 
                    print_kill_monster(); 
                    return 1;
                    break;
                }
            }
            else {
                print_choice(); 
                getchar(); 
                action = getchar(); 
                count = count + gold;
                if (action == 'a') {
                    if (count < 45) {
                        system("cls"); 
                        printf("\t     Найдено %d бонусных очков. \n", gold);
                        printf("\t В твоей копилке %d бонусных очков. \n", count);
                        print_bonus_image(count); 
                    }
                }
                if (count >= 45) {
                    system("cls"); 
                    printf("Ты набрал %d бонусов. Теперь ты можешь откупиться у монстра. Прощай!\n", count); 
                    printf(" \n"); 
                    print_goodbye(); 
                    return 1;
                    break;
                }
                if (action == 'r') {
                    system("cls"); 
                    print_exit(); 
                    return 1;
                    break;
                }
            }
            system("pause");
            system("cls");
        }
        return 0;
        press_for_continue(); 
    }
}
#define DEBUG
int start_guess_game() {
    system("cls");
    int random_num = 0, guessed_num = 0, counter = 0;

    srand(time(0));
    random_num = 1 + rand() % 100;
#ifdef DEBUG
    printf("Правильное число: %d\n", random_num);
#endif
#ifdef RUS
    printf("Угадай моё число!\n");
    while (1)
    {
        counter++;
        Sleep(1000);
        system("cls");
        printf("Введите число: ");
        scanf_s("%d", &guessed_num);
        system("cls");
        if (guessed_num == random_num)
        {
            printf("Ты правильно угадал с %d попытки! Поздравляю!\n", counter);
            return 1;
            break;
        }
        if (counter == 10 && (guessed_num != random_num)) {
            printf("Правильное число: %d\n", random_num); 
            printf("Вы не угадали число...\n");
            break;
        }
        if (guessed_num < random_num)
            printf("Ваше предположение слишком низкое. Угадайте еще раз. \n");

        if (guessed_num > random_num)
            printf("Ваше предположение слишком высокое. Угадайте еще раз. \n");


    }
#else
    printf("Guess my number!\n");
    while (1)
    { 
        counter++;
        Sleep(1000);
        system("cls");
        printf("Enter number: ");
        scanf_s("%d", &guessed_num);
        system("cls");
        if (guessed_num == random_num)
        {
            printf("You guessed correctly in %d tries! Congratulations!\n", counter);
            return 1;
            break;
        }

        if (guessed_num < random_num)
            printf("Your guess is too low. Guess again. \n");

        if (guessed_num > random_num)
            printf("Your guess is too high. Guess again. \n");

        if (counter == 10) {
            printf("You didn't guess the number...\n");
            break;
        }
    }
 
#endif
    return 0;
    press_for_continue();
}

int start_tic_tac_toe() {
    system("cls"); 
    input_field();
    char player_symbol, computer_symbol;
    int turn = start_toss(&player_symbol, &computer_symbol);

#ifdef RUS
    while (1) {
        print_field();
        if (turn == 0) {
            start_user_move(player_symbol);
            if (check_win(player_symbol)) {
                print_field();
                printf("Поздравляем! Вы выиграли!\n");
                break;
            }
            turn = 1; // Меняем ход
        }
        else {
            start_computer_move(computer_symbol);
            if (check_win(computer_symbol)) {
                print_field();
                printf("Компьютер выиграл!\n");
                break;
            }
            turn = 0;
        }

        if (check_end()) {
            print_field();
            printf("Игра закончилась ничьей!\n");
            break;
        }
    }
#else
    while (1) {
        print_field();
        if (turn == 0) {
            start_user_move(player_symbol);
            if (check_win(player_symbol)) {
                print_field();
                printf("Congratulations! You win!\n");
                break;
            }
            turn = 1; // Меняем ход
        }
        else {
            start_computer_move(computer_symbol);
            if (check_win(computer_symbol)) {
                print_field();
                printf("Computer win!\n");
                break;
            }
            turn = 0;
        }

        if (check_end()) {
            print_field();
            printf("Draw!\n");
            break;
        }
    }
#endif
}
int start_sapper() {
    system("cls"); 
    start_main_menu(); 
}
int start_cards() {
    system("cls");
    char user_field[COUNT_OF_CARDS];
    char game_field[COUNT_OF_CARDS];  
    char symbols[] = { '>', '@', '#', '$', '%', '&', '*', '<' };
    int flag = 0;
    int first_card = 0;
    int second_card = 0;
    int count_couple_cards = 0;
    int game_over = 0; // Флаг окончания игры

    srand(time(NULL)); 

    completion(user_field, game_field);
    generate_game_field(user_field, game_field, symbols, COUNT_OF_CARDS);
    // Установка начального времени
    int start_time = (int)time(NULL);
    while (!game_over) { // Продолжаем, пока флаг окончания игры равен 0
        main_rec(user_field, game_field, symbols, &flag, first_card, second_card, count_couple_cards, &start_time, &game_over);
    }
    printf("Игра окончена!!!\n");
}
int main() {
    int user, isExit = 0, isWin, isBack = 0;
#ifdef RUS
    setlocale(LC_ALL, "rus");
#endif
    srand(time(0));

    while (1) {
        print_main_menu(); 
        scanf_s("%d", &user);
        switch (user) {
        case 1:
            start_game_menu();
            break;
        case 2:
            start_settings_menu();
            break;
        case 0:
            isExit = 1;
            break;
        default:
            break;
        }
        if (isExit) break;
    }
    return 0;
} 