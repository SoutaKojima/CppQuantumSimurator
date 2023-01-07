#include <iostream>
#include "QuantumCircuit.h"
using namespace std;

int main()
{
	QuantumCircuit qc(3);

	qc.H(0);
	//qc.X(0);
	//qc.H(1);
	//qc.X(1);

	qc.CX(0, 1);
	//qc.X(0);

	//qc.Detection(1e4);
	qc.Amplitude();

	return 0;
}
