//OptionPricer_Main.cpp
//Testing the following batches:
//Batch 1: T = 0.25, K = 65, sig = 0.30, r = 0.08, S = 60 (then C = 2.13293, P = 5.84584).
//Batch 2 : T = 1.0, K = 100, sig = 0.2, r = 0.0, S = 100 (then C = 7.96632, P = 7.96632).
//Batch 3 : T = 1.0, K = 10, sig = 0.50, r = 0.12, S = 5 (C = 0.204121, P = 4.0733).
//Batch 4 : T = 30.0, K = 100.0, sig = 0.30, r = 0.08, S = 100.0 (C = 92.1749, P = 1.24651).

#include "EUOptionCall.hpp"
#include "EUOptionPut.hpp"
#include "Batch1.hpp"
#include "Batch2.hpp"
#include "Batch3.hpp"
#include "Batch4.hpp"
#define NL cout << endl;

int main() {
	
	int batch_number;
	cout << "Please, input the number of batch you would like to test...\n> ";
	cin >> batch_number;
	NL;
	switch (batch_number) {
	case 1: 
		Batch1();
		break;
	case 2:
		Batch2();
		break;
	case 3:
		Batch3();
		break;
	case 4:
		Batch4();
		break;
	default:
		cout << "Invalid input. Enter an integer 1 through 4..." << endl;
	}

	//S = 105, T = 0.5, r = 0.1, b = 0 and sig = 0.36 (exact delta call = 0.5946, delta put = -0.3566).
	NL;
	cout << "Computing sensitivities for an option with the following parameters..." << endl;
	double S = 105;
	OptionData greeks_batch{ 0.1, 0.36, 100, 0.5, 0 };
	EuOptPut GreeksPut(greeks_batch);
	/*Retrieving parameters of OptionData. We could also use the getters functions on GreeksPut object*/
	cout << "Strike price: " << greeks_batch.K << endl;
	cout << "Maturity: " << greeks_batch.T << endl;
	cout << "Volatility: " << greeks_batch.sig << endl;
	cout << "Rate: " << greeks_batch.rf << endl;
	cout << "Cost of carry: " << greeks_batch.b << endl;
	NL;
	cout << "The Delta of the put option is: " << GreeksPut.Delta(S) << endl;
	cout << "The Delta of the put option using the Divided Differences Method: " << GreeksPut.DeltaDDM(S, 5) << endl; //h=5, if we decrease it the value will converge at -0.3566...
	cout << "The Gamma of the put option is: " << GreeksPut.Gamma(S) << endl;
	cout << "The Gamma of the put option using the Divided Differences Mehtod: " << GreeksPut.GammaDDM(S, 5) << endl; //h=5, if we decrease it the value will converge at 0.01349...
	cout << "The Vega of the put option is: " << GreeksPut.Vega(S) << endl;
	cout << "The Theta of the put option is: " << GreeksPut.Theta(S) << endl;
	NL;
	double incr = 5;
	double end_S = 120;
	NL;
	cout << "Computing a mesh of put deltas as a f(S)..." << endl;
	std::vector<double> mesh_put = GreeksPut.GreeksRange(incr, S, end_S, 1);
	for (int i = 0; i <= 5; i++) {
		cout << "Put delta @t" << i << ": " << mesh_put[i] << endl;
	}
	NL;
	EuOptCall GreeksCall(greeks_batch);
	cout << "The Delta of the call option is: " << GreeksCall.Delta(S) << endl;
	cout << "The Delta of the call option using the Divided Differences Method: " << GreeksCall.DeltaDDM(S, 5) << endl; //h=5, if we decrease it the value will converge at 0.5946
	cout << "The Gamma of the call option is: " << GreeksCall.Gamma(S) << endl;
	cout << "The Gamma of the call option using the Divided Differences Mehtod: " << GreeksCall.GammaDDM(S, 5) << endl; //h=5, if we decrease it the value will converge at 0.01349...
	cout << "The Vega of the call option is: " << GreeksCall.Vega(S) << endl;
	cout << "The Theta of the call option is: " << GreeksCall.Theta(S) << endl;
	NL;
	cout << "Computing a mesh of call deltas as a f(S)..." << endl;
	std::vector<double> mesh_call = GreeksCall.GreeksRange(incr, S, end_S, 1);
	for (int i = 0; i <= 5; i++) {
		cout << "Call delta @t" << i << ": " << mesh_call[i] << endl;
	}

	return 0;
}
