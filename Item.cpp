//
//  Item.cpp
//  cpp_algo
//
//  Created by 이승원 on 2022/05/01.
//

#include "Item.hpp"

Item::Item() {
    this -> row = -1;
    this -> column = -1;
}

Item::Item(int row, int column) {
    this -> row = row;
    this -> column = column;
}

int Item::getX() const{
    return this -> x;
}

int Item::getY() const{
    return this -> y;
}

int Item::getItem() const{
    return rand() % 2 + 3;
}

void Item::randSet() {
    srand((unsigned int)time(NULL));
    this -> x = rand() % (row - 2) + 1;
    this -> y = rand() % (column - 2) + 1;
}
