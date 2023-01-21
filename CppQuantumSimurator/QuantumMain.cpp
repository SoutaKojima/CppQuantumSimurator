#include"QuantumMachineLearning.h"
#include<fstream>
using namespace std;

int main()
{
	ofstream text_data;
	text_data.open("data/sin_curve.dat");

	random_device rd;
	default_random_engine eng(rd());
	uniform_real_distribution<double> distr(0, 1);

	for (int i = 0; i < 100; ++i) {
		double x = distr(eng) * 2 - 1;
		text_data << x << ' ';
		double noise = (distr(eng) * 2 - 1) * 0.05;
		double f_x = sin(x*_Pi) + noise;
		text_data << f_x << endl;
	}

	return 0;
}
