#pragma once
#include<vector>
#include<map>
#include<math.h>
#include<iostream>
#include<random>
#include<iomanip>
#include<bitset>
#include"Qubit.h"

namespace std
{
	class QuantumCircuit
	{
	private:
		//vector<Qubit> c;
		map<int, complex> amp;
		//long pattern_length;
		//int gate_id = 0;
		int qc_size;
	public:
		void Init(int n);
		void Detection(int n);
		void Detection();
		void Amplitude();
		void H(int index);
		void X(int index);
		void CX(int ctrl, int index);
		void Swap(int a, int b);

		QuantumCircuit(int n) {
			Init(n);
		}
	};
}
