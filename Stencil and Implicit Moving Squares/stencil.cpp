/**
 * University of Pittsburgh
 * Department of Computer Science
 * CS1645: Introduction to HPC Systems
 * Instructor: Esteban Meneses, PhD (emeneses@pitt.edu)
 * Student: Brian Lester
 * OpenMP 4.0 parallel stencil code.
 */
#include <omp.h>
#include <cstdio>
#include <cstdlib>
#include <math.h>

#define LINEAR(x,y,z) (z)*X*Y + (x)*Y + (y)
//
int stencil(double *grid, int X, int Y, int Z, double tol, int max_iter){
  int iter=0;
  double error = tol+1;
  double *gridNew;
  posix_memalign((void**)&gridNew, 64, X*Y*Z*sizeof(double));
  #pragma offload target(mic) inout(grid, gridNew:length(X*Y*Z))
  while(error > tol && iter < max_iter){
    error = 0.0; 
    #pragma omp parallel for reduction(max:error)
    for(int k = 1; k < Z-1; k++){
      for(int i = 1; i < X-1; i++){
        for(int j = 1; j < Y-1; j++){
          gridNew[LINEAR(i,j,k)] = (grid[LINEAR(i,j,k)] + grid[LINEAR(i-1,j,k)] + grid[LINEAR(i+1,j,k)] + grid[LINEAR(i,j-1,k)] + grid[LINEAR(i,j+1,k)] + grid[LINEAR(i,j,k-1)] + grid[LINEAR(i,j,k+1)])/7.0;
          error = fmax(error, fabs(gridNew[LINEAR(i,j,k)] - grid[LINEAR(i,j,k)]));
        }
      }
    }
    #pragma omp parallel for
    for(int i = 1; i < X-1; i++){
      for(int j = 1; j < Y-1; j++){
        for(int k = 1; k < Z-1; k++){
          grid[LINEAR(i,j,k)] = gridNew[LINEAR(i,j,k)];
        }
      }
    }
    iter++;
  }
  return iter;
}
