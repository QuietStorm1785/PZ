#include <string>
#include "zombie/vehicles/UI3DScene$SceneCharacter.h"

namespace zombie {
namespace vehicles {

SceneObjectRenderData UI3DScene$SceneCharacter::renderMain() {
    // TODO: Implement renderMain
    return nullptr;
}

Matrix4f UI3DScene$SceneCharacter::getLocalTransform(Matrix4f var1) {
    // TODO: Implement getLocalTransform
    return nullptr;
}

Matrix4f UI3DScene$SceneCharacter::getAttachmentTransform(const std::string& var1, Matrix4f var2) {
    // TODO: Implement getAttachmentTransform
    return nullptr;
}

int UI3DScene$SceneCharacter::hitTestBone(int var1, Ray var2, Ray var3, Matrix4f var4) {
    // TODO: Implement hitTestBone
    return 0;
}

std::string UI3DScene$SceneCharacter::pickBone(float var1, float var2) {
    // TODO: Implement pickBone
    return "";
}

Matrix4f UI3DScene$SceneCharacter::getBoneMatrix(const std::string& var1, Matrix4f var2) {
    // TODO: Implement getBoneMatrix
    return nullptr;
}

PositionRotation UI3DScene$SceneCharacter::getBoneAxis(const std::string& var1, PositionRotation var2) {
    // TODO: Implement getBoneAxis
    return nullptr;
}

} // namespace vehicles
} // namespace zombie
