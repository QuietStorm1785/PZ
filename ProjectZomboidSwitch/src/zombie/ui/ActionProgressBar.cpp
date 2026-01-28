#include "zombie/ui/ActionProgressBar.h"

namespace zombie {
namespace ui {

public ActionProgressBar::ActionProgressBar(int var1, int var2) {
    // TODO: Implement ActionProgressBar
    return nullptr;
}

void ActionProgressBar::render() {
    // Legacy render is now handled by ImGuiRender
    ImGuiRender();
}

void ActionProgressBar::ImGuiRender() {
    if (!isVisible()) return;
    ImGui::Begin("Action Progress", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
    ImGui::Text("Action Progress");
    ImGui::ProgressBar(deltaValue, ImVec2(200, 24));
    ImGui::End();
}

void ActionProgressBar::setValue(float var1) {
    // TODO: Implement setValue
}

float ActionProgressBar::getValue() {
    // TODO: Implement getValue
    return 0;
}

void ActionProgressBar::update(int var1) {
    // TODO: Implement update
}

void ActionProgressBar::updateScreenPos(int var1) {
    // TODO: Implement updateScreenPos
}

} // namespace ui
} // namespace zombie
