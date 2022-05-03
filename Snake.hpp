//
//  Snake.hpp
//  cpp_algo
//
//  Created by 이승원 on 2022/04/29.
//

#ifndef Snake_hpp
#define Snake_hpp

#include <stdio.h>
#include <stdlib.h>
#include "SnakeBody.hpp"

class Snake {
    
private:
    int top, dir_x, dir_y;
    SnakeBody *snakeBody;
    
public:
    //constructor
    Snake(int num);
    //getter
    int getTop();
    int getDirX();
    int getDirY();
    SnakeBody* getSnakeBody();
    void getHeadPos(int *x, int *y);
    void getSnakePos(int num, int *x, int *y);
    //setter
    void setTop(int top);
    void setDirection(int x, int y);
    void setHeadPos(int x, int y);
    //push
    void snakePush(int x, int y, char* shape);
    //pop
    void snakePop();
    //event
    void snakeMove();
    int eventDeath();

    //test
    void test();
    
};

#endif /* Snake_hpp */
