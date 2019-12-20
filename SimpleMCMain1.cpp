// requires Random1.cpp
/*
requires Random1.cpp

Although our derivation of the SDE involved working with the long
of the spot, we have carefully avoided using log in this routine
because log and exp are slow to compute in comparison to addition 
and multiplication. We therefore want to make as few calls to them
as possible.*/

#include "Random1.h"
#include <iostream>
#include <cmath>
using namespace std;

/*
The function which does all of the work.

It takes in all the standard inputs for the Black-Scholes model,
the expiry and strike of the option, and the number of paths
to be used in the Monte Carlo
*/
double SimpleMonteCarlo1(double Expiry, double Strike, double Spot, double Vol, double r, unsigned long NumberOfPaths)
{
	// Pre-computing the variance of the log over the option's life
	double variance = Vol * Vol * Expiry;
	// Pre-computing the square root of the variance
	double rootVariance = sqrt(variance);
	// Pre-computing the adjustment term for the drift of the log
	double itoCorrection = -0.5 * variance;

	// Partially pre-computing the final value of spot
	double movedSpot = Spot * exp(r * Expiry + itoCorrection);
	double thisSpot;

	// runningSum will store the sum so far of the option pay-offs at all times
	double runningSum = 0;

	// Looping over all the paths, drawing a random number from the N(0,1)
	// distribution using the Box-Muller algorithm and put it in
	// the variable thisGaussian
	for (unsigned long i = 0; i < NumberOfPaths; ++i)
	{
		// Generate N(0,1) random number
		double thisGaussian = GetOneGaussianByBoxMuller();
		// the spot value at the end of the path is 'thisSpot'
		thisSpot = movedSpot * exp(rootVariance * thisGaussian);
		// Computing the calls option pay off
		double thisPayoff = thisSpot - Strike;
		// Taking the max between the pay off and 0
		thisPayoff = thisPayoff > 0 ? thisPayoff : 0;
		// Incrementing the running sum by the pay off
		runningSum += thisPayoff;
	}
	
	// dividing by number of paths to get the expectation
	double mean = runningSum / NumberOfPaths;
	// discounting our estimate of the price which we return
	mean *= exp(-r * Expiry);

	return mean;
}

int main()
{
	// Declaring the variables to be used as arguments
	double Expiry;
	double Strike;
	double Spot;
	double Vol;
	double r;
	unsigned long NumberOfPaths;

	// Getting the necessary values from the user
	cout << "\nEnter expiry\n";
	cin >> Expiry;
	cout << "\nEnter strike\n";
	cin >> Strike;
	cout << "\nEnter spot\n";
	cin >> Spot;
	cout << "\nEnter vol\n";
	cin >> Vol;
	cout << "\nEnter 'r'\n";
	cin >> r;
	cout << "\nNumber of paths\n";
	cin >> NumberOfPaths;

	// Calling the model
	double result = SimpleMonteCarlo1(Expiry, Strike, Spot, Vol, r, NumberOfPaths);

	// Displaying the model results
	cout << "The price is " << result << endl;

	return 0;
}