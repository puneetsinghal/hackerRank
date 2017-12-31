#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

void print(vector<int> const &data){
    for(int i =0; i<data.size();i++){
        cout<<data[i]<<" ";
    }
    cout<<endl;
    return;   
}

bool hasParent(int size, int childIndex){
    return((childIndex-1)/2>=0);
}

void heapify(vector<int> &data){
    if(data.size()<2){
        return;
    }
    int level, parentIndex;
    //level = floor(log2(data.size()));
    int childIndex = data.size()-1;
    //for(int l=level-1; l>=0; l--){
    while(hasParent(data.size(), childIndex)){    
        //print(data);
        //cout<<"Children Index:  "<<childIndex<<endl;
        parentIndex = (childIndex-1)/2;
        if(data[childIndex]<data[parentIndex])
        {
            //cout<<"data exchange"<<data[globalIndexCurrent]<<"    "<<data[globalIndexPrev]<<endl;
            int temp = data[parentIndex];
            data[parentIndex] = data[childIndex];
            data[childIndex] = temp;
            childIndex = parentIndex;
        }
        else{
            return;
        }
    }
    return;
}

bool hasChildren(vector<int> const& data, int parentIndex){
    return((2*parentIndex+1) < data.size());
}

void deleteElement(vector<int> &data, int index){
    if(data.size()==0)
        return;
    data[index] = data[data.size()-1];
    data.pop_back();
    
    while(hasChildren(data,index)){
        int smallestChildIndex = (2*index+1);
        if((2*index+2<=data.size()-1)){
            smallestChildIndex = (data[smallestChildIndex]<data[smallestChildIndex+1])? (smallestChildIndex): (smallestChildIndex+1);
        }
        if(data[index]<data[smallestChildIndex]){
            return;
        }
        else {
            int temp = data[index];
            data[index] = data[smallestChildIndex];
            data[smallestChildIndex] = temp;
            index = smallestChildIndex;
        }
    }
    return;
}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   int numQuery;
    int num;
    cin>>num;
    vector<int> data;
    int desiredSweetness;
    cin>>desiredSweetness;
    for(int query=0; query<num; query++){
        int val;
        cin>>val;
        data.push_back(val);
        heapify(data);
    }
    int count = 0;
    while(data[0]<desiredSweetness && data.size()>1){
        //print(data);
        int cookiesToMix1 = data[0];
        int smallestChildIndex = 1;
        if((data.size()>2)){
            smallestChildIndex = (data[smallestChildIndex]<data[smallestChildIndex+1])? (smallestChildIndex): (smallestChildIndex+1);
        }
        int cookiesToMix2 = data[smallestChildIndex];
        deleteElement(data,smallestChildIndex);
        //print(data);
        deleteElement(data,0);
        //print(data);
        int newCookie = cookiesToMix1 + 2* cookiesToMix2;
        data.push_back(newCookie);
        heapify(data);
        count++;
    }
    //print(data);
    if(data.size()==1 && data[0]<desiredSweetness)
        cout<<-1;
    else
        cout<<count;
    return 0;
}