/*
; jaypark3, jin50
Errors:
In main.c, there is an syntax error at the line 26 from the
original code where it should have ; at the end of the
ret = ... line. It will not compile because of this.
Then, in semiprime.c, the is_prime function basically, gets the number from 2 to until a number 1 less than the number in the 
parameter. It checks whether it is fully divisible with 0
as the remainder, so it returns 1 even if it is not prime.
Then, I changed the code, so if the number can be dividible
by 1 and itself, it returns 1, using counter. Then in the
print_semiprimes, in line 37 of the original code, it sets
k = i%j, which sets the k value to whatever is the remainder, 
but it should set k = i/j to check the other factor k to see
if it is prime. So, I changed the code to k = i/j and then
combined the if functions of is_prime to test both
j and k. Then I set break after printing line, which is after
line 39 of the original code, so after it checks that the
number is semi-prime, it will break out of the loop, so it will
not print the same number. Then, I made a c variable that checks
how many numbers it printed, and then put if statment before
return ret, so when the c is not equal to 0, it sets 0 and returns.

*/

#include <stdlib.h>
#include <stdio.h>
#include "semiprime.h"


/*
    Main function: checks for valid inputs and runs the print_semiprimes function.
    Inputs: none
    Outputs: if provided a,b are invalid, returns -1. If there were no
    semiprimes in the range, returns 0. If there were semiprimes, returns 1.
*/
int main(){

   int a, b;
   int ret = 0;
   printf("Input two numbers: ");
   scanf("%d %d", &a, &b);
   if( a <= 0 || b <= 0 ){
     printf("Inputs should be positive integers\n");
     return -1;
   }

   if( a > b ){
     printf("The first number should be smaller than or equal to the second number\n");
     return -1;
   }

   ret = print_semiprimes(a, b);
   
   return ret;
}
