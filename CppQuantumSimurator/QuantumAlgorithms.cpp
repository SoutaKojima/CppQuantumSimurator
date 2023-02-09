#include "QuantumAlgorithms.h"

namespace std {
    void QuantumAlgorithms::DeutschJoszaAlgorithm() {
        clock_t start = clock();
        QuantumCircuit qc(4);

        qc.H(0);
        qc.X(0);
        qc.H(1);
        qc.H(2);
        qc.X(2);
        qc.X(3);
        qc.H(3);

        qc.CX(0, 3);
        qc.CX(1, 3);
        qc.CX(2, 3);


        qc.X(0);
        qc.H(0);
        qc.H(1);
        qc.X(2);
        qc.H(2);


        qc.Amplitude();
        qc.Detection();

        clock_t end = clock();
        cout << "Time : " << (end - start) << "ms" << endl;
        return;
    }
    //ref:https://qiskit.org/textbook/ja/ch-algorithms/deutsch-jozsa.html

    void QuantumAlgorithms::GroverAlgorithm() {
        clock_t start = clock();
        QuantumCircuit qc(2);

        qc.H(0);
        qc.H(1);

        qc.Amplitude();

        qc.CZ(0, 1);

        qc.Amplitude();

        qc.H(0);
        qc.H(1);
        qc.Z(0);
        qc.Z(1);
        qc.CZ(0, 1);
        qc.H(0);
        qc.H(1);

        qc.Amplitude();
        qc.Detection();

        clock_t end = clock();
        cout << "Time : " << (end - start) << "ms" << endl;

        return;
    }
    //ref:https://qiskit.org/textbook/ja/ch-algorithms/grover.html

    void QuantumAlgorithms::SudokuAlgorithm() {
        clock_t start = clock();
        QuantumCircuit qc(9);

        for (int i = 0; i < 4; ++i) qc.H(i);

        for (int j = 0; j < 2; ++j) {
            qc.X(8);
            qc.H(8);

            qc.CX(0, 4);
            qc.CX(1, 4);
            qc.CX(0, 5);
            qc.CX(2, 5);
            qc.CX(1, 6);
            qc.CX(3, 6);
            qc.CX(2, 7);
            qc.CX(3, 7);

            qc.C4X(4, 5, 6, 7, 8);

            qc.CX(0, 4);
            qc.CX(1, 4);
            qc.CX(0, 5);
            qc.CX(2, 5);
            qc.CX(1, 6);
            qc.CX(3, 6);
            qc.CX(2, 7);
            qc.CX(3, 7);

            for (int i = 0; i < 4; ++i) qc.H(i);
            for (int i = 0; i < 4; ++i) qc.X(i);
            qc.C3Z(1, 2, 3, 0);
            for (int i = 0; i < 4; ++i) qc.X(i);
            for (int i = 0; i < 4; ++i) qc.H(i);

            qc.Amplitude();
        }

        qc.Amplitude(4);
        qc.Detection(4);

        clock_t end = clock();
        cout << "Time : " << (end - start) << "ms" << endl;

        return;
    }


    void QuantumAlgorithms::ShorAlgorithm() {
        clock_t start = clock();
        QuantumCircuit qc(12);

        for (int i = 0; i < 8; ++i) qc.H(i);

        qc.X(0);
        qc.H(1);
        qc.H(2);
        qc.X(2);
        qc.X(3);
        qc.H(3);

        qc.CX(0, 3);
        qc.CX(1, 3);
        qc.CX(2, 3);


        qc.X(0);
        qc.H(0);
        qc.H(1);
        qc.X(2);
        qc.H(2);

        qc.Detection((int)1e4);
        //qc.Amplitude();
        clock_t end = clock();
        cout << "Time : " << (end - start) << "ms" << endl;

        return;
    }
}
