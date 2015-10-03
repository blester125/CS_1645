/**
 * University of Pittsburgh
 * Department of Computer Science
 * CS1645: Introduction to HPC Systems
 * Instructor: Esteban Meneses, PhD (emeneses@pitt.edu)
 * Student: Brian Lester
 * OpenMP parallel determinant computation.
 */

#include <stdio.h>
#include <math.h>

int det_serial(int **A, int N);

void print_mat(int **A, int N){
  for(int i = 0; i < N; i++){
    for(int j = 0; j < N; j++){
      printf("%d", A[i][j]);
    }
    printf("\n");
  }
}

// Determinant function
int determinant(int **A, int N){
  int result = 0;
  
  // YOUR CODE GOES HERE
 // print_mat(A,N); 
  if(N == 2){
    result = A[0][0] * A[1][1] - A[1][0] * A[0][1];
  }
  else{
    int* det_array = new int[N];
    //parallelize shared det_array
    #pragma omp parallel for shared(det_array)
    for(int minj = 0; minj < N; minj++){
      int* minor_elements = new int[(N-1)*(N-1)];
      int** minor = new int*[N-1];
      for(int k = 0; k < N-1; k++){
        minor[k] = new int[N-1];
      }
     // int minj = 0;
      int mini = 0;
      int itr = 0;  
      for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
          if(i == mini){
            continue;
          }
          if(j == minj){
            continue;
          }
          else{
            minor_elements[itr] = A[i][j];
            itr++;
          }
        }
      }
      itr = 0;
      for(int k = 0; k < N-1; k++){
        for(int l = 0; l < N-1; l++){
          minor[k][l] = minor_elements[itr];
          itr++;
        }
      }
   //   printf("~~~~~~~~~~~~Current Minor~~~~~~~~~~~~\n");
   //   print_mat(minor, N-1);
      det_array[minj] = det_serial(minor, N-1);
    }
    int cofactor = 0;
    for(int j = 0; j < N; j++){
      cofactor = pow(-1, 0+j) * A[0][j];
      result = result + cofactor * det_array[j];
    }
  }
 // print_mat(A, N);
 // printf("~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
 // result = det_serial(A, N);
  return result;
}

int det_serial(int **A, int N){
  int det = 0;
  if(N == 2){ 
    det =  A[0][0] * A[1][1] - A[1][0] * A[0][1];
  //  printf("det of: \n");
  //  print_mat(A,N);
  //  printf("%d\n", det);
    return det;   
  }  
  else{
    int* minor_elements = new int[(N-1)*(N-1)];
    int** minor = new int*[N-1];
    for(int k = 0; k < N-1; k++){
      minor[k] = new int[N-1];
    }  
    int itr = 0;
    int mini = 0;
    for(int minj = 0; minj < N; minj++){
      itr = 0;
      for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
          if(i == mini){
            continue;
          }
          if(j == minj){
            continue;
          }    
          else{
            minor_elements[itr] = A[i][j];
            itr++;
          }
        }
      }
      itr = 0;
      for(int k = 0; k < N-1; k++){
        for(int l = 0; l < N-1; l++){
          minor[k][l] = minor_elements[itr];
          itr++;
        }
      }
  //    printf("~~~~~~~~~~~Current Minor~~~~~~~~~~~~~~\n");
  //    print_mat(minor, N-1);
      int cofactor = 0;
      cofactor = pow(-1, mini+minj) * A[mini][minj];
  //    printf("Cofactor:\n");
  //    printf("%d\n", cofactor);
  //    printf("%d\n", det_serial(minor,N-1, det));
  //    printf("~~~~~~~~~~~~~~~~~~~~~~~~~\n");
      det = det + cofactor*det_serial(minor, N-1);
    }
  }
//  printf("%d\n", det);
  return det;
}
