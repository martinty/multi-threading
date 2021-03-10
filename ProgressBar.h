#pragma once

#include <iostream>
#include <string>

class ProgressBar {
   private:
    const std::string percent =
        "0%   10   20   30   40   50   60   70   80   90   100%";
    const std::string axis =
        "|----|----|----|----|----|----|----|----|----|----|";
    const size_t range;
    const long double rangeDouble;
    size_t progress = 0;
    unsigned int symbols = 0;
    const unsigned int scale = 50;
    bool valid = true;

   public:
    ProgressBar(size_t r)
        : range{r}, rangeDouble{static_cast<long double>(r)} {};
    ProgressBar(int r) : ProgressBar{static_cast<size_t>(r)} {};
    ProgressBar(unsigned int r) : ProgressBar{static_cast<size_t>(r)} {};
    ~ProgressBar() = default;
    void operator++() {
        if (!valid) {
            std::cout << "Progress bar is no longer valid" << std::endl;
            return;
        } else if (progress == 0) {
            std::cout << percent << "\n" << axis << "\n*" << std::flush;
        }
        progress++;
        unsigned int p = (progress / rangeDouble) * scale;
        if (p > symbols) {
            std::cout << std::string(p - symbols, '*') << std::flush;
            symbols = p;
        }
        if (progress == range) {
            std::cout << std::string(scale - symbols, '*') << std::endl;
            valid = false;
        }
    }
    void operator++(int) { ++(*this); }
};
