#include <chrono>
#include <iostream>
#include <thread>
#include <vector>

using namespace std;

void threadFunc(int t) {
    // Nå er vi inni en tråd
    this_thread::sleep_for(chrono::seconds(t));
    cout << "Hello from thread: " << t << endl;
}

void example1() {
    thread t1{threadFunc, 1};
    thread t2{threadFunc, 2};

    cout << "Hello from main thread" << endl;

    // Venter på trådene våre
    t1.join();
    t2.join();

    cout << "All trheads completed" << endl;
}

void example2() {
    vector<thread> myTrheads;

    const int T = 5;
    // Starter vi alle trådene
    for (int i = 0; i < T; i++) {
        myTrheads.push_back(thread{threadFunc, i});
    }

    // Venter på alle trådene
    for (int i = 0; i < T; i++) {
        myTrheads[i].join();
    }
}

void threadsArgs(int a, int* b, int& c) {
    cout << a + *b + c << endl;

    // Endrer vi på verdier
    a = 10;
    *b = 20;
    c = 30;
}

void example3() {
    // Oppretter variabler
    int a = 1;
    int b = 2;
    int c = 3;

    // Oppretter en tråd
    thread t1{threadsArgs, a, &b, ref(c)};

    t1.join();

    cout << "a: " << a << endl;
    cout << "b: " << b << endl;
    cout << "c: " << c << endl;
}

int a_glob = 0;
void sumNormal() {
    for (int i = 0; i < 100'000; i++) {
        a_glob++;
    }
}

void example4() {
    thread t1{sumNormal};
    thread t2{sumNormal};

    t1.join();
    t2.join();

    cout << "a_glob: " << a_glob << endl;
}

#include <mutex>
int a_glob_mutex = 0;
mutex mtx_glob;
void sumNormalMutex() {
    for (int i = 0; i < 100'000; i++) {
        mtx_glob.lock();
        a_glob_mutex++;
        mtx_glob.unlock();
    }
}

void example5() {
    thread t1{sumNormalMutex};
    thread t2{sumNormalMutex};

    t1.join();
    t2.join();

    cout << "a_glob_mutex: " << a_glob_mutex << endl;
}

#include <atomic>
atomic_int a_glob_atomic = 0;

void sumNormalAtomic() {
    for (int i = 0; i < 100'000; i++) {
        // "En handling!"
        a_glob_atomic++;
    }
}

void example6() {
    thread t1{sumNormalAtomic};
    thread t2{sumNormalAtomic};

    t1.join();
    t2.join();

    cout << "a_glob_atomic: " << a_glob_atomic << endl;
}

void sumWithOutGlobVar(int& a, int& b, atomic_int& c, mutex& mtx) {
    for (int i = 0; i < 100'000; i++) {
        // Normal sum
        a++;

        // Sum with mutex
        mtx.lock();
        b++;
        mtx.unlock();

        // Sum with atomic
        c++;
    }
}

void example_4_5_6_extra() {
    // Mye bedre å ikke bruke globale variabler
    // Da har man full kontroll over hvem som har tilgang
    int a = 0;
    int b = 0;
    atomic_int c = 0;
    mutex mtx;

    thread t1{sumWithOutGlobVar, ref(a), ref(b), ref(c), ref(mtx)};
    thread t2{sumWithOutGlobVar, ref(a), ref(b), ref(c), ref(mtx)};

    t1.join();
    t2.join();

    cout << "a: " << a << endl;
    cout << "b: " << b << endl;
    cout << "c: " << c << endl;
}

#include "Eigen/Dense"
using namespace Eigen;

void example7() {
    Matrix2d A, B, C;
    A << 1, 2, 3, 4;
    B << 4, 3, 2, 1;
    C << 1, 3, 1.5, 2;

    // Regner ut
    A += B + C;

    // Skriver ut
    cout << "Matrix A:\n" << A << endl;
    cout << "Matrix B:\n" << B << endl;
    cout << "Matrix C:\n" << C << endl;
}

void runLiveCode() {
    // Write live code
    // example1();
    // example2();
    // example3();
    // example4();
    // example5();
    // example6();
    example_4_5_6_extra();
    example7();
}