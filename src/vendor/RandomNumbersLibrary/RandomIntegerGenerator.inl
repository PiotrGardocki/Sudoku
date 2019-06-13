template<typename T>
RandomIntegerGenerator<T>::RandomIntegerGenerator(const T & min, const T & max)
{
    setNewRange(min, max);
}

template<typename T>
void RandomIntegerGenerator<T>::setNewRange(const T & min, const T & max)
{
    if (max >= min)
        mRandom = std::uniform_int_distribution<T>(min, max);
    else
        mRandom = std::uniform_int_distribution<T>(max, min);
}

template<typename T>
void RandomIntegerGenerator<T>::setNewRange(const std::pair<T, T> & range)
{
    setNewRange(range.first, range.second);
}

template<typename T>
T RandomIntegerGenerator<T>::getMin() const
{
    return mRandom.min();
}

template<typename T>
T RandomIntegerGenerator<T>::getMax() const
{
    return mRandom.max();
}

template<typename T>
std::pair<T, T> RandomIntegerGenerator<T>::getRange() const
{
    return std::pair<T, T>(mRandom.min(), mRandom.max());
}

template<typename T>
T RandomIntegerGenerator<T>::generateRandom()
{
    return mRandom(getEngine());
}

template<typename T>
inline T RandomIntegerGenerator<T>::operator()()
{
    return mRandom(getEngine());
}
