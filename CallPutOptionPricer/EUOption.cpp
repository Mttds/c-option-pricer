/* Call and Put Options functions implementation */
/*****************************************************
Name: EUOption.cpp
version: 0.1
Description:
Implementation of the functions in EUOption.hpp to
provide functionality for plain (European) equity options (with zero dividends)

Change history:
0.1 Initial version

Parameters:
T (expiry time/maturity). This is a number, e.g. T = 1 means one year.
K (strike price).
sig (volatility).
r (risk-free interest rate).
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

#include "EUOption.hpp"
#include <boost/math/distributions.hpp> // For non-member functions of distributions
#include <boost/math/distributions/normal.hpp>
#include "boost/random.hpp"
#include "boost/generator_iterator.hpp"

/*Generating random number for the contract*/
boost::mt19937 rng;
boost::uniform_int<> cnt(1, 1000000);
boost::variate_generator< boost::mt19937, boost::uniform_int<> > random(rng, cnt);

/*Gaussian functions implementation*/
using namespace boost::math;
double EuOpt::n(double x) const {
	normal_distribution<double> norm(0.0, 1.0);
	return pdf(norm, x);
}

double EuOpt::N(double x) const {
	normal_distribution<double> norm(0.0, 1.0);
	return cdf(norm, x);
}

/*Default constructor, parameterized constructor, copy constructor, and destructor implementation*/
EuOpt::EuOpt() { //batch 1 is the default initialization for the default constructor
	m_contract = random();
}

EuOpt::EuOpt(const EuOpt& source) {
	m_contract = source.m_contract;
}

EuOpt::~EuOpt() {

}

/*Overload operators implementation*/
EuOpt& EuOpt::operator = (const EuOpt& source) {
	if (this != &source) {//checking if the objects are equal before performing assignment operations
		m_contract = source.m_contract;
	}
	return *this;
}

/*ToString member function implementation*/
std::string EuOpt::ToString() const {
	std::stringstream ss;
	ss << "\nContract Number: " << m_contract << endl;
	return ss.str();
}

/*Print member function implementation*/
std::string EuOpt::Print() const {
	std::stringstream print_info;
	print_info << ToString() << std::endl; //use ToString polymorphic function
	return print_info.str();
}



