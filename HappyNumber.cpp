#include <iostream>
#include <vector>
using namespace std;

vector<int> v;

void happyNumber(int input) {

    if (input == 1) {
        cout << "HAPPY" << endl;
        return;
    }

    for(int i=0; i<v.size(); i++)
        if (input == v[i]) {
            cout << "UNHAPPY" << endl;
            return;
        }
    v.push_back(input);

    int copy = input;
    int result = 0;

    while (copy) {
        result += (copy % 10)*(copy % 10);
        copy /= 10;
    }
    happyNumber(result);

}

int main(void){
    int num;
    cin >> num;

    happyNumber(num);
    return 0;

}