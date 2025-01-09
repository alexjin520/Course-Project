#include "acc.h"
#include <pthread.h>

int main() {
    // Holds pthread_t's for all generated threads
    pthread_t threads[NUM_THREADS];

    // Holds thread id's for all generated threads
    int thread_args[NUM_THREADS];

    // Temporary thread_id for looping purposes
    int thread_id;

    // Loop to create NUM_THREADS threads with pthread_create (Your code goes here)
    pthread_mutex_init(&result_mutex, NULL);
    for (thread_id = 0; thread_id < NUM_THREADS; thread_id++) {
        // Since parallel_acc_wrapper only accepts a pointer (instead of an int),
        // all values of thread_id must be stored in an array, otherwise the pointer
        // passed to this function will not retain its value when the function fetches it (Create Pointer and threads)


        // Create the new thread (Your code goes here)
      thread_args[thread_id] = thread_id;
        if (pthread_create(&threads[thread_id], NULL, parallel_acc_wrapper, (void*)&thread_args[thread_id])) {
            perror("Failed to create thread");
            
        }

    }

    // Wait for all threads to complete and join them (Your code goes here)
    for (thread_id = 0; thread_id < NUM_THREADS; thread_id++) {
      if (pthread_join(threads[thread_id], NULL)) {
            perror("Failed to join thread");
           
        }
        
    }

    // Write the calculated result to parallel_output.txt
    FILE *out = fopen("parallel_output.txt", "w");
    
    fprintf(out, "%llu\n", result);
    fclose(out);
    
    return 0;
}
