#include <iostream>
#include <cstring>
#include <sstream>
#include <string>

using namespace std;

void Adj_mat (int n){
    cin >> n;
    cin.ignore();

    int mat[n+5][n+5] = {};
    for (int i = 1; i <= n; ++i){
        string s;
        getline (cin, s);
        stringstream ss(s);
        string res;
        while (ss >> res){
            mat[i][stoi(res)] = 1;
        }        
    }

    for (int i = 1; i <=n; ++i){
        for (int j = 1; j <=n; ++j){
            cout << mat[i][j] << " ";
        }
        cout << "\n";
    }
}

void EdgeList (int n){
    cin >> n;
    cin.ignore();
    for (int i = 1; i <= n; ++i){
        string s;
        getline(cin,s);
        stringstream ss (s);
        string res;
        while (ss >> res){
            if (stoi (res) >= i) cout << i << " "  << stoi(res) << "\n";
        }
    }
}
int main()
{
    int n;
    EdgeList(n);
    return 0;
}