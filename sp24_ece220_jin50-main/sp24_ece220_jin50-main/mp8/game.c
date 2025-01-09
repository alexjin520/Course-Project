//partners: jaypark3, jin50
#include "game.h"
/*
First,make_game initializes the game structure, sets rows, columns, and scores, 
and cells. remake_game reinitializes a game with new dimensions, 
resetting it. get_cell accesses a specific cell, checking for valid range. 
Movement functions (move_w, move_s, move_a, move_d) slide tiles in the
directions, doing tile merging to avoid duplicates within a move. legal_move_check 
evaluates if legal moves exist by checking for empty or adjacent matching tiles.
*/

game * make_game(int rows, int cols)
/*! Create an instance of a game structure with the given number of rows
    and columns, initializing elements to -1 and return a pointer
    to it. (See game.h for the specification for the game data structure) 
    The needed memory should be dynamically allocated with the malloc family
    of functions.
*/
{
    //Dynamically allocate memory for game and cells (DO NOT modify this)
    game * mygame = malloc(sizeof(game));
    mygame->cells = malloc(rows*cols*sizeof(cell));

    //YOUR CODE STARTS HERE:  Initialize all other variables in game struct

	mygame->rows = rows; //setting row
	mygame->cols = cols; //setting col
	mygame->score = 0; //score is initially 0

    for(int i = 0; i < rows; i++){
	for(int j = 0; j < cols; j++){
		mygame->cells[i*cols+j] = -1; //empty cell
	}
    }
    return mygame;
}

void remake_game(game ** _cur_game_ptr,int new_rows,int new_cols)
/*! Given a game structure that is passed by reference, change the
	game structure to have the given number of rows and columns. Initialize
	the score and all elements in the cells to -1. Make sure that any 
	memory previously allocated is not lost in this function.	
*/
{
	/*Frees dynamically allocated memory used by cells in previous game,
	 then dynamically allocates memory for cells in new game.  DO NOT MODIFY.*/
	free((*_cur_game_ptr)->cells);
	(*_cur_game_ptr)->cells = malloc(new_rows*new_cols*sizeof(cell));

	 //YOUR CODE STARTS HERE:  Re-initialize all other variables in game struct
        (*_cur_game_ptr)->rows = new_rows; //new rows
	(*_cur_game_ptr)->cols = new_cols; //new cols
	(*_cur_game_ptr)->score = 0; 
	for(int i = 0 ; i < new_rows; i++){ //for-loop
		for(int j = 0; j < new_cols; j++){
			(*_cur_game_ptr)->cells[i*new_cols+j] = -1; //empty cells
		}
	}
	return;	
}

void destroy_game(game * cur_game)
/*! Deallocate any memory acquired with malloc associated with the given game instance.
    This includes any substructures the game data structure contains. Do not modify this function.*/
{
    free(cur_game->cells);
    free(cur_game);
    cur_game = NULL;
    return;
}

cell * get_cell(game * cur_game, int row, int col)
/*! Given a game, a row, and a column, return a pointer to the corresponding
    cell on the game. (See game.h for game data structure specification)
    This function should be handy for accessing game cells. Return NULL
	if the row and col coordinates do not exist.
*/
{
    //YOUR CODE STARTS HERE
	int rows = cur_game->rows; 
	int cols = cur_game->cols;
	if(0 <= row && row < rows && 0 <= col && col < cols){ //checking if it is within the range
		return &(cur_game)->cells[row*cols+col]; //return
	}
    return NULL;
}

int move_w(game * cur_game) {
    int row = cur_game->rows; //getting total row
    int col = cur_game->cols; //getting total col
    int change = 0; 

    for (int j = 0; j < col; j++) { //for-loop
        int last_merge_row = -1; 
        for (int i = 1; i < row; i++) {  //for-loop
            if (cur_game->cells[i * col + j] != -1) { 
                int cur_val = cur_game->cells[i * col + j];
                int target_row = i; //row that is evaluated
                while (target_row > 0 && (cur_game->cells[(target_row - 1) * col + j] == -1 || cur_game->cells[(target_row - 1) * col + j] == cur_val) && last_merge_row != target_row - 1) {
                   
                    target_row--;
                }
                if (target_row != i) { 
                    if (cur_game->cells[target_row * col + j] == cur_val) { //if they are teh same
                        cur_game->cells[target_row * col + j] *= 2; //adding
                        cur_game->score += cur_game->cells[target_row * col + j];  //adding score
                        last_merge_row = target_row; 
                    } else {  //if they are not same
                        cur_game->cells[target_row * col + j] = cur_val;
                    }
                    cur_game->cells[i * col + j] = -1; 
                    change = 1; //checks for a change
                }
            }
        }
    }

    if (change == 0) {
        return 0; //no change returns 0
    } else {
        return 1; //change return 0
    }
}


int move_s(game * cur_game) {
    int row = cur_game->rows; //getting total row
    int col = cur_game->cols; //getting total col
    int change = 0; //no change 

    for (int j = 0; j < col; j++) { //for-loop for col
        int last_merged_row = row; 
        for (int i = row - 2; i >= 0; i--) { //for-loop for the row
            if (cur_game->cells[i * col + j] != -1) { 
                int cur_val = cur_game->cells[i * col + j];
                int target_row = i;
                
                while (target_row < row - 1 && (cur_game->cells[(target_row + 1) * col + j] == -1 || 
                       (cur_game->cells[(target_row + 1) * col + j] == cur_val && target_row + 1 != last_merged_row))) {
                    target_row++;
                } //while loop
               
                if (cur_game->cells[target_row * col + j] == cur_val && target_row != last_merged_row) {//checking for same values that are adjacent
                    cur_game->cells[target_row * col + j] *= 2; //multiplying it by 2
                    cur_game->score += cur_game->cells[target_row * col + j];  //changing score
                    last_merged_row = target_row;
                } else if (target_row != i) { 
                    cur_game->cells[target_row * col + j] = cur_val;
                }
                if (target_row != i) { //checking change
                    cur_game->cells[i * col + j] = -1;
                    change = 1; 
                }
            }
        }
    }
    if (change == 0) { //checking for a change
        return 0; 
    } else {
        return 1; 
    }
    
}


int move_a(game * cur_game) {
    int row = cur_game->rows;
    int col = cur_game->cols;
    int change = 0;
    for (int i = 0; i < row; i++) { //for loop
        int last_merged_col = -1; 
        for (int j = 1; j < col; j++) { //for loop
            if (cur_game->cells[i * col + j] != -1) { //chekcing that it is not empty
                int cur_val = cur_game->cells[i * col + j];
                int target_col = j; //target col set
                
                while (target_col > 0 && cur_game->cells[i * col + target_col - 1] == -1) { //checking for empty cell in the direction
                    target_col--; //decrementing target_col
                }
                
                if (target_col > 0 && cur_game->cells[i * col + target_col - 1] == cur_val && last_merged_col != target_col - 1) {
                    cur_game->cells[i * col + target_col - 1] *= 2; //multiply the cell val
                    cur_game->score += cur_game->cells[i * col + target_col - 1]; //set the cell score
                    cur_game->cells[i * col + j] = -1;
                    last_merged_col = target_col - 1; 
                    change = 1;
                } else if (target_col != j) { //if target col is not same as j
                    if (cur_game->cells[i * col + target_col] == -1) { 
                        cur_game->cells[i * col + target_col] = cur_val;
                        cur_game->cells[i * col + j] = -1;
                        change = 1; //there was a change
                    }
                }
            }
        }
    }
    if (change == 0) { //if there was not chanage return 0
        return 0; 
    } else { //if there was a change return 1
        return 1; 
    }
    
}

//moving in right direction
int move_d(game * cur_game) {
    int row = cur_game->rows; //getting total row
    int col = cur_game->cols; //getting total col
    int change = 0; //setting change to 0
    for (int i = 0; i < row; i++) { // for loop for the row
        int merge = col; 
        for (int j = col - 2; j >= 0; j--) { //for loop for the col
            if (cur_game->cells[i * col + j] != -1) { //if it is not empty
                int cur_val = cur_game->cells[i * col + j]; //finding current value
                int target_col = j;
                while (target_col < col - 1 && cur_game->cells[i * col + target_col + 1] == -1) { 
                    target_col++;
                }
                if (cur_game->cells[i * col + target_col + 1] == cur_val && merge != target_col + 1) { 
                    cur_game->cells[i * col + target_col + 1] *= 2; //combine the cells
                    cur_game->score += cur_game->cells[i * col + target_col + 1]; //adding the score
                    cur_game->cells[i * col + j] = -1; 
                    merge = target_col + 1;
                    change = 1;//changed
                } else if (target_col != j) { //empty cell found
                    cur_game->cells[i * col + target_col] = cur_val;
                    cur_game->cells[i * col + j] = -1;
                    change = 1; //changed
                }
            }
        }
    }
    if (change == 0) { //return 0 if there is no change
        return 0; 
    } else {
        return 1; 
    }
    
}


int legal_move_check(game * cur_game)
/*! Given the current game check if there are any legal moves on the board. There are
    no legal moves if sliding in any direction will not cause the game to change.
	Return 1 if there are possible legal moves, 0 if there are none.
 */
{
    //YOUR CODE STARTS HERE
	int r = cur_game->rows;
	int c = cur_game->cols;

	for (int i = 0; i < r; i++){ //for loop row
		for(int j = 0; j < c; j++){ //for loop col
			int check = cur_game->cells[i*c+j];
			if(check == -1) return 1; //checking for any possible movements

		}
	}
    return 1;
}


/*! code below is provided and should not be changed */

void rand_new_tile(game * cur_game)
/*! insert a new tile into a random empty cell. First call rand()%(rows*cols) to get a random value between 0 and (rows*cols)-1.
*/
{
	
	cell * cell_ptr;
    cell_ptr = 	cur_game->cells;
	
    if (cell_ptr == NULL){ 	
        printf("Bad Cell Pointer.\n");
        exit(0);
    }
	
	
	//check for an empty cell
	int emptycheck = 0;
	int i;
	
	for(i = 0; i < ((cur_game->rows)*(cur_game->cols)); i++){
		if ((*cell_ptr) == -1){
				emptycheck = 1;
				break;
		}		
        cell_ptr += 1;
	}
	if (emptycheck == 0){
		printf("Error: Trying to insert into no a board with no empty cell. The function rand_new_tile() should only be called after tiles have succesfully moved, meaning there should be at least 1 open spot.\n");
		exit(0);
	}
	
    int ind,row,col;
	int num;
    do{
		ind = rand()%((cur_game->rows)*(cur_game->cols));
		col = ind%(cur_game->cols);
		row = ind/cur_game->cols;
    } while ( *get_cell(cur_game, row, col) != -1);
        //*get_cell(cur_game, row, col) = 2;
	num = rand()%20;
	if(num <= 1){
		*get_cell(cur_game, row, col) = 4; // 1/10th chance
	}
	else{
		*get_cell(cur_game, row, col) = 2;// 9/10th chance
	}
}

int print_game(game * cur_game) 
{
    cell * cell_ptr;
    cell_ptr = 	cur_game->cells;

    int rows = cur_game->rows;
    int cols = cur_game->cols;
    int i,j;
	
	printf("\n\n\nscore:%d\n",cur_game->score); 
	
	
	printf("\u2554"); // topleft box char
	for(i = 0; i < cols*5;i++)
		printf("\u2550"); // top box char
	printf("\u2557\n"); //top right char 
	
	
    for(i = 0; i < rows; i++){
		printf("\u2551"); // side box char
        for(j = 0; j < cols; j++){
            if ((*cell_ptr) == -1 ) { //print asterisks
                printf(" **  "); 
            }
            else {
                switch( *cell_ptr ){ //print colored text
                    case 2:
                        printf("\x1b[1;31m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 4:
                        printf("\x1b[1;32m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 8:
                        printf("\x1b[1;33m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 16:
                        printf("\x1b[1;34m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 32:
                        printf("\x1b[1;35m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 64:
                        printf("\x1b[1;36m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 128:
                        printf("\x1b[31m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 256:
                        printf("\x1b[32m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 512:
                        printf("\x1b[33m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 1024:
                        printf("\x1b[34m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 2048:
                        printf("\x1b[35m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 4096:
                        printf("\x1b[36m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 8192:
                        printf("\x1b[31m%04d\x1b[0m ",(*cell_ptr));
                        break;
					default:
						printf("  X  ");

                }

            }
            cell_ptr++;
        }
	printf("\u2551\n"); //print right wall and newline
    }
	
	printf("\u255A"); // print bottom left char
	for(i = 0; i < cols*5;i++)
		printf("\u2550"); // bottom char
	printf("\u255D\n"); //bottom right char
	
    return 0;
}

int process_turn(const char input_char, game* cur_game) //returns 1 if legal move is possible after input is processed
{ 
	int rows,cols;
	char buf[200];
	char garbage[2];
    int move_success = 0;
	
    switch ( input_char ) {
    case 'w':
        move_success = move_w(cur_game);
        break;
    case 'a':
        move_success = move_a(cur_game);
        break;
    case 's':
        move_success = move_s(cur_game);
        break;
    case 'd':
        move_success = move_d(cur_game);
        break;
    case 'q':
        destroy_game(cur_game);
        printf("\nQuitting..\n");
        return 0;
        break;
	case 'n':
		//get row and col input for new game
		dim_prompt: printf("NEW GAME: Enter dimensions (rows columns):");
		while (NULL == fgets(buf,200,stdin)) {
			printf("\nProgram Terminated.\n");
			return 0;
		}
		
		if (2 != sscanf(buf,"%d%d%1s",&rows,&cols,garbage) ||
		rows < 0 || cols < 0){
			printf("Invalid dimensions.\n");
			goto dim_prompt;
		} 
		
		remake_game(&cur_game,rows,cols);
		
		move_success = 1;
		
    default: //any other input
        printf("Invalid Input. Valid inputs are: w, a, s, d, q, n.\n");
    }

	
	
	
    if(move_success == 1){ //if movement happened, insert new tile and print the game.
         rand_new_tile(cur_game); 
		 print_game(cur_game);
    } 

    if( legal_move_check(cur_game) == 0){  //check if the newly spawned tile results in game over.
        printf("Game Over!\n");
        return 0;
    }
    return 1;
}
