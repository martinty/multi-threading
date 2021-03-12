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
    size_t symbols = 0;
    const size_t scale = 50;
    bool valid = true;

    void pre(size_t n) {
        if (!valid) {
            std::cout << "Progress bar is no longer valid!" << std::endl;
        } else if (n < progress) {
            std::cout << "Not valid movement!" << std::endl;
            std::cout << "Progress bar is no longer valid!" << std::endl;
            valid = false;
        } else if (progress == 0) {
            std::cout << percent << "\n" << axis << "\n*" << std::flush;
        }
    }
    void post() {
        if (progress >= range) {
            std::cout << std::string(scale - symbols, '*') << std::endl;
            valid = false;
        } else {
            unsigned int p = (progress / rangeDouble) * scale;
            if (p > symbols) {
                std::cout << std::string(p - symbols, '*') << std::flush;
                symbols = p;
            }
        }
    }

   public:
    ProgressBar(size_t r)
        : range{r}, rangeDouble{static_cast<long double>(r)} {};
    ProgressBar(int r) : ProgressBar{static_cast<size_t>(r)} {};
    ProgressBar(unsigned int r) : ProgressBar{static_cast<size_t>(r)} {};
    ~ProgressBar() = default;
    void move(size_t n) {
        pre(n);
        if (valid) {
            progress = n + 1;
            post();
        }
    }
    void operator++() { move(progress); }
    void operator++(int) { move(progress); }
    bool isValid() const { return valid; }
    size_t getRange() const { return range; }
    size_t getProgress() const { return progress; }
};
