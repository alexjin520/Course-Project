//jaypark3, jin50

#include "sparsemat.h"

#include <stdio.h>
#include <stdlib.h>

/*This program processes input .txt files to carry out matrix
 operations such as addition and multiplication. 
Instead of using full array matrices, which can be large, it utilizes a linked list. 
Each node in the list contains a tuple that specifies 
both the position in the matrix and the value at that position. 
The matrix is represented by the `sp_tuples` data structure, 
which details the matrix's dimensions, 
the number of non-zero elements, and the head of the
linked list that contains the tuple nodes. 
We used load_tuples() to initialize the matrix from a file, gv_tuples() 
to get the value of an element, set_tuples() to set the value,
add_tuples() to add two matrices, save_tuples() to write the matrix to the file, 
and destroy_tuples() to free memory,
 */
sp_tuples * load_tuples(char* input_file)
{
    FILE *file;
    file = fopen(input_file, "r");//open file for reading

    sp_tuples * tuples = malloc(sizeof(sp_tuples));// Dynamically allocates memory for the matrix representation
    int rows;
    int cols;
    fscanf(file, "%d %d", &rows, &cols);

    tuples->m = rows;//#rows
    tuples->n = cols;//#columns
    tuples->nz = 0;
    tuples->tuples_head=NULL;// Initial linked list head is NULL
    double a;
    while (feof(file)==0)  {
        fscanf(file, "%d %d %lf", &rows, &cols, &a); 
        set_tuples(tuples, rows, cols, a);
    } 
    fclose(file);
    return tuples;
}



double gv_tuples(sp_tuples * mat_t,int row,int col)

{
  sp_tuples_node *pCurrent = mat_t->tuples_head; 
    while(pCurrent != NULL){   
        if(pCurrent->row == row && pCurrent->col == col) return pCurrent->value;// Returns the value if the node with the specified row and col is found
        else pCurrent = pCurrent->next;
    }
    return 0;
}


void delete_node(sp_tuples * mat_t, int row, int col){
    sp_tuples_node *pCurrent = mat_t->tuples_head;

    if(pCurrent == NULL) return;//If the list is empty, simply return
    if(pCurrent->row == row && pCurrent->col == col){//if the first node is the target, adjust the head
            free(pCurrent);
            mat_t->nz --;
            mat_t->tuples_head = NULL;
            return;
        }

    while(pCurrent != NULL){  
        if(pCurrent->next == NULL) break;
        if(pCurrent->next->row == row && pCurrent->next->col == col){//find the node and unlink it
            sp_tuples_node *temp = pCurrent->next;
            pCurrent->next = temp->next;
            free(temp);
            mat_t->nz = mat_t->nz- 1;
            return;
        }

        pCurrent = pCurrent->next;
    }


    return;

}


void set_tuples(sp_tuples * mat_t, int row, int col, double value)
{

    if(value == 0){
        delete_node(mat_t, row, col);// Removes the node if the value is zero since no need to store zero values
        return;
    }
   
    mat_t->nz += 1;// Increments the count of non-zero elements

    sp_tuples_node *new = malloc(sizeof(sp_tuples_node));

    new->col = col; //set column of the new node
    new->row = row; // set row of the new node
    new->value = value; //set value of the new node


    sp_tuples_node *current = mat_t->tuples_head;

   
    if(current==NULL){
        mat_t->tuples_head = new;// If list is empty, new node becomes the head
       
        new->next=NULL;
        return;
    }

 
    if((current->row > row || (current->row == row && current->col > col))){
        new->next = current;
        mat_t->tuples_head = new;
        return;
    }


    while(current!=NULL){ 
        if(current->row == row && current->col == col){
	  current->value = value; //update the node if it exists
            free(new);
            mat_t->nz--; //decrement non-zero count as we're replacing
            return;
        }
 
        if(current->next==NULL){
            current->next = new;
            new->next = NULL;
            return;
        }

        if(current->next->row > row || (current->next->row == row && current->next->col > col)){
            new->next = current->next;
            current->next = new;
            return;

        }

        current=current->next;//move to the next node in the list
        
    }
}



void save_tuples(char * file_name, sp_tuples * mat_t)
{
  FILE * file = NULL; 
  file = fopen(file_name, "w"); //open file for writing
  fprintf(file, "%d %d\n", mat_t->m, mat_t->n); //Print the matrix dimensions
  sp_tuples_node *current = mat_t->tuples_head;
  for(int i=0; i<mat_t->nz; i++){
        fprintf(file, "%d %d %lf\n", current->row, current->col, current->value);
        current = current->next;
    }
  fclose(file); //close the file after writing
	return;
}



sp_tuples * add_tuples(sp_tuples * matA, sp_tuples * matB){
  sp_tuples *matC = malloc(sizeof(sp_tuples)); //create a new matrix for the result
    matC->m = matA->m;
    matC->nz = 0;
    matC->n = matA->n;

    sp_tuples_node *pCurrent = matA->tuples_head;

    while(pCurrent != NULL){ //add all elements of MatA to MAtC
        set_tuples(matC, pCurrent->row, pCurrent->col, pCurrent->value);
        pCurrent = pCurrent->next;
    }

    pCurrent = matB->tuples_head;

    while(pCurrent != NULL){ //add all elements of MatB to MatC
        set_tuples(matC, pCurrent->row, pCurrent->col, gv_tuples(matC, pCurrent->row, pCurrent->col)+pCurrent->value);
        pCurrent = pCurrent->next;
    }

	return matC;
}



sp_tuples * mult_tuples(sp_tuples * matA, sp_tuples * matB){ 
  
    if (matA->n != matB->m)
        return NULL;
 
    sp_tuples_node *currentA = matA->tuples_head;
    sp_tuples_node *currentB = matB->tuples_head;

    sp_tuples * matC = malloc(sizeof(sp_tuples));
   
    matC->m = matA->m;
    matC->n = matB->n;
    matC->nz = 0;


    while(currentA != NULL)
    { 
        while(currentB != NULL)
        {
         
	  if (currentB->row == currentA->col) //check if indices are aligned for multiplication
            {
                set_tuples(matC, currentA->row, currentB->col, gv_tuples(matC, currentA->row, currentB->col)+currentA->value*currentB->value);
            }
            currentB = currentB->next;
        }
        currentA = currentA->next; 
        currentB = matB->tuples_head;
    }


    return matC;

}


	
void destroy_tuples(sp_tuples * mat_t){
    sp_tuples_node *curr = mat_t->tuples_head;
    sp_tuples_node *temp = NULL;
    while(curr != NULL){ //Traverse the list and free each node
        temp = curr->next;
        free(curr);
        curr = temp;

    }
    free(mat_t); //Finally, free the matrix structure itself	
    return;
}  

