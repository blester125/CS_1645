/**
 * University of Pittsburgh
 * Department of Computer Science
 * CS1645: Introduction to HPC Systems
 * Instructor Esteban Meneses, PhD (emeneses@pitt.edu)
 * OpenMP 4.0 parallel stencil code.
 */

#include <cstdio>
#include <cstdlib>
#include <omp.h>
#include <math.h>
#include "timer.h"
#include "io.h"

#define MAX 1000
#define MAX_ITER 1000

int stencil(double *grid, int X, int Y, int Z, double tol, int max_iter);

// Main method      
int main(int argc, char* argv[]) {
	double elapsedTime;
	int X,Y,Z,iter;
	double *grid, tol;

	// checking parameters
	if (argc != 5 && argc != 6) {
		cout << "Parameters: <X> <Y> <Z> <tol> [<file>]" << endl;
		return 1;
	}
	X = atoi(argv[1]);
	Y = atoi(argv[2]);
	Z = atoi(argv[3]);
	tol = atof(argv[4]);

	// allocating multidimensional array
	posix_memalign((void**)&grid, 64, X*Y*Z*sizeof(double));

	// reading files (optional)
	if(argc == 6){
		read3DArrayFile(grid,X,Y,Z,argv[5]);
	} else {
		srand48(time(NULL));
		for(int k=0; k<Z; k++){
			for(int i=0; i<X; i++){
				for(int j=0; j<Y; j++){
					grid[k*X*Y+i*Y+j] = (double)(lrand48() % MAX);
				}
			}
		}
	}
	
	// starting timer
	timerStart();

	// calling shear sort function
	iter = stencil(grid,X,Y,Z,tol,MAX_ITER);

	// testing the results is correct
	if(argc == 6){
		print3DArray(grid,X,Y,Z);
	}
	
	// stopping timer
	elapsedTime = timerStop();

	cout << "Duration: " << elapsedTime << " seconds in " << iter << " iterations" << std::endl;

	return 0;
}

