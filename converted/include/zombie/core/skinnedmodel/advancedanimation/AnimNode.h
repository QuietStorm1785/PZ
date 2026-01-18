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
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class AnimNode {
public:
 private static Comparator<AnimEvent> s_eventsComparator = (animEvent1, animEvent0) -> Float.compare(animEvent1.m_TimePc, animEvent0.m_TimePc);
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
 float m_SpeedScaleF = Float.POSITIVE_INFINITY;
 float m_randomAdvanceFraction = 0.0F;
 float m_maxTorsoTwist = 15.0F;
 std::string m_Scalar = "";
 std::string m_Scalar2 = "";
 bool m_AnimReverse = false;
 bool m_SyncTrackingEnabled = true;
 public List<Anim2DBlend> m_2DBlends = std::make_unique<ArrayList<>>();
 public List<AnimCondition> m_Conditions = std::make_unique<ArrayList<>>();
 public List<AnimEvent> m_Events = std::make_unique<ArrayList<>>();
 public List<Anim2DBlendTriangle> m_2DBlendTri = std::make_unique<ArrayList<>>();
 public List<AnimTransition> m_Transitions = std::make_unique<ArrayList<>>();
 public List<AnimBoneWeight> m_SubStateBoneWeights = std::make_unique<ArrayList<>>();
 Anim2DBlendPicker m_picker;
 AnimState m_State = nullptr;
 AnimTransition m_transitionOut;

 /**
 * Loads an AnimNode from the specified source. The source can either be a file path, or a File GUID.
 * @return The deserialized AnimNode instance, or NULL if failed.
 */
 static AnimNode Parse(const std::string& source) {
 try {
 AnimNode animNode = PZXmlUtil.parse(AnimNode.class, source);
 if (animNode.m_2DBlendTri.size() > 0) {
 animNode.m_picker = std::make_unique<Anim2DBlendPicker>();
 animNode.m_picker.SetPickTriangles(animNode.m_2DBlendTri);
 }

 PZArrayUtil.forEach(animNode.m_Events, animEvent -> {
 if ("SetVariable".equalsIgnoreCase(animEvent.m_EventName) {
 String[] strings = animEvent.m_ParameterValue.split("=");
 if (strings.length == 2) {
 animEvent.m_SetVariable1 = strings[0];
 animEvent.m_SetVariable2 = strings[1];
 }
 }
 });
 animNode.m_Events.sort(s_eventsComparator);

 try {
 animNode.m_SpeedScaleF = Float.parseFloat(animNode.m_SpeedScale);
 } catch (NumberFormatException numberFormatException) {
 animNode.m_SpeedScaleVariable = animNode.m_SpeedScale;
 }

 if (animNode.m_SubStateBoneWeights.empty()) {
 animNode.m_SubStateBoneWeights.add(new AnimBoneWeight("Bip01_Spine1", 0.5F);
 animNode.m_SubStateBoneWeights.add(new AnimBoneWeight("Bip01_Neck", 1.0F);
 animNode.m_SubStateBoneWeights.add(new AnimBoneWeight("Bip01_BackPack", 1.0F);
 animNode.m_SubStateBoneWeights.add(new AnimBoneWeight("Bip01_Prop1", 1.0F);
 animNode.m_SubStateBoneWeights.add(new AnimBoneWeight("Bip01_Prop2", 1.0F);
 }

 for (int int0 = 0; int0 < animNode.m_SubStateBoneWeights.size(); int0++) {
 AnimBoneWeight animBoneWeight = animNode.m_SubStateBoneWeights.get(int0);
 animBoneWeight.boneName = JAssImpImporter.getSharedString(animBoneWeight.boneName, "AnimBoneWeight.boneName");
 }

 animNode.m_transitionOut = nullptr;

 for (int int1 = 0; int1 < animNode.m_Transitions.size(); int1++) {
 AnimTransition animTransition = animNode.m_Transitions.get(int1);
 if (StringUtils.isNullOrWhitespace(animTransition.m_Target) {
 animNode.m_transitionOut = animTransition;
 }
 }

 return animNode;
 } catch (PZXmlParserException pZXmlParserException) {
 System.err.println("AnimNode.Parse threw an exception reading file: " + source);
 ExceptionLogger.logException(pZXmlParserException);
 return nullptr;
 }
 }

 bool checkConditions(IAnimationVariableSource varSource) {
 std::vector list = this->m_Conditions;
 return AnimCondition.pass(varSource, list);
 }

 float getSpeedScale(IAnimationVariableSource varSource) {
 return this->m_SpeedScaleF != Float.POSITIVE_INFINITY ? this->m_SpeedScaleF : varSource.getVariableFloat(this->m_SpeedScale, 1.0F);
 }

 /**
 * Returns TRUE if this AnimNode represents an Idle animation. TODO: Make this a flag in the AnimNode, instead of relying on the name
 */
 bool isIdleAnim() {
 return this->m_Name.contains("Idle");
 }

 AnimTransition findTransitionTo(IAnimationVariableSource varSource, const std::string& targetName) {
 AnimTransition animTransition0 = nullptr;
 int int0 = 0;

 for (int int1 = this->m_Transitions.size(); int0 < int1; int0++) {
 AnimTransition animTransition1 = this->m_Transitions.get(int0);
 if (StringUtils.equalsIgnoreCase(animTransition1.m_Target, targetName) && AnimCondition.pass(varSource, animTransition1.m_Conditions) {
 animTransition0 = animTransition1;
 break;
 }
 }

 return animTransition0;
 }

 std::string toString() {
 return String.format("AnimNode{ Name: %s, AnimName: %s, Conditions: %s }", this->m_Name, this->m_AnimName, this->getConditionsString());
 }

 std::string getConditionsString() {
 return PZArrayUtil.arrayToString(this->m_Conditions, AnimCondition::getConditionString, "( ", " )", ", ");
 }

 bool isAbstract() {
 return !StringUtils.isNullOrWhitespace(this->m_AnimName) ? false : this->m_2DBlends.empty();
 }

 float getBlendOutTime() {
 if (this->m_transitionOut != nullptr) {
 return this->m_transitionOut.m_blendOutTime;
 } else {
 return this->m_BlendOutTime >= 0.0F ? this->m_BlendOutTime : this->m_BlendTime;
 }
 }

 std::string getDeferredBoneName() {
 return StringUtils.isNullOrWhitespace(this->m_DeferredBoneName) ? "Translation_Data" : this->m_DeferredBoneName;
 }

 BoneAxis getDeferredBoneAxis() {
 return this->m_deferredBoneAxis;
 }

 int getPriority() {
 return this->m_Priority;
 }
}
} // namespace advancedanimation
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
