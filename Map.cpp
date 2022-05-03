//
//  Map.cpp
//  cpp_algo
//
//  Created by 이승원 on 2022/05/01.
//

#include "Map.hpp"
//makeMap
int** makeMap(int row, int column, int stage) {
    int** map = new int*[row];
    for (int i = 0; i < row; i++) {
        map[i] = new int[column];
        for (int j = 0; j < column; j++) {
            if (i == 0 || j == 0 || i == row - 1 || j == column - 1) {
                map[i][j] = 1;
            } else
                map[i][j] = 0;
        }
    }
    
    map[0][0] = map[0][column-1] = map[row-1][column-1] = map[row-1][0] = 2;
    
    if (stage >= 2) {
        for (int i = 0; i < row; i++) {
            map[i][column / 2] = 1;
        }
        map[0][column/2] = 2;
        map[row-1][column/2] = 2;
        if (stage >= 3) {
            for (int i = 0; i < column; i++) {
                map[row/2][i] = 1;
            }
            map[row/2][column/2] = 2;
            map[row/2][0] = map[row/2][column-1] = 2;
            if (stage == 4) {
                map[row/4][column/4] = 1;
                map[row/2 + row/4][column/2 + column/4] = 1;
            }
        }
    }
    
    return map;
}
