#pragma once

#include <iostream>
#include <string>

class ProgressBar {
   private:
    std::string percent =
        "0%   10   20   30   40   50   60   70   80   90   100%";
    std::string axis = "|----|----|----|----|----|----|----|----|----|----|";
    unsigned int range;
    unsigned int stride;
    unsigned int progress;

   public:
    ProgressBar(unsigned int r) : range{r}, stride{r / 50}, progress{0} {
        if (stride < 1) {
            stride = 1;
        }
    };
    ~ProgressBar() = default;
    void reset(unsigned int r) { *this = ProgressBar{r}; }
    void operator++() {
        if (progress == 0) {
            std::cout << percent << "\n" << axis << "\n*" << std::flush;
        } else if (progress % stride == 0) {
            std::cout << '*' << std::flush;
        }
        if (++progress == range) {
            std::cout << '*' << std::endl;
        }
    }
    void operator++(int) { ++(*this); }
};
