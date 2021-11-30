#include <iostream>
#include <cmath>

using namespace std;

int main(){
    int x1, y1, x2, y2, x3, y3; //좌표
    int a[3]; // a,b,c 변의 길이
    int p;
    cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;
    a[0] = sqrt(pow(x2-x1,2) * pow(y2-y1,2)); //a의 길이
    a[1] = sqrt(pow(x3-x2,2) * pow(y3-y2,2)); //b의 길이
    a[2] = sqrt(pow(x3-x1,2) * pow(y3-y1,2)); //c의 길이

    if(x1 == y1 && x2 == y2 && x3 == y3){
        cout << "It's just a Line" << endl;
        return 0;
    }
    else if(x1 == 1 && x2 == x3){
        cout << "It's just a Line" << endl;
        return 0;
    }
    else if(y1 == y2 && y2 == y3){
        cout << "It's just a Line" << endl;
        return 0;
    }
    
    int i=0;
    while(i<2){ //변의 길이 순서대로 정리
        int temp;
        if(a[i]>a[i+1]){
            temp = a[i];
            a[i] = a[i+1];
            a[i+1] = temp;
        }
        i++;
    }
    i=0;
    while(i<3){
        cout << a[i] << " " << endl;
        i++;
    }
    p=pow(a[0],2)*pow(a[1],2);
    if(p == pow(a[2],2)){
        cout << "직각삼각형" << endl;
    }
    else if(p < pow(a[2],2)){
        cout << "둔각삼각형" << endl;
    }
    else
        cout << "예각삼각형" << endl;
    
    return 0;
    
    
    
}
