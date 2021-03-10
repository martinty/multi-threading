#include <stdlib.h>

#include <ctime>

#include "multiThreading.h"
// #include "testEigen.h"

int main() {
    srand(static_cast<unsigned int>(time(nullptr)));

    // showEigenUsage();
    testThreads();

    return 0;
}
