#include <iostream>

using namespace std;


int main(){
    int n; cin >> n;
    for (long long i = 1; i <= n; ++i){
        long long total = (i * i) * (i * i - 1) / 2;
        long long invalid_cell = 4 * (i - 1) * (i - 2);
        cout << total - invalid_cell << "\n";
    }
    return 0;
}