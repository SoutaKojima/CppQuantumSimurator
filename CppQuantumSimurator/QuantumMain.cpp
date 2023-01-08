#include <iostream>
#include "QuantumCircuit.h"
using namespace std;

int main()
{
	QuantumCircuit qc(2);


	//qc.H(0);
	//qc.Z(0);
	
	qc.H(0);
	qc.H(1);

	qc.CZ(0, 1);
	qc.H(0);
	qc.H(1);

	qc.Z(0);
	qc.Z(1);
	qc.CZ(0, 1);
	qc.H(0);
	qc.H(1);
	
	qc.Amplitude();

	return 0;
}
