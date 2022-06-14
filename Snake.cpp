//
//  Snake.cpp
//  cpp_algo
//
//  
//

#include "Snake.hpp"
#include <stdlib.h>
#include <string>

using namespace std;
//constructor
Snake::Snake(int num) {
    this -> top = -1;
    this -> snakeBody = new SnakeBody[num];
    this -> dir_x = 0;
    this -> dir_y = -1;
}
//getter
int Snake::getTop() const{
    return this -> top;
}

int Snake::getDirX() const{
    return this -> dir_x;
}

int Snake::getDirY() const{
    return this -> dir_y;
}

SnakeBody* Snake::getSnakeBody() const{
    return this -> snakeBody;
}

void Snake::getSnakePos(int num, int *x, int *y) const{
    *x = this -> snakeBody[num].getX();
    *y = this -> snakeBody[num].getY();
}
//setter
void Snake::setTop(int top) {
    this -> top = top;
}

void Snake::setDirection(int x, int y) {
    this -> dir_x = x;
    this -> dir_y = y;
}

//push
void Snake::snakePush(int x, int y, const char* shape) {
    this -> top++;
    this -> snakeBody[this -> top].setX(x);
    this -> snakeBody[this -> top].setY(y);
    this -> snakeBody[this -> top].setShape(shape);
}
//pop
void Snake::snakePop() {
    this -> top--;
}
//move
void Snake::snakeMove() {
    for (int i = this -> top; i > 0; i--) {
        this -> snakeBody[i].setX(this -> snakeBody[i-1].getX());
        this -> snakeBody[i].setY(this -> snakeBody[i-1].getY());
        if (i == 1) break;
        this -> snakeBody[i].setShape(this -> snakeBody[i-1].getShape());
    }
    
    this -> snakeBody[0].setX(this -> snakeBody[0].getX() + this -> dir_x);
    this -> snakeBody[0].setY(this -> snakeBody[0].getY() + this -> dir_y);
}
//event
int Snake::eventDeath() const{
    int headX, headY;
    headX = this -> snakeBody[0].getX();
    headY = this -> snakeBody[0].getY();
    
    for (int i = 1; i <= this -> top; i++) {
        if (this -> snakeBody[i].getX() == headX && this -> snakeBody[i].getY() == headY) {
            return 1;
        }
    }
    
    return 0;
}

void Snake::getHeadPos(int *x, int *y) const{
    *x = this -> snakeBody[0].getX();
    *y = this -> snakeBody[0].getY();
}

void Snake::setHeadPos(int x, int y) {
    this -> snakeBody[0].setX(x);
    this -> snakeBody[0].setY(y);
}
