#ifndef SIMPLEMCPROCEDURAL_H
#define SIMPLEMCPROCEDURAL_H

#include "Random1.h"

/*
The function which does all of the work.

It takes in all the standard inputs for the Black-Scholes model,
the expiry and strike of the option, and the number of paths
to be used in the Monte Carlo
*/
double SimpleMonteCarlo1(char o_type, double Expiry, double Strike, double Spot,
                         double Vol, double r, unsigned long NumberOfPaths);

#endif
