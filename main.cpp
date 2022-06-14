#include <ncurses.h>
//#include <curses.h> 윈도우에서 동작시 주석을 풀어주시고 위에 헤더파일은 주석처리 해주세요
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
    mvprintw(17, 37, "HOW TO");
    mvprintw(19, 37, "EXIT");
}

int main(){
    int mode = 0, offset = 15;
    int keyNum, start = 0;;
    
    Game game(N, M);

    initscr();
    
    resize_term(24, 80);

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
                mode = (mode == 0) ? 2 : mode - 1;
                break;
            case KEY_DOWN:
                mode = (mode == 2) ? 0 : mode + 1;
                break;
            case 32:
                if (mode == 2) {
                    endwin();
                    return 0;
                }
                start = 1;
                break;
        }
        if(start) {
            game.setMode(mode);
            game.gameInit(start);
            start = game.GameStart();
        }
    }
    
    return 0;
}
