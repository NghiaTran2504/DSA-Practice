#include <iostream>

using namespace std;
#define ll long long

void mergesort(int[], int, int);
int lowerbound(int[], int, int);
struct Fenwick
{
    ll *BIT;
    ll *a;
    int n;

    Fenwick()
    {
        cin >> n;
        BIT = new ll[n + 5]();
        a = new ll[n + 5]();

        for (int i = 1; i <= n; ++i)
        {
            cin >> a[i];
        }
    }

    void update(int pos)
    {
        while (pos <= n)
        {
            BIT[pos] += 1;
            pos += pos & -pos;
        }
    }

    ll query(int val)
    {
        ll ans = 0;
        while (val)
        {
            ans += BIT[val];
            val -= val & -val;
        }
        return ans;
    }

    void clear()
    {
        delete[] a;
        delete[] BIT;
    }
};

void mergesort(int a[], int left, int right)
{
    if (left >= right)
        return;
    ll mid = left + (right - left) / 2;
    mergesort(a, left, mid);
    mergesort(a, mid + 1, right);

    int len1 = mid - left + 1;
    int len2 = right - mid;
    int i = 0, j = 0;

    int x[len1], y[len2];
    for (int i = 0; i < len1; ++i)
        x[i] = a[i + left];
    for (int i = 0; i < len2; ++i)
        y[i] = a[mid + 1 + i];

    while (i < len1 && j < len2)
    {
        if (x[i] <= y[j])
            a[left++] = x[i++];
        else
            a[left++] = y[j++];
    }

    while (i < len1)
        a[left++] = x[i++];
    while (j < len2)
        a[left++] = y[j++];
}

int lowerbound(int a[], int n, int val)
{
    int left = 1, right = n + 1;
    while (left < right)
    {
        int mid = left + (right - left) / 2;
        if (a[mid] >= val)
            right = mid;
        else
            left = mid + 1;
    }

    return right;
}
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    Fenwick T;

    int b[T.n + 5];
    for (int i = 1; i <= T.n; ++i)
    {
        b[i] = T.a[i];
    }

    mergesort(b, 1, T.n);

    // Number compress:
    for (int i = 1; i <= T.n; ++i)
    {
        T.a[i] = lowerbound(b, T.n, T.a[i]);
    }

    ll cnt = 0;
    for (int i = 1; i <= T.n; ++i)
    {
        ll kq = T.query(T.a[i]);
        cnt += i - kq - 1;
        T.update(T.a[i]);
    }

    cout << cnt << " ";
    T.clear();
    return 0;
}