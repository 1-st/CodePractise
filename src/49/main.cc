//
// Created by admin on 2020/5/8.
//

#include <vector>
#include <iostream>


using namespace std;

class Solution {
public:
    int maximalSquare(vector<vector<char>>& matrix) {
        if(matrix.empty()){
            return {};
        }
        int ** res;
        int lenX = matrix.size();
        int lenY = matrix[0].size();
        res = new int*[lenX];
        for(int i=0;i<lenX;i++){
            res[i] = new int[lenY]{0};
        }
        int max = 0;
        for(int i=0;i<lenX;i++){
            res[i][0] = matrix[i][0]-'0';
            if(res[i][0]>max){
                max = res[i][0];
            };
        }
        for(int i=0;i<lenY;i++){
            res[0][i] = matrix[0][i]-'0';
            if(res[0][i]>max){
                max = res[0][i];
            };
        }
        for(int i=1;i<lenX;i++){
            for(int j=1;j<lenY;j++){
                if(matrix[i][j]=='1'){
                    int min = (res[i-1][j] < res[i-1][j-1]) ? res[i-1][j] : res[i-1][j-1];
                    min = (min < res[i][j-1]) ? min : res[i][j-1];
                    res[i][j] = min+1;
                    if(res[i][j]>max){
                        max = res[i][j];
                    }
                }
            }
        }
        return max*max;
    }
};

int main(){
    vector<char> v1 = {'1','0','1','0','0'};
    vector<char> v2 = {'1','0','1','1','1'};
    vector<char> v3 = {'1','1','1','1','1'};
    vector<char> v4 = {'1','1','0','1','0'};
    vector<vector<char>> v;
    v.emplace_back(v1);
    v.emplace_back(v2);
    v.emplace_back(v3);
    v.emplace_back(v4);
    Solution s;
    s.maximalSquare(v);
}