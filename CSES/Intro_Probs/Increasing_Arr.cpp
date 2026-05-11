#include <iostream>

using namespace std;

int main(){
    int n; cin >> n;
    int arr[n + 5]{};
    for (int i =0; i < n; ++i)
        cin >> arr[i];

    int prev_num = arr[0];
    long long moves = 0;
    for (int i = 0; i < n; ++i){
        if (arr[i] < prev_num)
            moves += prev_num - arr[i];
        else prev_num = arr[i];
    }

    cout << moves << "\n";
    return 0;

}