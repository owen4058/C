#include<iostream>

using namespace std;
int Area(int ax,int ay,int bx,int by,int cx,int cy);
int main(){

    int ax,ay,bx,by,cx,cy;
    cin >> ax >> ay >> bx >> by >> cx >> cy;
    int answer;
    answer = Area(ax,ay,bx,by,cx,cy);
    if (answer == 0)
        cout << answer << ' ' << 0 << endl;
    else if (answer < 0)
        cout << -answer << ' ' << -1 << endl;
    else
        cout <<  answer << ' ' << 1 << endl;


    return 0;
}
int Area(int ax, int ay, int bx, int by, int cx, int cy){
    return ((bx-ax)*(cy-ay)-(cx-ax)*(by-ay));
}