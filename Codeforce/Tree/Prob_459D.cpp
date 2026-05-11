#include <iostream>
#include <cstring>

using namespace std;
#define ll long long

void heapify (ll* a, int n, int i){
    int node = i;

    while (1){
        int left = 2 * node + 1;
        int right = 2* node + 2;
        int largest = node;

        if (left < n && a[left] > a[largest])
            largest = left;
        if (right < n && a[right] > a[largest])
            largest = right;

        if (largest == node) return;
        swap (a[node], a[largest]);
        node = largest;
    }
}

void heapsort (ll* a, int n){
    for (int i = n / 2 - 1; i >= 0; --i){
        heapify (a, n, i);
    }

    for (int i = n - 1; i >= 0; --i){
        swap (a[i], a[0]);
        heapify (a, i, 0);
    }
}

int lowerbound (ll* a, int n, int val){
    int left = 0, right = n - 1, res = n;
    while (left <= right){
        int mid = left + (right - left) / 2;
        if (a[mid] >= val){
            res = mid;
            right = mid - 1;
        }
        else left = mid + 1;
    }

    return res;
}

void update (ll* bit, int n, int x, int v){
    while (x <= n){
        bit[x] += v;
        x += x & -x;
    }
}

ll gett (ll *bit, int n, int x){
    ll res = 0;
    while (x){
        res += bit[x];
        x &= x - 1;
    }
    return res;
}

void solve(){
    int n; cin >> n;
    ll *a = new ll [n+5]();
    ll *freq = new ll [n+5]();
    ll *suffix = new ll[n+5]();
    ll *prefix = new ll[n+5]();
    ll* b = new ll[n+5]();


    for (int i = 1; i <= n; ++i){
        cin >> a[i];
        b[i - 1] = a[i];
    }

    //Compress numbers
    heapsort (b, n);

    for (int i = 1; i <= n; ++i){
        a[i] = lowerbound (b, n, a[i]) + 1;
    }
    //###################################

    //Prefix
    for (int i = 1; i <= n; ++i){
        freq[a[i]]++;
        prefix[i] = freq[a[i]];
    }

    //Suffix
    // //Set freq array all to 0

    memset (freq, 0, sizeof (ll) * (n+5));
    for (int i = n; i >= 1; --i){
        freq[a[i]]++;
        suffix[i] = freq[a[i]];
    }

    // bit[i] sẽ quản lý k thằng freq[x]
    // nghĩa là bit[i] sẽ cho biết TỔNG số lượng xuất hiện của 
    // các value mà nó quản lý
    ll *bit = new ll [n+5]();
    ll ans = 0;

    for (int i = 1; i <= n; ++i){
        //ví dụ: suffix[i] = 2 (nghĩa là trong đoạn [i, n] có 2 thằng a[i])
        //Hàm gett trả về: 3 (nghĩa là trong đoạn [1, i - 1], có 3 thằng prefix <= suffix[i])
        // mà tổng độ dài đoạn [1, i - 1] đang xét là 4
        // ==> có 4 - 3 = 1 thằng prefix > suffix[i]
        // nghĩa là đã có 1 cặp i, j thỏa yêu cầu đề
        ans += i - 1 - gett(bit, n, suffix[i]); 
        update(bit, n, prefix[i], 1);
    }
    cout << ans << "\n";

    delete[] bit;
    delete[]a;
    delete[]freq;
    delete[]suffix;
    delete[]prefix;
    delete[] b;
}
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    solve();

    return 0;
}