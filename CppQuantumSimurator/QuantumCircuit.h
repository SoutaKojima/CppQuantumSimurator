#pragma once
#include<vector>
#include<map>
#include<math.h>
#include<iostream>
#include<random>
#include<iomanip>
#include<bitset>
#include"complex.h"

namespace std
{
	class QuantumCircuit
	{
	private:
		map<int, complex> amp;
		int qc_size;
	public:
		void Init(int n);
		vector<int> Detection(int n);
		vector<int> Detection();
		void Amplitude();
		void Amplitude(int n);
		void H(int index);
		void X(int index);
		void Z(int index);
		void CX(int ctrl, int index);
		void Swap(int a, int b);
		void CZ(int a, int b);
		void Ry(int index,double theta);
		void Rz(int index,double theta);

		QuantumCircuit();
		QuantumCircuit(int n) {
			Init(n);
		}
	};
}
