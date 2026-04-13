#include <iostream>

using namespace std;

int gcd (int a, int b){
    if (b == 0) return a;
    return gcd (b, a % b);
}

struct Pair{
    int GCD;
    int count;

    Pair(){
        count = 0;
    }
};

Pair merge (Pair left, Pair right){
    Pair parent;

    int gcd_parent = gcd(left.GCD, right.GCD);
    parent.GCD = gcd_parent;

    if (left.GCD == right.GCD)
    {
        parent.count = left.count + right.count;
    }
    else if (gcd_parent ==  left.GCD)
    {
        parent.count = left.count;
    }
    else if (gcd_parent == right.GCD)
    {
        parent.count = right.count;
    }
    else
    {
        parent.count = 0;
    }

    return parent;
}
void build (int v, int l, int r, int* a, Pair seg[]){
    if (l == r){
        seg[v].GCD = a[l];
        seg[v].count = 1;
    }
    else{
        int m = l + (r - l)  / 2;
        build (2 * v, l, m, a, seg);
        build (2 * v + 1, m + 1, r, a, seg);
        seg[v] = merge(seg[2 * v], seg[2 * v + 1]);
    }
}

int maxx (int a, int b){
    if (a >= b) return a;
    return b;
}
int minn (int a, int b){
    if (a <= b) return a;
    return b;
}
Pair query (int v, int segL, int segR, int l, int r, int *a, Pair seg[]){
    if (l > r){
        Pair p;
        p.GCD = 0;
        p.count = 0;
        return p;
    }
    if (segL == l && segR == r){
        return seg[v];
    }
    else{
        int segM = segL + (segR - segL)  / 2;
        Pair p1 = query (2 * v, segL, segM, l, minn (r, segM), a, seg);
        Pair p2 = query (2 * v + 1, segM + 1, segR, maxx (l, segM + 1), r, a, seg);
        return merge (p1, p2);
    }
    
}
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    
    int n; cin >> n;
    int a[n+5]{};
    for (int i = 0; i < n; ++i) cin >> a[i];
    Pair seg[4 * n];
    build (1, 0, n - 1, a, seg);

    int t;
    cin >> t;
    while (t--){
        int l, r;
        cin >> l >> r;
        --l, -- r;
        cout << (r - l) + 1 - query (1, 0, n - 1, l, r, a, seg).count << "\n";
    }
    return 0;
}