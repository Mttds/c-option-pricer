/* Put Options functions implementation */
/*****************************************************
Name: EUOptionPut.cpp
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

#include "EUOptionPut.hpp"
#include <cmath>
#include <iostream>

/*Default constructor, parameterized constructor, copy constructor, and destructor implementation*/
EuOptPut::EuOptPut() : T(0.25), K(65), rf(0.08), sig(0.30), b(rf), EuOpt() {//batch 1 is the default initialization for the default constructor
	//Black-Scholes stock option model (1973). 
	//The cost of carry varies depending on the model, but since our plain options pay no dividends we will approximate it to the risk free rate
}

EuOptPut::EuOptPut(const EuOptPut& source) : EuOpt(source) {
	T = source.T;
	K = source.K;
	rf = source.rf;
	sig = source.sig;
	b = source.b;
}

EuOptPut::EuOptPut(double p_rf, double p_sig, double p_K, double p_T, double p_b) : EuOpt() {
	rf = p_rf;
	sig = p_sig;
	K = p_K;
	T = p_T;
	b = p_b;
}

EuOptPut::EuOptPut(OptionData& data) : T(data.T), K(data.K), rf(data.rf), sig(data.sig), b(data.b), EuOpt() {
	//Constructor that takes a structure with the option data defined in OptionData.hpp
}

EuOptPut::~EuOptPut() {

}

/*Overload operators implementation*/
EuOptPut& EuOptPut::operator = (const EuOptPut& source) {
	if (this != &source) {//checking if the objects are equal before performing assignment operations
		EuOpt::operator=(source);
		T = source.T;
		K = source.K;
		rf = source.rf;
		sig = source.sig;
		b = source.b;
	}
	return *this;
}

/*Implementation of member functions to retrieve data*/
double EuOptPut::maturity() const {
	return T;
}

double EuOptPut::sigma() const {
	return sig;
}

double EuOptPut::rate() const {
	return rf;
}

double EuOptPut::strike() const {
	return K;
}

double EuOptPut::CostOfCarry() const {
	return b;
}

/*Implementation of member functions to set the data*/
void EuOptPut::maturity(double new_T) {
	T = new_T;
}
void EuOptPut::sigma(double new_sig) {
	sig = new_sig;
}
void EuOptPut::rate(double new_rf) {
	rf = new_rf;
}
void EuOptPut::strike(double new_K) {
	K = new_K;
}
void EuOptPut::CostOfCarry(double new_b) {
	b = new_b;
}

/*Pricer and sensitivities functions implementation*/
double EuOptPut::Price(double S) const {
	double denominator = sig * sqrt(T);
	double d1 = (log(S / K) + (b + (sig*sig)*0.5) * T) / denominator;
	double d2 = d1 - denominator;

	return (K * exp(-rf * T)* N(-d2)) - (S * exp((b - rf)*T) * N(-d1));
}

/*double EuOptPut::Price(double S, OptionData& data) {
	double denominator = data.sig * sqrt(data.T);
	double d1 = (log(S / data.K) + (data.b + (data.sig * data.sig) * 0.5) * data.T) * denominator;
	double d2 = d1 - denominator;

	return (data.K * exp(-data.rf * data.T) * N(-d2)) - (S * exp((data.b - data.rf) * data.T) * N(-d1));
}*/

double EuOptPut::PutCallParity(double P, double S) const {
	double C; //Compute call price using the put pricer function
	C = P + S - K * exp(-rf * T);
	return C;
}

double EuOptPut::PutCallParity(double S) const {
	double P; //compute put price using put call parity equation
	double denominator = sig * sqrt(T);
	double d1 = (log(S / K) + (b + (sig*sig)*0.5) * T) / denominator;
	double d2 = d1 - denominator;

	double C = (S * exp((b - rf)*T) * N(d1)) - (K * exp(-rf * T)* N(d2));

	return P = C + K * exp(-rf * T) - S;
}

std::vector<double> EuOptPut::PriceRange(int num, double start_S, double end_S)
{ //num equals the number of increments before reaching the end price end_S
	std::vector<double> vec;
	vec.resize(num+1); //allocates space
	double mesh_size = (end_S - start_S) / num; //increment size h
	for (int i = 0; i <= num; i++) {//using an iterator is also possible
		vec[i] = this->Price(start_S + i*mesh_size); //mesh of spots from start_S to end_S separated by h = mesh_size: [start_s, start_s + h, ... , end_S]
		cout << "Underlying S @t0 equals: " << start_S + i*mesh_size << endl;
	}
	return vec;
}

std::vector<double> EuOptPut::PriceRange(int num, double S, double start, double end, int param) {
	std::vector<double> vec;
	vec.resize(num + 1); //allocates space
	double mesh_size = (end - start) / num; //increment size h
	if (param == 1) { //1 for a mesh of prices with maturity incrementals
		double org_T = this->maturity(); //set the original object maturity at the end of the vector computation
		for (int i = 0; i <= num; i++) {
			this->maturity(start + i*mesh_size);
			cout << "T @ " << i << " : " << this->maturity() << endl;
			vec[i] = this->Price(S);
		}
		this->maturity(org_T);
	}
	else if (param == 2) { //2 for a mesh of prices with maturity incrementals
		double org_sig = this->sigma(); //set the original object sigma at the end of the vector computation
		for (int i = 0; i <= num; i++) {
			this->sigma(start + i*mesh_size);
			cout << "sig @ " << i << " : " << this->sigma() << endl;
			vec[i] = this->Price(S);
		}
		this->sigma(org_sig);
	}
	else {
		cout << "Invalid input.\n1. For Maturity incrementals\n2. For volatility incrementals" << endl;
	}
	return vec;
}

//Greeks initialization
double EuOptPut::Delta(double S) const {
	//exp((b - rf)*T) * (N(d1) - 1.0) -- f'(P) with respect to S
	double denominator = sig * sqrt(T);
	double d1 = (log(S / K) + (b + (sig*sig)*0.5) * T) / denominator;

	return exp((b - rf)*T) * (N(d1) - 1.0);
}

double EuOptPut::Gamma(double S) const {
	//exp((b-rf)*T)*(n(d1)/(S*sig*sqrt(T)) -- f''(P) with respect to S
	double denominator = sig * sqrt(T);
	double d1 = (log(S / K) + (b + (sig*sig)*0.5) * T) / denominator;

	return exp((b - rf)*T)*(n(d1) / (S*sig*sqrt(T)));
}

double EuOptPut::Vega(double S) const {
	//K*exp(-rf*T)*n(d2)*sqrt(T) -- f'(P) with respect to sigma
	double denominator = sig * sqrt(T);
	double d1 = (log(S / K) + (b + (sig*sig)*0.5) * T) / denominator;
	double d2 = d1 - denominator;

	return K*exp(-rf*T)*n(d2)*sqrt(T);
}

double EuOptPut::Theta(double S) const {
	//-exp((b-rf)*T) * ((S*n(di)*sig)/(2*sqrt(T))) + rf*K*exp(-rf*T)*N(-d2)-(rf-b)*S*exp((b-rf)*T)*N(-d1) -- -f'(P) with respect to T
	double denominator = sig * sqrt(T);
	double d1 = (log(S / K) + (b + (sig*sig)*0.5) * T) / denominator;
	double d2 = d1 - denominator;

	return -exp((b - rf)*T) * ((S*n(d1)*sig) / (2.0 * sqrt(T))) + rf*K*exp(-rf*T)*N(-d2) - (rf - b)*S*exp((b - rf)*T)*N(-d1);
}

std::vector<double> EuOptPut::GreeksRange(int num, double start_S, double end_S, int param) {
	//num equals the number of increments before reaching the end price end_S
	std::vector<double> vec;
	vec.resize(num + 1); //allocates space
	double mesh_size = (end_S - start_S) / num; //increment size h
	if (param == 1) { //1 for a mesh of deltas
		for (int i = 0; i <= num; i++) {//using an iterator is also possible
			vec[i] = this->Delta(start_S + i*mesh_size); //mesh of deltas from start_S to end_S separated by h = mesh_size: [start_s, start_s + h, ... , end_S]
			cout << "Underlying S @t0 equals: " << start_S + i*mesh_size << endl;
		}
	}
	else if (param == 2) { //2 for a mesh of gammas
		for (int i = 0; i <= num; i++) {//using an iterator is also possible
			vec[i] = this->Gamma(start_S + i*mesh_size); //mesh of gammas from start_S to end_S separated by h = mesh_size: [start_s, start_s + h, ... , end_S]
			cout << "Underlying S @t0 equals: " << start_S + i*mesh_size << endl;
		}
	}
	else if (param == 3) { //3 for a mesh of vegas
		for (int i = 0; i <= num; i++) {//using an iterator is also possible
			vec[i] = this->Vega(start_S + i*mesh_size); //mesh of vegas from start_S to end_S separated by h = mesh_size: [start_s, start_s + h, ... , end_S]
			cout << "Underlying S @t0 equals: " << start_S + i*mesh_size << endl;
		}
	}
	else if (param == 4) { //4 for a mesh of thetas
		for (int i = 0; i <= num; i++) {//using an iterator is also possible
			vec[i] = this->Theta(start_S + i*mesh_size); //mesh of thetas from start_S to end_S separated by h = mesh_size: [start_s, start_s + h, ... , end_S]
			cout << "Underlying S @t0 equals: " << start_S + i*mesh_size << endl;
		}
	}
	else {
		cout << "Invalid input.\n1. For a mesh of Deltas\n2. For a mesh of Gammas\n3. For a mesh of Vegas\n4. For a mesh of Thetas" << endl;
	}
	return vec;
}

//We now use divided differences to approximate option sensitivities.
//In general, we can approximate first and second - order derivatives in S by 3-point second order approximations
double EuOptPut::DeltaDDM(double S, double h) const {
	//(V(S+h) - V(S-h))/2h where V is the value of the option (i.e put value in this case) and h is the increment
	return (Price(S + h) - Price(S - h)) / (2.0 * h);
}

double EuOptPut::GammaDDM(double S, double h) const {
	//(V(S+h) - 2V(S) + V(S-h))/h^2 where V is the value of the option
	return (Price(S + h) - 2 * Price(S) + Price(S - h)) / (h*h);
}

std::vector<double> EuOptPut::GreeksRangeDDM(int num, double h, double start_S, double end_S, int param) {
	//num equals the number of increments before reaching the end price end_S
	std::vector<double> vec;
	vec.resize(num + 1); //allocates space
	double mesh_size = (end_S - start_S) / num; //increment size h
	if (param == 1) { //1 for a mesh of deltas
		for (int i = 0; i <= num; i++) {//using an iterator is also possible
			vec[i] = this->DeltaDDM(start_S + i*mesh_size, h); //mesh of deltas from start_S to end_S separated by mesh_size: [start_s, start_s + h, ... , end_S]
			cout << "Underlying S @t0 equals: " << start_S + i*mesh_size << endl;
		} //h in this case is the approximation of the DDM
	}
	else if (param == 2) { //2 for a mesh of gammas
		for (int i = 0; i <= num; i++) {//using an iterator is also possible
			vec[i] = this->GammaDDM(start_S + i*mesh_size, h); //mesh of gammas from start_S to end_S separated by mesh_size: [start_s, start_s + h, ... , end_S]
			cout << "Underlying S @t0 equals: " << start_S + i*mesh_size << endl;
		} //h in this case is the approximation of the DDM
	}
	else {
		cout << "Invalid input.\n1. For a mesh of Deltas\n2. For a mesh of Gammas" << endl;
	}
	return vec;
}

/*Print function implementation*/
std::string EuOptPut::ToString() const {
	std::string s = EuOpt::ToString();
	std::stringstream ss;
	ss << s << "\n********** PUT OPTION PARAMETERS **********\n" << "T: " << T << "\nK: " << K << "\nrf: " << rf << "\nsig: " << sig << "\nb: " << b << endl;
	return ss.str();
}
