//jin50, jaypark3
/*
There are 4 key functions that are wrote within sudoku.c, such as solve_sudoku, is_val_in_row, is_val_in_col, 
and is_val_in_3x3_zone to check if a number exists in a specific row, column, or 3x3 zone of 
the 9x9 grid. Then solve_sudoku uses recursive backtracking to fill in the grid, until the puzzle is solved. 
This approach recursively checks for possible placements, adjusting the grid based on the backtracking algorithm's logic.
*/
#include "sudoku.h"

//-------------------------------------------------------------------------------------------------
// Start here to work on your MP7
//-------------------------------------------------------------------------------------------------

// You are free to declare any private functions if needed.

// Function: is_val_in_row
// Return true if "val" already existed in ith row of array sudoku.
int is_val_in_row(const int val, const int i, const int sudoku[9][9]) {

  assert(i>=0 && i<9);

  // BEG TODO
  for (int k=0;k<9;k++) //for-loop
    {
      if(sudoku[i][k]==val) //checks if the value is in the row
	{
	  return 1;
	}  
    }


      return 0;
  // END TODO
}

// Function: is_val_in_col
// Return true if "val" already existed in jth column of array sudoku.
int is_val_in_col(const int val, const int j, const int sudoku[9][9]) {

  assert(j>=0 && j<9);

  // BEG TODO
  for (int k=0;k<9;k++) //for-loop
    {
      if(sudoku[k][j]==val) //find if the value is in col
	{
	  return 1;
	}
      
    }
  return 0;
  // END TODO
}

// Function: is_val_in_3x3_zone
// Return true if val already existed in the 3x3 zone corresponding to (i, j)
int is_val_in_3x3_zone(const int val, const int i, const int j, const int sudoku[9][9]) {
   
  assert(i>=0 && i<9);
  
  // BEG TODO
  if(i%3==0) //checking for row 3, 6, 9
    {
      for(int k=i;k<=i+2;k++) //for-loop
	{
	  if(j%3==0) //checking for col 3, 6, 9
	    {
	      for(int p=j;p<=j+2;p++)
		{
		  if(sudoku[k][p]==val) //checking the val
		    {
		      return 1;
		    }
		}
	    }
	  else if(j%3==1) //checking for col 1, 4, 7
	    {
	      for(int p=j-1;p<=j+1;p++)
		{
		  if(sudoku[k][p]==val)
		    {
		      return 1;
		    }
		}
	    }
	  else
	    {
	      for(int p=j-2;p<=j;p++)
		{
		  if(sudoku[k][p]==val)
		    {
		      return 1;
		    }
		}
	    }
	  
	}
    }
   if(i%3==1) //checking for row 1, 4, 7
    {
      for(int k=i-1;k<=i+1;k++) //for-loop
	{
	  if(j%3==0) //checking for col 3, 6, 9
	    {
	      for(int p=j;p<=j+2;p++)
		{
		  if(sudoku[k][p]==val) //checking val
		    {
		      return 1;
		    }
		}
	    }
	  else if(j%3==1) //checking for col 1, 4, 7
	    {
	      for(int p=j-1;p<=j+1;p++)
		{
		  if(sudoku[k][p]==val)
		    {
		      return 1;
		    }
		}
	    }
	  else
	    {
	      for(int p=j-2;p<=j;p++)
		{
		  if(sudoku[k][p]==val)
		    {
		      return 1;
		    }
		}
	    }
	  
	}
    }
    if(i%3==2) //checking for row 2, 5, 8
    {
      for(int k=i-2;k<=i;k++) //for-loop
	{
	  if(j%3==0) //checking for col 3, 6, 9
	    {
	      for(int p=j;p<=j+2;p++)
		{
		  if(sudoku[k][p]==val) //checking val
		    {
		      return 1;
		    }
		}
	    }
	  else if(j%3==1) //checking for col 1, 4, 7
	    {
	      for(int p=j-1;p<=j+1;p++)
		{
		  if(sudoku[k][p]==val)
		    {
		      return 1;
		    }
		}
	    }
	  else
	    {
	      for(int p=j-2;p<=j;p++)
		{
		  if(sudoku[k][p]==val)
		    {
		      return 1;
		    }
		}
	    }
	  
	}
    }
  return 0;
  // END TODO
}

// Function: is_val_valid
// Return true if the val is can be filled in the given entry.
int is_val_valid(const int val, const int i, const int j, const int sudoku[9][9]) {

  assert(i>=0 && i<9 && j>=0 && j<9);

  // BEG TODO
  if(is_val_in_row(val,i,sudoku) == 1 || is_val_in_col(val,j,sudoku) ==1 || is_val_in_3x3_zone(val,i,j,sudoku) ==1)
							      {
								return 0;
							      }
  return 1;
  // END TODO
}

// Procedure: solve_sudoku
// Solve the given sudoku instance.
int solve_sudoku(int sudoku[9][9]) {

  // BEG TODO.

  int i,j;
  int flag=-1;
  
  for(i=0;i<9;i++) //for-loop row
    {
      for(j=0;j<9;j++) //for-loop col
	{
	  if(sudoku[i][j]==0) //checking if there is val 0, which is invalid
	    {	     
	      flag=1;
	      break;
	    }
	}
      if(flag==1) //checking if there was val 0
	break;
    }
  if(flag ==-1)
    {
      return 1;
    }
  int num;   
  for(num=1;num<=9;num++) //for-loop 
	{
	  if(is_val_valid(num,i,j,sudoku)==1) //checking valid
	    {
	      sudoku[i][j]=num;
	      if(solve_sudoku(sudoku)) //recursive call
		{
		  return 1;
		}
	      else
		{
		  sudoku[i][j]=0;
		}
		
	    }
	}
    
      
		       
  return 0;
  // END TODO.
}

// Procedure: print_sudoku
void print_sudoku(int sudoku[9][9])
{
  int i, j;
  for(i=0; i<9; i++) {
    for(j=0; j<9; j++) {
      printf("%2d", sudoku[i][j]);
    }
    printf("\n");
  }
}

// Procedure: parse_sudoku
void parse_sudoku(const char fpath[], int sudoku[9][9]) {
  FILE *reader = fopen(fpath, "r");
  assert(reader != NULL);
  int i, j;
  for(i=0; i<9; i++) {
    for(j=0; j<9; j++) {
      fscanf(reader, "%d", &sudoku[i][j]);
    }
  }
  fclose(reader);
}
