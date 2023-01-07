#include <iostream>
#include "QuantumCircuit.h"
using namespace std;

int main_()
{
	QuantumCircuit qc(4);

	qc.H(0);
	qc.X(0);
	qc.H(1);
	qc.H(2);
	qc.X(2);
	qc.X(3);
	qc.H(3);

	qc.CX(0, 3);
	qc.CX(1, 3);
	qc.CX(2, 3);


	qc.X(0);
	qc.H(0);
	qc.H(1);
	qc.X(2);
	qc.H(2);

	qc.Detection(1e4);
	//qc.Amplitude();

	return 0;
}