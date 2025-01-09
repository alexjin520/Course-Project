#include "merge_sort.h"


/*
    Split a linked list in half from the middle point

    ARGS:
        Node* in    -> head of the linked list
        int* length -> pointer to a memory location where the length of the first half of the list can be placed
    RET:
        returns the head of the second half list while the input pointer still points to the first half
*/
Node* split_ll(Node* in, int* length) {

    // @TODO insert your code here
    if (in == NULL || in->next == NULL) {
        *length = in != NULL ? 1 : 0;
        return NULL;
    }

    Node *fast = in->next;
    Node *slow = in;
    *length = 1;

    while (fast != NULL && fast->next != NULL) {
        fast = fast->next->next;
        slow = slow->next;
        (*length)++;
    }

    Node *second_half = slow->next;
    slow->next = NULL; // Split the list
    return second_half;

}

/*
    Merge two linked lists that are already sorted

    ARGS:
        Node* heada -> one linked list
        Node* headb -> the other linked list
    RET:
        returns the head of the merged list
*/
Node* merge_ordered_ll(Node* heada, Node* headb) {

    // @TODO insert your code here
    Node dummy;
    Node *tail = &dummy;
    dummy.next = NULL;

    while (heada != NULL && headb != NULL) {
        if (heada->val <= headb->val) {
            tail->next = heada;
            heada = heada->next;
        } else {
            tail->next = headb;
            headb = headb->next;
        }
        tail = tail->next;
    }

    tail->next = heada ? heada : headb;
    return dummy.next;

}

/*
    Recursively sort a linked list

    ARGS:
        Node* head -> linked list head
    RET:
        returns the head of the sorted list
*/
Node* merge_sort(Node* head) {

    // @TODO insert your code here
    if (head == NULL || head->next == NULL) {
        return head;
    }

    int length;
    Node* second_half = split_ll(head, &length);

    Node* sorted_first_half = merge_sort(head);
    Node* sorted_second_half = merge_sort(second_half);

    return merge_ordered_ll(sorted_first_half, sorted_second_half);

}
