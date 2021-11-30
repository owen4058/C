#include <iostream>
#include <algorithm>
#include <string>
#include <cstring>
#include <queue>

using namespace std;
queue<char> input;

bool CheckEnd(){
    string temp;
    for(int i=0; i<3; i++){
        temp[i] = input.front();
        input.pop();
    }
    if(temp != "101"){ return false; }
    else return true;
}
bool


int main(void) {
    string answer;
    char data;
    for(int i=0; i<95; i++){
        cin >> data;
        input.push(data);
    }

    if(!CheckEnd()) return 0;
    getline(3,)



    cout << answer << endl;
    return 0;
}