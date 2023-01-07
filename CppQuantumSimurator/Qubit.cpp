#include "Qubit.h"


namespace std
{
	Qubit Qubit::Init() {
		Qubit q;
		complex c;
		q.ket[0] = c.set(1, 0);
		q.ket[1] = c.set(0, 0);
		ket[0] = q.ket[0];
		ket[1] = q.ket[1];
		return q;
	}

	void Qubit::Show() {
		cout << "ket[0] re:" << ket[0].re << " ";
		cout << "ket[0] im:" << ket[0].im << endl;
		cout << "ket[1] re:" << ket[1].re << " ";
		cout << "ket[1] im:" << ket[1].im << endl;
		cout << endl;
	}

	void Qubit::Detection(int n) {
		double zero_prob = ket[0].norm();
		int count[] = { 0,0 };
		random_device rd;
		default_random_engine eng(rd());
		uniform_real_distribution<double> distr(0, 1);

		for (int i = 0; i < n; ++i) {
			double r = distr(eng);
			//cout << (zero_prob > r ? 0 : 1);
			++count[(zero_prob > r ? 0 : 1)];
			//if (i % 10 == 9) cout << endl;
		}
		//cout << endl;
		cout << "zero:" << count[0] << endl;
		cout << " one:" << count[1] << endl;
		cout << endl;
	}

	void Qubit::H() {
		Qubit tmp = tmp.Init();
		tmp.ket[0] = (ket[0] + ket[1]) / sqrt(2);
		tmp.ket[1] = (ket[0] - ket[1]) / sqrt(2);
		ket[0] = tmp.ket[0];
		ket[1] = tmp.ket[1];
	}

	void Qubit::X() {
		Qubit tmp = tmp.Init();
		tmp.ket[0] = ket[1];
		tmp.ket[1] = ket[0];
		ket[0] = tmp.ket[0];
		ket[1] = tmp.ket[1];
	}
}