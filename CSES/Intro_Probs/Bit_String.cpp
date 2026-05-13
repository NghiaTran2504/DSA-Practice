#include <iostream>

using namespace std;

long long Pow (long long a, long long b){
    long long ans = 1;
    long long MOD = 1e9 + 7;
    a %= MOD;
    while (b > 0){
        if ((b & 1) == 1){
            ans = (ans * a) % MOD;
        }
        a = (a * a) % MOD;
        b /= 2;
    }

    return ans;
}
int main()
{
    int n; cin >> n;
    cout << Pow (2, n);
    return 0;
}