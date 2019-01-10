/*
Cory Mollenhour
CSCI 4350 - Joshua Phillips
Due: 10/25/2018 11:00 PM
Finds the maximum value of the Sum of Gaussians (SoG) function
Using simulated Annealing
*/


#include <iostream>
#include <cstdlib>
#include "SumofGaussians.h"
#include <random>

using namespace std;

//Prototypes
double newRandom(double origin, double span);
double probability(double newY, double oldY, double tmpr);
double randomInRange(double min, double max);
default_random_engine generator;

int main(int argc, char* argv[])
{
	int seed;
	int dims;
	int ncenters;

	if (argc == 4) {
		seed = atoi(argv[1]);
		dims = atoi(argv[2]);
		ncenters = atoi(argv[3]);
	} else {
		cout << "Needs 3 arguments" << endl;
		return 0;
	}
	int i = 0;
	srand(seed);
	SumofGaussians sog(dims, ncenters);
	double * input = new double[dims];
	double * dz = new double[ncenters];
	int maxIterations = 100000;
	double * currentLoc = new double[dims];
	double * newLoc = new double[dims];
	double * bestLoc = new double[dims];

	double gY;
	double gX;

	double tmprMin = 0.01;
	double alpha = 0.999;

	double acceptance;
	double randOrigin;
	bool isUnderTolerance = false;
	i = 0;
	double tmpr = 1.0;	
	double * startOrigin = new double[dims];
	for (int x = 0; x < dims; x++) {
			startOrigin[x] = getRandom() * 10;
	}
	while(tmpr > tmprMin && i < maxIterations){
		for (int x = 0; x < dims; x++) {
			currentLoc[x] = newRandom(startOrigin[x], tmpr * 10);
			newLoc[x] = newRandom(startOrigin[x], tmpr * 10);
		}
		gY = sog.eval(newLoc);
		gX = sog.eval(currentLoc);
		acceptance = probability(gY, gX, tmpr);
		if (gY > gX) {	// Evaluate at new point
			bestLoc = newLoc;
		} else {
			if (acceptance >= randomInRange(0, 1)) { //Encourage checking around while the temp is hot
				bestLoc = newLoc;
			} else {
				for (int x = 0; x < dims; x++) {
					newLoc[x] = currentLoc[x] + randomInRange(-0.01, 0.01);
				}
				gY = sog.eval(newLoc);
				if (gY > gX) {	// Evaluate at new point
					bestLoc = newLoc;
				}else{
					bestLoc = currentLoc;
				}
			}
		}		
		for (int x = 0; x < dims; x++) {
			if(tmpr < 0.1){
				cout << bestLoc[x] << " "; //Print xPos
			}
			
			startOrigin[x] = bestLoc[x];
		}
		if(tmpr < 0.1){
			cout << sog.eval(bestLoc) << " "; //Print yPos
			cout << endl;
		}
		tmpr *= alpha;
		i++;
	}
	return 0;
}

//Calculate probablity of acceptance
double probability(double gY, double gX, double tmpr) {
	if (gY > gX)
		return 1.0;
	else
		return exp((gY - gX) / tmpr);
}

//Generate a new Random location based on a current location
double newRandom(double origin, double span)
{
	double newLoc = 0;
	double lh, rh;
	rh = origin + span;
	lh = origin - span;
	if(lh < 0) lh = 0;
	if (rh > 10) rh = 10;
	return randomInRange(lh, rh);
}

// Get a random value between min and max
double randomInRange(double min, double max)
{
	uniform_real_distribution<double> distr(min, max);
	return distr(generator);
}
