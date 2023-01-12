#include"QuantumMachineLearning.h"
using namespace std;

int main()
{
	//QuantumAlgorithms qa;
	//qa.SudokuAlgorithm();

	QuantumCircuit qc(3);

	qc.H(0);
	qc.H(1);
	qc.CCX(0, 1, 2);
	qc.Amplitude();

	return 0;
}
