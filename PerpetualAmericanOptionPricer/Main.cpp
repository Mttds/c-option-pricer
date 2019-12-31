//Main.cpp
//Testing the following batches:
//K = 100, sig = 0.1, r = 0.1, b = 0.02, S = 110 (C = 18.5035, P = 3.03106).

#include "AmericanOptionCall.hpp"
#include "AmericanOptionPut.hpp"
#define NL cout << endl

int main() {

	double S1 = 110;
	OptionData batch1{ 0.1, 0.1, 100, 0.02 };
	UsOptCall batch1_call(batch1);
	cout << batch1_call.Print() << endl;
	cout << "The call value of the option is: " << batch1_call.Price(S1) << endl;
	UsOptPut batch1_put(batch1);
	cout << batch1_put.Print() << endl;
	cout << "The put value of the option is: " << batch1_put.Price(S1) << endl;
	NL;
	cout << "Incrementing the Underlying price, all else equal, gives us the following call values: " << endl;
	NL;
	double increments = 5;
	double end_S1 = 135;
	std::vector<double> mesh_call = batch1_call.PriceRange(increments,S1, end_S1);
	for (int i = 0; i <= increments; i++) {
		cout << "Value @t" << i << ": " << mesh_call[i] << endl;
	}
	NL;
	cout << "Incrementing the Underlying price, all else equal, gives us the following put values: " << endl;
	NL;
	std::vector<double> mesh_put = batch1_put.PriceRange(increments, S1, end_S1);
	for (int i = 0; i <= increments; i++) {
		cout << "Value @t" << i << ": " << mesh_put[i] << endl;

	}

	return 0;
}