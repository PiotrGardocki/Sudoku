#ifndef INDEXERROR_HPP
#define INDEXERROR_HPP

#include <stdexcept>

class IndexError : public std::runtime_error
{
public:
    IndexError(unsigned short row, unsigned short column);
};

#endif // INDEXERROR_HPP
