#include <bits/stdc++.h>

using namespace std;

void solve(vector <int> arr, int money) {
    // Complete this function
    unordered_multimap<int, int> costMap;
    for(int i=0; i<arr.size();i++){
        costMap.insert(pair <int, int> (arr[i],i+1));
    }
    
    for(int cost: arr){
        if((money == 2*cost) && costMap.count(cost)>1){
            auto range = costMap.equal_range(cost);
            int vec[2];
            int i = 1;
            for (auto it = range.first; it != range.second; ++it) {
                vec[i] = it->second;
                i--;
            }
            cout<<vec[0]<<" "<<vec[1]<<endl;
            return;
        }
        else if(costMap.find((money-cost)) != costMap.end()){
            cout<<((costMap.find(cost))->second)<<" "<<((costMap.find(money-cost))->second);
            cout<<endl;
            return;
        }
    }
    return;
}

int main() {
    int t;
    cin >> t;
    for(int a0 = 0; a0 < t; a0++){
        int money;
        cin >> money;
        int n;
        cin >> n;
        vector<int> arr(n);
        for(int arr_i = 0; arr_i < n; arr_i++){
           cin >> arr[arr_i];
        }
        solve(arr, money);
    }
    return 0;
}
