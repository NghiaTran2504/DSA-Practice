#include <iostream>

using namespace std;

int main(){
    int n; cin >> n;
    if (n == 1) cout << 1;
    else if (n == 2 || n == 3) cout << "NO SOLUTION";
    else{
        int odd = 1, even = 2;
        while  (even <= n){
            cout << even << " ";
            even += 2;
        }
        while (odd <= n){
            cout << odd << " ";
            odd += 2;
        }
    }
    return 0;
}