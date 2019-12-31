/* Call and Put Options functions */
/*****************************************************
Name: AmericanOption.hpp
version: 0.1
Description:
These functions provide functionality for Perpetual American Options

Change history:
0.1 Initial version

Parameters:
T (expiry time/maturity). This is a number, e.g. T = 1 means one year.
K (strike price).
sig (volatility).
rf (risk-free interest rate).
S (current stock price where we wish to price the option).
C = call option price, P = put option price.

European option can only be exercised at the expiry date T and an exact solution is known. An American
option is a contract that can be exercised at any time prior to T. Most traded stock options are American style. In
general, there is no known exact solution to price an American option but there is one exception, namely
perpetual American options. The formulae are:

C = K/(y1-1)*((y1-1)/y1 * S/K)^y1
y1 = 1/2 - b/sig^2 + sqrt((b/sig^2 - 1/2)^2 + (2*r)/sig^2)

and,

P = (K/(1-y2))*((y2-1)/y2 *S/K)^y2
y2 = 1/2 - b/sig^2 - sqrt((b/sig^2 - 1/2)^2 + (2*r)/sig^2)

In general, the perpetual price is the time-homogeneous price and is the same as the normal price when the
expiry price T tends to infinity. In general, American options are worth more than European options.

******************************************************/

#ifndef USOPTION_HPP
#define USOPTION_HPP

#include <string>
#include <iostream>
#include <sstream>
#include "OptionData.hpp"
#include <vector>
#include <iterator>
using namespace std;

class UsOpt {
private:
	/*Contract number and underlying stock*/
	int m_contract;
	string underlying;	//name of underlying asset

public:
	/*Default constructor, parameterized constructor, copy constructor, and destructor*/
	UsOpt();
	UsOpt(const UsOpt& source); //copy constructor
	virtual ~UsOpt();

	/*Overload operators*/
	UsOpt& operator = (const UsOpt& source);

	/*Printing functions*/
	virtual std::string ToString() const;
	std::string Print() const;
};

#endif

