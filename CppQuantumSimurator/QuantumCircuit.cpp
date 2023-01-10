#include "QuantumCircuit.h"

namespace std
{
	void QuantumCircuit::Detection(int n) {
		random_device rd;
		default_random_engine eng(rd());
		uniform_real_distribution<double> distr(0, 1);

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
					count[(itr->first)] = count[(itr->first)] + 1;
					break;
				}
				r -= (itr->second).norm();
			}
		}

		for (map<int, int>::iterator itr = count.begin(); itr != count.end(); ++itr) {
			cout << bitset<8>(itr->first) << '(' << (itr->first) << ')' << ':';
			cout << (itr->second) << endl;
		}
	}

	void QuantumCircuit::Detection() {
		Detection(1000);
		return;
	}

	void QuantumCircuit::Amplitude() {
		double prob = 0;
		for (map<int, complex>::iterator itr = amp.begin(); itr != amp.end(); ++itr) {
			if ((itr->second).norm() != 0) {
				cout << bitset<8>(itr->first) << '(' << (itr->first) << ')' << " : Prob=";
				cout << (itr->second).norm() << " : Amp=";
				cout << (itr->second).re << " + " << (itr->second).im << "i" << endl;
				prob += (itr->second).norm();
			}
		}
		cout << "Sum of Probability : " << prob << endl;
		cout << endl;
		return;
	}

	void QuantumCircuit::Amplitude(int n) {
		double prob = 0;
		map<int, double> mp;
		int mask = 0;
		for (int i = 0; i < n; ++i) mask = mask | (1 << i);
		for (map<int, complex>::iterator itr = amp.begin(); itr != amp.end(); ++itr) {
			if ((itr->second).norm() != 0) {
			mp[(itr->first) & mask] = mp[(itr->first) & mask] + (itr->second).norm();}
		}
		for (map<int, double>::iterator itr = mp.begin(); itr != mp.end(); ++itr) {
			if ((itr->second) != 0) {
				cout << bitset<32>(itr->first) << '(' << (itr->first) << ')' << " : Prob=";
				cout << (itr->second) << endl;
				prob += (itr->second);
			}
		}
		cout << "Sum of Probability : " << prob << endl;
		cout << endl;
		return;
	}

	void QuantumCircuit::Init(int n) {
		qc_size = n;
		complex a = a.set(1, 0);
		amp[0] = a;
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
}
