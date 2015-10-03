/**
 * University of Pittsburgh
 * Department of Computer Science
 * CS1645: Introduction to HPC Systems
 * Instructor Esteban Meneses, PhD (emeneses@pitt.edu)
 * Input/output operations for arrays and matrices.
 */

#include <iostream>
#include <fstream>
#include "types.h"

using namespace std;

// Reads a matrix from text file
int readArrayFile(int *A, int N, char *fileName){
	ifstream file(fileName);
	if(file.is_open()){
		
		// reading array values
		for(int i=0; i<N; i++){
			file >> A[i];
		}

		// closing file
		file.close();

	} else {
		cout << "Error opening file: " << fileName << endl;
		return 1;
	}
	return 0;
}

// Prints array to standard output
void printArray(int *A, int N){
	for(int i=0; i<N; i++){
		cout << A[i] << "\t";
	}
	cout << endl;
}

// Reads a matrix from text file
int readMatrixFile(int **matrix, int N, char *fileName){
	ifstream file(fileName);
	if(file.is_open()){
		
		// reading matrix values
		for(int i=0; i<N; i++){
			for(int j=0; j<N; j++){
				file >> matrix[i][j];
			}
		}

		// closing file
		file.close();

	} else {
		cout << "Error opening file: " << fileName << endl;
		return 1;
	}
	return 0;
}

// Prints matrix to standard output
void printMatrix(int **matrix, int N){
	for(int i=0; i<N; i++){
		for(int j=0; j<N; j++){
			cout << matrix[i][j] << "\t";
		}
		cout << endl;
	}
}

// Reads a 3D array from text file
int read3DArrayFile(double *grid, int X, int Y, int Z, char *fileName){
	ifstream file(fileName);
	if(file.is_open()){
		
		// reading array values
		for(int k=0; k<Z; k++){
			for(int i=0; i<X; i++){
				for(int j=0; j<Y; j++){
					file >> grid[k*X*Y+i*Y+j];
				}
			}
		}

		// closing file
		file.close();

	} else {
		cout << "Error opening file: " << fileName << endl;
		return 1;
	}
	return 0;
}

// Prints array to standard output
void print3DArray(double *grid, int X, int Y, int Z){
	for(int k=0; k<Z; k++){
		for(int i=0; i<X; i++){
			for(int j=0; j<Y; j++){
				cout << grid[k*X*Y+i*Y+j] << "\t";
			}
			cout << endl;
		}
		cout << endl;
	}
}

// Reads particle positions from text file
int readParticlesFile(Coordinates *particles, int N, char *fileName){
	ifstream file(fileName);
	if(file.is_open()){
		
		// reading array values
		for(int i=0; i<N; i++){
			file >> particles[i].x;
			file >> particles[i].y;
			file >> particles[i].z;
			file >> particles[i].nx;
			file >> particles[i].ny;
			file >> particles[i].nz;
		}

		// closing file
		file.close();

	} else {
		cout << "Error opening file: " << fileName << endl;
		return 1;
	}
	return 0;
}

