#pragma once
#include"QuantumAlgorithms.h"
#include<time.h>
#include<utility>

namespace std {
	class QuantumMachineLearning
	{
	public:
		QuantumCircuit qc;
		vector<double> thetas;
		vector < pair<pair<int, int>, int>> train;
		void MachineLearningXOR();
		void U_in(pair<int,int>);
		void U_Set();
		void U_Reset();
		void Loss();

		QuantumMachineLearning() {
			qc.Init(2);
		};
	};

}