/*
    Author: Dr. Owen Chen
    Datetime: 2023-12-16 09:57
    USACO 2023 December Contest, Bronze
    Problem 1. Candy Cane Feast
    http://www.usaco.org/index.php?page=viewproblem2&cpid=1347

    Dr. Chen's Analysis:
        - Cow heights and candy heights are large numbers [1, 10^9].  Need long long numbers
        - Feed one candy for all cows.  Keep tracking of current candy height.
        - When a candy is finished, hang the next candy.  Cows will start in the same order from the first cow
          instead of the next cow to the last fed cow.
        - Algorithm:
            - Read N, M
            - Read N cows
            - Two loops M * N:
                - Loop over each candy of M:
                    - read candy cane height: cane
                    - set current candy lowest level at 0  (current_height)
                    - Loop over each cow j of N:
                        if cow[j] > current_height:
                            candy_eaten = min(cow[j], cane) - current_height
                            update cow[j]
                            update current_height
                        Break from the current candy loop if the candy is gone (current_height >= cane).
    - Complexity:  
        O(N*M)
*/
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
int main() {
    int N, M;
    cin >> N >> M;
    ll cows[N];
    for (int i = 0; i < N; i++) {        
        cin >> cows[i];
    }
    ll cane, current_height, candy_eaten;
    for (int i = 0; i < M; i++) {
        cin >> cane;
        current_height = 0;
        for (int j = 0; j < N && cane > current_height; j++) {   
            if (cows[j] > current_height) {
                candy_eaten = min(cows[j], cane) - current_height;
                cows[j] += candy_eaten;
                current_height += candy_eaten;
            }
        }
    }   
    for (auto& c: cows) {        
        cout << c << endl;
    }
    return 0;
}