#pragma once
#include <stack>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "java/text/SimpleDateFormat.h"
#include "zombie/ai/State.h"
#include "zombie/ai/StateMachine/SubstateSlot.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/characters/action/ActionState.h"
#include "zombie/core/logger/LoggerManager.h"
#include "zombie/core/skinnedmodel/advancedanimation/AnimState.h"
#include "zombie/core/skinnedmodel/advancedanimation/IAnimationVariableSource.h"
#include "zombie/core/skinnedmodel/advancedanimation/LiveAnimNode.h"
#include "zombie/core/skinnedmodel/animation/AnimationTrack.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/iso/Vector2.h"
#include "zombie/iso/Vector3.h"
#include <algorithm>
#include <fstream>
#include <iostream>

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace animation {
namespace debug {


class AnimationPlayerRecorder {
public:
    bool m_isRecording = false;
    const AnimationTrackRecordingFrame m_animationTrackFrame;
    const AnimationNodeRecordingFrame m_animationNodeFrame;
    const AnimationVariableRecordingFrame m_animationVariableFrame;
    const IsoGameCharacter m_character;
    static std::string s_startupTimeStamp = nullptr;
    static const SimpleDateFormat s_fileNameSdf = std::make_shared<SimpleDateFormat>("yy-MM-dd_HH-mm");

    public AnimationPlayerRecorder(IsoGameCharacter var1) {
      this.m_character = var1;
    std::string var2 = this.m_character.getUID();
    std::string var3 = var2 + "_AnimRecorder";
      this.m_animationTrackFrame = std::make_shared<AnimationTrackRecordingFrame>(var3 + "_Track");
      this.m_animationNodeFrame = std::make_shared<AnimationNodeRecordingFrame>(var3 + "_Node");
      this.m_animationVariableFrame = std::make_shared<AnimationVariableRecordingFrame>(var3 + "_Vars");
   }

    void beginLine(int var1) {
      this.m_animationTrackFrame.reset();
      this.m_animationTrackFrame.setFrameNumber(var1);
      this.m_animationNodeFrame.reset();
      this.m_animationNodeFrame.setFrameNumber(var1);
      this.m_animationVariableFrame.reset();
      this.m_animationVariableFrame.setFrameNumber(var1);
   }

    void endLine() {
      this.m_animationTrackFrame.writeLine();
      this.m_animationNodeFrame.writeLine();
      this.m_animationVariableFrame.writeLine();
   }

    void discardRecording() {
      this.m_animationTrackFrame.closeAndDiscard();
      this.m_animationNodeFrame.closeAndDiscard();
      this.m_animationVariableFrame.closeAndDiscard();
   }

    static PrintStream openFileStream(const std::string& var0, bool var1, Consumer<std::string> var2) {
    std::string var3 = getTimeStampedFilePath(var0);

      try {
         var2.accept(var3);
    File var4 = std::make_shared<File>(var3);
         return std::make_shared<PrintStream>(std::make_shared<FileOutputStream>(var4, var1));
      } catch (FileNotFoundException var5) {
         DebugLog.General.error("Exception thrown trying to create animation player recording file.");
         DebugLog.General.error(var5);
         var5.printStackTrace();
    return nullptr;
      }
   }

    static std::string getTimeStampedFilePath(const std::string& var0) {
      return LoggerManager.getLogsDir() + File.separator + getTimeStampedFileName(var0) + ".csv";
   }

    static std::string getTimeStampedFileName(const std::string& var0) {
    return getStartupTimeStamp();
   }

    static std::string getStartupTimeStamp() {
      if (s_startupTimeStamp == nullptr) {
         s_startupTimeStamp = s_fileNameSdf.format(Calendar.getInstance().getTime());
      }

    return s_startupTimeStamp;
   }

    void logAnimWeights(List<AnimationTrack> var1, int[] var2, float[] var3, Vector2 var4) {
      this.m_animationTrackFrame.logAnimWeights(var1, var2, var3, var4);
   }

    void logAnimNode(LiveAnimNode var1) {
      if (var1.isTransitioningIn()) {
         this.m_animationNodeFrame
            .logWeight("transition(" + var1.getTransitionFrom() + "->" + var1.getName() + ")", var1.getTransitionLayerIdx(), var1.getTransitionInWeight());
      }

      this.m_animationNodeFrame.logWeight(var1.getName(), var1.getLayerIdx(), var1.getWeight());
   }

    void logActionState(ActionState var1, List<ActionState> var2) {
      this.m_animationNodeFrame.logActionState(var1, var2);
   }

    void logAIState(State var1, List<SubstateSlot> var2) {
      this.m_animationNodeFrame.logAIState(var1, var2);
   }

    void logAnimState(AnimState var1) {
      this.m_animationNodeFrame.logAnimState(var1);
   }

    void logVariables(IAnimationVariableSource var1) {
      this.m_animationVariableFrame.logVariables(var1);
   }

    void logCharacterPos() {
    IsoPlayer var1 = IsoPlayer.getInstance();
    IsoGameCharacter var2 = this.getOwner();
    Vector3 var3 = var1.getPosition(std::make_shared<Vector3>());
    Vector3 var4 = var2.getPosition(std::make_shared<Vector3>());
    Vector3 var5 = var3.sub(var4, std::make_shared<Vector3>());
      this.m_animationNodeFrame.logCharacterToPlayerDiff(var5);
   }

    IsoGameCharacter getOwner() {
      return this.m_character;
   }

    bool isRecording() {
      return this.m_isRecording;
   }

    void setRecording(bool var1) {
      if (this.m_isRecording != var1) {
         this.m_isRecording = var1;
         DebugLog.General.println("AnimationPlayerRecorder %s.", this.m_isRecording ? "recording" : "stopped");
      }
   }
}
} // namespace debug
} // namespace animation
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
