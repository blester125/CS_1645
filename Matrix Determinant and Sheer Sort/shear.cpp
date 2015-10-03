/**
 * University of Pittsburgh
 * Department of Computer Science
 * CS1645: Introduction to HPC Systems
 * Instructor: Esteban Meneses, PhD (emeneses@pitt.edu)
 * Student: 
 * OpenMP parallel shear sort.
 */

#include <stdio.h>
#include <math.h>

void even_odd_sort(int* A, int M);
void even_odd_sort_reverse(int* A, int M);
void print_mat(int** A, int M){
  for(int i = 0; i < M; i++){
    for(int j = 0; j < M; j++){
      printf("%d ", A[i][j]);
    }
    printf("\n");
  }
}

// Shear Sort function
void shear_sort(int **A, int M){
// print_mat(A, M);
// printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
// // YOUR CODE GOES HERE
  for(int i = 0; i < log2(M*M); i++){
    //sort rows in opposite order
    #pragma omp parallel for
    for(int j = 0; j < M; j++){
      if(j & 1){
        even_odd_sort_reverse(A[j], M);
      } else {
        even_odd_sort(A[j], M);
      }
    }
    //sort coulmns
    #pragma omp parallel for
    for(int col = 0; col < M; col++){
      //copy column into array 
      int* column = new int[M];
      for(int row = 0; row < M; row++){
        column[row] = A[row][col];
      } 
      //sort column
      even_odd_sort(column, M);
      //copy coulmn array into matrix
      for(int row = 0; row < M; row++){
        A[row][col] = column[row];
      }
    } 
  }
// print_mat(A, M);
// printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
}

//parallelize
void even_odd_sort(int* A, int M){
  for(int i = 0; i < M; ++i){
    if(i & 1){
    //  #pragma omp parallel for
      for(int j = 2; j < M; j += 2){
        if(A[j] < A[j-1]){
          int temp = A[j];
          A[j] = A[j-1];
          A[j-1] = temp;
        }
      }
    } else {
    //  #pragma omp parallel for
      for(int j = 1; j < M; j += 2){
        if(A[j] < A[j-1]){
          int temp = A[j];
          A[j] = A[j-1];
          A[j-1] = temp;
        }
      }
    }
  }
}

//parallelize
void even_odd_sort_reverse(int* A, int M){
  for(int i = 0; i < M; ++i){
    if(i & 1){
    //  #pragma omp parallel for
      for(int j = 2; j < M; j += 2){
        if(A[j] > A[j-1]){
          int temp = A[j];
          A[j] = A[j-1];
          A[j-1] = temp;
        }
      }
    } else {
    //  #pragma omp parallel for
      for(int j = 1; j < M; j += 2){
        if(A[j] > A[j-1]){
          int temp = A[j];
          A[j] = A[j-1];
          A[j-1] = temp;
        }
      }
    }
  }
}

