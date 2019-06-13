#ifndef RANDOMINTEGERGENERATOR_HPP_
#define RANDOMINTEGERGENERATOR_HPP_

#include <type_traits>
#include <utility>
#include "RandomGeneratorBase.hpp"

template <typename T>
class RandomIntegerGenerator : private RandomGeneratorBase
{
    static_assert(std::is_integral<T>::value, "RandomIntegerGenerator has to be integral type");

public:
    RandomIntegerGenerator(const T & min, const T & max);

    void setNewRange(const T & min, const T & max);
    void setNewRange(const std::pair<T, T> & range);

    T getMin() const;
    T getMax() const;
    std::pair<T, T> getRange() const;

    T generateRandom();
    T operator()();

private:
    std::uniform_int_distribution<T> mRandom;
};

#include "RandomIntegerGenerator.inl"

#endif // RANDOMINTEGERGENERATOR_HPP_
