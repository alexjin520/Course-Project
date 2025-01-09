/*This program is designed to recreate a classic and well-known simulation known as the Game of Life.
 * It features a two-dimensional grid of square cells, each of which can be in one of two states: alive or dead.
 * The simulation follows four main rules: a cell will die from underpopulation if it has fewer than two live neighbors;
 * a cell with two or three live neighbors will survive to the next generation; a cell with more than three live neighbors will die 
 * of overpopulation; and a dead cell with exactly three live neighbors will come to life, simulating reproduction. To implement these rules,
 * we used the provided algorithms from the project description, alongside pointers, loops, and conditional logic.
 * partner: jaypark3, jin50
 */
/*
 * countLiveNeighbor
 * Inputs:
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * row: the row of the cell that needs to count alive neighbors.
 * col: the col of the cell that needs to count alive neighbors.
 * Output:
 * return the number of alive neighbors. There are at most eight neighbors.
 * Pay attention for the edge and corner cells, they have less neighbors.
 */
int countLiveNeighbor(int* board, int boardRowSize, int boardColSize, int row, int col){
  int num_of_alive = 0;//initiate alive counter
  for (int i = row-1; i <= row+1; i++){//loop through row
    if(i >= 0 && i < boardRowSize){
      for(int j = col-1; j <= col+1; j++){ //loop through cols
        if(j >= 0 && j < boardColSize){
          if (i != row || j != col){//not the row and col in the parameter
            int check = 0;
            check = *(board+ (i*(boardColSize)) + j);
            if(check == 1){ //seeing if they are alive
              num_of_alive++; //increment number of alive
            } 
          }  
        }
      }
    }
  } 
  
  return num_of_alive;
}
/*
 * Update the game board to the next step.
 * Input: 
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * Output: board is updated with new values for next step.
 */
void updateBoard(int* board, int boardRowSize, int boardColSize) {
int temp[boardRowSize * boardColSize];
for(int i = 0; i < boardRowSize; i++){//going through the rows.
    for(int j = 0; j < boardColSize; j++){ //going through the cols.
       int result = 0;
       result = countLiveNeighbor(board, boardRowSize, boardColSize, i, j);
       if (board[i * boardColSize + j] == 1) //if cell is alive
      {
        if(result == 2 || result == 3)
        {
          temp[i * boardColSize + j] = 1;
        }
        else
        {
          temp[i * boardColSize + j] = 0;
        }
      }
       else if (board[i * boardColSize + j] == 0)//if cell is dead
      {
        if (result == 3)
        {
          temp[i * boardColSize + j] = 1;
        }
        else
        {
          temp[i * boardColSize + j] = 0;
        }
      }
    }
  }
 for (int i = 0; i < boardRowSize*boardColSize; i++) //recursive call
  {
    board[i] = temp[i];
  }

}

/*
 * aliveStable
 * Checks if the alive cells stay the same for next step
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * Output: return 1 if the alive cells for next step is exactly the same with 
 * current step or there is no alive cells at all.
 * return 0 if the alive cells change for the next step.
 */ 
int aliveStable(int* board, int boardRowSize, int boardColSize){
    int newBoard[boardRowSize*boardColSize];
    for(int i = 0; i < boardColSize*boardRowSize; i++){
        newBoard[i] = *(board+i);
    }
    updateBoard(newBoard, boardRowSize, boardColSize); //calls recursive function
    for(int i = 0; i < boardColSize*boardRowSize; i++){//checking if they are the same
        if(*(board+i) != newBoard[i]) {
	  return 0;//if any change is detected, return 0
    }
    }
    return 1; 
}
