/**
 * University of Pittsburgh
 * Department of Computer Science
 * CS1645: Introduction to HPC Systems
 * Instructor Esteban Meneses, PhD (emeneses@pitt.edu)
 * OpenMP 4.0 parallel implicit moving squares method.
 */

#include <cstdio>
#include <cstdlib>
#include <omp.h>
#include <math.h>
#include "timer.h"
#include "io.h"

#define PRECISION 1000

void implicit(double *grid, int X, int Y, int Z, Coordinates *particles, int N);

// Main method      
int main(int argc, char* argv[]) {
	double elapsedTime;
	int X,Y,Z,N;
	double *grid;
	Coordinates *particles;

	// checking parameters
	if (argc != 5 && argc != 6) {
		cout << "Parameters: <X> <Y> <Z> <N> [<file>]" << endl;
		return 1;
	}
	X = atoi(argv[1]);
	Y = atoi(argv[2]);
	Z = atoi(argv[3]);
	N = atoi(argv[4]);

	// allocating multidimensional array
	posix_memalign((void**)&grid, 64, X*Y*Z*sizeof(double));
	posix_memalign((void**)&particles, 64, N*sizeof(Coordinates));

	// setting values to 0
	for(int k=0; k<Z; k++){
		for(int i=0; i<X; i++){
			for(int j=0; j<Y; j++){
				grid[k*X*Y+i*Y+j] = 0.0;
			}
		}
	}	

	// reading files (optional)
	if(argc == 6){
		readParticlesFile(particles,N,argv[5]);
	} else {
		srand48(time(NULL));
		for(int i=0; i<N; i++){
			particles[i].x = (double)(lrand48() % (X*PRECISION))/(double)(X*PRECISION)*X;
			particles[i].y = (double)(lrand48() % (Y*PRECISION))/(double)(Y*PRECISION)*Y;
			particles[i].z = (double)(lrand48() % (Z*PRECISION))/(double)(Z*PRECISION)*Z;
			particles[i].nx = particles[i].x/(double)X;
			particles[i].ny = particles[i].y/(double)Y;
			particles[i].nz = particles[i].z/(double)Z;
		}
	}
	
	// starting timer
	timerStart();

	// calling shear sort function
	implicit(grid,X,Y,Z,particles,N);

	// testing the results is correct
	if(argc == 6){
		print3DArray(grid,X,Y,Z);
	}
	
	// stopping timer
	elapsedTime = timerStop();

	cout << "Duration: " << elapsedTime << " seconds" << std::endl;

	return 0;	
}

