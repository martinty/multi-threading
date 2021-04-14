#include "multiThreading.h"

#include <atomic>
#include <chrono>
#include <cmath>
#include <functional>  // std::ref
#include <iostream>
#include <numeric>
#include <string>
#include <thread>

#include "stdmt/ProgressBar.h"
#include "stdmt/RandomEngine.h"
#include "stdmt/Walltime.h"
#include "stdmt/utilities_stdmt.h"

using namespace std;
using namespace stdmt;

namespace test {

void worker(const int nT, mutex& mtx) {
    mtx.lock();  // Critical section begin

    cout << "Thread number: " << nT << "\n";
    cout << "Thread ID: " << this_thread::get_id() << "\n";
    this_thread::sleep_for(chrono::seconds(1));

    mtx.unlock();  // Critical section end
}

void normalSum(int& a) {
    for (uint i = 0; i < 1'000'000; i++) {
        a++;  // a = a + 1
    }
}

void atomicSum(atomic_int& a) {
    for (uint i = 0; i < 1'000'000; i++) {
        a++;  // a = a + 1
    }
}

void sumSquareElement(const vector<int>& vec, const uint begin, const uint end,
                      double& sum) {
    for (uint i{begin}; i < end; i++) {
        sum += std::pow(vec[i], 2);
    }
}

void threadFunc(int n) {
    // Threads can split each other lines
    // cout is thread safe, but other threads can print to terminal in between
    // "... << ..."
    // Can be solved with mutex as shown in worker()
    cout << "Hello from thread: " << n << endl;
}

void threadArgs(int a, int* b, int& c) { cout << a + *b + c << endl; }

int a_glob = 0;  // Global variable
void threadDataRace() {
    for (int i{0}; i < 1000000; i++) {
        a_glob++;  // Data race, a = a + 1
    }
};

mutex mtx_glob;
int a_glob_mutex = 0;
void threadMutex() {
    mtx_glob.lock();  // Critical section begin
    for (int i{0}; i < 1000000; i++) {
        a_glob_mutex++;
    }
    mtx_glob.unlock();  // Critical section end
};

atomic_int a_glob_atomic = 0;
void threadAtomic() {
    for (int i{0}; i < 1000000; i++) {
        a_glob_atomic++;  // Atomic action
    }
};

void testWorker() {
    Walltime wt;  // Also start timer

    constexpr int T = 5;
    mutex mtx;
    vector<thread> myThreads;

    mtx.lock();
    for (int n = 0; n < T; n++) {
        myThreads.push_back(thread{worker, n, ref(mtx)});
    }
    mtx.unlock();

    for (auto& t : myThreads) {
        t.join();
    }

    wt.stop();
    cout << wt << "\n";
}

void testNormalSum() {
    Walltime wt;  // Also start timer

    int a = 0;
    thread t1{normalSum, ref(a)};
    thread t2{normalSum, ref(a)};

    t1.join();
    t2.join();

    cout << "a: " << a << "\n";
    wt.stop();
    cout << wt << "\n";
}

void testAtomicSum() {
    Walltime wt;  // Also start timer

    atomic_int a = 0;
    thread t1{atomicSum, ref(a)};
    thread t2{atomicSum, ref(a)};

    t1.join();
    t2.join();

    cout << "a: " << a << "\n";
    wt.stop();
    cout << wt << "\n";
}

void testVectorWork() {
    Walltime wt;  // Also start timer

    const uint N = 100'000'000;
    ProgressBar bar{N};
    vector<int> vec(N);
    RandomEngine engine;
    cout << "Vector size: " << N << "\n"
         << "Generate random numbers [-10, 10] for vector" << endl;
    for (uint i{0}; i < vec.size(); ++i) {
        vec[i] = engine.getRandInt(-10, 10);
        ++bar;
    }
    wt.stop();
    cout << wt << "\n\n";

    // **********************

    wt.start();
    constexpr int T = 4;
    uint skip = vec.size() / T;
    vector<thread> myThreads;
    vector<double> result(T);

    cout << "With " << T << " threads\n";
    for (int t{0}; t < T; t++) {
        uint begin = skip * t;
        uint end = (t < T - 1) ? begin + skip : vec.size();
        myThreads.push_back(
            thread{sumSquareElement, ref(vec), begin, end, ref(result[t])});
    }
    for (auto& t : myThreads) {
        t.join();
    }
    double sum1 = accumulate(result.begin(), result.end(), 0.0);

    cout << "Norm: " << std::sqrt(sum1) << "\n";
    wt.stop();
    double t1 = wt.getDuration();
    cout << wt << "\n\n";

    // **********************

    wt.start();
    double sum2 = 0;

    cout << "With only main thread\n";
    sumSquareElement(vec, 0, vec.size(), sum2);

    cout << "Norm: " << std::sqrt(sum2) << "\n";
    wt.stop();
    double t2 = wt.getDuration();
    cout << wt << "\n\n";

    // **********************

    cout << "Speedup with threads: " << t2 / t1 << endl;
}

void testThreadFunc() {
    thread t1{threadFunc, 1};  // Spawn new thread
    thread t2{threadFunc, 2};
    // Main thread is free to do work ...
    t1.join();  // block until t1 is finished
    t2.join();
    cout << "Thread 1 and 2 completed\n";
}

void testThreadArgs() {
    int a = 1;
    int b = 2;
    int c = 3;
    thread t1{threadArgs, a, &b, ref(c)};
    t1.join();
}

void testThreadDataRace() {
    thread t1{threadDataRace};
    thread t2{threadDataRace};
    t1.join();
    t2.join();
    cout << "a_glob: " << a_glob << "\n";
}

void testThreadMutex() {
    thread t1{threadMutex};
    thread t2{threadMutex};
    t1.join();
    t2.join();
    cout << "a_glob_mutex: " << a_glob_mutex << "\n";
}

void testThreadAtomic() {
    thread t1{threadAtomic};
    thread t2{threadAtomic};
    t1.join();
    t2.join();
    cout << "a_glob_atomic: " << a_glob_atomic << "\n";
}

void testThreadsMenu() {
    int input = 1;
    while (input) {
        cout << "\n" << string(40, '-') << "\n";
        cout << "0) Exit\n";
        cout << "1) Run worker threads\n";
        cout << "2) Normal sum with threads\n";
        cout << "3) Atomic sum with threads\n";
        cout << "4) Sum the square of every element in vector\n";
        cout << "5) Run 'Hello from thread'\n";
        cout << "6) Run thread with args\n";
        cout << "7) Run thread with global variable\n";
        cout << "8) Run thread with mutex\n";
        cout << "9) Run thread with atomic_int\n";
        input = getInput(0, 9);
        cout << endl;
        switch (input) {
            case 1: {
                testWorker();
                break;
            }
            case 2: {
                testNormalSum();
                break;
            }
            case 3: {
                testAtomicSum();
                break;
            }
            case 4: {
                testVectorWork();
                break;
            }
            case 5: {
                testThreadFunc();
                break;
            }
            case 6: {
                testThreadArgs();
                break;
            }
            case 7: {
                testThreadDataRace();
                break;
            }
            case 8: {
                testThreadMutex();
                break;
            }
            case 9: {
                testThreadAtomic();
                break;
            }
            default:
                break;
        }
    }
}

}  // namespace test
