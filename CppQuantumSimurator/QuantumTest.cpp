#include <iostream>
#include "QuantumSystem.h"
using namespace std;
using namespace QuantumSystem;

int main()
{
    QuantumCircuit qc;
    qc.Init(2);

    qc.H(0);
    qc.H(1);

    qc.Detection(10000);
   
    return 0;
}
