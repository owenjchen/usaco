/*
    Author: Dr. Owen Chen
    Datetime: 2023-12-17 14:22
    USACO 2023 January Contest, Bronze
    Problem 1. Leaders
    http://www.usaco.org/index.php?page=viewproblem2&cpid=1275

    Complexity:
      O(N)
      
    https://github.com/owenjchen/usaco/blob/main/bronze_2023Jan/usaco2023b_jan_p1_leaders.cpp
*/
#include <bits/stdc++.h>
using namespace std;

int main(){
  int N;
  string breeds;
  cin >> N >> breeds;
  int temp;
  int cows[N];
  int firstG, firstH; //earliest guernsey, earliest holstein
  int lastG, lastH; //latest guernsey, latest holstein
  int ans;

  for (int i = 0; i < N; i++) {
        cin >> temp;
        cows[i] = temp - 1;
  }
  //get first G;
  for (int i = 0; i < N; i++) {
    if (breeds[i] == 'G'){
        firstG = i;
        break;
    }
  }
  //get last G;
  for (int i = N - 1; i >= 0; i--) {
    if (breeds[i] == 'G'){
      lastG = i;
      break;
    }
  }
  //get first H
  for (int i = 0; i < N; i++) {
    if (breeds[i] == 'H') {
      firstH = i;
      break;
    }
  }
  //last H
  for (int i = N - 1; i >= 0; i--) {
    if (breeds[i] == 'H') {
      lastH = i;
      break;
    }
  }

  if (cows[firstG] >= lastG){
    //earliest guernsey visited everybody and is the leader.
    //holstein leader has to visit earliest guernsey or visit all holsteins.
    //handle case where holstein leader has visited earliest guernsey.
    for (int i = 0; i < firstG; i++){
      if (i != firstH && breeds[i] == 'H' && cows[i] >= firstG)    //ignore the case where the holstein leader is earliest holstein
        ans++;
    }
  }
  if (cows[firstH] >= lastH)  {
    //earliest holstein visited everybody.
    for (int i = 0; i < firstH; i++) {
      if (i != firstG && breeds[i] == 'G' && cows[i] >= firstH)
        ans++;
    }
  }
  //check whether earliest guernsey and earliest holstein can together be leaders.
  if ((cows[firstG] >= lastG || (firstG <= firstH && cows[firstG] >= firstH)) && 
      (cows[firstH] >= lastH || (firstH <= firstG && cows[firstH] >= firstG)) ) {
    ans++;
  }
  cout << ans << endl;
  return 0;
}