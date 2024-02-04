/*
    Author: Dr. Owen Chen
    Datetime: 2023-12-16 09:57
    USACO 2023 December Contest, Bronze
    Problem 3. Farmer John Actually Farms
    http://www.usaco.org/index.php?page=viewproblem2&cpid=1349

    Dr. Chen's Analysis
    - Use long long for h & g since they involces a product of two integers (growth * days)
    - Define a data structure for Plant:
      struct Plant {
          ll h;
          ll g;
          int t;
        };
    - Consider corner case: N = 1 :
        output 0 if plants[0].t == 0
        else output -1
    - Consider corner case: N = 2:
      - sort two plants based on t
      - output 0 if plants[0].h > plants[1].h
        else if plants[0].g <= plants[1].g, it is impossible
        else calculate # of days:
          div_ceil((plants[1].h - plants[0].h + 1), (plants[0].g - plants[1].g)) 
    - General case N > 2:
        - sort plants based on ascending t: after certain days: tallest plant -> smallest plant
        - Do a pairwise comparison as in N = 2 case: compare plant i vs plant i+1
          if (plants[i].h >  plants[i+1].h) 
            - we are done: max_days = 0 
          if (plants[i].h <= plants[i+1].h) {
            // check growth rates
            if (plants[i].g <= plants[i+1].g) {
              max_days = -1;  // impossible
              break;
            } else {
              // calculate number of days for plant i to outgrow plant i+1
              days = div_ceil((plants[i+1].h - plants[i].h + 1), (plants[i].g - plants[i+1].g));
              if (days > max_days) 
                max_days = days;
            }
          }
    - integer ceiling division: 
        div_ceil(a, b) = (a + b - 1) / b

    Complexity:
        O(N)    
*/
#include <bits/stdc++.h>
using namespace std;
using ll = long long;   //alias ll = long long
struct Plant {
  ll h;
  ll g;
  int t;
};

bool sort_by_t(Plant& a, Plant& b ){
    return (a.t < b.t);
}

// ceil of division on two integers:  ceil(a/b) = floor((a + b - 1)/b)
int div_ceil(ll a, ll b) {
  return (a + b - 1) / b;
}

int main() {
  int Tests;
  cin >> Tests;
  while (Tests--) {
    int N;
    cin >> N;
    vector<Plant> plants(N);
    for (int i = 0; i < N; ++i) {
      cin >> plants[i].h;
    }
    for (int i = 0; i < N; ++i) {
      cin >> plants[i].g;
    }
    for (int i = 0; i < N; ++i) {
      cin >> plants[i].t;
    }
    if (N == 1) {
      if (plants[0].t == 0) {
        cout << 0 << endl;
      } else {
        cout << -1 << endl;
      }
    } else if ( N == 2){
      // sort plants based on t: after certain days: tallest plant -> smallest plant
      sort(plants.begin(), plants.end(), sort_by_t);
      if (plants[0].h > plants[1].h) {
        cout << 0 << endl;
      } else {
        if (plants[0].g <= plants[1].g) {
          cout << -1 << endl;
        } else {
          cout << div_ceil((plants[1].h - plants[0].h + 1), (plants[0].g - plants[1].g)) << endl;
        }
      }
    } else {
      // sort plants based on t: after certain days:  tallest plant -> smallest plant
      sort(plants.begin(), plants.end(), sort_by_t);
      // check each pair i, i+1,
      ll days = 0, max_days = 0;
      for (int i = 0; i < N-1; i++){
        if (plants[i].h <= plants[i+1].h) {
          if (plants[i].g <= plants[i+1].g) {
            max_days = -1;
            break;
          } else {
            days = div_ceil((plants[i+1].h - plants[i].h + 1), (plants[i].g - plants[i+1].g));
            if (days > max_days) 
              max_days = days;
          }
        }
      }
      // verify that after max_days, the plants are in the right order
      for (int i = 0; i < N-1; i++){
        if ((plants[i].h + plants[i].g*max_days) <= (plants[i+1].h + plants[i+1].g*max_days)) {
          max_days = -1;
          break;
        }
      }      
      cout << max_days << endl;
    }
  }
  return 0;
}
