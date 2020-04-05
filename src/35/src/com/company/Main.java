package com.company;
import java.util.LinkedList;
import java.util.Queue;

class ListNode{
    int val;
    ListNode next;
    ListNode(int x){
        val = x;
    }
    public static void listForEach(ListNode root){
        var p = root;
        while(p!=null){
            System.out.println(p.val);
            p = p.next;
        }
    }
}
//很愚蠢的解法
class Solution {
    public ListNode removeNthFromEnd(ListNode head, int n) {
        ListNode curr =  head;
        Queue<ListNode> q = new LinkedList<>();
        while(curr!=null){
            if (q.size() <= n) {
                q.offer(curr);
            }else{
                q.offer(curr);
                q.poll();
            }
            curr = curr.next;
        }
        if(q.size()==n+1){
            var beforeDelete = q.peek();
            assert beforeDelete != null;
            beforeDelete.next = beforeDelete.next.next;
            return head;
        }else{
            assert q.peek() != null;
            return q.peek().next;
        }
    }
}


public class Main {

    public static void main(String[] args) {
	    var a = new Solution();
	    var l1 = new ListNode(1);
	    var l2 = new ListNode(2);
	    var l3 = new ListNode(3);
	    l1.next = l2;
	    l2.next = l3;
	    l3.next = null;
        ListNode.listForEach(l1);
	    a.removeNthFromEnd(l1,3);
        ListNode.listForEach(l1);

    }

}
