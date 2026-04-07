#include <iostream>

using namespace std;
#define ll long long

const int maxn = 2e5;
int n, a[maxn], seg[4 * maxn];

int Max (int a, int b){
    if (a >= b) return a;
    return b;
}

int Min (int a, int b){
    if (a <= b) return a;
    return b;
}

void build (int v, int l, int r){
    if (l == r){
        seg[v] = a[l];
    }
    else{
        int m = l + (r - l) / 2;
        build (2 * v, l, m);
        build (2 * v + 1, m + 1, r);
        seg[v] = seg[ 2 * v] + seg[2 * v + 1];
    }
}

void update (int v, int l, int r, int pos, int val){
    if (l == r){
        seg[v] = val;
    }
    else{
        int m = l + (r - l) / 2;
        if (pos <= m) update (2 * v, l, m, pos, val);
        else update (2 * v + 1, m + 1, r, pos, val);

        seg[v] = seg[2 * v] + seg[2 * v + 1];
    }
}

int query (int v, int segL, int segR, int l, int r)
{
    if (l > r) return 0;
    if (segL == l && segR == r) return seg[v];

    int segM = segL + (segR - segL)  / 2;
    int s1 = query (2 * v, segL, segM, l, Min (r, segM));
    int s2 = query (2 * v + 1, segM + 1, segR, Max (l, segM + 1), r);
    return s1 + s2;
}

int main(){
    cin >> n;
    for (int i = 0; i <= n; ++i){
        cin >> a[i];
    }

    build (1, 0, n - 1);
    update (1, 0, n - 1, 4, 26);


    cout << query (1, 0, n - 1, 0, 4);
    return 0;
}