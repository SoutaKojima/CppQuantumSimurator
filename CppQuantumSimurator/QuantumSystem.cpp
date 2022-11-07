#include "QuantumSystem.h"
#include <math.h>
#include <iostream>

namespace QuantumSystem
{
    Qubit Qubit::Init() {
        Qubit q;
        q.zero_ket = complex::set(1, 0);
        q.one_ket = complex::set(0, 0);
        return q;
    }

    void Qubit::Show(Qubit a) {
        std::cout << "zero_ket re:" << a.zero_ket.re << " ";
        std::cout << "zero_ket im:" << a.zero_ket.im << std::endl;
        std::cout << "one_ket re:" << a.one_ket.re << " ";
        std::cout << "one_ket im:" << a.one_ket.im << std::endl;
    }

    Qubit Qubit::H(Qubit a) {
        Qubit tmp = Qubit::Init();
        tmp.zero_ket = (a.zero_ket + a.one_ket) / sqrt(2);
        tmp.one_ket = (a.zero_ket - a.one_ket) / sqrt(2);
        return tmp;
    }

    Qubit Qubit::X(Qubit a) {
        Qubit tmp = Qubit::Init();
        tmp.zero_ket = a.one_ket;
        tmp.one_ket = a.zero_ket;
        return tmp;
    }

    complex complex::set(double a, double b) {
        complex tmp;
        tmp.re = a;
        tmp.im = b;
        return tmp;
    }

    double complex::norm(complex a) {
        return a.re * a.re + a.im * a.im;
    }

    double complex::abs(complex a) {
        return sqrt(complex::norm(a));
    }

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
