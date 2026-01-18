#include "zombie/core/skinnedmodel/animation/debug/AnimationNodeRecordingFrame.h"

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace animation {
namespace debug {

public
AnimationNodeRecordingFrame::AnimationNodeRecordingFrame(
    const std::string &fileKey) {
  // TODO: Implement AnimationNodeRecordingFrame
  return nullptr;
}

void AnimationNodeRecordingFrame::logActionState(
    ActionState state, List<ActionState> childStates) {
  // TODO: Implement logActionState
}

void AnimationNodeRecordingFrame::logAIState(
    State state, List<StateMachine.SubstateSlot> subStates) {
  // TODO: Implement logAIState
}

void AnimationNodeRecordingFrame::logAnimState(AnimState state) {
  // TODO: Implement logAnimState
}

void AnimationNodeRecordingFrame::logCharacterToPlayerDiff(Vector3 diff) {
  // TODO: Implement logCharacterToPlayerDiff
}

void AnimationNodeRecordingFrame::writeHeader(StringBuilder logLine) {
  // TODO: Implement writeHeader
}

void AnimationNodeRecordingFrame::writeData(StringBuilder stringBuilder) {
  // TODO: Implement writeData
}

} // namespace debug
} // namespace animation
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
