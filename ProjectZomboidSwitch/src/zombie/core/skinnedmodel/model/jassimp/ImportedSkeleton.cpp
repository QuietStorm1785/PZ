#include <string>
#include <vector>
#include "zombie\core\skinnedmodel\model\jassimp/ImportedSkeleton.h"

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace model {
namespace jassimp {

private ImportedSkeleton::ImportedSkeleton() {
    // TODO: Implement ImportedSkeleton
    return nullptr;
}

ImportedSkeleton ImportedSkeleton::process(ImportedSkeletonParams var0) {
    // TODO: Implement process
    return nullptr;
}

void ImportedSkeleton::processAiScene(ImportedSkeletonParams var1) {
    // TODO: Implement processAiScene
}

void ImportedSkeleton::processAnimationOld(AiAnimation var1, bool var2) {
    // TODO: Implement processAnimationOld
}

void ImportedSkeleton::processAnimation(AiAnimation var1, bool var2, float var3, Quaternion var4) {
    // TODO: Implement processAnimation
}

void ImportedSkeleton::addDefaultAnimTrack(const std::string& var1, int var2, Quaternion var3, Vector3f var4, std::vector<Keyframe> var5, float var6) {
    // TODO: Implement addDefaultAnimTrack
}

bool ImportedSkeleton::doesParentBoneHaveAnimFrames(std::vector<std::vector<float>>& var1, std::vector<std::vector<AiNodeAnim>> var2, int var3) {
    // TODO: Implement doesParentBoneHaveAnimFrames
    return false;
}

bool ImportedSkeleton::doesBoneHaveAnimFrames(std::vector<std::vector<float>>& var1, std::vector<std::vector<AiNodeAnim>> var2, int var3) {
    // TODO: Implement doesBoneHaveAnimFrames
    return false;
}

void ImportedSkeleton::collectBoneFrames(AiAnimation var1, std::vector<std::vector<float>>& var2, std::vector<std::vector<AiNodeAnim>> var3) {
    // TODO: Implement collectBoneFrames
}

int ImportedSkeleton::getParentBoneIdx(int var1) {
    // TODO: Implement getParentBoneIdx
    return 0;
}

int ImportedSkeleton::getNumBoneAncestors(int var1) {
    // TODO: Implement getNumBoneAncestors
    return 0;
}

Vector3f ImportedSkeleton::GetKeyFramePosition(AiNodeAnim var1, float var2, double var3) {
    // TODO: Implement GetKeyFramePosition
    return nullptr;
}

Quaternion ImportedSkeleton::GetKeyFrameRotation(AiNodeAnim var1, float var2, double var3) {
    // TODO: Implement GetKeyFrameRotation
    return nullptr;
}

Vector3f ImportedSkeleton::GetKeyFrameScale(AiNodeAnim var1, float var2, double var3) {
    // TODO: Implement GetKeyFrameScale
    return nullptr;
}

} // namespace jassimp
} // namespace model
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
