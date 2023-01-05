#pragma once

namespace std
{
    class complex
    {
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
}

