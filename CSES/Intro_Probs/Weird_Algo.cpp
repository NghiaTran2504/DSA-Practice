#include <iostream>

using namespace std;

int main()
{
    int n; cin >> n;
    long long ans = n;
    while (ans != 1){
        cout << ans << " ";
        if ((ans & 1) == 0)
            ans /= 2;
        else{
            ans = ans * 3 + 1;
        }
    }
    cout << ans;
    return 0;
}