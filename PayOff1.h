#ifndef PAYOFF_H
#define PAYOFF_H

class PayOff
{
public:

	// used to distinguish different sorts of pay-offs
	enum OptionType {call, put};

	/*
	The constructor.
	
	Takes in the strike of the option and the tyupe of the option pay-off.
	*/
	PayOff(double Strike_, OptionType TheOptionsType_);

	/*
	The main method of this class.
	
	The purpose of this method is that given a value of a spot,
	it returns the value of the pay-off.

	We have overloaded operator(), so to call this function for some
	instantiated obect "thisPayoff", we would write "thisPayoff(S)".
	Thus, this is a function object or functor.
	*/
	double operator ()(double Spot) const;

private:
	double Strike;
	OptionType TheOptionsType;

	/*
	Sets the strike price of this option to the argument 'S'.
	*/
	void setStrike(double S);

	/*
	Sets the option type for this option.
	*/
	void setOptionType(OptionType);
};

#endif