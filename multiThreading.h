#pragma once

#include <atomic>
#include <mutex>
#include <numeric>
#include <vector>

#ifndef INT_MIN
#define INT_MIN (-2147483647 - 1)
#endif
#ifndef INT_MAX
#define INT_MAX 2147483647
#endif
#ifndef uint
typedef unsigned int uint;
#endif

int getIntInput(int lower = INT_MIN, int upper = INT_MAX);
void worker(const int nT, std::mutex& mtx);
void normalSum(int& a);
void atomicSum(std::atomic_int& a);
void sumSquareElement(const std::vector<int>& vec, const uint begin,
                      const uint end, double& sum);
void testWorker();
void testNormalSum();
void testAtomicSum();
void testVectorWork();
void testThreadsMenu();
