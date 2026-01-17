#pragma once
#include "java/text/SimpleDateFormat.h"
#include "zombie/ai/State.h"
#include "zombie/ai/StateMachine.h"
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
#include <cstdint>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace animation {
namespace debug {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

/**
 * Used for recording the activity of an AnimationPlayer
 */
class AnimationPlayerRecorder {
public:
  bool m_isRecording = false;
  const AnimationTrackRecordingFrame m_animationTrackFrame;
  const AnimationNodeRecordingFrame m_animationNodeFrame;
  const AnimationVariableRecordingFrame m_animationVariableFrame;
  const IsoGameCharacter m_character;
  static std::string s_startupTimeStamp = null;
  static const SimpleDateFormat s_fileNameSdf =
      new SimpleDateFormat("yy-MM-dd_HH-mm");

public
  AnimationPlayerRecorder(IsoGameCharacter owner) {
    this.m_character = owner;
    std::string string0 = this.m_character.getUID();
    std::string string1 = string0 + "_AnimRecorder";
    this.m_animationTrackFrame =
        new AnimationTrackRecordingFrame(string1 + "_Track");
    this.m_animationNodeFrame =
        new AnimationNodeRecordingFrame(string1 + "_Node");
    this.m_animationVariableFrame =
        new AnimationVariableRecordingFrame(string1 + "_Vars");
  }

  void beginLine(int frameNo) {
    this.m_animationTrackFrame.reset();
    this.m_animationTrackFrame.setFrameNumber(frameNo);
    this.m_animationNodeFrame.reset();
    this.m_animationNodeFrame.setFrameNumber(frameNo);
    this.m_animationVariableFrame.reset();
    this.m_animationVariableFrame.setFrameNumber(frameNo);
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

  static PrintStream openFileStream(const std::string &key, bool append,
                                    Consumer<String> fileNameConsumer) {
    std::string string = getTimeStampedFilePath(key);

    try {
      fileNameConsumer.accept(string);
      File file = new File(string);
      return new PrintStream(new FileOutputStream(file, append));
    } catch (FileNotFoundException fileNotFoundException) {
      DebugLog.General.error(
          "Exception thrown trying to create animation player recording file.");
      DebugLog.General.error(fileNotFoundException);
      fileNotFoundException.printStackTrace();
      return null;
    }
  }

  static std::string getTimeStampedFilePath(const std::string &string) {
    return LoggerManager.getLogsDir() + File.separator +
           getTimeStampedFileName(string) + ".csv";
  }

  static std::string getTimeStampedFileName(const std::string &string) {
    return getStartupTimeStamp();
  }

  static std::string getStartupTimeStamp() {
    if (s_startupTimeStamp == nullptr) {
      s_startupTimeStamp =
          s_fileNameSdf.format(Calendar.getInstance().getTime());
    }

    return s_startupTimeStamp;
  }

  void logAnimWeights(List<AnimationTrack> list, int[] ints, float[] floats,
                      Vector2 vector) {
    this.m_animationTrackFrame.logAnimWeights(list, ints, floats, vector);
  }

  void logAnimNode(LiveAnimNode liveNode) {
    if (liveNode.isTransitioningIn()) {
      this.m_animationNodeFrame.logWeight(
          "transition(" + liveNode.getTransitionFrom() + "->" +
              liveNode.getName() + ")",
          liveNode.getTransitionLayerIdx(), liveNode.getTransitionInWeight());
    }

    this.m_animationNodeFrame.logWeight(
        liveNode.getName(), liveNode.getLayerIdx(), liveNode.getWeight());
  }

  void logActionState(ActionState state, List<ActionState> childStates) {
    this.m_animationNodeFrame.logActionState(state, childStates);
  }

  void logAIState(State state, List<StateMachine.SubstateSlot> subStates) {
    this.m_animationNodeFrame.logAIState(state, subStates);
  }

  void logAnimState(AnimState state) {
    this.m_animationNodeFrame.logAnimState(state);
  }

  void logVariables(IAnimationVariableSource varSource) {
    this.m_animationVariableFrame.logVariables(varSource);
  }

  void logCharacterPos() {
    IsoPlayer player = IsoPlayer.getInstance();
    IsoGameCharacter character = this.getOwner();
    Vector3 vector0 = player.getPosition(new Vector3());
    Vector3 vector1 = character.getPosition(new Vector3());
    Vector3 vector2 = vector0.sub(vector1, new Vector3());
    this.m_animationNodeFrame.logCharacterToPlayerDiff(vector2);
  }

  IsoGameCharacter getOwner() { return this.m_character; }

  bool isRecording() { return this.m_isRecording; }

  void setRecording(bool value) {
    if (this.m_isRecording != value) {
      this.m_isRecording = value;
      DebugLog.General.println("AnimationPlayerRecorder %s.",
                               this.m_isRecording ? "recording" : "stopped");
    }
  }
}
} // namespace debug
} // namespace animation
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
