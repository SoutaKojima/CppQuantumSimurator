#pragma once
#include<vector>
#include"Qubit.h"

namespace std
{
	class QuantumCircuit
	{
	private:
		vector<Qubit> c;
		long pattern_length;
		int gate_id = 0;
	public:
		void Init(int n);
		void Detection(int n);
		void Detection();
		void H(int index);
		void X(int index);
		void CX(int ctrl, int index);

		QuantumCircuit(int n) {
			Init(n);
		}
	};
}
