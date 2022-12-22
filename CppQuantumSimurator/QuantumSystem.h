#pragma once
#include<vector>

namespace QuantumSystem
{
    class complex {
    public:
        double re, im;
        complex set(double a, double b); // return a+bi
        double norm();
        double abs();
        const complex operator+(const complex& a) const;
        const complex operator-(const complex& a) const;
        const complex operator*(const complex& a) const;
        const complex operator/(const double& a) const;
    };

    class Qubit
    {
    public:
        complex zero_ket, one_ket;
        Qubit Init();
        void Show();
        void Detection(int n);
        void H();
        void X();
    };

    class QuantumCircuit
    {
    private:
        std::vector<Qubit> c;
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
