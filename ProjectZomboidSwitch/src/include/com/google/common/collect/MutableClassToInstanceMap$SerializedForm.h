#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <fstream>
#include <iostream>

namespace com {
namespace google {
namespace common {
namespace collect {


class MutableClassToInstanceMap {
public:
   private const Map<Class<? : public B>, B> backingMap;
    static const long serialVersionUID = 0L;

   MutableClassToInstanceMap$SerializedForm(Map<Class<? : public B>, B> backingMap) {
      this.backingMap = backingMap;
   }

    void* readResolve() {
      return MutableClassToInstanceMap.create(this.backingMap);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
