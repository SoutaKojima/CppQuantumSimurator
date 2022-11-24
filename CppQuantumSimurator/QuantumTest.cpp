#include <iostream>
#include "QuantumSystem.h"
using namespace QuantumSystem;

int main()
{
    int count = 0;
    Qubit q = q.Init();
    q.X();
    q.H();
    q.Show(); 
    
    q.Detection(100);

    return 0;
}
