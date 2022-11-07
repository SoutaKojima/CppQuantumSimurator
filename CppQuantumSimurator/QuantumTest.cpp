#include <iostream>
#include "QuantumSystem.h"

int main()
{
    int count = 0;
    QuantumSystem::Qubit q = QuantumSystem::Qubit::Init();
    q.Show(q);
    std::cout << std::endl;
    q = QuantumSystem::Qubit::Init();
    q = q.H(q);
    q.Show(q); 
    std::cout << std::endl;
    q = QuantumSystem::Qubit::Init();
    q = q.X(q);
    q.Show(q);
    std::cout << std::endl;
    q = QuantumSystem::Qubit::Init();
    q = q.X(q);
    q = q.H(q);
    q.Show(q);
    std::cout << std::endl;
    q = QuantumSystem::Qubit::Init();
    q = q.H(q);
    q = q.H(q);
    q.Show(q);

    return 0;
}
