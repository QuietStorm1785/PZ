#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/config/BooleanConfigOption.h"
#include "zombie/core/Core.h"
#include "zombie/debug/options/IDebugOption.h"
#include "zombie/debug/options/IDebugOptionGroup.h"

namespace zombie {
namespace debug {


class BooleanDebugOption : public BooleanConfigOption {
public:
    IDebugOptionGroup m_parent;
    const bool m_debugOnly;

    public BooleanDebugOption(const std::string& var1, bool var2, bool var3) {
      super(var1, var3);
      this.m_debugOnly = var2;
   }

    bool getValue() {
      return !Core.bDebug && this.isDebugOnly() ? super.getDefaultValue() : super.getValue();
   }

    bool isDebugOnly() {
      return this.m_debugOnly;
   }

    IDebugOptionGroup getParent() {
      return this.m_parent;
   }

    void setParent(IDebugOptionGroup var1) {
      this.m_parent = var1;
   }
}
} // namespace debug
} // namespace zombie
