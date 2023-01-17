#include "QuantumCircuit.h"

namespace std
{
	/*QuantumCircuit::QuantumCircuit()
	{
		return;
	}*/

	vector<int> QuantumCircuit::Detection(int size, int n) {
		random_device rd;
		default_random_engine eng(rd());
		uniform_real_distribution<double> distr(0, 1);

		int mask = 0;
		for (int i = 0; i < size; ++i) mask = mask | (1 << i);

		double prob = 0;
		for (map<int, complex>::iterator itr = amp.begin(); itr != amp.end(); ++itr) {
			prob += (itr->second).norm();
		}
		if (prob < 0.99) {
			cout << "Sum of Probability is " << prob << ", not 1 !" << endl;
			exit(1);
		}
		cout << "Sum of Probability : " << prob << endl;


		map<int, int> count;
		for (int i = 0; i < n; ++i) {
			double r = distr(eng);
			for (map<int, complex>::iterator itr = amp.begin(); itr != amp.end(); ++itr) {
				if (r < (itr->second).norm()) {
					//count[(itr->first)] = count[(itr->first)] + 1;
					count[(itr->first) & mask] = count[(itr->first) & mask] + 1;
					break;
				}
				r -= (itr->second).norm();
			}
		}

		vector<int> v;
		for (map<int, int>::iterator itr = count.begin(); itr != count.end(); ++itr) {
			cout << bitset<16>(itr->first) << '(' << (itr->first) << ')' << ':';
			cout << (itr->second) << endl;
			v.push_back(itr->second);
		}

		return v;
	}

	vector<int> QuantumCircuit::Detection(int size) {
		return Detection(size, 10000);
	}

	vector<int> QuantumCircuit::Detection() {
		return Detection(qc_size, 10000);
	}

	void QuantumCircuit::Amplitude() {
		double prob = 0;
		for (map<int, complex>::iterator itr = amp.begin(); itr != amp.end(); ++itr) {
			if ((itr->second).norm() != 0) {
				cout << bitset<16>(itr->first) << '(' << (itr->first) << ')' << " : Prob=";
				cout << (itr->second).norm() << " : Amp=";
				cout << (itr->second).re << " + " << (itr->second).im << "i" << endl;
				prob += (itr->second).norm();
			}
		}
		cout << "Sum of Probability : " << prob << endl;
		cout << endl;
		return;
	}

	void QuantumCircuit::Amplitude(int size) {
		double prob = 0;
		map<int, double> mp;
		int mask = 0;
		for (int i = 0; i < size; ++i) mask = mask | (1 << i);
		for (map<int, complex>::iterator itr = amp.begin(); itr != amp.end(); ++itr) {
			if ((itr->second).norm() != 0) {
				mp[(itr->first) & mask] = mp[(itr->first) & mask] + (itr->second).norm();
			}
		}
		for (map<int, double>::iterator itr = mp.begin(); itr != mp.end(); ++itr) {
			if ((itr->second) != 0) {
				cout << bitset<16>(itr->first) << '(' << (itr->first) << ')' << " : Prob=";
				cout << (itr->second) << endl;
				prob += (itr->second);
			}
		}
		cout << "Sum of Probability : " << prob << endl;
		cout << endl;
		return;
	}


	//void QuantumCircuit::Init(int n) {
	//	amp.clear();
	//	//qc_size = n;
	//	complex a = a.set(1, 0);
	//	amp[0] = a;
	//	return;
	//}

	void QuantumCircuit::I(int index) {
		if (index < 0 or qc_size <= index) {
			cout << "Index out of range!(I)" << endl;
			exit(1);
		}

		return;
	}

	void QuantumCircuit::H(int index) {
		if (index < 0 or qc_size <= index) {
			cout << "Index out of range!(H)" << endl;
			exit(1);
		}

		map<int, complex> tmp;
		complex half = half.set(1 / sqrt(2), 0);
		for (map<int, complex>::iterator itr = amp.begin(); itr != amp.end(); ++itr) {
			if ((itr->first) & (1 << index)) {
				tmp[itr->first] = tmp[itr->first] + (itr->second) * half * (-1);
				tmp[(itr->first) & ~(1 << index)] = tmp[(itr->first) & ~(1 << index)] + (itr->second) * half;
			}
			else {
				tmp[itr->first] = tmp[itr->first] + (itr->second) * half;
				tmp[(itr->first) | (1 << index)] = tmp[(itr->first) | (1 << index)] + (itr->second) * half;
			}
		}
		amp = tmp;
		return;
	}

	void QuantumCircuit::X(int index) {
		if (index < 0 or qc_size <= index) {
			cout << "Index out of range!(X)" << endl;
			exit(1);
		}

		map<int, complex> tmp;
		for (map<int, complex>::iterator itr = amp.begin(); itr != amp.end(); ++itr) {
			if ((itr->first) & (1 << index)) {
				tmp[(itr->first) & ~(1 << index)] = tmp[(itr->first) & ~(1 << index)] + (itr->second);
			}
			else {
				tmp[(itr->first) | (1 << index)] = tmp[(itr->first) | (1 << index)] + (itr->second);
			}
		}
		amp = tmp;
		return;
	}

	void QuantumCircuit::Y(int index) {
		if (index < 0 or qc_size <= index) {
			cout << "Index out of range!(X)" << endl;
			exit(1);
		}

		map<int, complex> tmp;
		complex i = i.set(0, 1);
		for (map<int, complex>::iterator itr = amp.begin(); itr != amp.end(); ++itr) {
			if ((itr->first) & (1 << index)) {
				tmp[(itr->first) & ~(1 << index)] = tmp[(itr->first) & ~(1 << index)] - i * (itr->second);
			}
			else {
				tmp[(itr->first) | (1 << index)] = tmp[(itr->first) | (1 << index)] + i * (itr->second);
			}
		}
		amp = tmp;
		return;
	}

	void QuantumCircuit::Z(int index) {
		if (index < 0 or qc_size <= index) {
			cout << "Index out of range!(X)" << endl;
			exit(1);
		}

		map<int, complex> tmp;
		for (map<int, complex>::iterator itr = amp.begin(); itr != amp.end(); ++itr) {
			if ((itr->first) & (1 << index)) {
				tmp[(itr->first)] = tmp[(itr->first)] + (itr->second) * (-1);
			}
			else {
				tmp[(itr->first)] = tmp[(itr->first)] + (itr->second);
			}
		}
		amp = tmp;
		return;
	}

	void QuantumCircuit::CX(int ctrl, int index) {
		if (ctrl < 0 or qc_size <= ctrl or index < 0 or qc_size <= index or ctrl == index) {
			cout << "Index out of range!(CX)" << endl;
			exit(1);
		}

		map<int, complex> tmp;
		complex zero = zero.set(0, 0);
		for (map<int, complex>::iterator itr = amp.begin(); itr != amp.end(); ++itr) {
			if ((itr->first) & (1 << ctrl)) {
				if ((itr->first) & (1 << index)) {
					tmp[(itr->first) & ~(1 << index)] = tmp[(itr->first) & ~(1 << index)] + (itr->second);
				}
				else {
					tmp[(itr->first) | (1 << index)] = tmp[(itr->first) | (1 << index)] + (itr->second);
				}
			}
			else {
				tmp[(itr->first)] = (itr->second);
			}
		}
		amp = tmp;
		return;
	}

	void QuantumCircuit::CY(int ctrl, int index) {
		if (ctrl < 0 or qc_size <= ctrl or index < 0 or qc_size <= index or ctrl == index) {
			cout << "Index out of range!(CY)" << endl;
			exit(1);
		}

		map<int, complex> tmp;
		complex i = i.set(0, 1);
		for (map<int, complex>::iterator itr = amp.begin(); itr != amp.end(); ++itr) {
			if ((itr->first) & (1 << ctrl)) {
				if ((itr->first) & (1 << index)) {
					tmp[(itr->first) & ~(1 << index)] = tmp[(itr->first) & ~(1 << index)] + (itr->second) * i * (-1);
				}
				else {
					tmp[(itr->first) | (1 << index)] = tmp[(itr->first) | (1 << index)] + (itr->second) * i;
				}
			}
			else {
				tmp[(itr->first)] = (itr->second);
			}
		}
		amp = tmp;
		return;
	}


	void QuantumCircuit::CZ(int a, int b) {
		if (a < 0 or qc_size <= a or b < 0 or qc_size <= b or a == b) {
			cout << "Index out of range!(Swap)" << endl;
			exit(1);
		}
		H(b);
		CX(a, b);
		H(b);
		return;
	}

	void QuantumCircuit::Swap(int a, int b) {
		if (a < 0 or qc_size <= a or b < 0 or qc_size <= b or a == b) {
			cout << "Index out of range!(Swap)" << endl;
			exit(1);
		}
		CX(a, b);
		CX(b, a);
		CX(a, b);
		return;
	}


	void QuantumCircuit::Rx(int index, double theta) {
		if (index < 0 or qc_size <= index) {
			cout << "Index out of range!(Rx)" << endl;
			exit(1);
		}

		map<int, complex> tmp;
		complex c = c.set(cos(theta / 2), 0);
		complex s = c.set(sin(theta / 2), 0);
		complex mi = mi.set(0, -1);
		for (map<int, complex>::iterator itr = amp.begin(); itr != amp.end(); ++itr) {
			if ((itr->first) & (1 << index)) {
				tmp[itr->first] = tmp[itr->first] + (itr->second) * c;
				tmp[(itr->first) & ~(1 << index)] = tmp[(itr->first) & ~(1 << index)] + (itr->second) * s * mi;
			}
			else {
				tmp[itr->first] = tmp[itr->first] + (itr->second) * c;
				tmp[(itr->first) | (1 << index)] = tmp[(itr->first) | (1 << index)] + (itr->second) * s * mi;
			}
		}
		amp = tmp;
		return;
	}

	void QuantumCircuit::Ry(int index, double theta) {
		if (index < 0 or qc_size <= index) {
			cout << "Index out of range!(Ry)" << endl;
			exit(1);
		}

		map<int, complex> tmp;
		complex c = c.set(cos(theta / 2), 0);
		complex s = c.set(sin(theta / 2), 0);
		for (map<int, complex>::iterator itr = amp.begin(); itr != amp.end(); ++itr) {
			if ((itr->first) & (1 << index)) {
				tmp[itr->first] = tmp[itr->first] + (itr->second) * c;
				tmp[(itr->first) & ~(1 << index)] = tmp[(itr->first) & ~(1 << index)] + (itr->second) * s * (-1);
			}
			else {
				tmp[itr->first] = tmp[itr->first] + (itr->second) * c;
				tmp[(itr->first) | (1 << index)] = tmp[(itr->first) | (1 << index)] + (itr->second) * s;
			}
		}
		amp = tmp;
		return;
	}

	void QuantumCircuit::Rz(int index, double theta) {
		if (index < 0 or qc_size <= index) {
			cout << "Index out of range!(Rz)" << endl;
			exit(1);
		}

		map<int, complex> tmp;
		complex plus = plus.set(cos(theta / 2), sin(theta / 2));
		complex minus = minus.set(cos(theta / 2), (-1) * sin(theta / 2));
		for (map<int, complex>::iterator itr = amp.begin(); itr != amp.end(); ++itr) {
			if ((itr->first) & (1 << index)) {
				tmp[itr->first] = tmp[itr->first] + (itr->second) * plus;
			}
			else {
				tmp[itr->first] = tmp[itr->first] + (itr->second) * minus;
			}
		}
		amp = tmp;
		return;
	}

	void QuantumCircuit::S(int index) {
		if (index < 0 or qc_size <= index) {
			cout << "Index out of range!(S)" << endl;
			exit(1);
		}

		map<int, complex> tmp;
		complex i = i.set(0, 1);
		for (map<int, complex>::iterator itr = amp.begin(); itr != amp.end(); ++itr) {
			if ((itr->first) & (1 << index)) {
				tmp[itr->first] = tmp[itr->first] + (itr->second) * i;
			}
			else {
				tmp[itr->first] = tmp[itr->first] + (itr->second);
			}
		}
		amp = tmp;
		return;
	}

	void QuantumCircuit::Sdag(int index) {
		if (index < 0 or qc_size <= index) {
			cout << "Index out of range!(Sdag)" << endl;
			exit(1);
		}

		map<int, complex> tmp;
		complex i = i.set(0, 1);
		for (map<int, complex>::iterator itr = amp.begin(); itr != amp.end(); ++itr) {
			if ((itr->first) & (1 << index)) {
				tmp[itr->first] = tmp[itr->first] + (itr->second) * i * (-1);
			}
			else {
				tmp[itr->first] = tmp[itr->first] + (itr->second);
			}
		}
		amp = tmp;
		return;
	}

	void QuantumCircuit::T(int index) {
		if (index < 0 or qc_size <= index) {
			cout << "Index out of range!(T)" << endl;
			exit(1);
		}

		map<int, complex> tmp;
		double theta = _Pi / 4;
		complex plus = plus.set(cos(theta), sin(theta));
		for (map<int, complex>::iterator itr = amp.begin(); itr != amp.end(); ++itr) {
			if ((itr->first) & (1 << index)) {
				tmp[itr->first] = tmp[itr->first] + (itr->second) * plus;
			}
			else {
				tmp[itr->first] = tmp[itr->first] + (itr->second);
			}
		}
		amp = tmp;
		return;
	}

	void QuantumCircuit::Tdag(int index) {
		if (index < 0 or qc_size <= index) {
			cout << "Index out of range!(Tdag)" << endl;
			exit(1);
		}

		map<int, complex> tmp;
		double theta = _Pi / 4;
		complex plus = plus.set(cos(theta), sin(theta));
		for (map<int, complex>::iterator itr = amp.begin(); itr != amp.end(); ++itr) {
			if ((itr->first) & (1 << index)) {
				tmp[itr->first] = tmp[itr->first] + (itr->second) * plus * (-1);
			}
			else {
				tmp[itr->first] = tmp[itr->first] + (itr->second);
			}
		}
		amp = tmp;
		return;
	}

	void QuantumCircuit::Phase(int index, double theta) {
		if (index < 0 or qc_size <= index) {
			cout << "Index out of range!(Rz)" << endl;
			exit(1);
		}

		map<int, complex> tmp;
		complex plus = plus.set(cos(theta), sin(theta));
		for (map<int, complex>::iterator itr = amp.begin(); itr != amp.end(); ++itr) {
			if ((itr->first) & (1 << index)) {
				tmp[itr->first] = tmp[itr->first] + (itr->second) * plus;
			}
			else {
				tmp[itr->first] = tmp[itr->first] + (itr->second);
			}
		}
		amp = tmp;
		return;
	}

	void QuantumCircuit::U3(int index, double theta, double phi, double lambda) {
		if (index < 0 or qc_size <= index) {
			cout << "Index out of range!(Rz)" << endl;
			exit(1);
		}

		Rz(index, lambda);
		Ry(index, theta);
		Rz(index, phi);

		return;
	}

	void QuantumCircuit::U2(int index, double phi, double lambda) {
		if (index < 0 or qc_size <= index) {
			cout << "Index out of range!(Rz)" << endl;
			exit(1);
		}

		U3(index, _Pi / 2, phi, lambda);
		return;
	}
	void QuantumCircuit::U1(int index, double lambda) {
		if (index < 0 or qc_size <= index) {
			cout << "Index out of range!(Rz)" << endl;
			exit(1);
		}
		U3(index, 0, 0, lambda);
		return;
	}

	void QuantumCircuit::CCX(int ctrl1, int ctrl2, int index) {
		set<int> s;
		s.insert(ctrl1);
		s.insert(ctrl2);
		s.insert(index);
		int max = *(s.rbegin());
		int min = *(s.begin());
		if (min < 0 or qc_size <= max or min == max) {
			cout << "Index out of range!(C4X)" << endl;
			exit(1);
		}

		map<int, complex> tmp;
		complex zero = zero.set(0, 0);
		for (map<int, complex>::iterator itr = amp.begin(); itr != amp.end(); ++itr) {
			if (((itr->first) & (1 << ctrl1)) and ((itr->first) & (1 << ctrl2))) {
				if ((itr->first) & (1 << index)) {
					tmp[(itr->first) & ~(1 << index)] = tmp[(itr->first) & ~(1 << index)] + (itr->second);
				}
				else {
					tmp[(itr->first) | (1 << index)] = tmp[(itr->first) | (1 << index)] + (itr->second);
				}
			}
			else {
				tmp[(itr->first)] = (itr->second);
			}
		}
		amp = tmp;
		return;
	}

	void QuantumCircuit::C4X(int ctrl1, int ctrl2, int ctrl3, int ctrl4, int index) {
		set<int> s;
		s.insert(ctrl1);
		s.insert(ctrl2);
		s.insert(ctrl3);
		s.insert(ctrl4);
		s.insert(index);
		int max = *(s.rbegin());
		int min = *(s.begin());
		if (min < 0 or qc_size <= max or min == max) {
			cout << "Index out of range!(C4X)" << endl;
			exit(1);
		}

		map<int, complex> tmp;
		complex zero = zero.set(0, 0);
		for (map<int, complex>::iterator itr = amp.begin(); itr != amp.end(); ++itr) {
			if (((itr->first) & (1 << ctrl1))
				and ((itr->first) & (1 << ctrl2))
				and ((itr->first) & (1 << ctrl3))
				and ((itr->first) & (1 << ctrl4))) {
				if ((itr->first) & (1 << index)) {
					tmp[(itr->first) & ~(1 << index)] = tmp[(itr->first) & ~(1 << index)] + (itr->second);
				}
				else {
					tmp[(itr->first) | (1 << index)] = tmp[(itr->first) | (1 << index)] + (itr->second);
				}
			}
			else {
				tmp[(itr->first)] = (itr->second);
			}
		}
		amp = tmp;
		return;
	}

	void QuantumCircuit::C3Z(int ctrl1, int ctrl2, int ctrl3, int index) {
		set<int> s;
		s.insert(ctrl1);
		s.insert(ctrl2);
		s.insert(ctrl3);
		s.insert(index);
		int max = *(s.rbegin());
		int min = *(s.begin());
		if (min < 0 or qc_size <= max or min == max) {
			cout << "Index out of range!(C4X)" << endl;
			exit(1);
		}

		map<int, complex> tmp;
		complex zero = zero.set(0, 0);
		for (map<int, complex>::iterator itr = amp.begin(); itr != amp.end(); ++itr) {
			if (((itr->first) & (1 << ctrl1))
				and ((itr->first) & (1 << ctrl2))
				and ((itr->first) & (1 << ctrl3))) {
				if ((itr->first) & (1 << index)) {
					tmp[(itr->first)] = tmp[(itr->first)] + (itr->second) * (-1);
				}
				else {
					tmp[(itr->first)] = tmp[(itr->first)] + (itr->second);
				}
			}
			else {
				tmp[(itr->first)] = (itr->second);
			}
		}
		amp = tmp;
		return;
	}

	int QuantumCircuit::GetSize() {
		return qc_size;
	}
}