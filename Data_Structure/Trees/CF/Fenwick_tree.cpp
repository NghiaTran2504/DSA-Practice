#include <iostream>

using namespace std;
#define ll long long
struct FenwickTree
{
    ll *BIT;
    ll *a;
    int n;

    FenwickTree()
    {
        cin >> n;
        BIT = new ll[n + 5]();
        a = new ll[n + 5]();
    }
    void update(int pos, int val)
    {
        while (pos <= n)
        {
            BIT[pos] += val;
            pos += pos & -pos;
        }
    }

    ll query(int pos)
    {
        ll ans = 0;
        while (pos)
        {
            ans += BIT[pos];
            pos -= pos & -pos;
        }

        return ans;
    }

    void clear()
    {
        delete[] BIT;
        delete[] a;
    }
};

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    FenwickTree tree;

    for (int i = 1; i <= tree.n; ++i)
    {
        cin >> tree.a[i];
        tree.update(i, tree.a[i]);
    }

    for (int i = 1; i <= tree.n; ++i)
        cout << tree.BIT[i] << " ";

    int l, r;
    cin >> l >> r;
    cout << "\n\n"
         << tree.query(r) - tree.query(l - 1) << " ";
    tree.clear();

    return 0;
}