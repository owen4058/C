#include <iostream>
#include <algorithm>
#include <cstdio>
using namespace std;
int main() {

    int n;
    cin >> n;
    int arr[10001];
    for (int i = 0; i<n; i++) {
        scanf("%d", &arr[i]);
    }
    sort(arr, arr + n);
    if (arr[n - 1] <= 0) printf("%d\n", arr[0] * arr[1]);
    else {
        int plus=1;
        int minus=1;
        if(arr[n-3]*arr[n-2]*arr[n-1] > arr[n-2]*arr[n-1])
            plus = arr[n-3]*arr[n-2]*arr[n-1];
        else
            plus = arr[n-2] * arr[n-1];
        minus = max(arr[0] * arr[1], arr[0] * arr[1] * arr[n - 1]);
        if (plus > minus) printf("%d\n", plus);
        else printf("%d\n", minus);
    }
}