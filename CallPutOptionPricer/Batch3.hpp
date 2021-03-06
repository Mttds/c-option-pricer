//Batch3.hpp
//Batch 3 : T = 1.0, K = 10, sig = 0.50, r = 0.12, S = 5 (C = 0.204121, P = 4.0733).

#ifndef BATCH3_HPP
#define BATCH3_HPP

#include "EUOptionCall.hpp"
#include "EUOptionPut.hpp"
#define NL cout << endl;

void Batch3() {
	cout << "***************** BATCH 2 ******************" << endl;
	EuOptCall batch_call(0.12, 0.50, 10, 1.0, 0.12); //rf, sig, K, T, b
	double S = 5;
	cout << batch_call.Print() << endl;
	cout << "The value of the call option is: " << batch_call.Price(S) << endl;
	cout << "The put price calculated using the call price with the put-call parity is: " << batch_call.PutCallParity(batch_call.Price(S), S) << endl;
	cout << "The value of the call given by the put-call parity equation is: " << batch_call.PutCallParity(S) << endl;
	OptionData batch_data{ 0.12, 0.50, 10, 1.0, 0.12 }; //rf, sig, K, T, b
	EuOptPut batch_put(batch_data);
	cout << batch_put.Print() << endl;
	cout << "The value of the put option is: " << batch_put.Price(S) << endl;
	/*EuOptCall batch1_call(batch1_data);
	cout << batch1_call.Price(S1) << endl;*/
	NL;
	cout << "Computing range of put values at different underlying prices" << endl;
	NL;
	int increments1 = 4; //(45-5)/4. Every increment h is equal to 10
	double end_S = 45;
	std::vector<double> mesh = batch_put.PriceRange(increments1, S, end_S);
	for (int i = 0; i <= increments1; i++) {
		cout << "The put value @t" << i << ": " << mesh[i] << endl;
	}
	NL;
	cout << "Computing range of call values at different underlying prices" << endl;
	NL;
	mesh = batch_call.PriceRange(increments1, S, end_S); //assign mesh to the call batch now
	for (int i = 0; i <= increments1; i++) {
		cout << "The call value @t" << i << ": " << mesh[i] << endl;
	}
	NL;
	cout << "Computing range of put values at different maturities T" << endl;
	NL;
	int increments2 = 5; //(2.0-1.0)/5. Every increment h is equal to .20
	std::vector<double> mesh2 = batch_put.PriceRange(increments2, S, batch_put.maturity(), 2.0, 1);
	for (int i = 0; i <= increments2; i++) {
		cout << "The put value @t" << i << ": " << mesh2[i] << endl;
	}
	NL;
	cout << "Computing range of put values with different volatilities (sigma)" << endl;
	NL;
	std::vector<double> mesh3 = batch_put.PriceRange(increments2, S, batch_put.sigma(), 1.00, 2);
	for (int i = 0; i <= increments2; i++) {
		cout << "The put value @t" << i << ": " << mesh3[i] << endl;
	}
	NL;
	cout << "Computing range of call values at different maturities T" << endl;
	std::vector<double> mesh4 = batch_call.PriceRange(increments2, S, batch_call.maturity(), 2.0, 1);
	for (int i = 0; i <= increments2; i++) {
		cout << "The call value @t" << i << ": " << mesh4[i] << endl;
	}
	NL;
	cout << "Computing range of call values with different volatilities (sigma)" << endl;
	std::vector<double> mesh5 = batch_call.PriceRange(increments2, S, batch_call.sigma(), 1.00, 2);
	for (int i = 0; i <= increments2; i++) {
		cout << "The call value @t" << i << ": " << mesh5[i] << endl;
	}
}

#endif
