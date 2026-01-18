#include "zombie/core/skinnedmodel/animation/debug/AnimationPlayerRecorder.h"

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace animation {
namespace debug {

public
AnimationPlayerRecorder::AnimationPlayerRecorder(IsoGameCharacter owner) {
 // TODO: Implement AnimationPlayerRecorder
 return nullptr;
}

void AnimationPlayerRecorder::beginLine(int frameNo) {
 // TODO: Implement beginLine
}

void AnimationPlayerRecorder::endLine() {
 // TODO: Implement endLine
}

void AnimationPlayerRecorder::discardRecording() {
 // TODO: Implement discardRecording
}

PrintStream
AnimationPlayerRecorder::openFileStream(const std::string &key, bool append,
 Consumer<String> fileNameConsumer) {
 // TODO: Implement openFileStream
 return nullptr;
}

std::string
AnimationPlayerRecorder::getTimeStampedFilePath(const std::string &string) {
 // TODO: Implement getTimeStampedFilePath
 return "";
}

std::string
AnimationPlayerRecorder::getTimeStampedFileName(const std::string &string) {
 // TODO: Implement getTimeStampedFileName
 return "";
}

return AnimationPlayerRecorder::getStartupTimeStamp() {
 // TODO: Implement getStartupTimeStamp
 return nullptr;
}

std::string AnimationPlayerRecorder::getStartupTimeStamp() {
 // TODO: Implement getStartupTimeStamp
 return "";
}

void AnimationPlayerRecorder::logAnimWeights(List<AnimationTrack> list,
 int[] ints, float[] floats,
 Vector2 vector) {
 // TODO: Implement logAnimWeights
}

void AnimationPlayerRecorder::logAnimNode(LiveAnimNode liveNode) {
 // TODO: Implement logAnimNode
}

void AnimationPlayerRecorder::logActionState(ActionState state,
 List<ActionState> childStates) {
 // TODO: Implement logActionState
}

void AnimationPlayerRecorder::logAIState(
 State state, List<StateMachine.SubstateSlot> subStates) {
 // TODO: Implement logAIState
}

void AnimationPlayerRecorder::logAnimState(AnimState state) {
 // TODO: Implement logAnimState
}

void AnimationPlayerRecorder::logVariables(IAnimationVariableSource varSource) {
 // TODO: Implement logVariables
}

void AnimationPlayerRecorder::logCharacterPos() {
 // TODO: Implement logCharacterPos
}

IsoGameCharacter AnimationPlayerRecorder::getOwner() {
 // TODO: Implement getOwner
 return nullptr;
}

bool AnimationPlayerRecorder::isRecording() {
 // TODO: Implement isRecording
 return false;
}

void AnimationPlayerRecorder::setRecording(bool value) {
 // TODO: Implement setRecording
}

} // namespace debug
} // namespace animation
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
