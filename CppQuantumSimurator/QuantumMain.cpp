#include"QuantumMachineLearning.h"
using namespace std;

int main()
{
	QuantumMachineLearning qml(2);

	vector<double> train(qml.qc.GetSize() * 2, 0);
	//vector<vector<double>> data;

	train = { 0,0,1,0 };
	qml.data.push_back(train);
	train = { 0,1,0,1 };
	qml.data.push_back(train);
	train = { 1,0,0,1 };
	qml.data.push_back(train);
	train = { 1,1,1,0 };
	qml.data.push_back(train);

	qml.qc.H(0);
	qml.qc.Amplitude();

	return 0;
}
