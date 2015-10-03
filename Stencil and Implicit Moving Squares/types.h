/**
 * University of Pittsburgh
 * Department of Computer Science
 * CS1645: Introduction to HPC Systems
 * Instructor Esteban Meneses, PhD (emeneses@pitt.edu)
 * Type definitions.
 */

#ifndef TYPES_CS1645
#define TYPES_CS1645

// Type to store coordinates of a particle in space.
typedef struct{
    double x;
    double y;
    double z;
    double nx;
    double ny;
    double nz;
} Coordinates;

#endif
