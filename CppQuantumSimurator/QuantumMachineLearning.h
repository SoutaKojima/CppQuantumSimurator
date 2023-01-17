#pragma once
#include"QuantumAlgorithms.h"
#include<time.h>
#include<utility>

namespace std {
	class QuantumMachineLearning
	{
	private:
		int rep;
	public:
		QuantumCircuit qc;
		vector<vector<double>> thetas;
		vector<vector<double>> data;
		//vector < pair<pair<int, int>, int>> train;
		void MachineLearningXOR();
		void U_in(vector<double>);
		void U_ent();
		void U_loc();
		//void U_Set();
		void Theta_Reset();
		void Loss();

		QuantumMachineLearning(int n,int r) :qc(n),rep(r) {
			//qc.Init(2);
		};
	};

}