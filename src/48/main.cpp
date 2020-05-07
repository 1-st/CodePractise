#include <iostream>
#include <vector>
#include <set>

using namespace std;


class Solution {
public:
    vector<int> findSubstring(string s, vector<string>& words) {
        vector<int> res{};
        if(s.length()==0||words.empty()){
            return res;
        }
        multiset<string> wordSet{};
        multiset<string> matchedSet{};
        int count = 0;
        int wordLength = words[0].length();
        for(const auto& i:words){
            wordSet.insert(i);
            count ++;
        }
        for(int i=0;i<s.length()-wordLength*count+1;i++){
            int matchedCount = 0;
            int p = i;
            while(p<s.length()&&matchedCount<count){
                string next = s.substr(p,wordLength);
                if(wordSet.count(next)>matchedSet.count(next)){
                    matchedCount++;
                    matchedSet.insert(next);
                    p+=wordLength;
                }else{
                    matchedSet.clear();
                    break;
                }
            }
            if(matchedCount == count){
                res.push_back(i);
                matchedSet.clear();
            }
        }
        return res;
    }
};

int main() {
    Solution s{};
    vector<string> words{};
    words.emplace_back("a");
    words.emplace_back("a");
    s.findSubstring("aaa",words);
    return 0;
}
