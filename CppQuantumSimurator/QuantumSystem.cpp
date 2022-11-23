#include "QuantumSystem.h"
#include <math.h>
#include <iostream>
#include <random>
#include <iomanip>

namespace QuantumSystem
{
    Qubit Qubit::Init() {
        Qubit q;
        complex c;
        q.zero_ket = c.set(1, 0);
        q.one_ket = c.set(0, 0);
        zero_ket = q.zero_ket;
        one_ket = q.one_ket;
        return q;
    }

    void Qubit::Show() {
        std::cout << "zero_ket re:" << zero_ket.re << " ";
        std::cout << "zero_ket im:" << zero_ket.im << std::endl;
        std::cout << "one_ket re:" << one_ket.re << " ";
        std::cout << "one_ket im:" << one_ket.im << std::endl;
        std::cout << std::endl;
    }

    void Qubit::Detection(int n) {
        double zero_prob = zero_ket.norm();
        std::random_device rd;
        std::default_random_engine eng(rd());
        std::uniform_real_distribution<double> distr(0, 1);
        for (int i = 0; i < n; ++i) {
            std::cout << distr(eng) << std::endl;

        }
    }

    void Qubit::H() {
        Qubit tmp = tmp.Init();
        tmp.zero_ket = (zero_ket + one_ket) / sqrt(2);
        tmp.one_ket = (zero_ket - one_ket) / sqrt(2);
        zero_ket = tmp.zero_ket;
        one_ket = tmp.one_ket;
    }

    void Qubit::X() {
        Qubit tmp = tmp.Init();
        tmp.zero_ket = one_ket;
        tmp.one_ket = zero_ket;
        zero_ket = tmp.zero_ket;
        one_ket = tmp.one_ket;
    }

    complex complex::set(double a, double b) {
        complex tmp;
        tmp.re = a;
        tmp.im = b;
        return tmp;
    }

    double complex::norm() {
        return re * re + im * im;
    }

    double complex::abs() {
        return sqrt(norm());
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
