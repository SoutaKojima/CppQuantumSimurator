#include"QuantumMachineLearning.h"
#include<fstream>
using namespace std;

int main()
{
	ifstream text_data;
	text_data.open("data/test.dat");

	vector<double> v;
	double d;
	while (text_data) {
		text_data >> d;
		cout << d << endl;
		v.push_back(d);
	}
	v.erase(v.end() - 1);
	cout << v.size() << endl;

	for (vector<double>::iterator itr = v.begin(); itr != v.end(); ++itr) {
		cout << *itr << endl;
	}

	return 0;
}
