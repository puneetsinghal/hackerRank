#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

void print(vector<int> data){
	for (int i = 0; i < data.size(); ++i)
	{
		cout<<data[i]<<" ";
	}
	cout<<endl;
}

void move(vector<int> &data, int _case, int start, int end){
    
	vector<int> newVec;
	newVec.insert(newVec.begin(), data.begin()+start-1, data.begin()+end);
    // print(newVec);
	// print(data);
    data.erase(data.begin()+start-1, data.begin()+end);
    // print(data);
    if(_case==1){
        data.insert(data.begin(), newVec.begin(), newVec.end());
    }
    else{
        data.insert(data.end(), newVec.begin(), newVec.end());
    }
	
}


int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    int N;
    cin>>N;

    int M;
    cin>>M;

    vector<int> data;

    for (int i = 0; i < N; ++i)
    {
    	int val;
    	cin>>val;
    	data.push_back(val);
    }


    for (int query = 0; query < M; ++query)
    {
    	int _case, start, end;
    	cin>>_case;
    	cin>> start;
    	cin>> end;
    	move(data,_case,start,end);
        // print(data);
    }

    cout<<abs(data[0]-data[N-1])<<endl;
    print(data);
    return 0;
}