#include <iostream>
#include <cmath>
using namespace std;

int main() {
    int sheep, goat, total, eat; // sheep =양 , goat= 염소 , total= 전체마리 , eat= 전날 먹은 사료양
    cin >> sheep >> goat >> total >> eat; // 정수 입력
    int i = 0;
    int answer;
    if (sheep * total == eat or goat * total == eat)
    {
        answer = -1;
        cout << answer << " " << endl;
        return 0;
    }
    else if(sheep + goat > eat)
    {
        answer = -1;
        cout << answer << " " << endl;
        return 0;
    }
    while(i != eat)
    {
        answer = 0;

        answer = sheep * (total - i) + goat * (i);
        if (answer != eat)
        {
            i++;
            continue;
        }
        else if (answer == eat)
        {
            cout << total - i << " " << i << endl;
            break;
        }
        else {
            answer = -1;
            cout << answer  << " " << endl;
        }

    }


    return 0;
}