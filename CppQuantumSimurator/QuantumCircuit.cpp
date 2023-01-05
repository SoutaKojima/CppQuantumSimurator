#include "QuantumCircuit.h"
#include <math.h>
#include <iostream>
#include <random>
#include <iomanip>
#include <bitset>

namespace std
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
                    int result = 0;
                    double zero_prob;

                    for (vector<Entangle>::iterator itr = c_tmp[i].e.begin(); itr != c_tmp[i].e.end(); ++itr) {
                        if ((*itr).pair == -1) {
                            zero_prob = c_tmp[i].zero_ket.norm();
                            result = (zero_prob > r ? 0 : 1);
                            //cout << "enable == -1" << endl;//debug
                        }
                        else {
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
                                c_tmp[(*itr).pair].zero_ket = (*itr).zero_zero * radius;
                                c_tmp[(*itr).pair].one_ket = (*itr).zero_one * radius;
                                //cout << "       radius == " << radius << endl;//debug
                                //cout << "zero_zero_ket == " << c_tmp[(*itr).enable].zero_ket.norm() << endl;//debug
                                //cout << "zero_ one_ket == " << c_tmp[(*itr).enable].one_ket.norm() << endl;//debug
                            }
                            else {
                                //c[i].e.zero_zero = 0
                                //c[i].e.zero_one = 0
                                double radius = complex::Normalize((*itr).one_zero, (*itr).one_one);
                                c_tmp[(*itr).pair].zero_ket = (*itr).one_zero * radius;
                                c_tmp[(*itr).pair].one_ket = (*itr).one_one * radius;
                                //cout << "       radius == " << radius << endl;//debug
                                //cout << " one_zero_ket == " << c_tmp[(*itr).enable].zero_ket.norm() << endl;//debug
                                //cout << " one_ one_ket == " << c_tmp[(*itr).enable].one_ket.norm() << endl;//debug
                            }

                            //c_tmp[(*itr).pair].e.pair = -1;
                            //c_tmp[i].e.enable = -1;

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
            e_tmp.pair = index;
            e_tmp.zero_zero = zero_zero;
            e_tmp.zero_one = zero_one;
            e_tmp.one_zero = one_zero;
            e_tmp.one_one = one_one;
            c[ctrl].e.push_back(e_tmp);

            e_tmp.pair = ctrl;
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
}
