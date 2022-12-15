#include <iostream>
#include "QuantumSystem.h"
using namespace QuantumSystem;

int main()
{
    /*
    QuantumCircuit qc;
    qc.Init(2);

    qc.H(0);
    qc.X(1);

    qc.Detection(0);
    qc.Detection(1);
    */
    float a = 0.01;
    float b = 0;
    for (int i = 0; i < 10000; ++i) b += a;
    std::cout << b << std::endl;
    return 0;
}
