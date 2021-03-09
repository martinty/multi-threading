#include "multiThreading.h"

#include <atomic>
#include <chrono>
#include <cmath>
#include <functional>  // std::ref
#include <future>
#include <iostream>
#include <mutex>
#include <numeric>
#include <random>
#include <string>
#include <thread>
#include <vector>

#include "ProgressBar.h"
#include "Walltime.h"

using namespace std;

#ifndef uint
typedef unsigned int uint;
#endif

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

void testThreads() {
    Walltime wt;
    int input = 1;
    while (input) {
        cout << "\n" << string(40, '-') << "\n";
        cout << "0) Exit\n";
        cout << "1) Run test threads\n";
        cout << "2) Normal sum with threads\n";
        cout << "3) Atomic sum with threads\n";
        cout << "4) Sum the square of every element in vector\n";
        cin >> input;
        cout << endl;
        switch (input) {
            case 1: {
                wt.start();

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
                break;
            }
            case 2: {
                wt.start();

                int a = 0;
                thread t1{normalSum, ref(a)};
                thread t2{normalSum, ref(a)};

                t1.join();
                t2.join();

                cout << "a: " << a << "\n";
                wt.stop();
                cout << wt << "\n";

                break;
            }
            case 3: {
                wt.start();

                atomic_int a = 0;
                thread t1{atomicSum, ref(a)};
                thread t2{atomicSum, ref(a)};

                t1.join();
                t2.join();

                cout << "a: " << a << "\n";
                wt.stop();
                cout << wt << "\n";

                break;
            }
            case 4: {
                const uint N = 100'000'000;
                ProgressBar bar{N};
                vector<int> vec(N);
                cout << "Vector size: " << N << "\n"
                     << "Generate random numbers [-10, 10] for vector" << endl;
                for (uint i{0}; i < vec.size(); ++i) {
                    vec[i] = (rand() % 21) - 10;
                    ++bar;
                }
                cout << endl;

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
                    myThreads.push_back(thread{sumSquareElement, ref(vec),
                                               begin, end, ref(result[t])});
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

                break;
            }
            default:
                break;
        }
    }
}
