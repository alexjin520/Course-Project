#include "acc.h"

int main() {
    unsigned long long ret = 0;

    // Temporary index for looping purposes
    int file;

    // Loop through each file part, running acc_file on each file (Your Code Goes Here)
    for (file  = 0; file < NUM_THREADS; file++) {
        // Pass the appropriate arguments to your threads
      ret += acc_file(file);

    }

    
    // Write the calculated result to serial_output.txt
    FILE *out = fopen("serial_output.txt", "w");
    fprintf(out, "%llu\n", ret);
    fclose(out);
    
    return 0;
}
