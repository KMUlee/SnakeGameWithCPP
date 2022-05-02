//
//  Game.hpp
//  cpp_algo
//
//  Created by 이승원 on 2022/05/01.
//

#ifndef Game_hpp
#define Game_hpp

#include "Map.hpp"
#include "Snake.hpp"
#include <stdio.h>
#include <ncurses.h>
#include <chrono>
#include <thread>
#include "Item.hpp"

class Game {
    
private:
    Snake *snake;
    int** map;
    Item *item;
    int mode, row, column, stage, end;
    int best, growth, poison, gate;
public:
    //constructor
    Game(int row, int column);
    //setter
    void setMode(int mode);
    void setStage(int stage);
    //
    void gameInit(int stage);
    //draw
    void drawMap();
    void drawSnake();
    void drawScore();
    void drawTodo();
    //move
    void moveSnake();
    int GameStart();
    //evnt
    int eventDeath();
    void makeItem();
    //timer
};

#endif /* Game_hpp */
