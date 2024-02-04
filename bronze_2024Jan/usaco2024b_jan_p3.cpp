/*
    Author: Dr. Owen Chen
    Datetime: 2024-02-04
    USACO 2024 January Contest, Bronze
    Problem 3. Balancing Bacteria
    http://www.usaco.org/index.php?page=viewproblem2&cpid=1373

    Dr. Chen's analysis:
    Perform two accumulated sums:
        accum_sum1(i) = sum(-bateria(0 ... i))
        accum_sum2(i) = sum(accum_sum1(0, ..., i) - bateria(i))
        bateria(i) += accum_sum2(i)
        res = sum(abs(bateria(i)))

    Complexity:
        O(n)
*/
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    int N;
    cin >> N;
    vector<ll> bacteria(N);
    for (int i = 0; i < N; i++)
    {
        cin >> bacteria[i];
    }
    ll res = 0, accum_sum1 = 0, accum_sum2 = 0;
    for (int i = 0; i < N; i++)
    {
        bacteria[i] += accum_sum2; // bacteria[i] += sum(sum(-bateria(0 ... i-1) - bateria(i-1))
        accum_sum1 -= bacteria[i]; // accum_sum1 = sum(-bateria(0 ... i))
        accum_sum2 += accum_sum1 - bacteria[i]; // accum_sum2 = sum(sum(-bateria(0 ... i) - bateria(i))
        res += abs(bacteria[i]);
    }
    cout << res << endl;
    return 0;
}