#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/v2/runtime/unmarshaller/UnmarshallingContext/State.h"

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace runtime {
namespace unmarshaller {


class Discarder : public Loader {
public:
    static const Loader INSTANCE = std::make_shared<Discarder>();

    private Discarder() {
      super(false);
   }

    void childElement(State state, TagName ea) {
      state.setTarget(nullptr);
      state.setLoader(this);
   }
}
} // namespace unmarshaller
} // namespace runtime
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
