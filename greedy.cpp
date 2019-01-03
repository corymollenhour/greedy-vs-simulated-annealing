/*
Cory Mollenhour
CSCI 4350 - Joshua Phillips
Due: 10/25/2018 11:00 PM
Finds the maximum value of the Sum of Gaussians (SoG) function
*/


#include <iostream>
#include <cstdlib>

#include "SumofGaussians.h"

using namespace std;

//Prototypes
double newRandom();
void drawGraph(SumofGaussians * sog, double * input, double * dz, int dims, int iterations);

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

	srand(seed);
	rand();
	randomXPos = newRandom();
	for (int x = 0; x < dims; x++)
		input[x] = randomXPos; //Set xPos to random location

	sog.deriv(input, dz);		//Take derivative at the xLocation
	slope = dz[0];				//Check slope at the random location

	if (slope > 0) { // Positieve slope -> climb right
		slope = dz[0];
		while (slope > 0.00000001) {
			sog.deriv(input, dz);
			for (int x = 0; x < dims; x++) {
				cout << input[x] << " "; //Print xPos
				cout << sog.eval(input) << " "; //Print yPos
				input[x] += 0.01*dz[x];
				slope = dz[x];
				cout << endl;
			}

		}
	}
	else {			// Negative slope -> climb left
		slope = dz[0];
		while (slope < -0.00000001) {
			sog.deriv(input, dz);
			for (int x = 0; x < dims; x++) {
				cout << input[x] << " "; //Print xPos
				cout << sog.eval(input) << " "; //Print yPos
				input[x] -= 0.01*dz[x];
				slope = dz[x];
				cout << endl;
			}

		}
	}

	return 0;

}

double newRandom()
{
	return 0 + (double)rand() / RAND_MAX * (10 - 0);
}
