#include "imgui.h"
void zombie::ui::DialogButton::ImGuiRender() {
    if (!visible || !enabled) return;
    ImGui::SetCursorPos(ImVec2((float)x, (float)y));
    if (ImGui::Button(text.c_str(), ImVec2(width, height))) {
        clicked = true;
        // TODO: Call MessageTarget/ButtonClicked logic as needed
    }
}
#include <string>
#include "zombie/ui/DialogButton.h"

namespace zombie {
namespace ui {

public DialogButton::DialogButton(UIElement var1, float var2, float var3, const std::string& var4, const std::string& var5) {
    // TODO: Implement DialogButton
    return nullptr;
}

public DialogButton::DialogButton(UIEventHandler var1, int var2, int var3, const std::string& var4, const std::string& var5) {
    // TODO: Implement DialogButton
    return nullptr;
}

bool DialogButton::onMouseDown(double var1, double var3) {
    // TODO: Implement onMouseDown
    return false;
}

bool DialogButton::onMouseMove(double var1, double var3) {
    // TODO: Implement onMouseMove
    return false;
}

void DialogButton::onMouseMoveOutside(double var1, double var3) {
    // TODO: Implement onMouseMoveOutside
}

bool DialogButton::onMouseUp(double var1, double var3) {
    // TODO: Implement onMouseUp
    return false;
}

void DialogButton::render() {
    // TODO: Implement render
}

new DialogButton::Color() {
    // TODO: Implement Color
    return nullptr;
}

new DialogButton::Color() {
    // TODO: Implement Color
    return nullptr;
}

} // namespace ui
} // namespace zombie
