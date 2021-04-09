#pragma once

// Inspired by CMB (Climbing Mont Blanc)
// https://climb.idi.ntnu.no/#/howto
//
// Martin Tysseland - 08.04.2021
// Class to generate random numbers using std::subtract_with_carry_engine
// http://www.cplusplus.com/reference/random/subtract_with_carry_engine/
// Examples:
// {
//     RandomEngine re;
//     cout << "Random int [2, 7]: " << re.getRandInt(2, 7) << "\n";
//     cout << "Random char ['a', 'e']: " << re.getRandChar('a', 'e') << "\n";
//     cout << "Random number: " << re.rand() << "\n";
// }

#include <cassert>
#include <ctime>
#include <random>

class RandomEngine {
   private:
    std::subtract_with_carry_engine<unsigned int, 24, 10, 24> engine;

   public:
    RandomEngine() { engine.seed(static_cast<unsigned int>(time(nullptr))); }
    RandomEngine(unsigned int s) { engine.seed(s); }
    RandomEngine(int s) : RandomEngine{static_cast<unsigned int>(s)} {}
    ~RandomEngine() = default;
    void setSeed(unsigned int s) { engine.seed(s); }
    void discard(unsigned int n = 1) { engine.discard(n); }
    unsigned int getMax() const { return engine.max(); }
    unsigned int getMin() const { return engine.min(); }
    unsigned int getRand() { return engine(); }
    char getRandChar(char from, char to) {
        assert(from < to);
        return (engine() % (to - from + 1)) + from;
    }
    unsigned char getRandUchar(unsigned char from, unsigned char to) {
        assert(from < to);
        return (engine() % (to - from + 1)) + from;
    }
    int getRandInt(int from, int to) {
        assert(from < to);
        return (engine() % (to - from + 1)) + from;
    }
    unsigned int getRandUint(unsigned int from, unsigned int to) {
        assert(from < to);
        return (engine() % (to - from + 1)) + from;
    }
    size_t getRandSize_t(size_t from, size_t to) {
        assert(from < to);
        float fTmp = static_cast<float>(engine()) / (engine.max() + 1);
        return (fTmp * (to - from + 1)) + from;
    }
    float getRandFloat(float from, float to) {
        assert(from < to);
        float fTmp = static_cast<float>(engine()) / engine.max();
        return (fTmp * (to - from)) + from;
    }
    double getRandDouble(double from, double to) {
        assert(from < to);
        double dTmp = static_cast<float>(engine()) / engine.max();
        return (dTmp * (to - from)) + from;
    }
};
