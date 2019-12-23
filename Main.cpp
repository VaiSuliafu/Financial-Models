#include "PayOff1.h"
#include "Random1.h"
#include "SimpleMC.h"
#include "SimpleMCProcedural.h"
#include <cmath>
#include <iostream>

using namespace std;

int main() {
    // Declaring the variables to be used as arguments
    double Expiry;               // model 1,2
    double Strike;               // model 1,2
    double Spot;                 // model 1,2
    double Vol;                  // model 1,2
    double r;                    // model 1,2
    unsigned long NumberOfPaths; // model 1,2

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
    double resultCall1 =
        SimpleMonteCarlo1('C', Expiry, Strike, Spot, Vol, r, NumberOfPaths);

    double resultPut1 =
        SimpleMonteCarlo1('P', Expiry, Strike, Spot, Vol, r, NumberOfPaths);
    // Displaying the model results
    cout << "Model 1 call price: $" << resultCall1 << endl;

    cout << "Model 1 put price: $" << resultPut1 << endl;

    // Instantiating the pay off objects for model 2
    PayOff callPayOff(Strike, PayOff::call);
    PayOff putPayOff(Strike, PayOff::put);

    // Calling the second model
    double resultCall2 =
        SimpleMonteCarlo2(callPayOff, Expiry, Spot, Vol, r, NumberOfPaths);

    double resultPut2 =
        SimpleMonteCarlo2(putPayOff, Expiry, Spot, Vol, r, NumberOfPaths);

    cout << "Model 2 call price: $" << resultCall2 << endl;

    cout << "Model 2 put price: $" << resultPut2 << endl;

    return 0;
}