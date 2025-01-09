#include <stdio.h>
#include <stdlib.h>
#include "maze.h"
//jaypark3, jin50

/*
This program is designed to navigate through a maze using the Depth-First Search (DFS) algorithm. 
The maze, defined in a maze_t structure, includes dimensions, start and end positions, and a 2D array of cells. 
The program comprises four key functions: createMaze, which reads the maze from a file and initializes 
the maze; destroyMaze, which frees the memory; printMaze, which displays the maze; 
and solveMazeDFS, which recursively finds a path from the start to the end.
*/

/*
 * createMaze -- Creates and fills a maze structure from the given file
 * INPUTS:       fileName - character array containing the name of the maze file
 * OUTPUTS:      None 
 * RETURN:       A filled maze structure that represents the contents of the input file
 * SIDE EFFECTS: None
 */
maze_t * createMaze(char * fileName)
{
    // Your code here. Make sure to replace following line with your own code.
    FILE *file = fopen(fileName, "r"); //read file
    maze_t * maze = malloc(sizeof(maze_t)); //allocating maze
    char c;
    fscanf(file, "%d %d", &maze->height, &maze->width); //getting height and width from the file
    maze->cells = malloc(sizeof(maze->cells)*(maze->height)); //allocating space for cells
   
    for(int i = 0; i < maze->height; i++){
        maze->cells[i] = malloc(sizeof(maze->cells[i]) * maze->width);
    }
    fscanf(file, "%c", &c);
    for(int i = 0; i < maze->height; i++){ //for loop for row
        for(int j = 0; j < maze->width; j++){ //for loop for col
            fscanf(file, "%c", &c);
            maze->cells[i][j] = c;
          
            if(maze->cells[i][j] == 'S'){ //checks for starting position
                maze->startRow = i;
                maze->startColumn = j;
            }
            if(maze->cells[i][j] == 'E'){ //checks for ending position
                maze->endRow = i;
                maze->endColumn = j;
            }
        }
        fscanf(file, "%c", &c);   
    }
    fclose(file); //close file
    return maze;
}
/*
 * destroyMaze -- Frees all memory associated with the maze structure, including the structure itself
 * INPUTS:        maze -- pointer to maze structure that contains all necessary information 
 * OUTPUTS:       None
 * RETURN:        None
 * SIDE EFFECTS:  All memory that has been allocated for the maze is freed
 */
void destroyMaze(maze_t * maze)
{
    // Your code here.
  for(int i = 0; i < maze->height; i++){ //for-loop for freeing memory
			free(maze->cells[i]); 
	}
	free(maze->cells);
	free(maze); //free maze
}

/*
 * printMaze --  Prints out the maze in a human readable format (should look like examples)
 * INPUTS:       maze -- pointer to maze structure that contains all necessary information 
 *               width -- width of the maze
 *               height -- height of the maze
 * OUTPUTS:      None
 * RETURN:       None
 * SIDE EFFECTS: Prints the maze to the console
 */
void printMaze(maze_t * maze)
{
    // Your code here.
	for(int i = 0; i < maze->height; i++){ //for-loop for row
		for(int j = 0; j < maze->width; j++){ //for-loop for col
			printf("%c", maze->cells[i][j]); //print each cell
		}
		printf("\n"); //print new line
	}
}

/*
 * solveMazeManhattanDFS -- recursively solves the maze using depth first search,
 * INPUTS:               maze -- pointer to maze structure with all necessary maze information
 *                       col -- the column of the cell currently beinging visited within the maze
 *                       row -- the row of the cell currently being visited within the maze
 * OUTPUTS:              None
 * RETURNS:              0 if the maze is unsolvable, 1 if it is solved
 * SIDE EFFECTS:         Marks maze cells as visited or part of the solution path
 */

int solveMazeDFS(maze_t * maze, int col, int row)
{
  // Your code here. Make sure to replace following line with your own code.
  if((maze->cells)[row][col]=='E') return 1; //return if it gets to end point
  
  if((maze->cells)[row][col]!=' '&&(maze->cells)[row][col]!='S') 
    return 0;  
  
  if((maze->cells)[row][col]==' '){ //if it is empty check the path
    (maze->cells)[row][col] = '*';
    }
  
  if(row<(maze->height)-1 && solveMazeDFS(maze,col,row+1)) //down
    return 1; 
  
  if(col>0 && solveMazeDFS(maze,col-1,row)) //left
    return 1;                
  
  if(col<(maze->width)-1 && solveMazeDFS(maze,col+1,row)) //right
    return 1;  
  
  if(row>0 && solveMazeDFS(maze,col,row-1)) //up
    return 1;                 
  
  if((maze->cells)[row][col]=='*') (maze->cells)[row][col] = '~'; //path that we went
    return 0;
}
