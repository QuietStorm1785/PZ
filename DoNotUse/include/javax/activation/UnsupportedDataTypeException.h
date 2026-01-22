#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <fstream>
#include <iostream>

namespace javax {
namespace activation {


class UnsupportedDataTypeException : public IOException {
public:
    public UnsupportedDataTypeException() {
   }

    public UnsupportedDataTypeException(const std::string& s) {
      super(s);
   }
}
} // namespace activation
} // namespace javax
