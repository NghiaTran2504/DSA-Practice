#include <iostream>
#include <vector>
using namespace std;

int mergesort(vector<int> &v, int l, int r)
{
    if (l >= r)
        return 0;
    int ans = 0;

    int m = l + (r - l) / 2;
    ans += mergesort(v, l, m);
    ans += mergesort(v, m + 1, r);

    vector<int> x(v.begin() + l, v.begin() + m + 1);
    vector<int> y(v.begin() + m + 1, v.begin() + r + 1);

    int i = 0, j = 0;
    while (i < x.size() && j < y.size())
    {
        if (x[i] <= y[j])
            v[l++] = x[i++];
        else
        {
            ans += x.size() - i;
            v[l++] = y[j++];
        }
    }

    while (i < x.size())
        v[l++] = x[i++];
    while (j < y.size())
        v[l++] = y[j++];

    return ans;
}
int main()
{
    vector<int> v{5, 4, 3, 2, 1};
    cout << mergesort(v, 0, v.size() - 1) << "\n";

    for (int i = 0; i < v.size(); ++i)
        cout << v[i] << " ";
    return 0;
}