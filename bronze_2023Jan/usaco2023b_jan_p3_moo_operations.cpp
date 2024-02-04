/*
    Author: Dr. Owen Chen
    Datetime: 2023-12-17 16:16    
    USACO 2023 January Contest, Bronze
    Problem 3. Moo Operations
    http://www.usaco.org/index.php?page=viewproblem2&cpid=1277

    Dr. Chen's analysis:
    - Check the input string contains the following subscrings and 
    the number of operations need to convert to MOO:
        MOO  - 0 
        OOO  - 1
        MOM  - 1
        OOM  - 2
    - Make sure to check corner cases when the input string is less than or equal to 3 characters.

    Complexity:
        O(Q * log(N))  with log(N) for a substring search find()

*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int Q;
    cin >> Q;
    for (int i = 0; i < Q; i++){
        string Qstring;
        cin >> Qstring;
        int res = -1;
        int size = Qstring.size();
        if (size < 3) {
            cout << -1 << endl;
        } else if (size == 3) {
            if (Qstring[1] != 'O') 
                cout << -1 << endl;
            else if (Qstring == "MOO")
                cout << 0 << endl;
            else if (Qstring == "MOM" || Qstring == "OOO")
                cout << 1 << endl;
            else if (Qstring == "OOM") 
                cout << 2 << endl;
        } else {
            if (Qstring.find("MOO") != string::npos) 
                cout << size - 3 << endl;
            else if (Qstring.find("MOM") != string::npos || Qstring.find("OOO") != string::npos) 
                cout << size - 2 << endl;    
            else if (Qstring.find("OOM") != string::npos) 
                cout << size - 1 << endl; 
            else
                cout << -1 << endl;                                 
        }
    }
    return 0;
}