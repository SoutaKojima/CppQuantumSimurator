#include "complex.h"
#include <math.h>
#include <iostream>
#include <random>
#include <iomanip>
#include <bitset>

namespace std
{
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

    double complex::Normalize(complex a, complex b) {
        return 1 / (a.norm() + b.norm());
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

    const complex complex::operator*(const complex& a)const {
        complex tmp;
        tmp.re = re * a.re - im * a.im;
        tmp.im = re * a.im + im * a.re;
        return tmp;
    }

    const complex complex::operator*(const double& a)const {
        complex tmp;
        tmp.re = re * a;
        tmp.im = im * a;
        return tmp;
    }

    const complex complex::operator/(const double& a)const {
        complex tmp;
        tmp.re = re / a;
        tmp.im = im / a;
        return tmp;
    }
}