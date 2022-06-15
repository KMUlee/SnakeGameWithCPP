#include "SnakeBody.hpp"
#include <stdlib.h>


using namespace std;
//constructor
SnakeBody::SnakeBody(int x, int y, const char *shape) {
    this -> x = x;
    this -> y = y;
    strcpy(this -> shape, shape);
}

SnakeBody::SnakeBody() {
    this -> x = 0;
    this -> y = 0;
    this -> shape = new char[1] {'\0'};
}
//getter
int SnakeBody::getX() const {
    return this -> x;
}

int SnakeBody::getY() const {
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

void SnakeBody::setShape(const char *shape) {
    strcpy(this -> shape, shape);
}

