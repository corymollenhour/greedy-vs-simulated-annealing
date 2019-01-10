/*
Cory Mollenhour
CSCI 4350 - Joshua Phillips
Due: 10/25/2018 11:00 PM
Finds the maximum value of the Sum of Gaussians (SoG) function
*/


#include <iostream>
#include <cstdlib>
#include "SumofGaussians.h"
#include <random>
using namespace std;

//Prototypes
double newRandom();


int main(int argc, char* argv[])
{
	int seed;
	int dims;
	int ncenters;

	if (argc == 4) {
		seed = atoi(argv[1]);
		dims = atoi(argv[2]);
		ncenters = atoi(argv[3]);
	}
	else {
		cout << "Needs 3 arguments" << endl;
		return 0;
	}

	int i = 0;

	srand(seed);
	SumofGaussians sog(dims, ncenters);

	double * input = new double[dims];
	double * dz = new double[ncenters];
	double slope = 0;
	double randomXPos = newRandom();
	double slopeMin = exp(-8);
	srand(seed);
	rand();
	randomXPos = newRandom();
	for (int x = 0; x < dims; x++)
		input[x] = randomXPos; //Set xPos to random location

	sog.deriv(input, dz);		//Take derivative at the xLocation
	for (int x = 0; x < dims; x++)
		slope = dz[x];				//Check slope at the random location

	if (slope > 0) { // Positieve slope -> climb right
		for (int x = 0; x < dims; x++)
			slope = dz[x];
		while (slope > slopeMin) {
			for (int x = 0; x < dims; x++) {
				cout << input[x] << " "; //Print xPos
				input[x] += 0.01*dz[x];
				sog.deriv(input, dz);
				slope = dz[0];
			}
			cout << sog.eval(input) << " "; //Print yPos
			cout << endl;

		}
	}
	else {			// Negative slope -> climb left
		for (int x = 0; x < dims; x++)
			slope = dz[x];
		while (slope < slopeMin*-1) {
			for (int x = 0; x < dims; x++) {
				cout << input[x] << " "; //Print xPos
				input[x] -= 0.01*dz[x];
				sog.deriv(input, dz);
				slope = dz[0];
			}
			cout << sog.eval(input) << " "; //Print yPos
			cout << endl;

		}
	}

	return 0;

}

//Generate a random location
double newRandom()
{
	return 0 + (double)rand() / RAND_MAX * (10 - 0);
}
