/* Call Options functions */
/*****************************************************
Name: EUOptionCall.hpp
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

#ifndef EUOPTIONCALL_HPP
#define EUOPTIONCALL_HPP

#include "EUOption.hpp"

class EuOptCall : public EuOpt {
private:
	/*Initialization of parameters for the option pricing model*/
	double rf; //risk-free interest rate
	double sig; //volatility
	double K; //strike price
	double T; //expiry time/maturity expressed in years (e.g T = 2 is 2 years maturity)
	double b; //cost of carry that will equal rf for stock options

public:
	/*Default constructor, parameterized constructor, copy constructor, and destructor*/
	EuOptCall();
	EuOptCall(const EuOptCall& source); //copy constructor
	EuOptCall(double p_rf, double p_sig, double p_K, double p_T, double p_b);
	EuOptCall(OptionData& data);
	virtual ~EuOptCall();

	/*Overload operators*/
	EuOptCall& operator = (const EuOptCall& source);

	/*Member functions to retrieve data*/
	double maturity() const;
	double sigma() const;
	double rate() const;
	double strike() const;
	double CostOfCarry() const;

	/*Member functions to set the data*/
	void maturity(double new_T);
	void sigma(double new_sig);
	void rate(double new_rf);
	void strike(double new_K);
	void CostOfCarry(double new_b);

	/*Pricer & sensitivites functions*/
	double Price(double S) const;
	//double Price(double S, OptionData& data); //Pricer function that does not need to be called on an instance of the class
	double PutCallParity(double S) const;
	double PutCallParity(double C, double S) const;
	std::vector<double> PriceRange(int num, double start_S, double end_S); // Prices as f(S)
	std::vector<double> PriceRange(int num, double S, double start, double end, int param); //Prices as f(T) or f(sig) --expiry time or volatility
	//Greeks initialization
	double Delta(double S) const;
	double Gamma(double S) const;
	double Vega(double S) const;
	double Theta(double S) const;
	std::vector<double> GreeksRange(int num, double start_S, double end_S, int param); //Sensitivities as a f(S)
	//We now use divided differences to approximate option sensitivities.
	//In general, we can approximate first and second - order derivatives in S by 3-point second order approximations
	//As we input a smaller and smaller h, the approximation gets closer to the actual B-S formula
	double DeltaDDM(double S, double h) const; //approximate Delta using the Divided Differences Method
	double GammaDDM(double S, double h) const; //approximate Gamma using the Divided Differences Method
	std::vector<double> GreeksRangeDDM(int num, double h,double start_S, double end_S, int param); //Sensitivities as a f(S) using DDM

	/*Printing functions*/
	virtual std::string ToString() const;

};

#endif
