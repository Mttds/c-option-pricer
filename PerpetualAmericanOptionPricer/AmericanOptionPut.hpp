/* Put Options functions */
/*****************************************************
Name: AmericanOptionPut.hpp
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

#ifndef USOPTIONPUT_HPP
#define USOPTIONPUT_HPP

#include "AmericanOption.hpp"

class UsOptPut : public UsOpt {
private:
	/*Initialization of parameters for the option pricing model*/
	double rf; //risk-free interest rate
	double sig; //volatility
	double K; //strike price
	double b; //cost of carry that will equal rf for stock options

public:
	/*Default constructor, parameterized constructor, copy constructor, and destructor*/
	UsOptPut();
	UsOptPut(const UsOptPut& source); //copy constructor
	UsOptPut(double p_rf, double p_sig, double p_K, double p_b);
	UsOptPut(OptionData& data);
	virtual ~UsOptPut();

	/*Overload operators*/
	UsOptPut& operator = (const UsOptPut& source);

	/*Member functions to retrieve data*/
	double sigma() const;
	double rate() const;
	double strike() const;
	double CostOfCarry() const;

	/*Member functions to set the data*/
	void sigma(double new_sig);
	void rate(double new_rf);
	void strike(double new_K);
	void CostOfCarry(double new_b);

	/*Pricer functions*/
	double Price(double S) const;
	std::vector<double> PriceRange(int num, double start_S, double end_S);

	/*Printing functions*/
	virtual std::string ToString() const;

};

#endif
