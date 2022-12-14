#include <iostream>
#include "QuantumSystem.h"
using namespace QuantumSystem;

int main()
{
    QuantumCircuit qc;
    qc.Init(2);

    qc.H(0);
    qc.X(1);

    qc.Detection(0);
    qc.Detection(1);

    return 0;
}
