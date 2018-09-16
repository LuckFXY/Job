#include<iostream>

using namespace std;
struct list{
    int e;
    list* next;
    list(){
        e=0;
        next = nullptr;
    }
    list(int a){
        e = a;
        next= nullptr;
    }
};
void reverse(list* &start, list* &end){
    list* pre = start;
    if(start != end && start->next != nullptr && end != nullptr){

        list* ptr = start->next;
        list* post;
        pre->next = nullptr;
        while(ptr != end){
            post = ptr->next;
            ptr->next = pre;
            pre = ptr;
            ptr = post;
        }
        end->next = pre;

    }

}
int reverse_list(){
    int k=0, a=0, n=0;
    char ch=0;
    scanf("%d%c", &a, &ch);
    list* head = new list(a);
    list* tail = head;
    while(ch != '\n' && scanf("%d%c", &a, &ch)==2) {
        list* one = new list(a);
        tail->next = one;
        tail = tail->next;
    }
    scanf("%d", &k);

    list *ptr = head;
    list* ptail= nullptr;
    list* pptr= nullptr;
    list* post=0;
    tail = head;
    int cnt=0;
    while(tail != nullptr){
        cnt += 1;
        post = tail->next;
        if(cnt % k == 0){
            reverse(ptr, tail);
            pptr = ptail;
            ptr = tail;
        }
        if(pptr)
            pptr->next = tail;
        ptr->next = post;
        ptail = tail;
        tail = tail->next;
    }

    return 0;
}