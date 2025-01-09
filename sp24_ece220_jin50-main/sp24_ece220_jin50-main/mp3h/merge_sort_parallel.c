#include "merge_sort.h"
#include <pthread.h>

#define THRESHOLD 16384

void* merge_sort_thread_wrapper(void *arg){
    Node* head = (Node*)arg;
    int length = 0;
    Node* new_head = split_ll(head, &length);

    // if number of nodes less than threshold, use sequential version
    if (length < THRESHOLD) {
        head = merge_sort(head);
        new_head = merge_sort(new_head);
        head = merge_ordered_ll(head, new_head);
        pthread_exit((void*)head);
    }

    // @TODO insert your code here
    pthread_t thread1;
if (pthread_create(&thread1, NULL, merge_sort_thread_wrapper, (void*)head) != 0) {
    fprintf(stderr, "Error creating thread for first half of the list\n");
    return NULL;
}

// Sequential sort of the second half of the list
Node* sorted_second_half = merge_sort(new_head);

// Wait for the first half to finish sorting
Node* sorted_first_half = NULL;
if (pthread_join(thread1, (void**)&sorted_first_half) != 0) {
    fprintf(stderr, "Error joining thread for first half of the list\n");
    return NULL;
}

// Merge the two sorted halves
Node* sorted_full_list = merge_ordered_ll(sorted_first_half, sorted_second_half);
return (void*)sorted_full_list;
   
}



int main() {
    Node* head = make_ll_from_file("input.txt");

    // @TODO insert your code here
    pthread_t sort_thread;
    void *sorted_head = NULL;
    pthread_create(&sort_thread, NULL, merge_sort_thread_wrapper, (void *)head);

    pthread_join(sort_thread, &sorted_head);

    head = (Node*)sorted_head;

    print_list(head,"parallel_output.txt");
    free_list(head);
    return 0;
}
