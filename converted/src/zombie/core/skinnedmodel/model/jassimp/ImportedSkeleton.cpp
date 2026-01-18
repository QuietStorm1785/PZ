#include "zombie/core/skinnedmodel/model/jassimp/ImportedSkeleton.h"

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace model {
namespace jassimp {

private ImportedSkeleton::ImportedSkeleton() {
 // TODO: Implement ImportedSkeleton
 return nullptr;
}

ImportedSkeleton ImportedSkeleton::process(ImportedSkeletonParams importedSkeletonParams) {
 // TODO: Implement process
 return nullptr;
}

void ImportedSkeleton::processAiScene(ImportedSkeletonParams importedSkeletonParams) {
 // TODO: Implement processAiScene
}

void ImportedSkeleton::processAnimationOld(AiAnimation aiAnimation, bool boolean0) {
 // TODO: Implement processAnimationOld
}

void ImportedSkeleton::processAnimation(AiAnimation aiAnimation, bool boolean2, float float4, Quaternion quaternion1) {
 // TODO: Implement processAnimation
}

void ImportedSkeleton::addDefaultAnimTrack(const std::string& string, int int0, Quaternion quaternion, Vector3f vector3f1, ArrayList<Keyframe> arrayList, float float0) {
 // TODO: Implement addDefaultAnimTrack
}

bool ImportedSkeleton::doesParentBoneHaveAnimFrames(TFloatArrayList[] tFloatArrayLists, ArrayList<ArrayList<AiNodeAnim>> arrayList, int int1) {
 // TODO: Implement doesParentBoneHaveAnimFrames
 return false;
}

bool ImportedSkeleton::doesBoneHaveAnimFrames(TFloatArrayList[] tFloatArrayLists, ArrayList<ArrayList<AiNodeAnim>> arrayList1, int int0) {
 // TODO: Implement doesBoneHaveAnimFrames
 return false;
}

void ImportedSkeleton::collectBoneFrames(AiAnimation aiAnimation, TFloatArrayList[] tFloatArrayLists, ArrayList<ArrayList<AiNodeAnim>> arrayList1) {
 // TODO: Implement collectBoneFrames
}

int ImportedSkeleton::getParentBoneIdx(int int0) {
 // TODO: Implement getParentBoneIdx
 return 0;
}

int ImportedSkeleton::getNumBoneAncestors(int int2) {
 // TODO: Implement getNumBoneAncestors
 return 0;
}

Vector3f ImportedSkeleton::GetKeyFramePosition(AiNodeAnim aiNodeAnim, float float0, double double0) {
 // TODO: Implement GetKeyFramePosition
 return nullptr;
}

Quaternion ImportedSkeleton::GetKeyFrameRotation(AiNodeAnim aiNodeAnim, float float0, double double0) {
 // TODO: Implement GetKeyFrameRotation
 return nullptr;
}

Vector3f ImportedSkeleton::GetKeyFrameScale(AiNodeAnim aiNodeAnim, float float0, double var3) {
 // TODO: Implement GetKeyFrameScale
 return nullptr;
}

} // namespace jassimp
} // namespace model
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
