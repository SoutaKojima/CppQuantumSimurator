#include "QuantumMachineLearning.h"

namespace std {
	void QuantumMachineLearning::MachineLearningXOR() {
		vector<double> train(qc.GetSize() * 2, 0);

		train = { 0,0,1,0 };
		data.push_back(train);
		train = { 0,1,0,1 };
		data.push_back(train);
		train = { 1,0,0,1 };
		data.push_back(train);
		train = { 1,1,1,0 };
		data.push_back(train);

		Theta_Reset();

		for (vector<vector<double>>::iterator itr = data.begin(); itr != data.end(); ++itr) {
			U_in(*itr);
		}

		for (vector<vector<double>>::iterator itr = thetas.begin(); itr != thetas.end(); ++itr) {
			U_ent();
			U_loc(*itr);
		}

		Loss();
		return;
	}
	//ref:https://arxiv.org/ftp/arxiv/papers/1910/1910.14266.pdf

	void MachineLearningXRegression() {

	}
	//ref:https://arxiv.org/ftp/arxiv/papers/1910/1910.14266.pdf
	//ref:https://qiita.com/Ugo-Nama/items/04814a13c9ea84978a4c
	//ref:https://arxiv.org/pdf/1804.11326.pdf
	//ref:http://www.cs.utoronto.ca/~hinton/absps/naturebp.pdf

	void QuantumMachineLearning::U_in(vector<double> v) {
		for (int i = 0; i < qc.GetSize(); ++i) {
			qc.Rz(i, acos(v[i] * v[i]));
			qc.Ry(i, asin(v[i]));
		}
	}

	void QuantumMachineLearning::U_ent() {
		for (int i = 0; i < qc.GetSize(); ++i) {
			qc.CZ(i, (i + 1) % qc.GetSize());
		}

	}


	void QuantumMachineLearning::U_loc(vector<double> v) {
		for (int i = 0; i < qc.GetSize(); ++i) {
			qc.Rz(i, acos(v[i] * v[i]));
			qc.Ry(i, asin(v[i]));
		}
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
}