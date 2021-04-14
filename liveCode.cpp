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

void exmaple1() {
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

void exmaple4() {
    thread t1{sumNormal};
    thread t2{sumNormal};

    t1.join();
    t2.join();

    cout << "a_glob: " << a_glob << endl;
}

#include <mutex>
int a_glob_mutex = 0;
mutex mtx;
void numNormalMutex() {
    for (int i = 0; i < 100'000; i++) {
        mtx.lock();
        a_glob_mutex++;
        mtx.unlock();
    }
}

void exmaple5() {
    thread t1{numNormalMutex};
    thread t2{numNormalMutex};

    t1.join();
    t2.join();

    cout << "a_glob_mutex: " << a_glob_mutex << endl;
}

#include <atomic>
atomic_int a_glob_atomic = 0;

void numNormalAtomic() {
    for (int i = 0; i < 100'000; i++) {
        // "En handling!"
        a_glob_atomic++;
    }
}

void exmaple6() {
    thread t1{numNormalAtomic};
    thread t2{numNormalAtomic};

    t1.join();
    t2.join();

    cout << "a_glob_atomic: " << a_glob_atomic << endl;
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
    // exmaple1();
    // example2();
    // example3();
    // exmaple4();
    // exmaple5();
    // exmaple6();
    example7();
}