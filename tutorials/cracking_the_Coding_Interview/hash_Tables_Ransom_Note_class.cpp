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

using namespace std;


struct node{
    string word;
    int number;
    node * next;
};

class hashmap{
    private:
        int findIndex(string word){
            int value = 0;
            for(int i=0; i<word.length();i++){
                value += (int)word[i];
            }
            return(value%100);
        }
        static const int tableSize = 100;
    
    public: 
        node* items[tableSize];
        hashmap(){
            for(int i=0; i<tableSize; i++){
                node* newItem = new node;
                newItem->word = "empty";
                newItem-> number = 0;
                newItem->next = NULL;
                items[i] = newItem;
            }
        }
    
        void insert(string word){
            int index = findIndex(word);
            if(items[index] == NULL){
                node* newItem = new node;
                newItem->word = word;
                newItem-> number = 1;
                newItem->next = NULL;
                items[index] = newItem;
            }
            else{
                node* ptr = items[index];
                while(ptr->next!=NULL){
                    if(ptr->word==word){
                        ptr->number++;
                        return;
                    }
                    else{
                        ptr = ptr->next;
                    }
                }
                node* newItem = new node;
                newItem->word = word;
                newItem-> number = 1;
                newItem->next = NULL;
                ptr->next = newItem;
                return;
            }
        }
        int size(){
            return tableSize;
        }
    bool search(node *query){
        int index = findIndex(query->word);
        node *ptr = items[index];
        while(ptr!=NULL){
            if(ptr->word == query->word && ptr->number >= query->number){
                return true;
            }
            else{
                ptr = ptr->next;
            }
        }
        return false;
    }
};

void buildHashmap(hashmap *map, vector<string> words){
    for(int i=0; i<words.size(); i++){
        map->insert(words[i]);
    }
    return;
}

bool checkFeasibility(hashmap &magazineMap, hashmap &ransomMap){
    for(int i=0; i<ransomMap.size(); i++){
        if(ransomMap.items[i]==NULL){
            continue;
        }
        else{
            bool foundMatch = false;
            node* ptr = ransomMap.items[i];
            while(ptr!=NULL){
                if(magazineMap.search(ptr)){
                    ptr = ptr->next;
                }
                else{
                    return false;
                }
            }
        }
    }
    return true;
}

bool ransom_note(vector<string> magazine, vector<string> ransom) {
    hashmap magazineMap;
    hashmap ransomMap;
    buildHashmap(&magazineMap, magazine);
    buildHashmap(&ransomMap, ransom);
    
    return checkFeasibility(magazineMap, ransomMap);
}

int main(){
    int m;
    int n;
    cin >> m >> n;
    vector<string> magazine(m);
    for(int magazine_i = 0;magazine_i < m;magazine_i++){
       cin >> magazine[magazine_i];
    }
    vector<string> ransom(n);
    for(int ransom_i = 0;ransom_i < n;ransom_i++){
       cin >> ransom[ransom_i];
    }
    if(ransom_note(magazine, ransom))
        cout << "Yes\n";
    else
        cout << "No\n";
    return 0;
}
