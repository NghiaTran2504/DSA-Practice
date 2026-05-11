#include <iostream>

using namespace std;

bool solve(){
    int n; cin >> n;
    int t; cin >> t;
    int *a = new int[n + 5]{};
    for (int i = 1; i <= n; ++i) 
        cin >> a[i];

    int dest = 1;
    while (dest < n){
        dest += a[dest];
        if (dest == t) {
            delete[] a;
            return true;
        }
    }
    delete[] a;

    return false;
}
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    
    if (solve()) cout << "YES" << "\n";
    else cout << "NO" <<  "\n";
    return 0;
}