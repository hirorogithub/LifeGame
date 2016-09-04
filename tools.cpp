#include "tools.h"
bool ran_tf(double rate){
	//srand((int)time(0));
	if (rate>rand() / (double)(RAND_MAX))
		return true;
	else
		return false;
}

int ran_f_t(int from, int to){

	//srand((int)time(0));
	return from!=to?rand() % (to - from) + from:0;
}

double dran_f_t(double from, double to){
	//srand((int)time(0));
	return from!=to?(rand() / (double)(RAND_MAX))*(to - from) + from:0;

}
