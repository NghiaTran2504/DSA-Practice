#include <iostream>

using namespace std;

long long Pow (int a, int b){
    long long ans = 1;
    for (int i = 0; i < b; ++i){
        ans *= a;
    }
    return ans;
}

int main(){
    int t; cin >> t;
    while (t--){
        int row, col;
        long long ans;
        cin >> row >> col;
        if (row >= col){
            // Neu row la le
            if ((row & 1) == 1){
                ans = Pow (row - 1, 2) + 1 + (col - 1); 
            }
            // Neu row la chan
            else{
                ans = Pow (row, 2) - (col - 1);
            }
        }
        else{
            if ((col & 1) == 1){
                ans = Pow (col, 2) - (row - 1);
            }
            else{
                ans = Pow (col - 1, 2) + 1 + (row - 1);
            }
        }
        cout << ans << "\n";
    }
    return 0;
}