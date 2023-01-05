#include "Qubit.h"
#include <math.h>
#include <iostream>
#include <random>
#include <iomanip>
#include <bitset>

namespace std {
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
        int count[] = { 0,0 };
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

    
}