#pragma once

namespace QuantumSystem
{
    class Qubit
    {
    public:
        complex zero_ket, one_ket;
        static Qubit Init();
        static Qubit H(Qubit a);
    };

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

    const complex complex::operator+(const complex& a)const {
        complex tmp;
        tmp.re = re + a.re;
        tmp.im = im + a.im;
        return tmp;
    }

    const complex complex::operator-(const complex& a)const {
        complex tmp;
        tmp.re = re - a.re;
        tmp.im = im - a.im;
        return tmp;
    }

    const complex complex::operator/(const double& a)const {
        complex tmp;
        tmp.re = re / a;
        tmp.im = im / a;
        return tmp;
    }
}