#include"QuantumMachineLearning.h"
using namespace std;

int main()
{
	QuantumMachineLearning qml(2, 2);

	

	qml.qc.H(0);
	qml.qc.Amplitude();

	return 0;
}
