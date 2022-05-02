//
//  SnakeBody.cpp
//  cpp_algo
//
//
//

#include "SnakeBody.hpp"
#include <stdlib.h>
#include <string>

using namespace std;
//constructor
SnakeBody::SnakeBody(int x, int y, char* shape) {
    this -> x = x;
    this -> y = y;
    this -> shape = shape;
}

SnakeBody::SnakeBody() {
    this -> x = 0;
    this -> y = 0;
    this -> shape = "";
}
//getter
int SnakeBody::getX() {
    return this -> x;
}

int SnakeBody::getY() {
    return this -> y;
}

char* SnakeBody::getShape() {
    return this -> shape;
}
//setter
void SnakeBody::setX(int x) {
    this -> x = x;
}

void SnakeBody::setY(int y) {
    this -> y = y;
}

void SnakeBody::setShape(char* shape) {
    this -> shape = shape;
}

