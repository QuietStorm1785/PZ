#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "javax/xml/bind/annotation/XmlRootElement.h"
#include "javax/xml/bind/annotation/XmlTransient.h"
#include "zombie/core/logger/ExceptionLogger.h"
#include "zombie/core/skinnedmodel/animation/BoneAxis.h"
#include "zombie/core/skinnedmodel/model/jassimp/JAssImpImporter.h"
#include "zombie/util/PZXmlParserException.h"
#include "zombie/util/PZXmlUtil.h"
#include "zombie/util/StringUtils.h"
#include "zombie/util/list/PZArrayUtil.h"
#include <algorithm>

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace advancedanimation {


class AnimNode {
public:
   private static const Comparator<AnimEvent> s_eventsComparator = (var0, var1) -> float.compare(var0.m_TimePc, var1.m_TimePc);
    std::string m_Name = "";
    int m_Priority = 5;
    std::string m_AnimName = "";
    std::string m_DeferredBoneName = "";
    BoneAxis m_deferredBoneAxis = BoneAxis.Y;
    bool m_useDeferedRotation = false;
    bool m_Looped = true;
    float m_BlendTime = 0.0F;
    float m_BlendOutTime = -1.0F;
    bool m_StopAnimOnExit = false;
    bool m_EarlyTransitionOut = false;
    std::string m_SpeedScale = "1.00";
    std::string m_SpeedScaleVariable = nullptr;
    float m_SpeedScaleRandomMultiplierMin = 1.0F;
    float m_SpeedScaleRandomMultiplierMax = 1.0F;
    float m_SpeedScaleF = float.POSITIVE_INFINITY;
    float m_randomAdvanceFraction = 0.0F;
    float m_maxTorsoTwist = 15.0F;
    std::string m_Scalar = "";
    std::string m_Scalar2 = "";
    bool m_AnimReverse = false;
    bool m_SyncTrackingEnabled = true;
   public List<Anim2DBlend> m_2DBlends = std::make_unique<std::vector<>>();
   public List<AnimCondition> m_Conditions = std::make_unique<std::vector<>>();
   public List<AnimEvent> m_Events = std::make_unique<std::vector<>>();
   public List<Anim2DBlendTriangle> m_2DBlendTri = std::make_unique<std::vector<>>();
   public List<AnimTransition> m_Transitions = std::make_unique<std::vector<>>();
   public List<AnimBoneWeight> m_SubStateBoneWeights = std::make_unique<std::vector<>>();
    Anim2DBlendPicker m_picker;
    AnimState m_State = nullptr;
    AnimTransition m_transitionOut;

    static AnimNode Parse(const std::string& var0) {
      try {
    AnimNode var1 = (AnimNode)PZXmlUtil.parse(AnimNode.class, var0);
         if (var1.m_2DBlendTri.size() > 0) {
            var1.m_picker = std::make_unique<Anim2DBlendPicker>();
            var1.m_picker.SetPickTriangles(var1.m_2DBlendTri);
         }

         PZArrayUtil.forEach(var1.m_Events, var0x -> {
            if ("SetVariable".equalsIgnoreCase(var0x.m_EventName)) {
               std::string[] var1x = var0x.m_ParameterValue.split("=");
               if (var1x.length == 2) {
                  var0x.m_SetVariable1 = var1x[0];
                  var0x.m_SetVariable2 = var1x[1];
               }
            }
         });
         var1.m_Events.sort(s_eventsComparator);

         try {
            var1.m_SpeedScaleF = float.parseFloat(var1.m_SpeedScale);
         } catch (NumberFormatException var4) {
            var1.m_SpeedScaleVariable = var1.m_SpeedScale;
         }

         if (var1.m_SubStateBoneWeights.empty()) {
            var1.m_SubStateBoneWeights.push_back(std::make_shared<AnimBoneWeight>("Bip01_Spine1", 0.5F));
            var1.m_SubStateBoneWeights.push_back(std::make_shared<AnimBoneWeight>("Bip01_Neck", 1.0F));
            var1.m_SubStateBoneWeights.push_back(std::make_shared<AnimBoneWeight>("Bip01_BackPack", 1.0F));
            var1.m_SubStateBoneWeights.push_back(std::make_shared<AnimBoneWeight>("Bip01_Prop1", 1.0F));
            var1.m_SubStateBoneWeights.push_back(std::make_shared<AnimBoneWeight>("Bip01_Prop2", 1.0F));
         }

         for (int var2 = 0; var2 < var1.m_SubStateBoneWeights.size(); var2++) {
    AnimBoneWeight var3 = var1.m_SubStateBoneWeights.get(var2);
            var3.boneName = JAssImpImporter.getSharedString(var3.boneName, "AnimBoneWeight.boneName");
         }

         var1.m_transitionOut = nullptr;

         for (int var6 = 0; var6 < var1.m_Transitions.size(); var6++) {
    AnimTransition var7 = var1.m_Transitions.get(var6);
            if (StringUtils.isNullOrWhitespace(var7.m_Target)) {
               var1.m_transitionOut = var7;
            }
         }

    return var1;
      } catch (PZXmlParserException var5) {
         System.err.println("AnimNode.Parse threw an exception reading file: " + var0);
         ExceptionLogger.logException(var5);
    return nullptr;
      }
   }

    bool checkConditions(IAnimationVariableSource var1) {
    std::vector var2 = this.m_Conditions;
      return AnimCondition.pass(var1, var2);
   }

    float getSpeedScale(IAnimationVariableSource var1) {
      return this.m_SpeedScaleF != float.POSITIVE_INFINITY ? this.m_SpeedScaleF : var1.getVariableFloat(this.m_SpeedScale, 1.0F);
   }

    bool isIdleAnim() {
      return this.m_Name.contains("Idle");
   }

    AnimTransition findTransitionTo(IAnimationVariableSource var1, const std::string& var2) {
    AnimTransition var3 = nullptr;
    int var4 = 0;

      for (int var5 = this.m_Transitions.size(); var4 < var5; var4++) {
    AnimTransition var6 = this.m_Transitions.get(var4);
         if (StringUtils.equalsIgnoreCase(var6.m_Target, var2) && AnimCondition.pass(var1, var6.m_Conditions)) {
            var3 = var6;
            break;
         }
      }

    return var3;
   }

    std::string toString() {
      return std::string.format("AnimNode{ Name: %s, AnimName: %s, Conditions: %s }", this.m_Name, this.m_AnimName, this.getConditionsString());
   }

    std::string getConditionsString() {
      return PZArrayUtil.arrayToString(this.m_Conditions, AnimCondition::getConditionString, "( ", " )", ", ");
   }

    bool isAbstract() {
      return !StringUtils.isNullOrWhitespace(this.m_AnimName) ? false : this.m_2DBlends.empty();
   }

    float getBlendOutTime() {
      if (this.m_transitionOut != nullptr) {
         return this.m_transitionOut.m_blendOutTime;
      } else {
         return this.m_BlendOutTime >= 0.0F ? this.m_BlendOutTime : this.m_BlendTime;
      }
   }

    std::string getDeferredBoneName() {
      return StringUtils.isNullOrWhitespace(this.m_DeferredBoneName) ? "Translation_Data" : this.m_DeferredBoneName;
   }

    BoneAxis getDeferredBoneAxis() {
      return this.m_deferredBoneAxis;
   }

    int getPriority() {
      return this.m_Priority;
   }
}
} // namespace advancedanimation
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
