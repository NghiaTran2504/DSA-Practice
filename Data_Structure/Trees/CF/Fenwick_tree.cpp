#include <iostream>

using namespace std;

int n, a[200000], BIT[200000];

// Update BIT
void update(int pos, int val)
{
    for (; pos <= n; pos += pos & (-pos))
    {
        BIT[pos] += val;
    }
}

// Sum a[1] + a[2] + ... + a[pos]
long long sumQuerry(int pos)
{
    long long ans = 0;
    while (pos >= 1)
    {
        ans += BIT[pos];
        pos = pos - (pos & (-pos));
    }

    return ans;
}
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n;
    for (int i = 1; i <= n; ++i)
    {
        cin >> a[i];
        update(i, a[i]);
    }

    for (int i = 1; i <= n; ++i)
        cout << BIT[i] << " ";
    return 0;
}