#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <fstream>
#include <iostream>

namespace se {
namespace krka {
namespace kahlua {
namespace integration {
namespace processor {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class MethodParameterInformation {
public:
 static const MethodParameterInformation EMPTY = new MethodParameterInformation(Collections.EMPTY_LIST);
 static const long serialVersionUID = -3059552311721486815L;
 private List<String> parameterNames;

 public MethodParameterInformation(List<String> list) {
 this->parameterNames = list;
 }

 std::string getName(int int0) {
 return int0 >= this->parameterNames.size() ? "arg" + (int0 + 1) : this->parameterNames.get(int0);
 }
}
} // namespace processor
} // namespace integration
} // namespace kahlua
} // namespace krka
} // namespace se
