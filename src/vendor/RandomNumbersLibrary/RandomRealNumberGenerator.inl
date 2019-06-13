template<typename T>
RandomRealNumberGenerator<T>::RandomRealNumberGenerator(const T & min, const T & max)
{
    setNewRange(min, max);
}

template<typename T>
void RandomRealNumberGenerator<T>::setNewRange(const T & min, const T & max)
{
    if (max >= min)
        mRandom = std::uniform_real_distribution<T>(min, max);
    else
        mRandom = std::uniform_real_distribution<T>(max, min);
}

template<typename T>
void RandomRealNumberGenerator<T>::setNewRange(const std::pair<T, T> & range)
{
    setNewRange(range.first, range.second);
}

template<typename T>
T RandomRealNumberGenerator<T>::getMin() const
{
    return mRandom.min();
}

template<typename T>
T RandomRealNumberGenerator<T>::getMax() const
{
    return mRandom.max();
}

template<typename T>
std::pair<T, T> RandomRealNumberGenerator<T>::getRange() const
{
    return std::pair<T, T>(mRandom.min(), mRandom.max());
}

template<typename T>
T RandomRealNumberGenerator<T>::generateRandom()
{
    return mRandom(getEngine());
}

template<typename T>
T RandomRealNumberGenerator<T>::operator()()
{
    return mRandom(getEngine());
}
