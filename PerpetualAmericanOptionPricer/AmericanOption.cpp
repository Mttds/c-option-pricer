/* Call and Put Options functions */
/*****************************************************
Name: AmericanOption.cpp
version: 0.1
Description:
Implementation of the functions provided in AmericanOption.hpp for Perpetual American Options

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

#include "AmericanOption.hpp"
#include "boost/random.hpp"
#include "boost/generator_iterator.hpp"

/*Generating random number for the contract*/
boost::mt19937 rng;
boost::uniform_int<> cnt(1, 1000000);
boost::variate_generator< boost::mt19937, boost::uniform_int<> > random(rng, cnt);

/*Default constructor, parameterized constructor, copy constructor, and destructor implementation*/
UsOpt::UsOpt() { //batch 1 is the default initialization for the default constructor
	m_contract = random();
}

UsOpt::UsOpt(const UsOpt& source) {
	m_contract = source.m_contract;
}

UsOpt::~UsOpt() {

}

/*Overload operators implementation*/
UsOpt& UsOpt::operator = (const UsOpt& source) {
	if (this != &source) {//checking if the objects are equal before performing assignment operations
		m_contract = source.m_contract;
	}
	return *this;
}

/*ToString member function implementation*/
std::string UsOpt::ToString() const {
	std::stringstream ss;
	ss << "\nContract Number: " << m_contract << endl;
	return ss.str();
}

/*Print member function implementation*/
std::string UsOpt::Print() const {
	std::stringstream print_info;
	print_info << ToString() << std::endl; //use ToString polymorphic function
	return print_info.str();
}
