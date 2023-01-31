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

		cout << "checkpoint a." << endl;

		for (int i = 0; i < epoc; ++i) {
			for (vector<vector<double>>::iterator itr = data.begin(); itr != data.end(); ++itr) {
				U_in(*itr);
				//U_ent();
				for (vector<vector<double>>::iterator it = thetas.begin(); it != thetas.end(); ++it) {

					U_loc(*it);
					U_ent();
				}
				Loss(*itr);
			}
			cout << "epoc:" << i << endl;
		}



		cout << "checkpoint b." << endl;

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
			qc.Ry(i, acos(v[0] * v[0]));
			qc.Rz(i, asin(v[0]));
		}
	}

	void QuantumMachineLearning::U_ent() {
		for (int i = 0; i < qc.GetSize(); ++i) {
			qc.CZ(i, (i + 1) % qc.GetSize());
		}

	}


	void QuantumMachineLearning::U_loc(vector<double> v) {
		for (int i = 0; i < qc.GetSize(); ++i) {
			qc.Ry(i, v[i] * v[i]);
			qc.Rz(i, v[i]);
		}
	}

	void QuantumMachineLearning::Loss(vector<double> d) {
		map<int, int> v = qc.Detection();

		for (map<int, int>::iterator itr = v.begin(); itr != v.end(); ++itr) {
			if ((itr->first) < 2) continue;
			if ((itr->first) % 2 == 1) {
				v[1] += itr->second;
			}
			else {
				v[0] += itr->second;
			}
		}
		double p0 = (double)v[0] / (double)v[-1];
		double p1 = (double)v[1] / (double)v[-1];
		cout << v[0] << ' ' << v[1] << ' ' << v[-1] << endl;
		double z = p0 - p1;

		double eta = 0.05; //learning rate

		double loss = (2 * z - d[1]) * (2 * z - d[1]) / 2;
		//cout << "Loss:" << loss << endl;


		vector<double> v_pre;
		for (vector < vector<double>>::iterator itr = thetas.end() - 1;; --itr) {
			for (vector<double>::iterator it = (*itr).begin(); it != (*itr).end(); ++it) {
				double tmp = (*it);
				*it = tmp - eta * tmp * (2 * z - p1);
				//v_pre.push_back(2 * z - d[1]);
			}

			if (itr == thetas.end() - 1) {
				vector<double>::iterator it = (*itr).begin();
				double tmp = (*it);
				double grad = tmp * (2 * z - p1);

				*it = tmp - eta * tmp * (2 * z - p1);
				v_pre.push_back(2 * z - p1);

			}
			else {
				vector<double> v_tmp;
				for (vector<double>::iterator it = (*itr).begin(); it != (*itr).end(); ++it) {
					double tmp = (*it);
					*it = tmp - eta * tmp * v_pre[it - (*itr).begin()] * (2 * z - p1);
					v_tmp.push_back(v_pre[it - (*itr).begin()] * (2 * z - p1));
					//*it = tmp - eta * tmp * (2 * z - d[1]);
					//v_pre.push_back(2 * z - d[1]);
				}
				v_pre.clear();
				v_pre = v_tmp;
			}
			if (itr == thetas.begin()) break;
			//cout << "Loss:" << (2*z - d[1]) * (2 * z - d[1]) / 2 << endl;
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
			map<int, int> v = qc.Detection();


			//cout << "checkpoint c." << endl;

			for (map<int, int>::iterator itr = v.begin(); itr != v.end(); ++itr) {
				if ((itr->first) < 2) continue;
				if ((itr->first) % 2 == 1) {
					v[1] += itr->second;
				}
				else {
					v[0] += itr->second;
				}
			}
			double p0 = (double)v[0] / (double)v[-1];
			double p1 = (double)v[1] / (double)v[-1];
			//cout << v[0] << ' ' << v[1] << ' ' << v[-1] << endl;
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
		text_data.open("data/linear_curve.dat");

		random_device rd;
		default_random_engine eng(rd());
		uniform_real_distribution<double> distr(0, 1);

		for (int i = 0; i < 100; ++i) {
			double x = distr(eng) * 2 - 1;
			text_data << x << ' ';
			double noise = (distr(eng) * 2 - 1) * 0.05;
			double f_x = x + noise;
			text_data << f_x << endl;
		}

	}
}