#include <string>
#include "zombie/ui/UI_BodyPart.h"

namespace zombie {
namespace ui {

public UI_BodyPart::UI_BodyPart(BodyPartType var1, int var2, int var3, const std::string& var4, IsoGameCharacter var5, bool var6) {
    // TODO: Implement UI_BodyPart
    return nullptr;
}

void UI_BodyPart::onMouseMoveOutside(double var1, double var3) {
    // TODO: Implement onMouseMoveOutside
}

void UI_BodyPart::render() {
    // Legacy render is now handled by ImGuiRender
    ImGuiRender();
}

void UI_BodyPart::ImGuiRender() {
    if (!isVisible()) return;
    ImGui::Begin("Body Part", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
    ImGui::Text("Body Part: %s", BodyPartType.getName().c_str());
    ImGui::End();
}

} // namespace ui
} // namespace zombie
