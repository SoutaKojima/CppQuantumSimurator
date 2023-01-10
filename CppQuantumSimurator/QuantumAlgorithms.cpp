#include "QuantumAlgorithms.h"

namespace std {
	void QuantumAlgorithms::DeutschJoszaAlgorithm() {
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

		//qc.Detection(1e4);
		qc.Amplitude();

		return;
	}
	//ref:https://qiskit.org/textbook/ja/ch-algorithms/deutsch-jozsa.html

	void QuantumAlgorithms::GroverAlgorithm() {
		QuantumCircuit qc(2);

		qc.H(0);
		qc.H(1);

		qc.Amplitude();

		qc.CZ(0, 1);

		qc.Amplitude();

		qc.H(0);
		qc.H(1);
		qc.Z(0);
		qc.Z(1);
		qc.CZ(0, 1);
		qc.H(0);
		qc.H(1);

		qc.Amplitude();

		return;
	}
	//ref:https://qiskit.org/textbook/ja/ch-algorithms/grover.html


	void QuantumAlgorithms::ShorAlgorithm() {
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

		return;
	}
}
