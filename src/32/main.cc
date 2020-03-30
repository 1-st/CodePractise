//
// Created by admin on 2020/3/30.
//
#include <iostream>
#include <vector>
#include <map>
using namespace std;



class Solution {
public:
    vector<string> letterCombinations(const string &digits) {
        vector<string> res{};
        if(digits.empty()){
            return res;
        }
        vector<short> cur{}, size{};
        int count = 0;
        for (char digit : digits) {
            if (digit == '7' || digit == '9') {
                cur.push_back(3);
                size.push_back(3);
                count += 3;
            } else {
                cur.push_back(2);
                size.push_back(2);
                count += 2;
            }
        }
        while (count > 0) {
            string currentCombination{};
            for (int i = 0;i<digits.length();i++) {
                currentCombination += button[digits[i] - '0'][cur[i]];
            }
            res.push_back(currentCombination);
            int p = (int)digits.length() - 1;
            while (cur[p] == 0) p--;
            cur[p]--;
            count--;
            p++;
            while (p < digits.length()) {
                count += size[p];
                cur[p] = size[p];
                p++;
            }
        }
        string currentCombination{};
        for (char digit : digits) {
            currentCombination += button[digit - '0'][0];
        }
        res.push_back(currentCombination);
        return res;
    }
private:
    const string button[10]{"","","abc","def","ghi","jkl","mno","pqrs","tuv","wxyz"};
};



int main(){
    Solution s{};
    vector<string> str = s.letterCombinations("23");
    for (const string& i :str){
        cout<<i<<endl;
    }
    return 0;
}