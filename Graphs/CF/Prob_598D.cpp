#include <iostream>

using namespace std;

int dx[] = {0, 0, -1, 1};
int dy[] = {-1, 1, 0 , 0};
bool visited[1005][1005];
char a[1005][1005];
int id[1005][1005];
int result[1000005];
int n, m, k;

struct Pair{
    int x, y;
};

struct Stack{
    Pair stack[1000005];
    int size;

    Stack(){
        size = 0;
    }

    void push (Pair p){
        stack[++size] = p;
    }

    void pop (){
        size --;
    }
    bool empty(){
        return size == 0;
    }

    Pair top(){
        return stack[size];
    }
};

Stack st;

long long dfs (int n, int m, int x, int y, int flag){
    Pair p;
    p.x = x;
    p.y = y;
    st.push (p);
    visited[p.x][p.y] = true;
    id[p.x][p.y] = flag;
    long long cnt = 0;

    while (!st.empty()){
        Pair curr = st.top();
        st.pop();

        for (int i = 0; i < 4; ++i){
            Pair nxt;
            nxt.x = curr.x + dx[i];
            nxt.y = curr.y + dy[i];

            if (nxt.x >= 1 && nxt.x <= n && nxt.y >= 1 && nxt.y <= m){
                if (a[nxt.x][nxt.y] == '*'){
                    cnt++;
                }
                else if (a[nxt.x][nxt.y] == '.' && !visited[nxt.x][nxt.y]){
                    id[nxt.x][nxt.y] = flag;
                    visited[nxt.x][nxt.y] = true;
                    st.push (nxt);
                }
            }
        }
    }
    return cnt;
}

void Precompute (){
    int flag = 1;
    for (int i = 1; i <= n; ++i){
        for (int j = 1; j <= m; ++j){
            if (a[i][j] == '.' && !visited[i][j]){
                result[flag] = dfs (n, m, i, j, flag);
                flag++;
            }
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m >> k;
    for (int i = 1; i <= n; ++i){
        for (int j = 1; j <= m; ++j){
            cin >> a[i][j];
        }
    }

    Precompute();
    while (k--){
        int x, y; cin >> x >> y;
        cout << result[id[x][y]] << "\n";
    }
    return 0;
}