/* Call and Put Options functions */
/*****************************************************
Name: EUOption.hpp
version: 0.1
Description:
These functions provide functionality for plain (European) equity options (with zero dividends)

Change history:
0.1 Initial version

Parameters:
T (expiry time/maturity). This is a number, e.g. T = 1 means one year.
K (strike price).
sig (volatility).
rf (risk-free interest rate).
S (current stock price where we wish to price the option).
C = call option price, P = put option price.
note that n(x) is the normal (Gaussian) probability density function
and N(x) is the cumulative normal distribution function

Generalized Black-Scholes formula:
C = C(S;K; T; r; sig)
S = asset price
K = strike price
T = exercise (maturity) date
r = risk-free interest rate
sig = constant volatility
b = cost of carry

The exact formula for C and P is given by:
C = Se^((b-r)T) * N(d1) - Ke^(rT) * N(d2)
P = Ke^(-rT) * N(-d2) - Se^((b-r)T) * N(-d1)

For the case of stock options we will take b = r in your calculations

There is a relationship between the price of a European call option and the price of a European put option when
they have the same strike price K and maturity T. This is called put-call parity and is given by the formula:

									C + Ke^(-rT) = P + S

******************************************************/

#ifndef EUOPTION_HPP
#define EUOPTION_HPP

#include <string>
#include <iostream>
#include <sstream>
#include "OptionData.hpp"
#include <vector>
#include <iterator>
using namespace std;

class EuOpt {
private:
	/*Contract number and underlying stock*/
	int m_contract;
	string underlying;	//name of underlying asset

public:
	/*Default constructor, parameterized constructor, copy constructor, and destructor*/
	EuOpt();
	EuOpt(const EuOpt& source); //copy constructor
	virtual ~EuOpt();

	/*Overload operators*/
	EuOpt& operator = (const EuOpt& source);

	/*Printing functions*/
	virtual std::string ToString() const;
	std::string Print() const;

	/*Cumulative distribution function and Probability distribution function*/
	double n(double x) const; //pdf
	double N(double x) const; //cdf

};

#endif
