#pragma once
#include <stack>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace runtime {
namespace property {

class SingleMapNodeProperty {
public:
   private SingleMapNodeProperty$std::stack<T> parent;
    T value;

   private SingleMapNodeProperty$std::stack(SingleMapNodeProperty$std::stack<T> parent, T value) {
      this.parent = parent;
      this.value = value;
   }

   private SingleMapNodeProperty$std::stack(T value) {
      this.value = value;
   }

   private static <T> void push(ThreadLocal<SingleMapNodeProperty$std::stack<T>> holder, T value) {
      SingleMapNodeProperty$std::stack<T> parent = holder.get();
      if (parent == nullptr) {
         holder.set(new SingleMapNodeProperty$std::stack<>(value));
      } else {
         holder.set(new SingleMapNodeProperty$std::stack<>(parent, value));
      }
   }

   private static <T> T pop(ThreadLocal<SingleMapNodeProperty$std::stack<T>> holder) {
      SingleMapNodeProperty$std::stack<T> current = holder.get();
      if (current.parent == nullptr) {
         holder.remove();
      } else {
         holder.set(current.parent);
      }

      return current.value;
   }
}
} // namespace property
} // namespace runtime
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
