#include "QuantumSystem.h"
#include <math.h>
#include <iostream>
#include <random>
#include <iomanip>
#include <bitset>

namespace QuantumSystem
{
    void QuantumCircuit::Detection(int n) {
        try
        {
            std::vector<int> count(pattern_length,0);

            for (int i = 0; i < n; ++i) {
                std::random_device rd;
                std::default_random_engine eng(rd());
                std::uniform_real_distribution<double> distr(0, 1);
                std::vector<Qubit> c_tmp = c;
                int tmp = 0;
                for (int i = 0; i < c_tmp.size(); ++i) {
                    double r = distr(eng);
                    int result;
                    double zero_prob;
                    if (c_tmp[i].e.enable == -1) {
                        zero_prob = c_tmp[i].zero_ket.norm();
                        result = (zero_prob > r ? 0 : 1);
                        //std::cout << "enable == -1" << std::endl;//debug
                    }
                    else {
                        int partner = c_tmp[i].e.enable;
                        result = (c_tmp[i].e.zero_zero.norm() + c_tmp[i].e.zero_one.norm() > r ? 0 : 1);
                        //std::cout << "enable == " << c_tmp[i].e.enable << std::endl;//debug
                        //std::cout << c_tmp[i].e.zero_zero.norm() << std::endl;//debug
                        //std::cout << c_tmp[i].e.zero_one.norm() << std::endl;//debug
                        //std::cout << c_tmp[i].e.one_zero.norm() << std::endl;//debug
                        //std::cout << c_tmp[i].e.one_one.norm() << std::endl;//debug
                        if (result == 0) {
                            //c[i].e.one_zero = 0
                            //c[i].e.one_one = 0
                            double radius = complex::Normalize(c_tmp[i].e.zero_zero, c_tmp[i].e.zero_one);
                            c_tmp[c_tmp[i].e.enable].zero_ket = c_tmp[i].e.zero_zero * radius;
                            c_tmp[c_tmp[i].e.enable].one_ket = c_tmp[i].e.zero_one * radius;
                            //std::cout << "       radius == " << radius << std::endl;//debug
                            //std::cout << "zero_zero_ket == " << c_tmp[c_tmp[i].e.enable].zero_ket.norm() << std::endl;//debug
                            //std::cout << "zero_ one_ket == " << c_tmp[c_tmp[i].e.enable].one_ket.norm() << std::endl;//debug
                        }
                        else {
                            //c[i].e.zero_zero = 0
                            //c[i].e.zero_one = 0
                            double radius = complex::Normalize(c_tmp[i].e.one_zero, c_tmp[i].e.one_one);
                            c_tmp[c_tmp[i].e.enable].zero_ket = c_tmp[i].e.one_zero * radius;
                            c_tmp[c_tmp[i].e.enable].one_ket = c_tmp[i].e.one_one * radius;
                            //std::cout << "       radius == " << radius << std::endl;//debug
                            //std::cout << " one_zero_ket == " << c_tmp[c_tmp[i].e.enable].zero_ket.norm() << std::endl;//debug
                            //std::cout << " one_ one_ket == " << c_tmp[c_tmp[i].e.enable].one_ket.norm() << std::endl;//debug
                        }
                        c_tmp[c_tmp[i].e.enable].e.enable = -1;
                        c_tmp[i].e.enable = -1;
                    }
                    tmp += result << i;
                }
                ++count[tmp];
            }
            for (int i = 0; i<pattern_length ; ++i) {
                std::cout << std::bitset<8>(i)<<'('<<i<<')'<<':';
                std::cout << count[i] << std::endl;
            }
        }
        catch (const std::exception&)
        {
            std::cout << "Index out of range!(Detection)" << std::endl;
            exit(1);
        }
        return;
    }

    void QuantumCircuit::Detection() {
        try
        {
            Detection(1000);
        }
        catch (const std::exception&)
        {
            std::cout << "Index out of range!(Detection)" << std::endl;
            exit(1);
        }
        return;
    }

    void QuantumCircuit::Init(int n) {
        c.clear();
        pattern_length = 1;
        Qubit q = q.Init();
        for (int i = 0; i < n; ++i) {
            c.push_back(q);
            pattern_length *= 2;
        }
        return;
    }

    void QuantumCircuit::H(int index) {
        try
        {
            c[index].H();
        }
        catch (const std::exception&)
        {
            std::cout << "Index out of range!(H)" << std::endl;
            exit(1);
        }
        return;
    }

    void QuantumCircuit::X(int index) {
        try
        {
            c[index].X();
        }
        catch (const std::exception&)
        {
            std::cout << "Index out of range!(X)" << std::endl;
            exit(1);
        }
        return;
    }

    void QuantumCircuit::CX(int ctrl, int index) {
        try
        {
            complex zero_zero = c[ctrl].zero_ket * c[index].zero_ket;
            complex zero_one = c[ctrl].zero_ket * c[index].one_ket;
            complex one_zero = c[ctrl].one_ket * c[index].one_ket;
            complex one_one = c[ctrl].one_ket * c[index].zero_ket;

            c[ctrl].e.enable = index;
            c[ctrl].e.zero_zero = zero_zero;
            c[ctrl].e.zero_one = zero_one;
            c[ctrl].e.one_zero = one_zero;
            c[ctrl].e.one_one = one_one;

            c[index].e.enable = ctrl;
            c[index].e.zero_zero = zero_zero;
            c[index].e.zero_one = one_zero; //reversed
            c[index].e.one_zero = zero_one; //reversed
            c[index].e.one_one = one_one;
        }
        catch (const std::exception&)
        {
            std::cout << "Index out of range!(CX)" << std::endl;
            exit(1);
        }
       
    }

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
        int count[] = {0,0};
        std::random_device rd;
        std::default_random_engine eng(rd());
        std::uniform_real_distribution<double> distr(0, 1);

        for (int i = 0; i < n; ++i) {
            double r = distr(eng);
            //std::cout << (zero_prob > r ? 0 : 1);
            ++count[(zero_prob > r ? 0 : 1)];
            //if (i % 10 == 9) std::cout << std::endl;
        }
        //std::cout << std::endl;
        std::cout << "zero:" << count[0] << std::endl;
        std::cout << " one:" << count[1] << std::endl;
        std::cout << std::endl;
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

    double complex::Normalize(complex a,complex b) {
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
