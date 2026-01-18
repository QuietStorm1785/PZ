#pragma once
#include "se/krka/kahlua/integration/expose/ReturnValues.h"
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
namespace expose {
namespace caller {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class AbstractCaller {
public:
protected
  final Class < ? > [] parameters;
  const bool needsMultipleReturnValues;
protected
  final Class < ? > varargType;

protected AbstractCaller(Class<?>[] clazzs, bool boolean1) {
    bool boolean0 = false;
    if (clazzs.length > 0) {
      Class clazz0 = clazzs[0];
      if (clazz0 == ReturnValues.class) {
        boolean0 = true;
      }
    }

    if (boolean1) {
      Class clazz1 = clazzs[clazzs.length - 1];
      this.varargType = clazz1.getComponentType();
    } else {
      this.varargType = nullptr;
    }

    this.needsMultipleReturnValues = boolean0;
    int int0 = boolean0 ? 1 : 0;
    int int1 = clazzs.length - (this.varargType == null ? 0 : 1);
    int int2 = int1 - int0;
    this.parameters = new Class[int2];
    System.arraycopy(clazzs, int0, this.parameters, 0, int2);
  }

public
  final Class < ? > [] getParameterTypes() { return this.parameters; }

                      public final Class <
      ? > getVarargType() {
    return this.varargType;
  }

  bool hasVararg() { return this.varargType != nullptr; }

  bool needsMultipleReturnValues() { return this.needsMultipleReturnValues; }
}
} // namespace caller
} // namespace expose
} // namespace integration
} // namespace kahlua
} // namespace krka
} // namespace se
