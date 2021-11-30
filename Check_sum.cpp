#include <iostream>
using namespace std;

int main(){
    unsigned int n;
    cin >> n;  //ex 현재 50463225를 입력받았다고 가정
    unsigned int a,b,c,d; // 8바이트 할당 *4
    int sum =0;
    a = n>>8*3;
    b = n<<8;
    b = b>>8*2;
    c = n<<8*2;
    c = c>>8*3;
    d = n<<8*3;
    d = d>>8*3;
    sum  = a+b+c;
    while(sum>=256){
        sum-=256;
    }
    sum = 255-sum;
    if(sum==d){cout << "1" << endl;}
    else{cout << "0" << endl;}

    return 0;
}