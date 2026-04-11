#include <iostream>

using namespace std;

/* NghiaDepTry */

int dr[] = {0, 0, -1, -1, -1, 1, 1, 1};
int dc[] = {-1, 1, -1, 0, 1, -1, 0, 1};

struct Queen{
    int r, c;
    
};

struct Dest{
    int r, c;
};

struct King{
    int r, c;
};

Queen cq;
King nghia;
Dest dest;
bool visited[1005][1005];

void input ( int &n){
    cin >> n;
    for (int i = 1; i <= 3; ++i)
    {
        int x, y;
        cin >> x >> y;
        switch (i)
        {
        case 1:
            cq.c = x;
            cq.r = y;
            break;
        case 2:
            nghia.c = x;
            nghia.r = y;
            break;
        case 3:
            dest.c = x;
            dest.r = y;
            break;
        default:
            break;
        }
    }
}

int diagonal(int a, int b)
{
    if (a >= b) return a - b;
    return b - a;
}
// bool dfs (int n, int row, int col){
//     if (row == dest.r && col == dest.c){
//         return true;
//     }
//     else{
//         int nxt_r, nxt_c;
//         for (int i = 0; i < 8; ++i){
//             nxt_r = row + dr[i];
//             nxt_c = col + dc[i];
//             /* Check boundaries */
//             if (nxt_c >= 1 && nxt_c <= n && nxt_r >= 1 && nxt_r <= n
//                 && nxt_c != cq.c && nxt_r != cq.r
//                 && diagonal(nxt_c, cq.c) != diagonal(nxt_r, cq.r)){
//                 if (!visited[nxt_r][nxt_c])
//                 {
//                     visited[nxt_r][nxt_c] = true;
//                     if (dfs (n, nxt_r, nxt_c)) return true;
//                 }
//             }
//         }
//     }
//     return false;
// }
void solve(int n)
{
    /* DIEU KIEN THOA DE XET*/
    bool same_row = (nghia.r < cq.r && dest.r < cq.r || nghia.r > cq.r && dest.r > cq.r);
    bool same_col = (nghia.c < cq.c && dest.c < cq.c || nghia.c > cq.c && dest.c > cq.c);

    if (same_row == true && same_col == true) cout << "YES";
    else cout << "NO";
}
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n;
    input (n);
    solve(n);
    return 0;
}