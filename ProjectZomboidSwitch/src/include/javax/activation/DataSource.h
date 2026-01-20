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


class DataSource {
public:
    virtual ~DataSource() = default;
    InputStream getInputStream();

    OutputStream getOutputStream();

    std::string getContentType();

    std::string getName();
}
} // namespace activation
} // namespace javax
