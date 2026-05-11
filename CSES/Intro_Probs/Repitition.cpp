#include <iostream>
#include <string>

using namespace std;

int main()
{
    string s; cin >> s;
    int ans = 0;
    char prev_char = s[0];
    int count = 0;
    for (int i = 0; i < s.size(); ++i){
        if (prev_char == s[i]){
            ++count;
        }
        else{
            if (count > ans) ans = count;
            count = 1;
            prev_char = s[i];
        }

        if (i == s.size() - 1){
            if (count > ans) ans = count;
        }
    }

    cout << ans;
    return 0;
}