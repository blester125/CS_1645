/**
 * University of Pittsburgh
 * Department of Computer Science
 * CS1645: Introduction to HPC Systems
 * Instructor: Esteban Meneses, PhD (emeneses@pitt.edu)
 * Student: 
 * OpenMP 4.0 parallel implicit moving squares method.
 */

#include "types.h"

#include <math.h>

#define SIGMA 0.008
#define SIGMA_2 SIGMA*SIGMA
#define GRID_MIN_X -0.5
#define GRID_MAX_X 0.6
#define GRID_MIN_Y -1.4
#define GRID_MAX_Y 1.1
#define GRID_MIN_Z 2.4
#define GRID_MAX_Z 3.4
// Function to linearize (x,y,z) coordinates
#define LINEAR(x,y,z) (z)*X*Y + (x)*Y + (y)
// Function phi
#define PHI(dx,dy,dz) exp(-0.5*(pow((dx),2) + pow((dy),2) + pow((dz),2))/SIGMA_2)

// Parallel implicit moving squares method
void implicit(double *grid, int X, int Y, int Z, Coordinates *particles, int N){
  // MODIFY THE FOLLOWING CODE AND ADD DIRECTIVES
  int i, j, k, p, outside;
  double dx, dy, dz, x, y, z, sum, sumPhi, diff_x, diff_y, diff_z, phi;
 // compute the distances between grid points in each dimension
  dx = (GRID_MAX_X - GRID_MIN_X) / (X - 1.0);
  dy = (GRID_MAX_Y - GRID_MIN_Y) / (Y - 1.0);
  dz = (GRID_MAX_Z - GRID_MIN_Z) / (Z - 1.0);

	// iterates over all the grid points (gather style)
  #pragma offload target(mic) in(particles:length(N)) in(p,N) inout(grid:length(X*Y*Z)) out(sum) out(sumPhi)
  #pragma omp parallel for
  for(k=0; k<Z; k++){
    for(j=0; j<Y; j++){
      for(i=0; i<X; i++){
	// generating the coordinates of the grid point
	x = GRID_MIN_X + i*dx;
	y = GRID_MIN_Y + j*dy;
	z = GRID_MIN_Z + k*dz;

	// traversing the whole list of particles
	sum = 0.0;
	sumPhi = 0.0;
	for(p=0; p<N; p++){
	  diff_x = x - particles[p].x;
	  diff_y = y - particles[p].y;
	  diff_z = z - particles[p].z;
	  phi = PHI(diff_x,diff_y,diff_z);
	  sum += (diff_x * particles[p].nx + diff_y * particles[p].ny + diff_z * particles[p].nz) * phi;
	  sumPhi += phi;
	}

	// updating grid point value
	grid[LINEAR(i,j,k)] = sum / sumPhi;
				
      }
    }
  }
}
