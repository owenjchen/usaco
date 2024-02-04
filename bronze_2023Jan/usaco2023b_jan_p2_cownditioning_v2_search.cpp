/*
    Author: Dr. Owen Chen
    Datetime: 2023-11-11 20:36
	USACO 2023 January Contest, Bronze
	Problem 2. Air Cownditioning II
	http://www.usaco.org/index.php?page=viewproblem2&cpid=1276  
	
	Version 2 - Use a recursive search

	Complexity:
		O(2^M * N * M):
		- O(2^M) for a recursive search
		- O(N) for checking feasible set
		- O(M) for calculating cost
		
	https://github.com/owenjchen/usaco/blob/main/bronze_2023Jan/usaco2023b_jan_p2_cownditioning_v2_search.cpp
*/

#include <bits/stdc++.h>
#include <climits>
using namespace std;

int N, M, K;
// {s, t, c}
vector<array<int, 3> > cows;
// {a, b, p, m}
vector<array<int, 4> > air_conditioners;
// ACSwitches[i] == true: the i-th air conditioner is used
vector<bool> ACSwitches;

//Find out which cow occupies stall i and return its cooling requirement;
int getCowRequirement(int i) {
    int cow_requirement = 0;
    for (int j = 0; j < N; j++) {
        auto &[s, t, c] = cows[j];
        if (s <= i && i <= t) {
            cow_requirement = c;
            break;
        }
    }
    return cow_requirement;
}

//Find out stall i temperature
int getStallCooling(int i) {
    int cooling = 0;
    for (int j = 0; j < M; j++) {
        if (ACSwitches[j]) { 
            auto &[a, b, p, m] = air_conditioners[j];
            if (a <= i && i <= b) { cooling += p; }
        }
    }
    return cooling;
}

/*
 * Based on 'ACSwitches', determine if the current subset of air conditioners suffices
 * the constraints, 
 * 
 */
bool feasibleSet(){
	bool is_feasible = true;
    int stall_cooling, cow_temperature;
	// iterate through all stalls
	for (int i = 1; i <= K; i++) {
		// iterate through air conditioners to find the current cooling units
		stall_cooling = getStallCooling(i);
        cow_temperature = getCowRequirement(i);
		// For each position, the requirement of the cow must be met
		if (stall_cooling < cow_temperature) {
			is_feasible = false;
			break;
		}
	}
	return is_feasible;
}

int calcCost() {
	int cost = 0;
	for (int i = 0; i < M; i++) {
		if (ACSwitches[i]) 
			cost += air_conditioners[i][3]; 
	}
	return cost;
}

/**
 * Expand the subset, represented by 'ACSwitches', by choosing to (not) use the i-th
 * air conditioner
 */
void search(int i, int& min_cost) {
	if (i == M) {
		if (feasibleSet()) {
			int cost = calcCost();
			if (cost < min_cost) 
				min_cost = cost;
		}
	} else {
		search(i + 1, min_cost);
		ACSwitches[i] = true;
		search(i + 1, min_cost);
		ACSwitches[i] = false;	
	}
}

int main() {
	cin >> N >> M;

	for (int i = 0; i < N; i++) {
		int s, t, c;
		cin >> s >> t >> c;
		cows.push_back({s, t, c});
	}
	K = 0;	
	int min_cost = 0;
	for (int i = 0; i < M; i++) {
		int a, b, p, m;
		cin >> a >> b >> p >> m;
		air_conditioners.push_back({a, b, p, m});
		min_cost += m;
		if (b > K) {
			K = b;
		}
	}
	//initialize to all ACs to be off;
	ACSwitches.assign(M, false);
	search(0, min_cost);
	cout << min_cost << endl;
}