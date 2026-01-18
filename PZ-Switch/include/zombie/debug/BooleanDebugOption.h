#pragma once
#include "zombie/config/BooleanConfigOption.h"
#include "zombie/core/Core.h"
#include "zombie/debug/options/IDebugOption.h"
#include "zombie/debug/options/IDebugOptionGroup.h"
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace debug {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class BooleanDebugOption : public BooleanConfigOption {
public:
 IDebugOptionGroup m_parent;
 const bool m_debugOnly;

public
 BooleanDebugOption(const std::string &name, bool debugOnly,
 bool defaultValue) {
 super(name, defaultValue);
 this->m_debugOnly = debugOnly;
 }

 bool getValue() {
 return !Core.bDebug && this->isDebugOnly() ? super.getDefaultValue()
 : super.getValue();
 }

 bool isDebugOnly() { return this->m_debugOnly; }

 IDebugOptionGroup getParent() { return this->m_parent; }

 void setParent(IDebugOptionGroup parent) { this->m_parent = parent; }
}
} // namespace debug
} // namespace zombie
