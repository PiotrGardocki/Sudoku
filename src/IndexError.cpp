#include "IndexError.hpp"

#include <string>


IndexError::IndexError(unsigned short row, unsigned short column)
    : std::runtime_error(std::string("Given index (") + std::to_string(row) + ',' + std::to_string(column) + ") out of range [0,8]")
{
}
