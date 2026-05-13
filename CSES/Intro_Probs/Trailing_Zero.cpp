#include <iostream>

using namespace std;

long long Pow (long long a, long long b){
    long long ans = 1;
    while (b > 0){
        if ((b & 1) == 1){
            ans = ans * a;
        }
        a = (a * a);
        b /= 2;
    }

    return ans;
}
int main(){
    int count = 0;
    int n; cin >> n;
    int expo = 1;
    while (1){
        int tmp = n / Pow (5, expo);
        if (tmp == 0) break;
        count += tmp;
        expo ++;
    }

    cout << count;
    return 0;
}