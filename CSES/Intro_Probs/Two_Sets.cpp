#include <iostream>

using namespace std;


int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n; cin >> n;
    long long sum = 1LL * n * (n + 1) / 2;
    if ((sum & 1) == 0){
        cout << "YES" << '\n';
        long long sum_set = sum / 2;
        int idx1 = 0, idx2 = 0;
        int set1[n]{}, set2[n]{};
        for (int i = n; i >=  1; --i){
            if (i <= sum_set){
                set1[idx1++] = i;
                sum_set -= i;
            }
            else{
                set2[idx2++] = i;
            }
        }
        cout << idx1 << "\n";
        for (int i = 0; i < idx1; ++i)
            cout << set1[i] << " ";
        cout << "\n" << idx2 << "\n";
        for (int i = 0; i < idx2; ++i){
            cout << set2[i] << " ";
        }
    }

    else cout << "NO";
    return 0;
}