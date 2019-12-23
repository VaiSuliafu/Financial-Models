#include "PayOff1.h"
#include <minmax.h>

PayOff::PayOff(double Strike_, OptionType TheOptionsType_)
{
	setStrike(Strike_);
	setOptionType(TheOptionsType_);
}

double PayOff::operator ()(double spot) const
{
	switch (TheOptionsType)
	{
	case call:
		return max(spot - Strike, 0.0);
	
	case put:
		return max(Strike - spot, 0.0);

	default:
		throw("unknown option type found.");
	}
}

void PayOff::setStrike(double S)
{
	this->Strike = S;
}

void PayOff::setOptionType(OptionType o_type)
{
	this->TheOptionsType = o_type;
}
