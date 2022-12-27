#pragma once
using namespace std;
#include<vector>

namespace QuantumSystem
{
    class complex {
    public:
        double re, im;
        complex set(double a, double b); // return a+bi
        double norm();
        double abs();
        static double Normalize(complex a, complex b);
        const complex operator+(const complex& a) const;
        const complex operator-(const complex& a) const;
        const complex operator*(const complex& a) const;
        const complex operator*(const double& a) const;
        const complex operator/(const double& a) const;
    };

    class Entangle
    {
    public:
        int enable = -1;
        complex zero_zero;
        complex zero_one;
        complex one_zero;
        complex one_one;
    };

    class Qubit
    {
    public:
        complex zero_ket, one_ket;
        vector<Entangle> e;
        Qubit Init();
        void Show();
        void Detection(int n);
        void H();
        void X();
    };

    class QuantumCircuit
    {
    private:
        vector<Qubit> c;
        long pattern_length;
    public:
        void Init(int n);
        void Detection(int n);
        void Detection();
        void H(int index);
        void X(int index);
        void CX(int ctrl,int index);
    };

    
}
