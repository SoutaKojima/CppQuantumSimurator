#include "QuantumSystem.h"
#include <math.h>

namespace QuantumSystem
{
    Qubit Qubit::Init() {
        Qubit q;
        q.zero_ket = complex::set(1, 0);
        q.one_ket = complex::set(0, 0);
        return q;
    }

    Qubit Qubit::H(Qubit a) {
        Qubit tmp = Qubit::Init();
        tmp.zero_ket = (a.zero_ket + a.one_ket) / sqrt(2);
        tmp.one_ket = (a.zero_ket - a.one_ket) / sqrt(2);
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


}