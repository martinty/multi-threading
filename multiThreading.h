#pragma once

#include <atomic>
#include <mutex>
#include <vector>

#ifndef uint
typedef unsigned int uint;
#endif

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
