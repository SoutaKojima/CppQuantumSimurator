#include"QuantumMachineLearning.h"
using namespace std;

int main()
{
	//QuantumAlgorithms qa;
	//qa.SudokuAlgorithm();

	QuantumCircuit qc(1);

	qc.H(0);
	qc.U3(0, _Pi, _Pi / 2, _Pi / 4);

	qc.Amplitude();

	return 0;
}
