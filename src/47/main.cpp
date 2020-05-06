#include <iostream>
#include <vector>

struct ListNode {
    ListNode(int x) : val(x), next(nullptr) {}
    int val;
    ListNode *next;
 };


using namespace std;

class Solution {
public:
    ListNode* reverseKGroup(ListNode* head, int k) {
        ListNode * headReturn = resetHead(head,k);
        ListNode * pre = nullptr;
        auto ** pArr = new ListNode*[k];
        int i = -1;
        int count = 0;
        ListNode * p = head;
        while(p){
            if(count<k){
                pArr[++i] = p;
                count++;
                p = p->next;
            }else{
                ListNode * h = reverseGroup(pArr,i,&pre);
                pre = h;
                count = 0;
                i = -1;
            }
        }
        if(i+1==k){
            ListNode* h = reverseGroup(pArr,i,&pre);
            pre = h;
            if(pre!= nullptr){
                pre->next = nullptr;
            }
        }else if(i!=-1){
            if(pre!= nullptr){
                pre->next = pArr[0];
            }
        }
        delete[] pArr;
        return headReturn;
    }
private:
    static inline ListNode* reverseGroup(ListNode ** pArr,int i,ListNode ** pre){
        if((*pre)!=nullptr){
            (*pre)->next = pArr[i];
        }
        for(int ii =i;ii>0;ii--){
            pArr[ii]->next = pArr[ii-1];
        }
        return pArr[0];
    }

    static inline ListNode * resetHead(ListNode * head,int k){
        ListNode * headOrigin = head;
        int count = 0;
        while(head!=nullptr){
            head = head->next;
            count++;
            if(count==k-1){
                return head;
            }
        }
        return headOrigin;
    }
};

int main() {
    ListNode n5(5);
    ListNode n4(4);
    ListNode n3(3);
    ListNode n2(2);
    ListNode n1(1);
    n5.next = nullptr;
    n4.next = &n5;
    n3.next = &n4;
    n2.next = &n3;
    n1.next = &n2;
    Solution s{};
    s.reverseKGroup(&n1,3);
    return 0;
}
