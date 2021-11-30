#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
char input[100][100];
bool check[100][100];
int m, n, cnt;
int vertical[4] = {1, -1, 0, 0};
int horizontal[4] = {0, 0, 1, -1};

bool change(int a, int b)
{
    return a > b;
}

void Check_Roomsize(int i, int j)
{
    cnt++;
    check[i][j] = true;

    for (int k = 0; k < 4; k++)
    {
        int x, y;
        x = i + vertical[k];
        y = j + horizontal[k];

        if (x > 0 || x < n - 1 || y > 0 || y < m - 1)
            if (input[x][y] == '.' && check[x][y] == false)
                Check_Roomsize(x, y);
    }
}

int main()
{

    vector<int> v;
    cin >> m >> n;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
            cin >> input[i][j];
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
            check[i][j] = false;
    }
    for (int i = 1; i < n - 1; i++)
    {
        for (int j = 1; j < m - 1; j++)
        {
            if (input[i][j] == '.' && check[i][j] == false)
            {
                cnt = 0;
                Check_Roomsize(i, j);
                v.push_back(cnt);
            }
        }
    }

    sort(v.begin(), v.end(), change);
    cout << v.size() << endl;
    if (v.size() != 0)
    {
        for (int i = 0; i < v.size(); i++)
            cout << v[i] << " ";
    }


    return 0;
}