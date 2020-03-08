#include <iostream>
#include <deque>
using namespace std;


class MaxQueue{
public:
    MaxQueue()= default;
    void push_back(int value){
        while(!maximums.empty()&&value>=maximums.back()){
            maximums.pop_back();
        }
        data.push_back(value);
        maximums.push_back(value);
    }
    int pop_front(){
        if(maximums.empty()){
            return -1;
        }
        if(maximums.front()==data.front()){
            maximums.pop_front();
        }
        int res = data.front();
        data.pop_front();
        return res;
    }
    [[nodiscard]] int max_value() const{
        if(maximums.empty()){
            return -1;
        }
        return maximums.front();
    }
private:
    deque<int> data;
    deque<int> maximums;
};

int main(){
    auto* obj = new MaxQueue();
    int param_1 = obj->max_value();
    obj->push_back(1);
    int param_3 = obj->pop_front();
    delete obj;
    return 0;
}