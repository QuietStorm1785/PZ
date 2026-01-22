#pragma once
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
namespace unmarshaller {

class ChildLoader {
public:
    const Loader loader;
    const Receiver receiver;

    public ChildLoader(Loader loader, Receiver receiver) {
      assert loader != nullptr;

      this.loader = loader;
      this.receiver = receiver;
   }
}
} // namespace unmarshaller
} // namespace runtime
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
