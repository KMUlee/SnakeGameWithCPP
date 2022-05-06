//
//  Game.cpp
//  cpp_algo
//
//  Created by 이승원 on 2022/05/01.
//

#include "Game.hpp"

#define ITEM_TIME 10
#define GATE_TIME 15
#define GATE_END 10


//constructor
Game::Game(int row, int column) {
    this -> row = row;
    this -> column = column;
    this -> snake = new Snake(row * column);
    this -> item = new Item(row, column);
    this -> stage = 1;
    this -> gate_time = 0;
}
//setter
void Game::setMode(int mode) {
    this -> mode = mode;
}

void Game::setStage(int stage) {
    this -> stage = stage;
}
//
void Game::gameInit(int stage) {
    //속성 초기화
    this -> best = 0;
    this -> growth = 0;
    this -> poison = 0;
    this -> gate = 0;
    this -> end = 0;
    this -> stage = stage;
    this -> active_gate = 0;
    //뱀의 크기 초기화
    this -> snake -> setTop(-1);
    //map 초기화
    this -> map = makeMap(this -> row, this -> column, this -> stage);
    //초기 뱀의 형태
    this -> snake -> snakePush(10, 10, "@");
    this -> snake -> snakePush(10, 11, "O");
    this -> snake -> snakePush(10, 12, "O");
    //초기 뱀의 방향 설정
    this -> snake -> setDirection(0, -1);
    //아이템 만들기
    this -> makeItem();
}

int Game::GameStart() {
    //키 입력 변수
    int getKey;
    //시작 측정
    time_t t = time(NULL);
    int min, sec;
    //
    start_color();
    
    init_pair(1, COLOR_GREEN, COLOR_BLACK);
    
    while(this -> mode == 1) {\
        clear();
        this -> drawHowto();
        getKey = getch();
        
        if (getKey == 32) {
            this -> end = 0;
            break;
        }
    }
    
    while (this -> stage == 5) {
        clear();
        this -> drawClear();
        getKey = getch();
        
        if (getKey == 32) {
            this -> end = 0;
            this -> mode = 1;
            break;
        }
    }
    
    while(this -> mode == 0) {
        if (end) {
            break;
        }
        clear();
        this -> moveSnake();
        
        getKey = getch();
        
        switch (getKey) {
            case KEY_UP:
                this -> snake -> setDirection(-1, 0);
                break;
            case KEY_DOWN:
                this -> snake -> setDirection(1, 0);
                break;
            case KEY_LEFT:
                this -> snake -> setDirection(0, -1);
                break;
            case KEY_RIGHT:
                this -> snake -> setDirection(0, 1);
                break;
            case 32:
                this -> poison++;
                this -> growth++;
                this -> gate++;
                this -> best++;
                break;
        }
        //죽음 이벤트
        if (this -> eventDeath()) {
            break;
        }
        //아이템 생성
        if ((time(NULL) - t) % ITEM_TIME == 0) {
            this -> map[this -> item -> getX()][this -> item -> getY()] = 0;
            this -> makeItem();
        }
        //gate생성
        if (!this->active_gate && (time(NULL) - t) % GATE_TIME == 0 && time(NULL) - t != 0) {
            this -> makePotal();
            this -> check_gate = 0;
            this -> gate_time = time(NULL) - t;
        }
        //시간이 지나면 게이트 닫힘
        if (time(NULL) - t == this->gate_time + GATE_END) {
            if (!this -> check_gate) {
                this ->active_gate = 0;
                this->map[this->gateX_1][this->gateY_1] = 1;
                this->map[this->gateX_2][this->gateY_2] = 1;
            }
        }
        //draw
        this -> drawMap();
        this -> drawSnake();
        this -> drawScore();
        this -> drawTodo();
        //draw playtime
        min = (time(NULL) - t) / 60;
        sec = (time(NULL) - t) % 60;
        mvprintw(0, 16, "STAGE: %d", this -> stage);
        mvprintw(1, 12, "PLAY TIME: %2d:%2d", min, sec);
        
        refresh();
        
        std::this_thread::sleep_for(std::chrono::milliseconds(250));
    }
    
    return this -> end;
}
//draw
void Game::drawMap() {
    
    for (int i = 0; i < this -> row; i++) {
        for (int j = 0; j < this -> column; j++) {
            switch (this -> map[i][j]) {
                case 1:
                    mvprintw(i + 2, j, "#");
                    break;
                case 2:
                    mvprintw(i + 2, j, "*");
                    break;
                case 3:
                    mvprintw(i + 2, j, "+");
                    break;
                case 4:
                    mvprintw(i + 2, j, "-");
                    break;
                case 5:
                    attron(COLOR_PAIR(1));
                    mvprintw(i + 2, j, "G");
                    attroff(COLOR_PAIR(1));
                    break;
                default:
                    break;
            }
        }
    }
    refresh();
}

void Game::drawSnake() {
    SnakeBody* snakebody = this -> snake -> getSnakeBody();
    
    for (int i = 0; i <= this -> snake -> getTop(); i++) {
        mvprintw(snakebody[i].getX() + 2, snakebody[i].getY(), snakebody[i].getShape());
    }
    refresh();
}

void Game::drawScore() {
    int start_pos = this -> column;
    
    char *score_1 = " ___ __ ___ _ _ ___";
    char *score_2 = "(_-</ _/ _ \\ '_/ -_)";
    char *score_3 = "/__/\\__\\___/_| \\___|";
    //print "score"
    mvprintw(2, start_pos + 10, score_1);
    mvprintw(3, start_pos + 10, score_2);
    mvprintw(4, start_pos + 10, score_3);
    //print score
    this -> best = (this -> best < this -> snake -> getTop()) ? this -> snake -> getTop() : this -> best;
    mvprintw(7, start_pos + 18, "B: %2d", this -> best + 1);
    mvprintw(8, start_pos + 18, "+: %2d", this -> growth);
    mvprintw(9, start_pos + 18, "-: %2d", this -> poison);
    mvprintw(10, start_pos + 18, "G: %2d", this -> gate);
}

void Game::drawTodo() {
    int start_pos = this -> column;
    
    char *todo_1 = " _           _";
    char *todo_2 = "| |_ ___  __| |___";
    char *todo_3 = "|  _/ _ \\/ _` / _ \\";
    char *todo_4 = " \\__\\___/\\__,_\\___/";
    
    int t_best, t_growth, t_poison, t_gate;
    
    if (this -> stage == 1) {
        t_best = 5;
        t_growth = 5;
        t_poison = 5;
        t_gate = 3;
    } else if (this -> stage == 2) {
        t_best = 10;
        t_growth = 5;
        t_poison = 5;
        t_gate = 5;
    } else if (this -> stage == 3) {
        t_best = 15;
        t_growth = 10;
        t_poison = 10;
        t_gate = 5;
    } else {
        t_best = 15;
        t_growth = 15;
        t_poison = 15;
        t_gate = 10;
    }
    
    //print "todo"
    mvprintw(12, start_pos + 11, todo_1);
    mvprintw(13, start_pos + 11, todo_2);
    mvprintw(14, start_pos + 11, todo_3);
    mvprintw(15, start_pos + 11, todo_4);
    //print todo
    mvprintw(18, start_pos + 17, "B: %2d[%c]", t_best, this -> best >= t_best ? 'V' : ' ');
    mvprintw(19, start_pos + 17, "+: %2d[%c]", t_growth, this -> growth >= t_growth ? 'V' : ' ');
    mvprintw(20, start_pos + 17, "-: %2d[%c]", t_poison, this -> poison >= t_poison ? 'V' : ' ');
    mvprintw(21, start_pos + 17, "G: %2d[%c]", t_gate, this -> gate >= t_gate ? 'V' : ' ');
    
    if (this -> best >= t_best && this -> growth >= t_growth && this -> poison >= t_poison && this -> gate >= t_gate) {
        this -> snake -> setDirection(0, 0);
        this -> end = this -> stage + 1;
    }
}

void Game::drawHowto() {
    char *howto_1 = " _  _  _____      __  _____ ___";
    char *howto_2 = "| || |/ _ \\ \\    / / |_   _/ _ \\";
    char *howto_3 = "| __ | (_) \\ \\/\\/ /    | || (_) |";
    char *howto_4 = "|_||_|\\___/ \\_/\\_/     |_| \\___/";
    
    //print howto
    mvprintw(2, 23, howto_1);
    mvprintw(3, 23, howto_2);
    mvprintw(4, 23, howto_3);
    mvprintw(5, 23, howto_4);
    //print how to play
    mvprintw(10, 27, "Play with the arrow keys");
    mvprintw(12, 27, "+: Increase the length");
    mvprintw(13, 27, "-: Decrease the length");
    mvprintw(14, 27, "G: Go to the connected gate");
    mvprintw(18, 21, "Press the spacebar to go to the main");
    refresh();
}

void Game::drawClear() {
    char *clear_1 = "               __  ______  __  __   ____  ________     __________";
    char *clear_2 = "               \\ \\/ / __ \\/ / / /  / __ \\/  _/ __ \\   /  _/_  __/";
    char *clear_3 = "                \\  / / / / / / /  / / / // // / / /   / /  / /";
    char *clear_4 = "                / / /_/ / /_/ /  / /_/ // // /_/ /  _/ /  / /";
    char *clear_5 = "               /_/\\____/\\____/  /_____/___/_____/  /___/ /_/";
    
    //print clear
    mvprintw(9, 0, clear_1);
    mvprintw(10, 0, clear_2);
    mvprintw(11, 0, clear_3);
    mvprintw(12, 0, clear_4);
    mvprintw(13, 0, clear_5);
    mvprintw(18, 21, "Press the spacebar to go to the main");
    
    refresh();
}
//move
void Game::moveSnake() {
    //이동
    this -> snake -> snakeMove();
    //아이템을 먹었는지 확인
    int headX, headY;
    this -> snake -> getHeadPos(&headX, &headY);
    
    switch (this -> map[headX][headY]) {
        case 3:
            this -> snake -> snakePush(-1, -1, "");
            this -> map[headX][headY] = 0;
            this -> growth++;
            break;
        case 4:
            this -> snake -> snakePop();
            this -> map[headX][headY] = 0;
            this -> poison++;
            break;
        case 5:
            if (headX == this -> gateX_1 && headY == this -> gateY_1) {
                this -> snake -> setHeadPos(this -> gateX_2, this -> gateY_2);
            } else if (headX == this -> gateX_2 && headY == this -> gateY_2) {
                this -> snake -> setHeadPos(this -> gateX_1, this -> gateY_1);
            }
            this->potalEvent();
            break;
        default:
            break;
    }
    //Gate check
    int tmpX, tmpY;
    if (this -> check_gate) {
        for (int i = 0; i <= this->snake->getTop(); i++) {
            this -> snake -> getSnakePos(i, &tmpX, &tmpY);
            if ((tmpX == this->gateX_1 && tmpY == this->gateY_1) || (tmpX == this->gateX_2 && tmpY == this->gateY_2)) {
                return;
            }
        }
        this ->active_gate = 0;
        this->map[this->gateX_1][this->gateY_1] = 1;
        this->map[this->gateX_2][this->gateY_2] = 1;
        this -> check_gate = 0;
    }
    
    
}
//event
int Game::eventDeath() {
    //뱀의 머리가 몸통이랑 닿을 때
    if (this -> snake -> eventDeath()) {
        return 1;
    }
    // 뱀의 머리가 벽이랑 닿을 때
    int headX, headY;
    this -> snake -> getHeadPos(&headX, &headY);
    
    if (this -> map[headX][headY] == 1) {
        return 1;
    }
    //뱀의 길이가 3보다 작을 때
    if (this -> snake -> getTop() < 2) {
        return 1;
    }
    
    return 0;
}

void Game::potalEvent() {
    this -> gate++;
    this -> check_gate = 1;
    int headX, headY;
    int dirx = this -> snake -> getDirX(), diry = this -> snake -> getDirY();
    this -> snake -> getHeadPos(&headX, &headY);
    //벽에 생성되었을 때
    if (headX == 0) {
        this -> snake -> setDirection(1, 0);
        return;
    } else if (headX == this -> row - 1) {
        this -> snake -> setDirection(-1, 0);
        return;
    }
    if(headY == 0) {
        this -> snake -> setDirection(0, 1);
        return;
    } else if (headY == this -> column - 1) {
        this -> snake -> setDirection(0, -1);
        return;
    }
    //진입방향 체크
    if (headX + dirx < this->row && headX + dirx >= 0 && headY + diry < this->column && headY + diry >= 0) {
        if(this->map[headX + dirx][headY + diry] == 0) {
            return;
        }
    }
    //시계방항
    if (headX + diry < this->row && headX + diry >= 0 && headY - dirx < this->column && headY - dirx >= 0) {
        if(this->map[headX + diry][headY - dirx] == 0) {
            this -> snake -> setDirection(diry, -dirx);
            return;
        }
    }
    //반시계
    if (headX - diry < this->row && headX - diry >= 0 && headY + dirx < this->column && headY + dirx >= 0) {
        if(this->map[headX - diry][headY + dirx] == 0) {
            this -> snake -> setDirection(-diry, dirx);
            return;
        }
    }
    //역방향
    if (headX - dirx < this->row && headX - dirx >= 0 && headY - diry < this->column && headY - diry >= 0) {
        if(this->map[headX - dirx][headY - diry] == 0) {
            return;
        }
    }
    
    
}
//makeItem
void Game::makeItem() {
    
    int itemX, itemY, chk;
    SnakeBody* snakebody = this -> snake -> getSnakeBody();
    
    while(true) {
        //check var
        chk = 1;
        //setRand
        this -> item -> randSet();
        //get x, y
        itemX = this -> item -> getX();
        itemY = this -> item -> getY();
        //해당 좌표의 값이 0 인지 확인
        if (this -> map[itemX][itemY] != 0) {
            continue;
        }
        //해당 좌표가 뱀이랑 겹치는 지 확인
        for (int i = 0; i <= this -> snake -> getTop(); i++) {
            if (snakebody[i].getX() == itemX && snakebody[i].getY() == itemY) {
                chk = 0;
                break;
            }
        }
        //겹치지 않으면 아이템 생성
        if (chk) {
            this -> map[itemX][itemY] = this -> item -> getItem();
            break;
        }
    }
}

void Game::makePotal() {
    srand(time(NULL));
    this -> active_gate = 1;
    
    while(true) {
        this -> gateX_1 = rand() % this->row;
        this -> gateX_2 = rand() % this->row;
        this -> gateY_1 = rand() % this->column;
        this -> gateY_2 = rand() % this->column;
        
        if (this->map[this->gateX_1][this->gateY_1] == 1 && this->map[this->gateX_2][this->gateY_2] == 1) {
            break;
        }
    }
    this->map[this->gateX_1][this->gateY_1] = 5;
    this->map[this->gateX_2][this->gateY_2] = 5;
}
