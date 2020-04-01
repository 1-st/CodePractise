#include <iostream>
#include <vector>
#include <map>
using namespace std;

const int NUM = 4;



struct SetTree{
    int value;
    map<int,SetTree*> node;
    ~SetTree(){
        map<int,SetTree*>::iterator iter;
        for (iter=this->node.begin();iter!=this->node.end();iter++){
            delete iter->second;
        }
    };
};


void SetTreeInsert(SetTree & root,vector<int>& arr){
    SetTree * p = &root;
    for(int & i : arr){
        if(p->node.count(i)!=0){
            p = p->node.at(i);
        }else{
            auto newTree = new SetTree{};
            p->node.insert(std::pair<int,SetTree*>(i,newTree));
            p = newTree;
        }
    }
}

bool SetTreeSearch(SetTree & root,vector<int>& arr){
    SetTree * p = &root;
    for(int & i: arr){
        if(p->node.count(i)!=0){
            p = p->node.at(i);
        }else{
            return false;
        }
    }
    return true;
}

void SetTreeExport(SetTree& root,vector<vector<int>>* to,int len,int *arr){
    if(len==0){
        vector<int> v(NUM);
        for(int i=0;i<NUM;i++){
            v[i] = arr[NUM-i-1];
        }
        (*to).push_back(move(v));
    }else{
        map<int,SetTree*>::iterator iter;
        for(iter = root.node.begin();iter!=root.node.end();iter++){
            arr[len-1] = iter->first;
            SetTreeExport(*iter->second,to,len-1,arr);
        }
    }
}



class Solution {
private:
    SetTree set{};
public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        sort(nums.begin(),nums.end());
        auto combineResult = new int[NUM-2]{};
        combineIncrease(nums,0,combineResult,NUM-2,(int)nums.size()-2,target);
        delete[] combineResult;

        vector<vector<int>> res;
        auto arr = new int[NUM];
        SetTreeExport(this->set,&res,NUM,arr);
        return res;
    }
    static bool twoIndexSearch(vector<int>& arr,int start,int end,int target,vector<vector<int>>* twoIndexSearchResult){
        bool have1 = false;
        while(start<end){
            if(arr[start]+arr[end]==target){
                vector<int> v(2);
                v[0] = start;
                v[1] = end;
                (*twoIndexSearchResult).push_back(move(v));
                start++;
                end--;
                have1 = true;
            }else if(arr[start]+arr[end]<target){
                while(start<end&&arr[start]==arr[start+1]){
                    start++;
                }
                start++;
            }else{//>target
                while(start<end&&arr[end]==arr[end-1]){
                    end--;
                }
                end--;
            }
        }
        return have1;
    }
    void combineIncrease(vector<int>& arr, int start, int* CombineResult, int count,const int arrLen,int target) {
        for (int i = start; i < arrLen + 1 - count; i++) {
            CombineResult[count - 1] = i;
            if (count - 1 == 0) {
                int sum = 0;
                int twoIndexSearchTarget;
                for (int j=0;j<NUM-2;j++){
                    sum+=arr[CombineResult[j]];
                }
                twoIndexSearchTarget = target-sum;
                vector<vector<int>> twoIndexSearchResult{};
                if(twoIndexSearch(
                        arr,CombineResult[0]+1,
                        arrLen+1,twoIndexSearchTarget,
                        &twoIndexSearchResult)){
                   for(auto k:twoIndexSearchResult){
                       vector<int> v(NUM-2);
                       for(int j=0;j<NUM-2;j++){
                           v[j]=arr[CombineResult[j]];
                       }
                       v.push_back(arr[k[0]]);
                       v.push_back(arr[k[1]]);
                       SetTreeInsert(this->set,v);
                   }
                }
            } else combineIncrease(arr, i + 1, CombineResult, count - 1,arrLen,target);
        }
    }
};

int main() {
    auto a = Solution{};
    auto v = vector{-3,-2,-1,0,0,1,2,3};
    vector<vector<int>> res = a.fourSum(v,0);
    for (const auto& i:res){
        for(const auto j:i){
            cout<<j<<" ";
        }
        cout<<"\n";
    }
    return 0;
}
