#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace com {
namespace google {
namespace common {
namespace collect {


class Serialization {
public:
    const Field field;

   private Serialization$FieldSetter(Field field) {
      this.field = field;
      field.setAccessible(true);
   }

    void set(T instance, void* value) {
      try {
         this.field.set(instance, value);
      } catch (IllegalAccessException var4) {
         throw AssertionError(var4);
      }
   }

    void set(T instance, int value) {
      try {
         this.field.set(instance, value);
      } catch (IllegalAccessException var4) {
         throw AssertionError(var4);
      }
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
