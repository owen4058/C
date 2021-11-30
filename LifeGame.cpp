#include <iostream>

using namespace std;


int main(){
        int s, k;
        cin >> s >> k;
        int *a = new int [s];
        int *b = new int [s];
        for(int i =0; i<s; i++){
            cin >> *(a+i);
        }

        for(int time=0; time<k; time++){

            for(int i=0; i<s; i++){
            int sum = 0;
                if (i == 0){
                    sum = *(a+i+1);
                }
                else if (i == s-1){
                    sum = *(a+i-1);
                }
                else {
                sum = *(a+i+1) + *(a+i-1) ;
                }


                if (3 < sum and sum <=7){
                    if (*(a+i) < 9){
                        *(b+i) = *(a+i)+1 ;
                    }
                    else {
                        *(b+i) = *(a+i);
                    }
                }
                else if (sum == 3){
                    *(b+i) = *(a+i);
                }
                else{
                    if (*(a+i) > 0){
                        *(b+i) = *(a+i)-1;
                    }
                else{
                    *(b+i) = 0;
                }
                }
            }

            for(int i=0; i<s; i++){
                *(a+i) = *(b+i);
            }
        }

            for(int i=0; i<s; i++){
                cout << *(a+i) << " ";
            }

            cout << endl;
            delete[]a;
            delete[]b;

            return 0;
}