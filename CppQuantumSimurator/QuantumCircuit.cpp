#include "QuantumCircuit.h"
#include <math.h>
#include <iostream>
#include <random>
#include <iomanip>
#include <bitset>

namespace std
{
    void QuantumCircuit:: Detection(int n) {
        try
        {
            vector<int> count(pattern_length, 0);

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
                            zero_prob = c_tmp[i].ket[0].norm();
                            result = (zero_prob > r ? 0 : 1);
                            //cout << "         pair == -1" << endl;//debug
                        }
                        else {
                            result = ((*itr).kets[0][0].norm() + (*itr).kets[0][1].norm() > r ? 0 : 1);
                            //cout << "         pair == " << (*itr).pair << endl;//debug
                            //cout << (*itr).kets[0][0].norm() << endl;//debug
                            //cout << (*itr).kets[0][1].norm() << endl;//debug
                            //cout << (*itr).kets[1][0].norm() << endl;//debug
                            //cout << (*itr).kets[1][1].norm() << endl;//debug
                            /*
                            if (result == 0) {
                                double radius = complex::Normalize((*itr).kets[0][0], (*itr).kets[0][1]);
                                c_tmp[(*itr).pair].ket[0] = (*itr).kets[0][0] * radius;
                                c_tmp[(*itr).pair].ket[1] = (*itr).kets[0][1] * radius;
                                //cout << "       radius == " << radius << endl;//debug
                                //cout << "  zero_ket[0] == " << c_tmp[(*itr).enable].ket[0].norm() << endl;//debug
                                //cout << "  zero_ket[1] == " << c_tmp[(*itr).enable].ket[1].norm() << endl;//debug
                            }
                            else {
                                double radius = complex::Normalize((*itr).kets[1][0], (*itr).kets[1][1]);
                                c_tmp[(*itr).pair].ket[0] = (*itr).kets[1][0] * radius;
                                c_tmp[(*itr).pair].ket[1] = (*itr).kets[1][1] * radius;
                                //cout << "       radius == " << radius << endl;//debug
                                //cout << "   one_ket[0] == " << c_tmp[(*itr).enable].ket[0].norm() << endl;//debug
                                //cout << "  one_ ket[1] == " << c_tmp[(*itr).enable].ket[1].norm() << endl;//debug
                            }*/
                            double radius = complex::Normalize((*itr).kets[result][0], (*itr).kets[result][1]);
                            c_tmp[(*itr).pair].ket[0] = (*itr).kets[result][0] * radius;
                            c_tmp[(*itr).pair].ket[1] = (*itr).kets[result][1] * radius;
                            //cout << "       radius == " << radius << endl;//debug
                            //cout << "   one_ket[0] == " << c_tmp[(*itr).enable].ket[0].norm() << endl;//debug
                            //cout << "  one_ ket[1] == " << c_tmp[(*itr).enable].ket[1].norm() << endl;//debug
                            for(vector<Entangle>::iterator var = c_tmp[(*itr).pair].e.begin(); var != c_tmp[(*itr).pair].e.end(); ++var)
                            {
                                //cout << "       var_id == " << (*var).id << endl;//debug
                                //cout << "       itr_id == " << (*itr).id << endl;//debug
                                if ((*var).id == (*itr).id) {
                                    c_tmp[(*itr).pair].e.erase(var);
                                    //(*var).pair = -1;
                                    break;
                                }
                            }
                            //c_tmp[(*itr).pair].e.pair = -1;
                            //c_tmp[i].e.enable = -1;
                        }
                    }
                    tmp += result << i;
                }
                ++count[tmp];
            }
            for (int i = 0; i < pattern_length; ++i) {
                cout << bitset<8>(i) << '(' << i << ')' << ':';
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
            complex kets[2][2] = { c[ctrl].ket[0] * c[index].ket[0]
                                  ,c[ctrl].ket[0] * c[index].ket[1]
                                  ,c[ctrl].ket[1] * c[index].ket[0]
                                  ,c[ctrl].ket[1] * c[index].ket[1] };

            Entangle e_tmp;
            e_tmp.pair = index;
            e_tmp.id = gate_id;
            e_tmp.kets[0][0] = kets[0][0];
            e_tmp.kets[0][1] = kets[0][1];
            e_tmp.kets[1][0] = kets[1][0];
            e_tmp.kets[1][1] = kets[1][1];
            c[ctrl].e.push_back(e_tmp);

            e_tmp.pair = ctrl;
            e_tmp.kets[0][0] = kets[0][0];
            e_tmp.kets[0][1] = kets[0][1]; //kets[1][0]; //reversed
            e_tmp.kets[1][0] = kets[1][0]; //kets[0][1]; //reversed
            e_tmp.kets[1][1] = kets[1][1];
            c[index].e.push_back(e_tmp);

            ++gate_id;
        }
        catch (const exception&)
        {
            cout << "Index out of range!(CX)" << endl;
            exit(1);
        }
    }
}
