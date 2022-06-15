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
#include <cstring>

class SnakeBody {
private:
    int x, y;
    char *shape;
public:
    //constructor
    SnakeBody();
    SnakeBody(int x, int y, const char *shape);
    //getter
    int getX() const;
    int getY() const;
    char* getShape();
    //setter
    void setX(int x);
    void setY(int y);
    void setShape(const char *shape);
    
};


#endif /* Snake_hpp */
