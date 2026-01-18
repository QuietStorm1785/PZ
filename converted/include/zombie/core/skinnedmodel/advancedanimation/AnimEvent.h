#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "javax/xml/bind/annotation/XmlTransient.h"

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace advancedanimation {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


/**
 * class AnimEvent Used to set a game variable from an animation node. eg. Set a sword's collision box to Active during a swing animation, then Inactive once swing is done. Holds a time, name, and value The time is measured as a fraction of the animation's time. This means that scaling an animation's speed scales the Events as well.
 */
class AnimEvent {
public:
 std::string m_EventName;
 public AnimEvent.AnimEventTime m_Time = AnimEvent.AnimEventTime.Percentage;
 float m_TimePc;
 std::string m_ParameterValue;
 std::string m_SetVariable1;
 std::string m_SetVariable2;

 std::string toString() {
 return String.format("%s { %s }", this->getClass().getName(), this->toDetailsString());
 }

 std::string toDetailsString() {
 return String.format(
 "Details: %s %s, time: %s",
 this->m_EventName,
 this->m_ParameterValue,
 this->m_Time == AnimEvent.AnimEventTime.Percentage ? Float.toString(this->m_TimePc) : this->m_Time.name()
 );
 }

 public static enum AnimEventTime {
 Percentage,
 Start,
 End;
 }
}
} // namespace advancedanimation
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
