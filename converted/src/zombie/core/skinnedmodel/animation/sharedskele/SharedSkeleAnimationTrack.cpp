#include "zombie/core/skinnedmodel/animation/sharedskele/SharedSkeleAnimationTrack.h"

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace animation {
namespace sharedskele {

void SharedSkeleAnimationTrack::set(AnimTrackSampler sampler, float fps) {
 // TODO: Implement set
}

float SharedSkeleAnimationTrack::getTotalTime() {
 // TODO: Implement getTotalTime
 return 0;
}

bool SharedSkeleAnimationTrack::isLooped() {
 // TODO: Implement isLooped
 return false;
}

void SharedSkeleAnimationTrack::moveToTime(float time) {
 // TODO: Implement moveToTime
}

float SharedSkeleAnimationTrack::getCurrentTime() {
 // TODO: Implement getCurrentTime
 return 0;
}

void SharedSkeleAnimationTrack::getBoneMatrix(int boneIdx, Matrix4f out_matrix) {
 // TODO: Implement getBoneMatrix
}

int SharedSkeleAnimationTrack::getNumBones() {
 // TODO: Implement getNumBones
 return 0;
}

void SharedSkeleAnimationTrack::sampleAtTime_NonLooped(Matrix4f matrix4f, int int3, float float0) {
 // TODO: Implement sampleAtTime_NonLooped
}

void SharedSkeleAnimationTrack::sampleAtTime_Looped(Matrix4f matrix4f, int int3, float float0) {
 // TODO: Implement sampleAtTime_Looped
}

void SharedSkeleAnimationTrack::sampleBoneData(int int2, int int1, int int3, float float0, bool boolean0, Matrix4f matrix4f) {
 // TODO: Implement sampleBoneData
}

} // namespace sharedskele
} // namespace animation
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
