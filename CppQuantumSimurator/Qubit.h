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

