/**
 * Definition for singly-linked list. */
#include<iostream>
using namespace std;
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};
typedef ListNode* NodeType;


void createDemo(NodeType &head){
    int tmp[] = {};
    int n = sizeof(tmp) / sizeof(int);
    head->val = tmp[0];
    NodeType tail = head;
    for(int i=1; i<n; i++){
        tail->next = new ListNode(tmp[i]);
        tail = tail->next;
    }
}


void printList(NodeType list){
    NodeType ptr = list;
    while(ptr){
        cout<<ptr->val<<' ';
        ptr = ptr->next;
    }
    cout<<endl;
}

bool midcut(ListNode* const left, ListNode* &mid){
    NodeType pre, tail;
    pre = left;
    mid = left;

    if(!left->next){
        mid = left;
        return true;
    }
    else
        tail = left->next;
    while(tail){
        pre = mid;
        mid = mid->next;
        tail = tail->next;
        if(tail)
            tail = tail->next;
    }
    pre->next = NULL;
    return true;
}
void merge(NodeType &la, NodeType lb){

    NodeType head = new ListNode(-1);
    NodeType pa=la, pb=lb, tail=head;
    while(pa && pb){
        if(pa->val <= pb->val){
            tail->next = pa;
            tail = pa;
            pa = pa->next;
        }else{
            tail->next = pb;
            tail = pb;
            pb = pb->next;
        }
    }
    if(pa){
        tail->next = pa;
    }
    if(pb){
        tail->next = pb;
    }
    la = head->next;
}

ListNode *sortList(NodeType &head, NodeType mid = nullptr) {
    midcut(head, mid);
    if (head != mid){//more than one nodes
        //printList(head);
        //printList(mid);
        sortList(head);
        sortList(mid);
        merge(head, mid);
        //printList(head);
    }
    return head;
}
int list_sort_main(){
    NodeType head = nullptr;//new ListNode(0);
    //createDemo(head);
    //printList(head);
    sortList(head);
    printList(head);
    return 0;
}
