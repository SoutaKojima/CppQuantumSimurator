#pragma once
#include"QuantumCircuit.h"
#include<time.h>
#include<utility>

namespace std {
	class QuantumMachineLearning
	{
	public:
		QuantumCircuit qc;
		vector<double> thetas;
		void MachineLearningXOR();
		void U_in(pair<int,int>);
		void U_Set();
		void cost();

		QuantumMachineLearning() {
			qc.Init(2);
		};
	};

}