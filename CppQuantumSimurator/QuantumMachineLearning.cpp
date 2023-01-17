#include "QuantumMachineLearning.h"

namespace std {
	void QuantumMachineLearning::MachineLearningXOR() {
		/*for (int i = 0; i < 4; ++i) {
			int a = (i & (1));
			int b = (i & (1 << 1));
			int c = a ^ b;
			train.push_back(make_pair(make_pair(a, b), c));
		}*/

		//qc.Init(2);


		thetas.clear();

		vector<double> train(qc.GetSize() * 2, 0);
		//vector<vector<double>> data;

		train = { 0,0,1,0 };
		qml.data.push_back(train);
		train = { 0,1,0,1 };
		qml.data.push_back(train);
		train = { 1,0,0,1 };
		qml.data.push_back(train);
		train = { 1,1,1,0 };
		qml.data.push_back(train);

		//U_Reset();
		for (vector<vector<double>>::iterator itr = data.begin(); itr != data.end(); ++itr) {
			U_in(*itr);
		}

		/*for (int i = 0; i < 5; ++i) {
			cout << "theta" << i << ":" << thetas[i] << endl;
		}*/
		//cout << endl;

		Loss();
		return;
	}
	//ref:https://qiita.com/doiken_/items/1d66fe4d10805532d6a5

	void QuantumMachineLearning::U_in(vector<double> v) {
		for (int i = 0; i < qc.GetSize(); ++i) {
			qc.Ry(i, asin(v[i]));
			qc.Rz(i, acos(v[i] * v[i]));
		}
	}

	void QuantumMachineLearning::U_ent() {
		for (int i = 0; i < qc.GetSize(); ++i) {
			qc.CZ(i, (i + 1) % qc.GetSize());
		}

	}

	void QuantumMachineLearning::Theta_Reset() {
		random_device rd;
		default_random_engine eng(rd());
		uniform_real_distribution<double> distr(0, 1);
		double r;

		thetas.clear();
		for (int i = 0; i < rep; ++i) {
			vector<double> tmp;
			for (int j = 0; j < qc.GetSize(); ++j) {
				r = 2 * _Pi * distr(eng);
				tmp.push_back(r);
			}
			thetas.push_back(tmp);
		}
	}

	void QuantumMachineLearning::U_loc() {

	}
	
	/*void QuantumMachineLearning::U_Set() {
		random_device rd;
		default_random_engine eng(rd());
		uniform_real_distribution<double> distr(0, 1);

		qc.Ry(0, thetas[0]);
		qc.Ry(1, thetas[1]);

		qc.CX(0, 1);
		qc.Rz(1, thetas[2]);
		qc.CX(0, 1);

		qc.Ry(0, thetas[3]);
		qc.Ry(1, thetas[4]);
	}*/

	void QuantumMachineLearning::Loss() {
		qc.Amplitude();

		//for (vector < pair<pair<int, int>, int>>::iterator itr = train.begin(); itr != train.end(); ++itr) {
		//	//qc.Init(2);
		//	U_in(itr->first);
		//	U_Set();
		//	vector<int> v = qc.Detection((int)1e4);
		//	double mean = 0;
		//	for (vector<int>::iterator it = v.begin(); it != v.end(); ++it) {
		//		mean += (double)distance(v.begin(), it) * (double)(*it);
		//	}
		//	mean /= v.size();
		//	cout << "v.size: " << v.size() << endl;
		//	cout << "  mean: " << mean << endl;
		//}
		

	}
}