#pragma once

namespace QuantumSystem
{
    class complex {
    public:
        double re, im;
        static complex set(double a, double b); // return a+bi
        static double norm(complex a);
        static double abs(complex a);
        const complex operator+(const complex& a) const;
        const complex operator-(const complex& a) const;
        const complex operator/(const double& a) const;
    };

    class Qubit
    {
    public:
        complex zero_ket, one_ket;
        static Qubit Init();
        static void Show(Qubit a);
        static Qubit H(Qubit a);
        static Qubit X(Qubit a);
    };
}
