//OptionData.hpp
//This header file contains the structure definition for options parameters

#ifdef __cplusplus
extern "C" { // Declare as extern "C" if used from C++
#endif

	typedef struct __OptionData {
		double rf; //risk-free interest rate
		double sig; //volatility
		double K; //strike price
		double b; //cost of carry that will equal rf for stock options
	} OptionData;

#ifdef __cplusplus
}
#endif

