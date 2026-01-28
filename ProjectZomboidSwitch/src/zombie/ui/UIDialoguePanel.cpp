#include "imgui.h"
void zombie::ui::UIDialoguePanel::ImGuiRender() {
    if (!visible || !enabled) return;
    ImGui::SetNextWindowPos(ImVec2((float)x, (float)y), ImGuiCond_Always);
    ImGui::SetNextWindowSize(ImVec2(width, height), ImGuiCond_Always);
    ImGui::Begin(uiname.empty() ? "DialoguePanel" : uiname.c_str(), nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings);
    ImGui::Text("Dialogue Panel");
    // TODO: Render textures and children with ImGui::Image, ImGui::Child, etc.
    ImGui::End();
}
#include "zombie/ui/UIDialoguePanel.h"

namespace zombie {
namespace ui {

public UIDialoguePanel::UIDialoguePanel(float var1, float var2, float var3, float var4) {
    // TODO: Implement UIDialoguePanel
    // Use Rect and Color for nestedItems and color logic.
    return nullptr;
}

void UIDialoguePanel::Nest(UIElement var1, int var2, int var3, int var4, int var5) {
    // TODO: Implement Nest
}

void UIDialoguePanel::render() {
    // TODO: Implement render
}

void UIDialoguePanel::update() {
    // TODO: Implement update
}

} // namespace ui
} // namespace zombie
