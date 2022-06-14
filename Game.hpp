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
    int best, growth, poison, gate, maxLength;
    int gateX_1, gateY_1, gateX_2, gateY_2;
    int active_gate, check_gate, gate_time;
public:
    //constructor
    Game(int row, int column);
    //setter
    void setMode(int mode);
    void setStage(int stage);
    //
    void gameInit(int stage);
    //draw
    void drawMap() const;
    void drawSnake() const;
    void drawScore();
    void drawTodo();
    void drawHowto() const;
    void drawClear() const;
    //move
    void moveSnake();
    int GameStart();
    //evnt
    int eventDeath() const;
    void makeItem();
    void makePotal();
    void potalEvent();
    //timer
};

#endif /* Game_hpp */
