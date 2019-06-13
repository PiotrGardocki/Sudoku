#ifndef RANDOMREALNUMBERGENERATOR_HPP_
#define RANDOMREALNUMBERGENERATOR_HPP_

#include <type_traits>
#include <utility>
#include "RandomGeneratorBase.hpp"

template <typename T>
class RandomRealNumberGenerator : private RandomGeneratorBase
{
    static_assert(std::is_floating_point<T>::value, "RandomRealNumberGenerator has to be floating point type");

public:
    RandomRealNumberGenerator(const T & min, const T & max);

    void setNewRange(const T & min, const T & max);
    void setNewRange(const std::pair<T, T> & range);

    T getMin() const;
    T getMax() const;
    std::pair<T, T> getRange() const;

    T generateRandom();
    T operator()();

private:
    std::uniform_real_distribution<T> mRandom;
};

#include "RandomRealNumberGenerator.inl"

#endif // RANDOMREALNUMBERGENERATOR_HPP_
