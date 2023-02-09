#pragma once
#include"QuantumAlgorithms.h"
#include<time.h>
#include<utility>
#include<string>

namespace std {
    class QuantumMachineLearning
    {
    private:
        const int rep;
        const int epoc;
        //double diff_max;
    public:
        QuantumCircuit qc;
        vector<vector<double>> thetas;
        vector<vector<double>> data;
        //vector < pair<pair<int, int>, int>> train;
        void MachineLearningXOR();
        void MachineLearningRegression();
        void U_in(double);
        void U_ent();
        void U_loc(vector<double>);
        void Minimize(double);
        double Loss(double);
        void Theta_Reset();
        void ShowRegression(int s);
        void ShowThetas();
        void Data_Generating();

        QuantumMachineLearning(int n, int r, int e) :qc(n), rep(r), epoc(e) {
            //qc.Init(2);
            //diff_max = -1;
        };
    };

}