
function ListNode(val) {
      this.val = val;
      this.next = null;
}
/**
 * @param {ListNode} head
 * @return {ListNode}
 */
let swapPairs = function(head) {
      if (head==null||head.next==null){
            return head
      }
      let p = head;
      let res = head.next;
      while(p!=null){
            let p_next = p.next;
            let p_next_next = p_next.next;
            if(p_next_next!=null){
                  if(p_next_next.next==null){
                        p.next = p_next_next;
                        p_next.next = p;
                        return res
                  }else{
                        p.next = p_next_next.next;
                  }
            }else{
                  p.next = null
            }
            p_next.next = p;
            p = p_next_next;
      }
      return res
};

let l1 = new ListNode(1);
let l2 = new ListNode(2);
let l3 = new ListNode(3);
let l4 = new　ListNode(4);
l1.next = l2;
l2.next = l3;
l3.next = l4;
l4.next = null;

/**
 * @param{ListNode} head
 * @return {ListNode}
 */
let printList = function(head){
      while(head!=null){
            console.log(head.val);
            head = head.next
      }
};


printList(l1);
console.log("------");
let newHead = swapPairs(l1);
printList(newHead);