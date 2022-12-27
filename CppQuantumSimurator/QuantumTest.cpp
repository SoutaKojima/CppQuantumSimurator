#include <iostream>
#include "QuantumSystem.h"
using namespace std;
using namespace QuantumSystem;

int main()
{
    QuantumCircuit qc;
    qc.Init(2);

    qc.H(0);
    qc.CX(0, 1);



    qc.Detection(1e4);
   
    return 0;
}
