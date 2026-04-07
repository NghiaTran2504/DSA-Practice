#include <iostream>
#include <cstring>

using namespace std;
#define ll long long

void heapify (ll, int, int);
void heapsort (ll, int);
void Update (ll*, int, int);
ll Query (int);

void heapify (ll a[], int n, int i){
    int node = i;
    while (1){
        int left = 2 * node + 1;
        int right = 2 * node + 2;
        int largest = node;

        if (left < n && a[left] > a[largest])
            largest = left;
        if (right < n && a[right] > a[largest])
            largest = right;

        if (largest == node) return;
        swap (a[largest], a[node]);
        node = largest;
    }
}

void heapsort (ll a[], int n)
{
    for (int i =  n / 2 - 1; i >= 0; i--)
        heapify (a, n, i);
    
    for (int i = n - 1; i >= 1; --i){
        swap (a[0], a[i]);
        heapify (a, i, 0);
    }
}

int lowerbound (ll a[], int n, ll val){
    int left = 0, right = n - 1;
    int res = n;
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

void Update (ll *bit, int pos, int n){
    while (pos <= n){
        bit[pos]++;
        pos += pos & -pos;
    }
}

ll Query (ll *bit, int pos){
    ll ans = 0;
    while (pos){
        ans += bit[pos];
        pos -= pos & -pos;
    }
    return ans;
}

void solve(){
    int n; cin >> n;
    ll* a = new ll [n+5]();
    ll* bit = new ll[n+5]();
    for (int i = 1; i <= n; ++i) cin >> a[i];

    ll* b = new ll [n+5]();
    for (int i = 0; i < n; ++i){
        b[i] = a[i + 1];
    }
    heapsort (b, n);

    //Compress numbers
    for (int i = 1; i <= n; ++i){
        a[i] = lowerbound (b, n, a[i]) + 1;
    }
    //###############

    ll* suffix = new ll [n + 5]();
    ll* prefix = new ll [n + 5]();

    //Prefix
    for (int i = 1; i <= n; ++i){
        prefix[i] = i - 1 - Query (bit, a[i]);
        Update (bit, a[i], n);
    }

    memset (bit, 0, sizeof(ll) * (n + 5));

    for (int i = n; i >= 1; --i){
        suffix[i] = Query (bit, a[i] - 1);
        Update (bit, a[i], n);
    }

    // for (int i = 1; i <= n; ++i ) cout << prefix[i] << " ";
    // cout << "\n";
    // for (int i = 1; i <=n; ++i) cout << suffix[i] << " ";

    ll ans = 0;
    for (int i = 1; i <= n; ++i){
       // cout << prefix[i] << " " << suffix[i] << "\n";
        ans += prefix[i] * suffix[i];
    }

    cout << ans << " ";
    delete[] a;
    delete[] b;
    delete[] bit;
}
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    solve();

    return 0;
}