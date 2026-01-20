#pragma once
#include "se/krka/kahlua/integration/expose/MethodDebugInformation.h"
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace se {
namespace krka {
namespace kahlua {
namespace integration {
namespace doc {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class ApiInformation {
public:
 virtual ~ApiInformation() = default;
 List < Class < ? >> getAllClasses();

 List < Class < ? >> getRootClasses();

 List < Class < ? >> getChildrenForClass(Class < ? > var1);

 List<MethodDebugInformation> getMethodsForClass(Class<?> var1);

 List<MethodDebugInformation> getFunctionsForClass(Class<?> var1);
}
} // namespace doc
} // namespace integration
} // namespace kahlua
} // namespace krka
} // namespace se
