#include <string>
#include "zombie/ui/ModalDialog.h"

namespace zombie {
namespace ui {

public ModalDialog::ModalDialog(const std::string& var1, const std::string& var2, bool var3) {
    // TODO: Implement ModalDialog
    return nullptr;
    // Legacy render is now handled by ImGuiRender
    ImGuiRender();
}

void ModalDialog::ImGuiRender() {
    if (!isVisible()) return;
    ImGui::Begin("Modal Dialog", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
    ImGui::Text("%s", Name.c_str());
    if (ImGui::Button("OK")) {
        setVisible(false);
    }
    ImGui::End();
}

void ModalDialog::ButtonClicked(const std::string& var1) {
    // TODO: Implement ButtonClicked
}

void ModalDialog::Clicked(const std::string& var1) {
    // TODO: Implement Clicked
}

} // namespace ui
} // namespace zombie
