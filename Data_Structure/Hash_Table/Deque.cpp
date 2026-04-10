#include <iostream>

using namespace std;

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int q; cin >> q;
    int *deque = new int[2 * q + 5]{};
    int head = q, tail = q + 1;
    while (q--){
        int cmd;
        cin >> cmd;
        switch (cmd){
            case 1:
                int val; cin >> val;
                deque [tail++] = val;
                break;
            case 2:
                cin >> val;
                deque [head--] = val;
                break;

            case 3: 
                cout << deque[--tail] << "\n";
                break;
            
            case 4:
                cout << deque[++head] << "\n";
                break;

            case 5:
                cin >> val;
                cout << deque[head + 1 + val] << "\n";
            default:
                break;
        }
    }
    return 0;
}