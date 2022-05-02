#include <ncurses.h>
#include <cstring>
#include <iostream>
#include <cstring>
#include "Game.hpp"

#define N 22
#define M 40


void mainMenu() {
    char *menu_1 = "             _____             __           ______";
    char *menu_2 = "            / ___/____  ____ _/ /_____     / ____/___ _____ ___  ___";
    char *menu_3 = "            \\__ \\/ __ \\/ __ `/ //_/ _ \\   / / __/ __ `/ __ `__ \\/ _ \\";
    char *menu_4 = "           ___/ / / / / /_/ / ,< /  __/  / /_/ / /_/ / / / / / /  __/";
    char *menu_5 = "          /____/_/ /_/\\__,_/_/|_|\\___/   \\____/\\__,_/_/ /_/ /_/\\___/";
    
    //print snake game
    mvprintw(2, 0, "%s", menu_1);
    mvprintw(3, 0, "%s", menu_2);
    mvprintw(4, 0, "%s", menu_3);
    mvprintw(5, 0, "%s", menu_4);
    mvprintw(6, 0, "%s", menu_5);
    //print select menu
    mvprintw(11, 30, "PRESS THE SPACEBAR");
    mvprintw(15, 37, "START");
    mvprintw(17, 37, "RANKING");
}

int main(){
    int mode = 0, offset = 15;
    int keyNum, start = 0;;
    
    Game game(N, M);

    initscr();

    curs_set(false);
    noecho();
    nodelay(stdscr, TRUE);
    keypad(stdscr, TRUE);

    while(true) {

        clear();
        mainMenu();

        mvprintw(offset + (mode * 2), 33, "->");

        keyNum = getch();

        switch (keyNum) {
            case KEY_UP:
            case KEY_DOWN:
                mode = mode ? 0 : 1;
                break;
            case 32:
                start = 1;
                break;
        }
        if(start) {
            game.setMode(mode);
            game.gameInit(start == 0 ? 1 : start);
            start = game.GameStart();
        }
    }
    
    return 0;
}