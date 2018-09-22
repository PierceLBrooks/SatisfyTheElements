
// Author: Pierce Brooks

#ifndef STE_RANDOM_HPP
#define STE_RANDOM_HPP

#include <random>

namespace STE
{
    class Random
    {
    public:
        Random(unsigned int seed = 0);
        ~Random();
        void initialize(unsigned int seed = 0);
        bool getBool();
        bool getBool(float chance);
        int getInt(int minimum, int maximum);
        float getFloat(float minimum, float maximum);
    private:
        std::mt19937 rng;
        std::uniform_int_distribution<int> distributorInt;
        std::uniform_real_distribution<float> distributorFloat;
    };
}

#endif // STE_RANDOM_HPP
