#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "javax/xml/bind/annotation/XmlRootElement.h"

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace advancedanimation {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class AnimTransition {
public:
 std::string m_Target;
 std::string m_AnimName;
 float m_SyncAdjustTime = 0.0F;
 float m_blendInTime = Float.POSITIVE_INFINITY;
 float m_blendOutTime = Float.POSITIVE_INFINITY;
 float m_speedScale = Float.POSITIVE_INFINITY;
 public List<AnimCondition> m_Conditions = std::make_unique<ArrayList<>>();
}
} // namespace advancedanimation
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
