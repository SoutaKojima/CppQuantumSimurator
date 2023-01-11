#include "QuantumMachineLearning.h"

namespace std {
	void QuantumMachineLearning::MachineLearningXOR() {

		vector < pair<pair<int, int>, int>> train;
		for (int i = 0; i < 4; ++i) {
			int a = (i & (1));
			int b = (i & (1 << 1));
			int c = a ^ b;
			train.push_back(make_pair(make_pair(a, b), c));
		}

		qc.Init(2);
		//double angle = 0;


		thetas.clear();
		//U_in(_Pi);
		U_Set();

		for (int i = 0; i < 5; ++i) {
			cout << "theta" << i << ":" << thetas[i] << endl;
		}
		cout << endl;

		qc.Amplitude();
		qc.Detection((int)1e4);
		return;
	}
	//ref:https://qiita.com/doiken_/items/1d66fe4d10805532d6a5

	void QuantumMachineLearning::U_in(pair<int, int> p) {
		qc.Ry(0, asin(p.first));
		qc.Ry(1, asin(p.second));
	}

	void QuantumMachineLearning::U_Set() {
		random_device rd;
		default_random_engine eng(rd());
		uniform_real_distribution<double> distr(0, 1);
		double r;

		r = 2 * _Pi * distr(eng);
		thetas.push_back(r);
		qc.Ry(0, r);
		r = 2 * _Pi * distr(eng);
		thetas.push_back(r);
		qc.Ry(1, r);

		qc.CX(0, 1);
		r = (-1) * 2 * _Pi * distr(eng);
		thetas.push_back(r);
		qc.Rz(1, r);
		qc.CX(0, 1);

		r = 2 * _Pi * distr(eng);
		thetas.push_back(r);
		qc.Ry(0, r);
		r = 2 * _Pi * distr(eng);
		thetas.push_back(r);
		qc.Ry(1, r);


	}

	void QuantumMachineLearning::cost() {

	}
}