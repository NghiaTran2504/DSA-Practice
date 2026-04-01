#include <iostream>

using namespace std;

void copy(int a[], int b[], int start, int end)
{
    for (int i = 0; i < end - start + 1; ++i)
        b[i] = a[i + start];
}
int mergesort(int a[], int n, int l, int r)
{
    int ans = 0;
    if (l >= r)
        return 0;

    int m = l + (r - l) / 2;
    ans += mergesort(a, n, l, m);
    ans += mergesort(a, n, m + 1, r);

    int len1 = m - l + 1, len2 = r - m;
    int x[len1], y[len2];
    copy(a, x, l, m);
    copy(a, y, m + 1, r);

    int i = 0, j = 0;
    while (i < len1 && j < len2)
    {
        if (x[i] <= y[j])
            a[l++] = x[i++];
        else
        {
            ans += len1 - i;
            a[l++] = y[j++];
        }
    }
    while (i < len1)
    {
        a[l++] = x[i++];
    }
    while (j < len2)
    {
        a[l++] = y[j++];
    }

    return ans;
}
int main()
{
    int a[] = {5, 4, 3, 2, 1};
    int Size = sizeof(a) / sizeof(a[0]);
    cout << mergesort(a, Size, 0, Size - 1) << "\n";

    for (int i = 0; i < Size; ++i)
    {
        cout << a[i] << " ";
    }
    return 0;
}