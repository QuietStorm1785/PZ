#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <fstream>
#include <iostream>

namespace gnu {
namespace trove {
namespace strategy {


class HashingStrategy {
public:
    virtual ~HashingStrategy() = default;
    long serialVersionUID = 5674097166776615540L;

    int computeHashCode(T var1);

    bool equals(T var1, T var2);
}
} // namespace strategy
} // namespace trove
} // namespace gnu
