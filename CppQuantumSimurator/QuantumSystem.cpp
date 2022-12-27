#include "QuantumSystem.h"
#include <math.h>
#include <iostream>
#include <random>
#include <iomanip>
#include <bitset>
using namespace std;

namespace QuantumSystem
{
    void QuantumCircuit::Detection(int n) {
        try
        {
            vector<int> count(pattern_length,0);

            for (int i = 0; i < n; ++i) {
                random_device rd;
                default_random_engine eng(rd());
                uniform_real_distribution<double> distr(0, 1);
                vector<Qubit> c_tmp = c;
                int tmp = 0;
                for (int i = 0; i < c_tmp.size(); ++i) {
                    double r = distr(eng);
                    int result;
                    double zero_prob;

                    for (vector<Entangle>::iterator itr = c_tmp[i].e.begin(); itr != c_tmp[i].e.end(); ++itr) {
                        if ((*itr).enable == -1) {
                            zero_prob = c_tmp[i].zero_ket.norm();
                            result = (zero_prob > r ? 0 : 1);
                            //cout << "enable == -1" << endl;//debug
                        }
                        else {
                            int partner = (*itr).enable;
                            result = ((*itr).zero_zero.norm() + (*itr).zero_one.norm() > r ? 0 : 1);
                            //cout << "enable == " << (*itr).enable << endl;//debug
                            //cout << (*itr).zero_zero.norm() << endl;//debug
                            //cout << (*itr).zero_one.norm() << endl;//debug
                            //cout << (*itr).one_zero.norm() << endl;//debug
                            //cout << (*itr).one_one.norm() << endl;//debug
                            if (result == 0) {
                                //c[i].e.one_zero = 0
                                //c[i].e.one_one = 0
                                double radius = complex::Normalize((*itr).zero_zero, (*itr).zero_one);
                                c_tmp[(*itr).enable].zero_ket = (*itr).zero_zero * radius;
                                c_tmp[(*itr).enable].one_ket = (*itr).zero_one * radius;
                                //cout << "       radius == " << radius << endl;//debug
                                //cout << "zero_zero_ket == " << c_tmp[(*itr).enable].zero_ket.norm() << endl;//debug
                                //cout << "zero_ one_ket == " << c_tmp[(*itr).enable].one_ket.norm() << endl;//debug
                            }
                            else {
                                //c[i].e.zero_zero = 0
                                //c[i].e.zero_one = 0
                                double radius = complex::Normalize((*itr).one_zero, (*itr).one_one);
                                c_tmp[(*itr).enable].zero_ket = (*itr).one_zero * radius;
                                c_tmp[(*itr).enable].one_ket = (*itr).one_one * radius;
                                //cout << "       radius == " << radius << endl;//debug
                                //cout << " one_zero_ket == " << c_tmp[(*itr).enable].zero_ket.norm() << endl;//debug
                                //cout << " one_ one_ket == " << c_tmp[(*itr).enable].one_ket.norm() << endl;//debug
                            }
                            c_tmp[c_tmp[i].e.enable].e.enable = -1;
                            c_tmp[i].e.enable = -1;
                        }
                    }
                    tmp += result << i;
                }
                ++count[tmp];
            }
            for (int i = 0; i<pattern_length ; ++i) {
                cout << bitset<8>(i)<<'('<<i<<')'<<':';
                cout << count[i] << endl;
            }
        }
        catch (const exception&)
        {
            cout << "Index out of range!(Detection)" << endl;
            exit(1);
        }
        return;
    }

    void QuantumCircuit::Detection() {
        try
        {
            Detection(1000);
        }
        catch (const exception&)
        {
            cout << "Index out of range!(Detection)" << endl;
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
        catch (const exception&)
        {
            cout << "Index out of range!(H)" << endl;
            exit(1);
        }
        return;
    }

    void QuantumCircuit::X(int index) {
        try
        {
            c[index].X();
        }
        catch (const exception&)
        {
            cout << "Index out of range!(X)" << endl;
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

            Entangle e_tmp;
            e_tmp.enable = index;
            e_tmp.zero_zero = zero_zero;
            e_tmp.zero_one = zero_one;
            e_tmp.one_zero = one_zero;
            e_tmp.one_one = one_one;
            c[ctrl].e.push_back(e_tmp);

            e_tmp.enable = ctrl;
            e_tmp.zero_zero = zero_zero;
            e_tmp.zero_one = one_zero; //reversed
            e_tmp.one_zero = zero_one; //reversed
            e_tmp.one_one = one_one;
            c[index].e.push_back(e_tmp);
        }
        catch (const exception&)
        {
            cout << "Index out of range!(CX)" << endl;
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
        cout << "zero_ket re:" << zero_ket.re << " ";
        cout << "zero_ket im:" << zero_ket.im << endl;
        cout << "one_ket re:" << one_ket.re << " ";
        cout << "one_ket im:" << one_ket.im << endl;
        cout << endl;
    }

    void Qubit::Detection(int n) {
        double zero_prob = zero_ket.norm();
        int count[] = {0,0};
        random_device rd;
        default_random_engine eng(rd());
        uniform_real_distribution<double> distr(0, 1);

        for (int i = 0; i < n; ++i) {
            double r = distr(eng);
            //cout << (zero_prob > r ? 0 : 1);
            ++count[(zero_prob > r ? 0 : 1)];
            //if (i % 10 == 9) cout << endl;
        }
        //cout << endl;
        cout << "zero:" << count[0] << endl;
        cout << " one:" << count[1] << endl;
        cout << endl;
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
