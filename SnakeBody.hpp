//
//  SnakeBody.hpp
//  cpp_algo
//
//  Created by 이승원 on 2022/04/29.
//

#ifndef SnakeBody_hpp
#define SnakeBody_hpp

#include <stdio.h>
#include <stdlib.h>

class SnakeBody {
private:
    int x, y;
    char *shape;
public:
    //constructor
    SnakeBody();
    SnakeBody(int x, int y, char* shape);
    //getter
    int getX();
    int getY();
    char* getShape();
    //setter
    void setX(int x);
    void setY(int y);
    void setShape(char* shape);
    
};


#endif /* Snake_hpp */
