/*
    Author: Dr. Owen Chen
    Datetime: 2023-11-11 20:36
	USACO 2023 January Contest, Bronze
	Problem 2. Air Cownditioning II
	http://www.usaco.org/index.php?page=viewproblem2&cpid=1276    

	Version 1 - Generate all feasible subsets and find a subset with the min cost

	Complexity:
		O(2^M * N * M):
		- O(2^M) for # of subsets
		- O(N) for checking feasible set
		- O(M) for calculating cost
	
	https://github.com/owenjchen/usaco/blob/main/bronze_2023Jan/usaco2023b_jan_p2_cownditioning_v1_subsets.cpp
*/
#include <bits/stdc++.h>
#include <climits>
using namespace std;

//Generate all subsets of size K with boolean elements

template<typename T>
void generateSubsets(int K, vector<vector<T> >& includeSet,
				vector<bool>& elements, int index){
	// Add current elements to includeSet 
	includeSet.push_back(elements);

	// Generate includeSet by recursively including & excluding elements
	for (int i = index; i < K; i++) {
		// Add the current element to the elements
		elements[i] = true;
		// Recursively generate includeSet with the current element included
		generateSubsets(K, includeSet, elements, i + 1);   
		// Done with the current element - remove it from the elements
		// (backtracking)
		elements[i] = false;
	}
}

vector<vector<bool> > subsets(int K){
	vector<bool> elements(K, false);
	vector<vector<bool> > includeSet;
	generateSubsets(K, includeSet, elements, 0);
	return includeSet;
}

int N, M, K;
// {s, t, c}
vector<array<int, 3>> cows;
// {a, b, p, m}
vector<array<int, 4>> air_conditioners;

//Find out which cow occupies stall i and return its cooling requirement;
int getCowRequirement(int i) {
    for (int j = 0; j < N; j++) {
        auto &[s, t, c] = cows[j];
        if (s <= i && i <= t) {
            return c;
        }
    }
    return 0;
}

//Find out stall i temperature
int getStallCooling(int i, vector<bool>& ACSwitches) {
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
bool feasibleSet(vector<bool>& ACSwitches){
	bool is_feasible = true;
    int stall_cooling, cow_temperature;
	// iterate through all stalls
	for (int i = 1; i <= K; i++) {
		// iterate through air conditioners to find the current cooling units
		stall_cooling = getStallCooling(i, ACSwitches);
        cow_temperature = getCowRequirement(i);
		// For each position, the requirement of the cow must be met
		if (stall_cooling < cow_temperature) {
			is_feasible = false;
			break;
		}
	}
	return is_feasible;
}

int calcCost(vector<bool>& ACSwitches) {
	int cost = 0;
	for (int i = 0; i < M; i++) {
		if (ACSwitches[i]) 
			cost += air_conditioners[i][3]; 
	}
	return cost;
}


int main() {

	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		int s, t, c;
		cin >> s >> t >> c;
		cows.push_back({s, t, c});
	}
	K = 0;	
	int min_cost = 0;   //calculate initial min_cost when all ACs are on
	for (int i = 0; i < M; i++) {
		int a, b, p, m;
		cin >> a >> b >> p >> m;
		air_conditioners.push_back({a, b, p, m});
		min_cost += m;
		if (b > K) {
			K = b;
		}
	}

	//Generate a boolean array for all conditioners.
	int cost;
	bool feasible;
	vector<vector<bool> > subs = subsets(M);
    for (vector<bool>& ACSwitches : subs) {
		if (feasibleSet(ACSwitches)) {
        	cost = calcCost(ACSwitches);
			if (cost < min_cost)
				min_cost = cost;
		}			
    }
	cout << min_cost << endl;
}