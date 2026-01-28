#include "imgui.h"
void zombie::ui::UIServerToolbox::ImGuiRender() {
    if (!visible || !enabled) return;
    ImGui::SetNextWindowPos(ImVec2((float)x, (float)y), ImGuiCond_Always);
    ImGui::SetNextWindowSize(ImVec2(width, height), ImGuiCond_Always);
    ImGui::Begin(uiname.empty() ? "ServerToolbox" : uiname.c_str(), nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings);
    ImGui::Text("%s", Translator::getText("IGUI_ServerToolBox_Title").c_str());
    std::string ip = (externalAddress.empty() ? Translator::getText("IGUI_ServerToolBox_IPUnknown") : externalAddress);
    ImGui::Text("%s", Translator::getText("IGUI_ServerToolBox_ExternalIP", ip).c_str());
    if (!incomingConnections.empty()) {
        std::string user = incomingConnections[0];
        if (!user.empty()) {
            ImGui::Text("%s", Translator::getText("IGUI_ServerToolBox_UserConnecting", user).c_str());
        }
    }
    ImGui::End();
}
#include <string>
#include "zombie/ui/UIServerToolbox.h"

namespace zombie {
namespace ui {

public UIServerToolbox::UIServerToolbox(int var1, int var2) {
    // TODO: Implement UIServerToolbox
    return nullptr;
}

void UIServerToolbox::render() {
    // TODO: Implement render
}

void UIServerToolbox::update() {
    // TODO: Implement update
}

void UIServerToolbox::UpdateViewPos() {
    // TODO: Implement UpdateViewPos
}

void UIServerToolbox::PrintLine(const std::string& var1) {
    // TODO: Implement PrintLine
}

void UIServerToolbox::shutdown() {
    // TODO: Implement shutdown
}

void UIServerToolbox::DoubleClick(const std::string& var1, int var2, int var3) {
    // TODO: Implement DoubleClick
}

void UIServerToolbox::ModalClick(const std::string& var1, const std::string& var2) {
    // TODO: Implement ModalClick
}

void UIServerToolbox::Selected(const std::string& var1, int var2, int var3) {
    // TODO: Implement Selected
}

} // namespace ui
} // namespace zombie
