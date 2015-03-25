/*
 * Sort a linked list in O(n log n) time using constant space complexity.
 * */
#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <sys/time.h>
#include <stack>
#include <stdlib.h>
using namespace std;

struct ListNode {
     int val;
     ListNode *next;
     ListNode(int x) : val(x), next(NULL) {}
};

class SortLinkList{
public:
    ListNode* interSortList(ListNode* head)
    {
        if(head == NULL)
            return head;

        ListNode* postHead = head->next;//single head
        head->next = NULL;//pre head single chain
        while(postHead)
        {//untill ori tail
            ListNode* newhead = postHead->next; //post head single chain
            postHead->next = NULL;
            ListNode* tmp = head;
            while(tmp)
            {//insert sort
                if(postHead->val < tmp->val)
                {//at head
                    postHead->next = tmp;
                    head = postHead;
                    break;
                }
                else if(!tmp->next)
                {//at tail
                    tmp->next = postHead;
                    break;
                }
                else if(postHead->val >= tmp->val && tmp->next && postHead->val < tmp->next->val)
                {//insert in middle
                    postHead->next = tmp->next;
                    tmp->next = postHead;
                    break;
                }
                else
                {//slide next
                    tmp = tmp->next;
                }
            }
            postHead = newhead;
        }

        return head;
    }
    ListNode* sortList(ListNode* head)
    {
        ListNode* middle;
        ListNode* middle_pre;
        int len = 0, a = 0;
        //1. get len
        ListNode* tmp;
        tmp = head;
        //while(tmp) not while(tmp->next)
        while(tmp){
            tmp = tmp->next;
            len ++;
        }
        cout << "len:" << len << endl;
        //stop condition
        if(len == 1)
            return head;
        if(len == 2){
            //decide when to interchange
            if(head->val > head->next->val){
                middle_pre = head;
                middle = head->next;
                int value = middle_pre->val;
                middle_pre->val = middle->val;
                middle->val = value;
            }
            return head;
        }
        //2. get middle, middle_pre
        middle_pre = head;
        a = 0;
        while(a < len / 2 - 1 && middle_pre){
            middle_pre = middle_pre->next;
            a++;
        }
        middle = middle_pre->next;
        middle_pre->next = NULL;
        //3. sort in binary
        head = sortList(head);
        middle = sortList(middle);
        //4. merge
        ListNode* p = head;
        ListNode* q = middle;
        head = NULL;
        ListNode* new_tail = NULL;//合并链最后一个
        while(p && q)
        {
            if(p->val <= q->val){
                tmp = p;
                p = p->next;
            }
            else{
                tmp = q;
                q = q->next;
            }
            tmp->next = NULL;
            if(head == NULL){
                head = tmp;
            }
            else{
                new_tail->next = tmp;
            }
            new_tail = tmp;
        }
        if(p)
            new_tail->next = p;
        if(q)
            new_tail->next = q;
        return head;
    }
    void print(ListNode* head)
    {
        while(head){
            cout << head->val << " ";
            head = head->next;
        }
        cout << endl;
    }
};


int main()
{
    SortLinkList s;
    int arr[] = {8,7,6,3,4,9};
    ListNode* head = new ListNode(arr[0]);
    ListNode* tail = head;
    for(int i = 1 ; i < 6; i++)
    {
        ListNode* cur = new ListNode(arr[i]);
        tail->next = cur;
        tail = tail->next;
   }
   cout << "pre list:" << endl;
   s.print(head);
   head = s.interSortList(head);
   cout << "sort list:" << endl;
   s.print(head);
}
