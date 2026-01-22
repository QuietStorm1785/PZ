#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "javax/xml/bind/annotation/XmlTransient.h"
#include "zombie/core/skinnedmodel/advancedanimation/AnimEvent/AnimEventTime.h"

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace advancedanimation {


class AnimEvent {
public:
    std::string m_EventName;
    AnimEventTime m_Time = AnimEventTime.Percentage;
    float m_TimePc;
    std::string m_ParameterValue;
    std::string m_SetVariable1;
    std::string m_SetVariable2;

    std::string toString() {
      return std::string.format("%s { %s }", this.getClass().getName(), this.toDetailsString());
   }

    std::string toDetailsString() {
      return std::string.format(
         "Details: %s %s, time: %s",
         this.m_EventName,
         this.m_ParameterValue,
         this.m_Time == AnimEventTime.Percentage ? float.toString(this.m_TimePc) : this.m_Time.name()
      );
   }
}
} // namespace advancedanimation
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
