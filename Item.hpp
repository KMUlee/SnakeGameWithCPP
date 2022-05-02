//
//  Item.hpp
//  cpp_algo
//
//  Created by 이승원 on 2022/05/01.
//

#ifndef Item_hpp
#define Item_hpp

#include <stdio.h>
#include <ctime>
#include <stdlib.h>

class Item {
  
private:
    int row, column;
    int x, y;
    
public:
    //constructor
    Item();
    Item(int row, int column);
    //getter
    int getX();
    int getY();
    int getItem();
    //randSet
    void randSet();
    
};

#endif /* Item_hpp */
