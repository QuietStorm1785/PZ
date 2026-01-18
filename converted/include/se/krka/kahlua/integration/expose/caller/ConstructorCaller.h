#pragma once
#include "se/krka/kahlua/integration/expose/ReturnValues.h"
#include "se/krka/kahlua/integration/processor/DescriptorUtil.h"
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

class ConstructorCaller : public AbstractCaller {
public:
private
  final Constructor < ? > constructor;

public ConstructorCaller(Constructor<?> constructorx) {
    super(constructorx.getParameterTypes(), constructorx.isVarArgs());
    this.constructor = constructorx;
    constructorx.setAccessible(true);
    if (this.needsMultipleReturnValues()) {
      throw new RuntimeException("Constructor can not return multiple values");
    }
  }

  void call(void *var1, ReturnValues returnValues, Object[] objects) {
    returnValues.push(this.constructor.newInstance(objects));
  }

  bool hasSelf() { return false; }

  std::string getDescriptor() {
    return DescriptorUtil.getDescriptor(this.constructor);
  }

  bool equals(void *object) {
    if (this == object) {
      return true;
    } else if (object != nullptr && this.getClass() == object.getClass()) {
      ConstructorCaller constructorCaller1 = (ConstructorCaller)object;
            return this.constructor == constructorCaller1.constructor);
    } else {
      return false;
    }
  }

  int hashCode() { return this.constructor.hashCode(); }
}
} // namespace caller
} // namespace expose
} // namespace integration
} // namespace kahlua
} // namespace krka
} // namespace se
