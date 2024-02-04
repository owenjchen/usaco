/*
    Author: Dr. Owen Chen
    Datetime: 2024-01-28 
    USACO 2024 Jan Bronze
    USACO 2024 January Contest, Bronze
    Problem 2. Cannonball
    http://www.usaco.org/index.php?page=viewproblem2&cpid=1372

    Dr. Chen's analysis:
    - Use a Simulation approach:
        - current_position
        - current_direction ( 1 = forward, -1 = backward)
        - current_power
        - next_position = current_position + current_direction * current_power
    - Use a Map data structure to keep a track on breaking records

    Complexity:
        O(n*log(n))

*/
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    int N, S;
    cin >> N >> S;
    vector<pair<int, int>> q;
    int t, v;
    map<int, bool> records;
    for(int i = 0; i < N; i++) {
        cin >> t >> v;
        q.push_back({t, v});
        records[i] = false;
    }
    int res = 0;
    int maxSimul = 1000000;
    int simul = 0;
    int current_pos = S - 1;
    int current_power = 1; 
    int current_direction = 1; // 1 = forward, -1 = backward
    while (current_pos < N && current_pos >= 0 && simul < maxSimul){
        simul++;        
        if (q[current_pos].first == 0) {
            current_power += q[current_pos].second;
            current_direction *= -1;
        } else if (current_power >= q[current_pos].second && !records[current_pos] ) {
                records[current_pos] = true;
                res++;
        }
        current_pos += current_power*current_direction;
    }

    cout << res << endl;
    return 0;
}