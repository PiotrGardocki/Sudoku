#ifndef RANDOMGENERATORBASE_HPP_
#define RANDOMGENERATORBASE_HPP_

#include <random>

class RandomGeneratorBase
{
protected:
    RandomGeneratorBase() = default;

    std::mt19937 & getEngine() const;

private:
    static thread_local std::mt19937 mEngine;
};

#endif // RANDOMGENERATORBASE_HPP_
