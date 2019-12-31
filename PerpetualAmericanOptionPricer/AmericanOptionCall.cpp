/* Call Options functions */
/*****************************************************
Name: AmericanOptionCall.cpp
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

#include "AmericanOptionCall.hpp"
#include <cmath>
#include <iostream>

/*Default constructor, parameterized constructor, copy constructor, and destructor implementation*/
UsOptCall::UsOptCall() : K(65), rf(0.08), sig(0.30), b(rf), UsOpt() {//batch 1 is the default initialization for the default constructor
	
}

UsOptCall::UsOptCall(const UsOptCall& source) : UsOpt(source) {
	K = source.K;
	rf = source.rf;
	sig = source.sig;
	b = source.b;
}

UsOptCall::UsOptCall(double p_rf, double p_sig, double p_K, double p_b) : UsOpt() {
	rf = p_rf;
	sig = p_sig;
	K = p_K;
	b = p_b;
}

UsOptCall::UsOptCall(OptionData& data) : K(data.K), rf(data.rf), sig(data.sig), b(data.b), UsOpt() {
	//Constructor that takes a structure with the option data defined in OptionData.hpp
}

UsOptCall::~UsOptCall() {

}

/*Overload operators implementation*/
UsOptCall& UsOptCall::operator = (const UsOptCall& source) {
	if (this != &source) {//checking if the objects are equal before performing assignment operations
		UsOpt::operator=(source);
		K = source.K;
		rf = source.rf;
		sig = source.sig;
		b = source.b;
	}
	return *this;
}

/*Implementation of member functions to retrieve data*/
double UsOptCall::sigma() const {
	return sig;
}

double UsOptCall::rate() const {
	return rf;
}

double UsOptCall::strike() const {
	return K;
}

double UsOptCall::CostOfCarry() const {
	return b;
}

/*Implementation of member functions to set the data*/
void UsOptCall::sigma(double new_sig) {
	sig = new_sig;
}
void UsOptCall::rate(double new_rf) {
	rf = new_rf;
}
void UsOptCall::strike(double new_K) {
	K = new_K;
}
void UsOptCall::CostOfCarry(double new_b) {
	b = new_b;
}

/*Pricer functions implementation*/
double UsOptCall::Price(double S) const {
	double y1;
	double C;
	y1 = 0.5 - b/pow(sig,2) + sqrt((b/pow(sig,2) - 0.5)*(b / pow(sig, 2) - 0.5) + 2.0*rf/pow(sig, 2));
	if (y1 == 1.0)
	{
		return S;
	}
	C = (K / (y1 - 1)) * pow(((y1 - 1) / y1 * S / K), y1);
	
	return C;
}

std::vector<double> UsOptCall::PriceRange(int num, double start_S, double end_S) { //num equals the number of increments before reaching the end price end_S
	std::vector<double> vec;
	vec.resize(num + 1); //allocates space
	double mesh_size = (end_S - start_S) / num; //increment size h
	for (int i = 0; i <= num; i++) {//using an iterator is also possible
		vec[i] = this->Price(start_S + i*mesh_size); //mesh of spots from start_S to end_S separated by h = mesh_size: [start_s, start_s + h, ... , end_S]
		cout << "Underlying S @t0 equals: " << start_S + i*mesh_size << endl;
	}
	return vec;
}


/*Print function implementation*/
std::string UsOptCall::ToString() const {
	std::string s = UsOpt::ToString();
	std::stringstream ss;
	ss << s << "\n********** CALL OPTION PARAMETERS **********\n" << "\nK: " << K << "\nrf: " << rf << "\nsig: " << sig << "\nb: " << b << endl;
	return ss.str();
}