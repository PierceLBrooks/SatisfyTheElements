
// Author: Pierce Brooks

#include <STE/Random.hpp>

STE::Random::Random(unsigned int seed)
{
    initialize(seed);
}

STE::Random::~Random()
{

}

void STE::Random::initialize(unsigned int seed)
{
    rng.seed(seed);
}

bool STE::Random::getBool()
{
    return (getInt(0,1)==0);
}

bool STE::Random::getBool(float chance)
{
    if ((chance < 0.0f) || (chance > 1.0f))
    {
        return false;
    }
    return (getFloat(0.0f,1.0f)<chance);
}

int STE::Random::getInt(int minimum, int maximum)
{
    distributorInt = std::uniform_int_distribution<int>(minimum, maximum);
    return distributorInt(rng);
}

float STE::Random::getFloat(float minimum, float maximum)
{
    distributorFloat = std::uniform_real_distribution<float>(minimum, maximum);
    return distributorFloat(rng);
}
