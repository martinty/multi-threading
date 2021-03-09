#include "multiThreading.h"

#include <atomic>
#include <chrono>
#include <functional>  // std::ref
#include <future>
#include <iostream>
#include <mutex>
#include <string>
#include <thread>
#include <vector>

#include "Walltime.h"

using namespace std;

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

void testThreads() {
    Walltime wt;
    int input = 1;
    while (input) {
        cout << "\n" << string(40, '-') << "\n";
        cout << "0) Exit\n";
        cout << "1) Run test threads\n";
        cout << "2) Normal sum with threads\n";
        cout << "3) Atomic sum with threads\n";
        cin >> input;
        switch (input) {
            case 1: {
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

                cout << "Thread work done!\n";
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
                cout << "Walltime: " << wt << "\n";

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
                cout << "Walltime: " << wt << "\n";

                break;
            }
            default:
                break;
        }
    }
}
