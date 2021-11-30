#include <iostream>
#include <vector>
#include <string>
using namespace std;

int rule_len(vector<string> ISBN){
    int sum = 0;

    if(ISBN.size() != 4) return false;

    for(int i=0;i<4;i++){
        if(ISBN[i].size() <= 0) return false;
        sum += ISBN[i].size();
    }
    if(sum != 10) return false;

    if(ISBN[0].size()>5 || ISBN[1].size()>7 || ISBN[2].size()>6 || ISBN[3].size()>1)
        return false;

    return true;
}

int check(vector<string> ISBN){
    string str;
    int num = 10, sum = 0, mul = 0;

    for(int i=0; i<3;i++){
        for(int j=0; j<ISBN[i].size();j++){
            str = ISBN[i][j];
            if(atoi(str.c_str()) == 0 && str != "0")
                return false;
            sum += atoi(str.c_str()) * num;
            num--;
        }
    }

    string last(ISBN[3]);
    while(mul < sum){
        mul += 11;
    }

    if(mul-sum == 10){
        if("X" == last) return true;
    }
    else{
        if(mul-sum == atoi(last.c_str())) return true;
    }
    return false;
}


int main()
{
    vector<int> v(1, -1);
    vector<string> ISBN;
    string isbn;
    cin >> isbn;

    int s = -1, p = 0;
    while(1){
        s = isbn.find('-', s+1);
        if(s == -1){
            ISBN.push_back(isbn.substr(v[p]+1, isbn.size()));
            break;
        }
        v.push_back(s);
        ISBN.push_back(isbn.substr(v[p]+1, v[p+1]-v[p]-1));
        p++;
    }

    if(rule_len(ISBN) == false)
        cout << 0 << endl;
    else{
        if(check(ISBN) == false)
            cout << 0 << endl;
        else
            cout << 1 << endl;
    }

    return 0;
}
