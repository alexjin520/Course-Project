/*			
 *
 * prog5.c - source file adapted from UIUC ECE198KL Spring 2013 Program 4
 *           student code -- GOLD VERSION by Steven S. Lumetta
 */


/*
 * The functions that you must write are defined in the header file.
 * Blank function prototypes with explanatory headers are provided
 * in this file to help you get started.
 */
/* Program Description:
    The set_seed function (called by main) takes the user input (stored in a char string) and convert
    it to a integer representation using sscanf() while also checking only a single integer was entered by the user.
    Then we give this integer "seed" to srand(). 
    
    The start_game function (called by main) generates the randomized solution to be stored into a solution
    array of integers. We do this by applying modulus to a rand number such that the result is between 1 and 8.
    We also store these solutions into and array that is used in the make_guess function. Finally we push the 
    generated solutions into the main using pointers.

    In make_guess(), we first check for a valid guess. This is done using sscanf and an if statement. 
    Then, once we know the guess is valid, two temp arrays are initialized to store the solution and the 
    guesses entered by the user. First, we use a iterative loop to check perfect match between the
    solution and the guess; then we use two iterative loops to check for mismatches between the 2 arrays.
    To avoid repetition, whenever there is a match (mis or perfect), we change the value at that specific
    index to 0 (for the guess array) and 9 (for the solution array) so that these indexes would not be 
    able to pair with other elements in the array.

    partners: jin50,jaypark3

 */


#include <stdio.h>
#include <stdlib.h>

#include "prog5.h"


/*
 * You will need to keep track of the solution code using file scope
 * variables as well as the guess number.
 */

static int guess_number;
static int solution1;
static int solution2;
static int solution3;
static int solution4;
int solution_array[4];



/*
 * set_seed -- This function sets the seed value for pseudorandom
 * number generation based on the number the user types.
 * The input entered by the user is already stored in the string seed_str by the code in main.c.
 * This function should use the function sscanf to find the integer seed value from the 
 * string seed_str, then initialize the random number generator by calling srand with the integer
 * seed value. To be valid, exactly one integer must be entered by the user, anything else is invalid. 
 * INPUTS: seed_str -- a string (array of characters) entered by the user, containing the random seed
 * OUTPUTS: none
 * RETURN VALUE: 0 if the given string is invalid (string contains anything
 *               other than a single integer), or 1 if string is valid (contains one integer)
 * SIDE EFFECTS: initializes pseudo-random number generation using the function srand. Prints "set_seed: invalid seed\n"
 *               if string is invalid. Prints nothing if it is valid.
 */
int
set_seed (const char seed_str[])
{
//    Example of how to use sscanf to read a single integer and check for anything other than the integer
//    "int seed" will contain the number typed by the user (if any) and the string "post" will contain anything after the integer
//    The user should enter only an integer, and nothing else, so we will check that only "seed" is read. 
//    We declare
//    int seed;
//    char post[2];
//    The sscanf statement below reads the integer into seed. 
//    sscanf (seed_str, "%d%1s", &seed, post)
//    If there is no integer, seed will not be set. If something else is read after the integer, it will go into "post".
//    The return value of sscanf indicates the number of items read succesfully.
//    When the user has typed in only an integer, only 1 item should be read sucessfully. 
//    Check that the return value is 1 to ensure the user enters only an integer. 
//    Feel free to uncomment these statements, modify them, or delete these comments as necessary. 
//    You may need to change the return statement below
    int seed;
    char post[2];
    
    int result = sscanf(seed_str, "%d%1s", &seed, post);
    
    if(result == 1){
    srand(seed);
    return 1;
    }
    else{
        printf("set_seed: invalid seed\n");
	return 0;
    }
      

   
}


/*
 * start_game -- This function is called by main.c after set_seed but before the user makes guesses.
 *               This function creates the four solution numbers using the approach
 *               described in the wiki specification (using rand())
 *               The four solution numbers should be stored in the static variables defined above. 
 *               The values at the pointers should also be set to the solution numbers.
 *               The guess_number should be initialized to 1 (to indicate the first guess)
 * INPUTS: none
 * OUTPUTS: *one -- the first solution value (between 1 and 8)
 *          *two -- the second solution value (between 1 and 8)
 *          *three -- the third solution value (between 1 and 8)
 *          *four -- the fourth solution value (between 1 and 8)
 * RETURN VALUE: none
 * SIDE EFFECTS: records the solution in the static solution variables for use by make_guess, set guess_number
 */
void
start_game (int* one, int* two, int* three, int* four)
{
    
    solution1 = (rand()%8) +1;
    solution2 = (rand()%8) +1;
    solution3 = (rand()%8) +1;
    solution4 = (rand()%8) +1;

    
    solution_array[0]=solution1;
    solution_array[1]=solution2;
    solution_array[2]=solution3;
    solution_array[3]=solution4;
   
    *one = solution1;
    *two = solution2;
    *three = solution3;
    *four = solution4;
  
    

    //your code here
    
}

/*
 * make_guess -- This function is called by main.c after the user types in a guess.
 *               The guess is stored in the string guess_str. 
 *               The function must calculate the number of perfect and misplaced matches
 *               for a guess, given the solution recorded earlier by start_game
 *               The guess must be valid (contain only 4 integers, within the range 1-8). If it is valid
 *               the number of correct and incorrect matches should be printed, using the following format
 *               "With guess %d, you got %d perfect matches and %d misplaced matches.\n"
 *               If valid, the guess_number should be incremented.
 *               If invalid, the error message "make_guess: invalid guess\n" should be printed and 0 returned.
 *               For an invalid guess, the guess_number is not incremented.
 * INPUTS: guess_str -- a string consisting of the guess typed by the user
 * OUTPUTS: the following are only valid if the function returns 1 (A valid guess)
 *          *one -- the first guess value (between 1 and 8)
 *          *two -- the second guess value (between 1 and 8)
 *          *three -- the third guess value (between 1 and 8)
 *          *four -- the fourth color value (between 1 and 8)
 * RETURN VALUE: 1 if the guess string is valid (the guess contains exactly four
 *               numbers between 1 and 8), or 0 if it is invalid
 * SIDE EFFECTS: prints (using printf) the number of matches found and increments guess_number(valid guess) 
 *               or an error message (invalid guess)
 *               (NOTE: the output format MUST MATCH EXACTLY, check the wiki writeup)
 */
int
make_guess (const char guess_str[], int* one, int* two, 
	    int* three, int* four)
{
//  One thing you will need to read four integers from the string guess_str, using a process
//  similar to set_seed
//  The statement, given char post[2]; and four integers w,x,y,z,
//  sscanf (guess_str, "%d%d%d%d%1s", &w, &x, &y, &z, post)
//  will read four integers from guess_str into the integers and read anything else present into post
//  The return value of sscanf indicates the number of items sucessfully read from the string.
//  You should check that exactly four integers were sucessfully read.
//  You should then check if the 4 integers are between 1-8. If so, it is a valid guess
//  Otherwise, it is invalid.  
//  Feel free to use this sscanf statement, delete these comments, and modify the return statement as needed
  
    int x, y, z, w;
    int perfect_match = 0; //perfect match number
    int misplaced_match = 0; //misplaced matches number
    int valid_guess; //checks if 4 integers were entered
    char post[2];
    int temp_guess[4]; //store the guess
    int temp_solution_array[4]; //store the solution
    valid_guess = sscanf (guess_str, "%d%d%d%d%1s", &w, &x, &y, &z, post);
    if (valid_guess ==4 && w>=1 && w<=8 && x>=1 && x<=8 && y>=1 && y<=8 && z>=1 && z<=8){ //4 1-8 ints are entered
        temp_guess[0]=w;
        temp_guess[1]=x;
        temp_guess[2]=y;
        temp_guess[3]=z;
        *one = w;
        *two = x;
        *three = y;
        *four = z;
        for (int i=0; i<=3; i++){
            temp_solution_array[i]=solution_array[i]; //put values in solution_array into temp_solution_array
        }
    }
    else{
        printf("make_guess: invalid guess\n");
        return 0; 
    }
    for (int i=0; i<=3; i++){

      if(temp_solution_array[i]==temp_guess[i]){//loop for finding perfect match
           perfect_match++;
	   temp_solution_array[i]=-1;
	   temp_guess[i]=9;
       } 
    }
    for (int i=0; i<=3; i++){
        for (int j=0; j<=3; j++){
	  if ((temp_solution_array[i]==temp_guess[j])&&(i!=j)){ //loop for finding misplaced match
                misplaced_match++;
		temp_solution_array[i]=-1;
		temp_guess[j]=9;
                break; //we break this loop if we find a misplaced match
            }
        }

    }
    guess_number++;
    printf("With guess %d, you got %d perfect matches and %d misplaced matches.\n", guess_number, perfect_match, misplaced_match);
   
    return 1;
}


