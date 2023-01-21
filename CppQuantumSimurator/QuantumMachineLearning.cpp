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
				for (vector<vector<double>>::iterator it = thetas.begin(); it != thetas.end(); ++it) {
					U_ent();
					U_loc(*it);
				}
				//Loss();
			}


		}

		return;
	}
	//ref:https://arxiv.org/ftp/arxiv/papers/1910/1910.14266.pdf

	void QuantumMachineLearning::MachineLearningRegression() {
		vector<double> train;

		ifstream ifs("data/sin_curve.dat");

		double d;
		while (ifs) {
			ifs >> d;
			train.push_back(d);
			if (train.size() == 2) {
				data.push_back(train);
				train.clear();
			}
		}
		cout << "data size:" << data.size() << endl;

		Theta_Reset();
		cout << "reset complete" << endl;
		ShowRegression(0);

		for (int i = 0; i < epoc; ++i) {
			for (vector<vector<double>>::iterator itr = data.begin(); itr != data.end(); ++itr) {
				U_in(*itr);
				for (vector<vector<double>>::iterator it = thetas.begin(); it != thetas.end(); ++it) {
					U_ent();
					U_loc(*it);
				}
				Loss(*itr);
			}
			cout << "epoc:" << i << endl;
		}
		ShowRegression(1);

		return;

	}
	//ref:https://arxiv.org/ftp/arxiv/papers/1910/1910.14266.pdf
	//ref:https://qiita.com/Ugo-Nama/items/04814a13c9ea84978a4c
	//ref:https://arxiv.org/pdf/1804.11326.pdf
	//ref:http://www.cs.utoronto.ca/~hinton/absps/naturebp.pdf
	//ref:https://qiita.com/tky823/items/c2c69a5f69d9cf8ca751

	void QuantumMachineLearning::U_in(vector<double> v) {
		for (int i = 0; i < qc.GetSize(); ++i) {
			qc.Rz(i, acos(v[0] * v[0]));
			qc.Ry(i, asin(v[0]));
		}
	}

	void QuantumMachineLearning::U_ent() {
		for (int i = 0; i < qc.GetSize(); ++i) {
			qc.CZ(i, (i + 1) % qc.GetSize());
		}

	}


	void QuantumMachineLearning::U_loc(vector<double> v) {
		for (int i = 0; i < qc.GetSize(); ++i) {
			qc.Rz(i, v[i] * v[i]);
			qc.Ry(i, v[i]);
		}
	}

	void QuantumMachineLearning::Loss(vector<double> d) {
		vector<int> v = qc.Detection();

		for (vector<int>::iterator itr = v.begin() + 2; itr != v.end() - 1; ++itr) {
			if ((itr - v.begin()) % 2 == 1) {
				v[1] += *itr;
			}
			else {
				v[0] += *itr;
			}
		}
		double p0 = (double)v[0] / (double)(*(v.end() - 1));
		double p1 = (double)v[1] / (double)(*(v.end() - 1));
		//cout << v[0] << ' ' << v[1] << ' ' << (*(v.end() - 1)) << endl;
		double z = p0 - p1;

		double eta = 0.01; //learning rate

		for (vector<vector<double>>::iterator itr = thetas.begin(); itr != thetas.end(); ++itr) {
			for (vector<double>::iterator it = (*itr).begin(); it != (*itr).end(); ++it) {
				*it = (*it)  - (2 * z - d[1]);
			}
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

	void QuantumMachineLearning::ShowRegression(int s) {
		ofstream text_data;
		text_data.open("data/ShowRegression" + to_string(s) + ".dat");

		for (double d = -1; d <= 1; d += 0.01) {
			qc.Init();
			for (int i = 0; i < qc.GetSize(); ++i) {
				qc.Rz(i, acos(d * d));
				qc.Ry(i, asin(d));
			}
			for (vector<vector<double>>::iterator itr = thetas.begin(); itr != thetas.end(); ++itr) {
				U_ent();
				U_loc(*itr);
			}
			vector<int> v = qc.Detection();

			for (vector<int>::iterator itr = v.begin() + 2; itr != v.end() - 1; ++itr) {
				if ((itr - v.begin()) % 2 == 1) {
					v[1] += *itr;
				}
				else {
					v[0] += *itr;
				}
			}
			double p0 = (double)v[0] / (double)(*(v.end() - 1));
			double p1 = (double)v[1] / (double)(*(v.end() - 1));
			//cout << v[0] << ' ' << v[1] << ' ' << (*(v.end() - 1)) << endl;
			double z = p0 - p1;
			text_data << d << ' ' << z << endl;
		}
	}

	void QuantumMachineLearning::ShowThetas() {
		ofstream text_data;
		text_data.open("data/tehtas.csv");
		for (vector<vector<double>>::iterator itr = thetas.begin(); itr != thetas.end(); ++itr) {
			//U_ent();
			for (vector<double>::iterator it = (*itr).begin(); it != (*itr).end(); ++it) {
				if (it != (*itr).end() - 1) {
					text_data << *it << ",";
				}
				else {
					text_data << *it << endl;
				}

			}
		}
	}

	void QuantumMachineLearning::Data_Generating() {
		ofstream text_data;
		text_data.open("data/sin_curve.dat");

		random_device rd;
		default_random_engine eng(rd());
		uniform_real_distribution<double> distr(0, 1);

		for (int i = 0; i < 100; ++i) {
			double x = distr(eng) * 2 - 1;
			text_data << x << ' ';
			double noise = (distr(eng) * 2 - 1) * 0.05;
			double f_x = sin(x * _Pi) + noise;
			text_data << f_x << endl;
		}

	}
}