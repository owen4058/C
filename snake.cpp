#include <iostream>
#include <ncurses.h>
#include <locale.h>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <list>
#include <unistd.h>

using namespace std;

#define MAX_X 30
#define MAX_Y 30

WINDOW *win1;
int playtime = 100;
int score = 0;
bool keep_play = true;
int key; // to read key value
char dir = 'l'; // start left direction
int food_x=6,food_y=2; // food location
int poison_x=25,poison_y=25; // poison location
int length = 3;
vector<int> snake_position_x; // snake position
vector<int> snake_position_y; // snake position
int map[30][30] = { // map
        2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,
        1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
        1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
        1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
        1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
        1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
        1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
        1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
        1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
        1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
        1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
        1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
        1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
        1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
        1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
        1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
        1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
        1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
        1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
        1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
        1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
        1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
        1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
        1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
        1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
        1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
        1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
        1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
        1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
        2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2};
// map fucntions
void print_Map(){
    for(int i=0; i<MAX_X; i++){
        for(int j=0; j<MAX_Y; j++){
            switch(map[i][j]){
                case 0 : mvprintw(i, j, " "); break; // ????????? ?????? ??? ???????????? ?????? ??????
                case 1 : mvprintw(i, j, "*"); break; // wall
                case 2 : mvprintw(i, j, "*"); break;
                case 3 : mvprintw(i, j, "S"); break; // snake body
                case 4 : mvprintw(i, j, "S"); break;
                case 5 : mvprintw(i, j, "F"); break; // food
                case 6 : mvprintw(i, j, "P"); break; //poison
            }
        }
    }
    refresh();
}
void init()
{
    initscr();
    keypad(stdscr, TRUE);
    curs_set(0);
    start_color();
    resize_term(MAX_X+10, MAX_Y+10);
    refresh();
}

void set_Food(){
    time_t t = time(NULL);
    srand(t);
    mvprintw(food_y, food_x, " "); // remove previous food
    map[food_x][food_y] = 0; // remove previous food display
    food_x = rand() % MAX_X - 1; // set food randomly
    food_y = rand() % MAX_Y - 1;
    map[food_x][food_y] = 5;
    if(food_x != poison_x && food_y != poison_y){ // print food
        mvprintw(food_y, food_x, "F");
    }
    refresh();
}
void set_Posion(){
    time_t t = time(NULL);
    srand(t+100);
    mvprintw(poison_y, poison_x, " "); // remove previous poison
    map[poison_x][poison_y] = 0; // remove previous poison display
    poison_x = rand() % MAX_X - 1;
    poison_y = rand() % MAX_Y - 1;
    if(food_x != poison_x && food_y != poison_y){
        mvprintw(poison_y, poison_x, "P"); // print poison
    }
    refresh();
}

void set_Time(){ // set time
    mvprintw(31, 15, "TIME : ",playtime);
}
void set_Score(){ // set Score
    mvprintw(31, 0, "SCORE : ",score);
}
void move_Head(int key){ // move snake and set direction
    if(key == KEY_LEFT && dir != 'r'){
        map[snake_position_y.front()][snake_position_x.front()-1] = 3; dir = 'l'; // set snake body to map
        snake_position_x.insert(snake_position_x.begin(),snake_position_x.front()-1); //
        snake_position_y.insert(snake_position_y.begin(), snake_position_y.front());
    } // ?????? ?????? ??? snake position ????????? ??? ????????? ????????? ????????? ???????????????.
    else if(key == KEY_RIGHT && dir != 'l'){
        map[snake_position_y.front()][snake_position_x.front()+1] = 3; dir = 'r';
        snake_position_x.insert(snake_position_x.begin(),snake_position_x.front()+1);
        snake_position_y.insert(snake_position_y.begin(), snake_position_y.front());
    } // ?????? ????????? ???????????? ?????????.
    else if(key == KEY_UP && dir != 'd'){
        map[snake_position_y.front()-1][snake_position_x.front()] = 3; dir = 'u';
        snake_position_x.insert(snake_position_x.begin(),snake_position_x.front());
        snake_position_y.insert(snake_position_y.begin(), snake_position_y.front()-1);
    }
    else if(key == KEY_DOWN && dir != 'u'){
        map[snake_position_y.front()+1][snake_position_x.front()] = 3; dir = 'd';
        snake_position_x.insert(snake_position_x.begin(),snake_position_x.front());
        snake_position_y.insert(snake_position_y.begin(), snake_position_y.front()+1);
    }
}
void cut_Tail(){
    map[snake_position_y.back()][snake_position_x.back()] = 0;
    snake_position_x.pop_back(); snake_position_y.pop_back();
} // map??? snake position??? ????????? ????????? 0?????? ?????? ????????? ????????? ??? vector?????? ??????
bool eat_Food(){
    if(snake_position_y.front() == food_y && snake_position_x.front() == food_x){
        score += 10; length++;
        return true;
    } // snake position??? food??? ????????? ????????? score??? length??? ??????(Food?????? ??? ????????? ?????? ??? ?????? ????????? ????????? ????????? ???????????? ????????????_
    else return false;
}
void eat_Poison(){
    if(snake_position_y.front() == poison_y && snake_position_x.front() == poison_x){
        score -= 10; length--;
        cut_Tail();
    } // snake ??? poison??? ????????? ????????? score ??? length ??????
}


int main(int argc, const char * argv[]) {
    snake_position_x.push_back(4);
    snake_position_x.push_back(5);
    snake_position_x.push_back(6);
    snake_position_y.push_back(15);
    snake_position_y.push_back(15);
    snake_position_y.push_back(15); // ?????? snake ?????? ??????
    for(int i=0; i<length; i++){
        map[snake_position_y[i]][snake_position_x[i]] = 3; // ?????? snake ??????
    }
    init();
    set_Score();
    set_Time();
    int cnt=0;
    set_Food();
    set_Posion();
    while(keep_play){
        if(cnt % 15 == 0){ // ??? ?????? 15??? ?????? food, poison ?????? reset
            set_Food();
            set_Posion();
        }
        print_Map(); // map??? ?????? ????????? ???????????? ??????????????????
        key = getch();
        move_Head(key); // move snake's head with key
        if(!eat_Food()){ cut_Tail(); } // food??? ???????????? ????????? ?????? ??? ????????? ????????? ????????? ????????? ???????????? ????????????.
        eat_Poison(); // poison??? ???????????? ?????? ????????? ?????? ??? ?????? ?????? ??????
        cnt++;
        if(cnt == 300) // ??? ?????? 300??? ??? ??????
            break;
    }

    endwin();
    return 0;
}
