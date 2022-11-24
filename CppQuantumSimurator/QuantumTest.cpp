#include <iostream>
#include "QuantumSystem.h"
using namespace QuantumSystem;

int main()
{
    int count = 0;
    Qubit q = q.Init();
    q.H();
    q.Show(); 
    
    q.Detection(1000);

    return 0;
}
