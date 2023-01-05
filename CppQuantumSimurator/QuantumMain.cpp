#include <iostream>
#include "QuantumCircuit.h"
using namespace std;

int main()
{
    QuantumCircuit qc(2);

    qc.H(0);
    qc.CX(0, 1);

    qc.Detection(1e4);
   
    return 0;
}
