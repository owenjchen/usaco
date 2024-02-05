/*
    Author: Dr. Owen Chen
    Datetime: 2024-01-28 
    USACO 2024 January Contest, Bronze
    Problem 3. Balancing Bacteria
    Version 1 - Nested Loop

    - This nested loop solution is the most simple and intuitive solution
    - Complexity: O(N^2)
    - Unforunately this solution will only solve test cases 1-10 and
       will time out on test cases 11-15 when N is very large.
       
    - See the two-cumulative sum version for a complete solution:
        https://github.com/owenjchen/usaco/blob/main/bronze_2024Jan/usaco2024b_jan_p3.cpp
*/
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    int N;
    cin >> N;
    vector<ll> bacteria(N);
    for (int i = 0; i < N; i++) {
        cin >> bacteria[i];
    }
    ll res = 0;
    for (int i = 0; i < N; i++) {
        if (bacteria[i] != 0) {
            res += abs(bacteria[i]);
            for (int j = i+1; j < N; j++) {
                bacteria[j] -= bacteria[i] * ( j - i + 1);
            }
        }
    }
    cout << res << endl;
    return 0;
}