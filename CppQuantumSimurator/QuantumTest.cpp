#include <iostream>
#include "QuantumSystem.h"
using namespace std;
using namespace QuantumSystem;

int main()
{
    QuantumCircuit qc;
    qc.Init(3);

    qc.H(0);
    qc.H(1);
    qc.CX(0, 2);
    qc.CX(1, 2);



    qc.Detection(10000);
   
    return 0;
}
