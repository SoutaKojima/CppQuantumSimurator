#pragma once
#include <math.h>
#include <iostream>
#include <random>
#include <iomanip>
#include <bitset>

namespace std
{
	class complex
	{
	public:
		double re, im;
		complex set(double a, double b); // return a+bi
		complex set(double phase); // return exp(phase*sqrt(-1))
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

