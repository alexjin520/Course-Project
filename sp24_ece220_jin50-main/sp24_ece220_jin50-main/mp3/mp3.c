//jin50, jaypark3
/*
For the pascal triangle, we use for loop and the big pi to get the elements in the row.
We use the equation of big pi i = 1, to k, n+1-i/i to print each number in the row by column.
When we are doing the operation, we are multiplying the values first because if we divide them,
we might lose the value. The for loop prints the number of each column in the row that was
inputted by the user.
*/

//header file
#include <stdio.h> 
#include <stdlib.h>

//main function to start the program
int main()
{
//declare variable row
  int row;
//printing line that is asking for the user input
  printf("Enter a row index: ");
//user-input
  scanf("%d",&row);

  // Write your code here
//declare i as int
  int i;
//index is initialied index as unsigned long 1
  unsigned long  index = 1;
//for loop
  for (i=0;i<row+1;i++)
    {
//row 0 prints 1
      if (i==0)
    index = 1;
//other rows uses the big pi equation.
      else
    index = index*(row+1-i)/i;
//printing the values at the given row.
      printf("%lu ", index);
    }

  return 0;
}


