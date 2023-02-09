#pragma once
#include<vector>
#include<map>
#include<math.h>
#include<iostream>
#include<random>
#include<iomanip>
#include<bitset>
#include<set>
#include<fstream>
#include"complex.h"

namespace std
{
    class QuantumCircuit
    {
    private:
        map<int, complex> amp;
        int qc_size;
    public:
        void Init();
        map<int, int> Detection(int size, int n);
        map<int, int> Detection(int size);
        map<int, int> Detection();
        map<int, int> SubDetection(int n);
        vector<complex> Amplitude();
        vector<double> Amplitude(int n);
        void I(int index);
        void H(int index);
        void X(int index);
        void Y(int index);
        void Z(int index);
        void CX(int ctrl, int index);
        void CY(int ctrl, int index);
        void CZ(int a, int b);
        void Swap(int a, int b);
        void Rx(int index, double theta);
        void Ry(int index, double theta);
        void Rz(int index, double theta);
        void S(int index);
        void Sdag(int index);
        void T(int index);
        void Tdag(int index);
        void Phase(int index, double theta);
        void U3(int index, double theta,double phi,double lambda);
        void U2(int index, double phi,double lambda);
        void U1(int index, double lambda);
        void CCX(int ctrl1, int ctrl2, int index);
        void C4X(int ctrl1, int ctrl2, int ctrl3, int ctrl4, int index);
        void C3Z(int ctrl1, int ctrl2, int ctrl3, int index);
        int GetSize();

        QuantumCircuit(const int n){
            amp.clear();
            qc_size = n;
            complex a = a.set(1, 0);
            amp[0] = a;
            return;
        }
    };
}
