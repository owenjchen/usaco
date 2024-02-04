/*
    Author: Dr. Owen Chen
    Datetime: 2024-01-28
    USACO 2024 January Contest, Bronze
    Problem 1. Majority Opinion

    Dr. Chen's Analysis:
     - find any substring of 3 with two of them having the same type
     - use a set to keep tracking of types with a majority

    Complexity:
        O(N)

    https://github.com/owenjchen/usaco/blob/main/bronze_2024Jan/usaco2024b_jan_p1.cpp
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int T;
    cin >> T;
    while(T--) {
        int N;
        cin >> N;
        vector<int> h(N, 0);     
        for (int i = 0; i < N; i++) {
            cin >> h[i];
        }
        if (N == 1) {
            cout << h[0] << endl;
        } else if (N == 2) {
            if (h[0] == h[1])
                cout << h[0] << endl;
            else 
                cout << -1 << endl;
        } else {
            //find any substring of 3 with two of them having the same type
            set<int> favorite{};
            for (int i = 0; i < N-2; i++) {
                if (h[i] == h[i+1] || h[i] == h[i+2]) {
                    favorite.insert(h[i]);
                } else if ( h[i+1] == h[i+2]){
                    favorite.insert(h[i+1]);
                }
            }
            if (favorite.size() > 0) {
                int first = *(favorite.begin());
                cout << first;
                if (favorite.size() > 1) {
                    for(auto f: favorite) {
                        if (f != first) 
                            cout << " " << f;
                    }                
                }
            } else {
                cout << -1 ;
            }
            cout << endl;
        }
    }
    return 0;
}