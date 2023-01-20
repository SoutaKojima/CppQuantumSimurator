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

		for (int i = 0; i < epoc; ++i) {
			for (vector<vector<double>>::iterator itr = data.begin(); itr != data.end(); ++itr) {
				U_in(*itr);
			}

			for (vector<vector<double>>::iterator itr = thetas.begin(); itr != thetas.end(); ++itr) {
				U_ent();
				U_loc(*itr);
			}
			Loss();
		}

		return;
	}
	//ref:https://arxiv.org/ftp/arxiv/papers/1910/1910.14266.pdf

	void MachineLearningXRegression() {

	}
	//ref:https://arxiv.org/ftp/arxiv/papers/1910/1910.14266.pdf
	//ref:https://qiita.com/Ugo-Nama/items/04814a13c9ea84978a4c
	//ref:https://arxiv.org/pdf/1804.11326.pdf
	//ref:http://www.cs.utoronto.ca/~hinton/absps/naturebp.pdf
	//ref:https://qiita.com/tky823/items/c2c69a5f69d9cf8ca751

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

	void QuantumMachineLearning::Loss() {
		vector<int> v = qc.Detection();
		for (int i = 2; i < qc.GetSize(); ++i) {
			if (i & 1) {
				v[1] += v[i];
			}
			else {
				v[0] += v[i];
			}
		}

		double p0 = (double)v[0] / (double)v[qc.GetSize()];
		double p1 = (double)v[1] / (double)v[qc.GetSize()];
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