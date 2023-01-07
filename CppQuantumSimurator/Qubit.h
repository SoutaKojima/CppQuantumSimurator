#pragma once
#include"complex.h"
#include<vector>
#include<math.h>
#include<iostream>
#include<random>
#include<iomanip>
#include<bitset>

namespace std
{
	class Entangle
	{
	public:
		int pair = -1;
		int id=0;
		complex kets[2][2];
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

