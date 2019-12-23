/*
requires Random1.cpp

Although our derivation of the SDE involved working with the long
of the spot, we have carefully avoided using log in this routine
because log and exp are slow to compute in comparison to addition
and multiplication. We therefore want to make as few calls to them
as possible.*/

#include "SimpleMCProcedural.h"
#include "Random1.h"
#include <cmath>
#include <iostream>
using namespace std;

double SimpleMonteCarlo1(char o_type, double Expiry, double Strike, double Spot,
                         double Vol, double r, unsigned long NumberOfPaths) {
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
  for (unsigned long i = 0; i < NumberOfPaths; ++i) {
    // Generate N(0,1) random number
    double thisGaussian = GetOneGaussianByBoxMuller();
    // the spot value at the end of the path is 'thisSpot'
    thisSpot = movedSpot * exp(rootVariance * thisGaussian);

    // Declaring variable to hold value of this option pay off
    double thisPayoff = 0;

    if (o_type == 'C') {
      // Computing the call's option pay off
      thisPayoff = thisSpot - Strike;
    } else if (o_type == 'P') {
      // Computing this put's option pay off
      thisPayoff = Strike - thisSpot;
    }

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
