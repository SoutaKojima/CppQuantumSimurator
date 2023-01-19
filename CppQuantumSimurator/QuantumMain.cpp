#include"QuantumMachineLearning.h"
using namespace std;

void main()
{
	QuantumMachineLearning qml(2, 2, 10);



	qml.qc.H(0);
	qml.qc.Amplitude();

}
