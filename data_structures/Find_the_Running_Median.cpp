#include <map>
#include <set>
#include <list>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <stack>
#include <string>
#include <bitset>
#include <cstdio>
#include <limits>
#include <vector>
#include <climits>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <numeric>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <iomanip>

using namespace std;


class minIntHeap{
    vector<int> data;
    public: void print(){
        for(int i =0; i<data.size();i++){
            cout<<data[i]<<" ";
        }
        cout<<endl;
        return;   
    }
    
    public: int getSize(){
        return (data.size());
    }
    
    private: bool hasChildren(int parentIndex){
        return((2*parentIndex+1) < data.size());
    }
    
    private: bool hasParent(int childIndex){
        return((childIndex-1)/2>=0);
    }
    
    private: void swap(int indexOne, int indexTwo){
        int temp = data[indexOne];
        data[indexOne] = data[indexTwo];
        data[indexTwo] = temp;
        return;
    }
    
    private: void heapifyUp(){
        if(data.size()<2){
            return;
        }
        int parentIndex;
        int childIndex = data.size()-1;
        while(hasParent(childIndex)){
            parentIndex = (childIndex-1)/2;
            if(data[childIndex]<data[parentIndex])
            {
                swap(childIndex, parentIndex);
                childIndex = parentIndex;
            }
            else{
                return;
            }
        }
        return;
    }
    
    private: void heapifyDown(int index=0){
        while(hasChildren(index)){
            int smallestChildIndex = (2*index+1);
            if((2*index+2<=data.size()-1)){
                smallestChildIndex = (data[smallestChildIndex]<data[smallestChildIndex+1])? (smallestChildIndex): (smallestChildIndex+1);
            }
            if(data[index]<data[smallestChildIndex]){
                return;
            }
            else {
                swap(smallestChildIndex, index);
                index = smallestChildIndex;
            }
        }
        return;
    }
    
    private: void deleteElement(int index = 0){
        if(data.size()==0)
            return;
        data[index] = data[data.size()-1];
        data.pop_back();
        heapifyDown(index);
    }
    
    public: void addElement(int val){
        data.push_back(val);
        heapifyUp();
    }
    
    public: int popElement(){
        int val = data[0];
        deleteElement(0);
        return val;
    }
    
    public: int topElement(){
        return data[0];
    }
    
};

class maxIntHeap{
    vector<int> data;
    public: void print(){
        for(int i =0; i<data.size();i++){
            cout<<data[i]<<" ";
        }
        cout<<endl;
        return;   
    }
    
    public: int getSize(){
        return (data.size());
    }
    
    private: bool hasChildren(int parentIndex){
        return((2*parentIndex+1) < data.size());
    }
    
    private: bool hasParent(int childIndex){
        return((childIndex-1)/2>=0);
    }
    
    private: void swap(int indexOne, int indexTwo){
        int temp = data[indexOne];
        data[indexOne] = data[indexTwo];
        data[indexTwo] = temp;
        return;
    }
    
    private: void heapifyUp(){
        if(data.size()<2){
            return;
        }
        int parentIndex;
        int childIndex = data.size()-1;
        while(hasParent(childIndex)){
            parentIndex = (childIndex-1)/2;
            if(data[childIndex]>data[parentIndex])
            {
                swap(childIndex, parentIndex);
                childIndex = parentIndex;
            }
            else{
                return;
            }
        }
        return;
    }
    
    private: void heapifyDown(int index=0){
        while(hasChildren(index)){
            int largestChildIndex = (2*index+1);
            if((2*index+2<=data.size()-1)){
                largestChildIndex = (data[largestChildIndex]>data[largestChildIndex+1])? (largestChildIndex): (largestChildIndex+1);
            }
            if(data[index]>data[largestChildIndex]){
                return;
            }
            else {
                swap(largestChildIndex, index);
                index = largestChildIndex;
            }
        }
        return;
    }
    
    private: void deleteElement(int index = 0){
        if(data.size()==0)
            return;
        data[index] = data[data.size()-1];
        data.pop_back();
        heapifyDown(index);
    }
    
    public: void addElement(int val){
        data.push_back(val);
        heapifyUp();
    }
    
    public: int popElement(){
        int val = data[0];
        deleteElement(0);
        return val;
    }
    
    public: int topElement(){
        return data[0];
    }
    
};


float calculateMedian(minIntHeap &minHeap, maxIntHeap &maxHeap){
    if(minHeap.getSize() == maxHeap.getSize()){
        return float(minHeap.topElement() + maxHeap.topElement())/2;
    }
    else if(minHeap.getSize() == (maxHeap.getSize()+1)){
        return float(minHeap.topElement());
    }
    else if(maxHeap.getSize() == (minHeap.getSize()+1)){
        return float(maxHeap.topElement());
    }
    else{
        cout<<"error in sizes of minHeap and maxHeap"<<endl;
        return 0;
    }
}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    int num;
    cin>>num;
    minIntHeap minHeap;
    maxIntHeap maxHeap;
    float runningMedian;
    for(int i=0; i<num;i++){
        int val;
        cin>>val;
        if (i==0)
        {
            minHeap.addElement(val);
        }
        else if(i==1){
            if(minHeap.topElement()<val){
                maxHeap.addElement(minHeap.topElement());
                minHeap.popElement();
                minHeap.addElement(val);
            }
            else{
                maxHeap.addElement(val);
            }
        }
        else{
            if(val >= runningMedian){
                minHeap.addElement(val);
            }
            else{
                maxHeap.addElement(val);
            }
        }
        
        if((minHeap.getSize() - maxHeap.getSize())>1){
            maxHeap.addElement(minHeap.topElement());
            minHeap.popElement();
        }
        
        if((maxHeap.getSize()-minHeap.getSize())>1){
            minHeap.addElement(maxHeap.topElement());
            maxHeap.popElement();
        }
        //cout<<"min heap:  " ;
        //minHeap.print();
        //cout<<"max heap:  ";
        //maxHeap.print();
        
        runningMedian = calculateMedian(minHeap, maxHeap);
        cout<<setprecision(1) << fixed << runningMedian << endl;
    }
    return 0;
}
