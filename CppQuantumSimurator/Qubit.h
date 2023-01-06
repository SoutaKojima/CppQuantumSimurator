#pragma once
#include"complex.h"
#include<vector>

namespace std
{
    class Entangle
    {
    public:
        int pair = -1;
        int id;
        complex kets[2][2];
        /*complex zero_zero;
        complex zero_one;
        complex one_zero;
        complex one_one;*/
    };

    class Qubit
    {
    public:
        complex ket[2];
        vector<Entangle> e;
        Qubit Init();
        void Show();
        void Detection(int n);
        void H();
        void X();
    };
}

