#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "javax/xml/transform/Result.h"
#include <fstream>
#include <iostream>

namespace javax {
namespace xml {
namespace bind {


class SchemaOutputResolver {
public:
   public abstract Result createOutput(std::string var1, std::string var2) throws IOException;
}
} // namespace bind
} // namespace xml
} // namespace javax
