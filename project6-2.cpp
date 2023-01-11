//Cobi Sabo and Tyler Pollard
//May 1st 2017 
//Movie Madness
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "mpi.h" // message passing interface
using namespace std;

// Do this ONCE when you start up thomas
// module load openmpi-x86_64

// New compile and run commands for MPI!
// mpicxx -o blah file.cpp
// mpirun -np 32 blah

int main (int argc, char * argv[]) {

	int my_rank;			// my CPU number for this process
	int p;					// number of CPUs that we have
	int source;				// rank of the sender
	int dest;				// rank of destination
	int tag = 0;			// message number
	char message[100];		// message itself
	MPI_Status status;		// return status for receive
	
	// Start MPI
	MPI_Init(&argc, &argv);
	
	// Find out my rank!
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
	
	// Find out the number of processes!
	MPI_Comm_size(MPI_COMM_WORLD, &p);
	
	// THE REAL PROGRAM IS HERE

	// I'm setting up a random array of numbers here, fixed to a set seed.
	// This will create the same set of random numbers, as long as the seed isn't changed.
	// I would recommend you copy this boilerplate down into a separate program to figure out what the max, min, and average are for this seed. 
	// Then you know what answer you should get from your parallel program.
	// Be sure to test your program for different seed values!!! (So you only need to change the seed, nothing else.)
	
	// For the final output, run your program for seed value 2109, 6667, and 31237 and tell me the output from these three seed runs.
	int seed = 2109;
	srand(seed);
	const int n = 1000000;

	// The huge array is this one
	int a[n] = {0};
	for (int x = 0; x < n; x++)
		a[x] = rand();
	
	// Remember that your average has to be a decimal value, like a double!!!
	// Also remember that you need to compute the minimum and maximum!

	// WRITE CODE HERE!!!!!
	
	//Know the problem
	int max = 0;
	int min = 0;
	double avg = 0;
	
	//divide the problem up
	//assume 25 processors
	int locala[40000];
	int localn = n/p; //40000
	int localmin;
	int localmax;
	double localsum = 0;
	MPI_Scatter(&a[0], localn, MPI_INT, locala, localn, MPI_INT, 0, MPI_COMM_WORLD);
	
	//do the local work
	for(int x = 0; x < n/p -1; x++){
		for(int y = 1; y < n/p; y++){
			if(locala[x] > locala[y]){
				int temp = locala[x];
				locala[x] = locala[y];
				locala[y] = temp;
			} //end if 
		} //end 2nd for 
	} //end 1st for 
	localmin = locala[0];
	localmax = locala[n/p - 1];
	
	for(int x = 0; x < localn; x++)//avg
		localsum += locala[x];
	
	for(int x = 0; x < p; x++) //max
		MPI_Reduce(&localmax, &max, 1, MPI_INT, MPI_MAX, x, MPI_COMM_WORLD);
		
	for(int x = 0; x < p; x++) //min
		MPI_Reduce(&localmin, &min, 1, MPI_INT, MPI_MIN, x, MPI_COMM_WORLD);
		
	for(int x = 0; x < p; x++)
		MPI_Reduce(&localsum, &avg, 1, MPI_DOUBLE, MPI_SUM, x, MPI_COMM_WORLD);
	
	if(my_rank == 0){
		cout << "The average foot size is " << avg/n << " inches long!!!" << endl;
		cout << "The maximum foot size is " << max  << " inches long!! WOW!!!" << endl;
		cout << "The minimun foot size is " << min << " inches long!! BOO!!!" << endl;
	}
	// Shut down MPI
	MPI_Finalize();

	return 0;
}