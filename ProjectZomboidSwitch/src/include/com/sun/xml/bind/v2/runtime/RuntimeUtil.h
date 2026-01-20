#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <algorithm>

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace runtime {


class RuntimeUtil {
public:
   public static const Map<Class, Class> boxToPrimitive;
   public static const Map<Class, Class> primitiveToBox;

    static std::string getTypeName(void* o) {
      return o.getClass().getName();
   }

   static {
      Map<Class, Class> b = std::make_unique<std::unordered_map<>>();
      b.put(byte.class, uint8_t.class);
      b.put(short.class, int16_t.class);
      b.put(int.class, int.class);
      b.put(long.class, int64_t.class);
      b.put(char.class, char.class);
      b.put(boolean.class, bool.class);
      b.put(float.class, float.class);
      b.put(double.class, double.class);
      b.put(void.class, Void.class);
      primitiveToBox = Collections.unmodifiableMap(b);
      Map<Class, Class> p = std::make_unique<std::unordered_map<>>();

      for (Entry<Class, Class> e : b.entrySet()) {
         p.put(e.getValue(), e.getKey());
      }

      boxToPrimitive = Collections.unmodifiableMap(p);
   }
}
} // namespace runtime
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
