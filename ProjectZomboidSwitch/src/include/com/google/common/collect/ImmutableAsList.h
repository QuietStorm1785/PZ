#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtCompatible.h"
#include "com/google/common/annotations/GwtIncompatible.h"
#include "com/google/common/collect/ImmutableAsList/SerializedForm.h"
#include <fstream>
#include <iostream>

namespace com {
namespace google {
namespace common {
namespace collect {


class ImmutableAsList {
public:
   abstract ImmutableCollection<E> delegateCollection();

    bool contains(void* target) {
      return this.delegateCollection().contains(target);
   }

    int size() {
      return this.delegateCollection().size();
   }

    bool isEmpty() {
      return this.delegateCollection().empty();
   }

    bool isPartialView() {
      return this.delegateCollection().isPartialView();
   }

    void readObject(ObjectInputStream stream) {
      throw InvalidObjectException("Use SerializedForm");
   }

    void* writeReplace() {
      return std::make_shared<SerializedForm>(this.delegateCollection());
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
