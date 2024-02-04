/*
    Author: Dr. Owen Chen
    Datetime: 2023-12-16 09:57
    USACO 2023 December Contest, Bronze
    Problem 2. Cowntact Tracing 2
    http://www.usaco.org/index.php?page=viewproblem2&cpid=1348
    
    Dr. Chen's Analysis
    - Consider corner cases first
        - corner case 1: all infected
        - corner case 2: 0, 1 or 2 infected
    - General case: 3 or more infected:
        - bateria started from the left side
        - get cows infected from the left side:
            left = # of cows infected on the left
        - bateria started from the right side:
            right = # of cows infected on the right
        - bateria started in the middle:
                min_infected = 0;
                int growth = 2*min_nights + 1;
                if (left > 0) {
                    min_infected += div_ceil(left, growth);
                }
                if (right > 0) {
                    min_infected += div_ceil(right, growth);
                }
                for (int i : middles){
                    min_infected += div_ceil(i, growth);
                }
    - Integer ceilling division:
        [a/b] = (a + b - 1) / b

    Complexity:
        O(N)
        
    https://github.com/owenjchen/usaco/blob/main/bronze_2023Dec/usaco2023b_dec_p2.cpp
*/
#include <bits/stdc++.h>
using namespace std;

// ceiling division ceil (a/b) = floor (a+b-1)/b
int div_ceil(int a, int b) {
    return (a + b - 1) / b;
}

int main() {
    int N;
    cin >> N;
    string cows;
    cin >> cows;
    int infected=0;
    for(int i = 0; i < N; i++) {
        if (cows[i] == '1'){
            infected++;
        } 
    }
    if (infected == N) {
        cout << 1 << endl;   // corner case 1: all infected
    } else if (infected <= 2) {
        cout << infected << endl;  // corner case 2: 0, 1 or 2 infected
    } else {
        int min_infected = 0;
        int left=0, right=0;
        int last_infected = 0;
        //get number infected cows on the left edge
        if (cows[0] == '1') {
            last_infected = 1;
            while(last_infected < N && cows[last_infected] == '1')
                last_infected++;
            left = last_infected;
        }
        //get number of infected cows on the right edge
        if (cows[N-1] == '1') {
            last_infected = N-2;
            while(last_infected >= 0 && cows[last_infected] == '1')
                last_infected--;
            right = N - last_infected - 1;
        }
        if (left + right == infected) {
            // only on the left edge and/or right edge
            if (left > 0 && right > 0) {
                if (left == right) 
                    min_infected = 2;
                else if (left > right)
                    min_infected = (left + 2*right - 2) / (2*right - 2) + 1;
                else 
                    min_infected = (left + 2*left - 2) / (2*left - 2) + 1;               
            } else 
                min_infected = 1;
        } else {
            // having middle groups
            vector<int> middles;            
            min_infected = 0;
            int min_nights = 0;            
            int min_size = N;
            int size = 0;
            for(int i = left; i < (N-right); i++){
                if (cows[i] == '1' )
                    size++;
                else if (size > 0) {
                    middles.push_back(size);
                    if (size < min_size) 
                        min_size = size;
                    size = 0;
                }
            }
            if (min_size % 2 == 0) {
                min_nights = (min_size - 2) / 2;
            } else  {
                min_nights =  (min_size - 1) / 2;
            } 
            if (left > 0) 
                min_nights = min(min_nights, left-1);
            if (right > 0)
                min_nights = min(min_nights, right-1);
            if (min_nights == 0) {
                min_infected = infected;
            } else {
                min_infected = 0;
                int growth = 2*min_nights + 1;
                if (left > 0) {
                    min_infected += div_ceil(left, growth);
                }
                if (right > 0) {
                    min_infected += div_ceil(right, growth);
                }
                for (int i : middles){
                    min_infected += div_ceil(i, growth);
                }
            }
        } 
        cout << min_infected << endl;
    }
    return 0;
}