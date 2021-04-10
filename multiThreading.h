#pragma once

#include <numeric>

#ifndef INT_MIN
#define INT_MIN (-2147483647 - 1)
#endif
#ifndef INT_MAX
#define INT_MAX 2147483647
#endif

int getIntInput(int lower = INT_MIN, int upper = INT_MAX);
void testThreads();
