#include <queue>
#include "zombie/ui/LoadingQueueUI.h"

namespace zombie {
namespace ui {

public LoadingQueueUI::LoadingQueueUI() {
    // TODO: Implement LoadingQueueUI
    return nullptr;
}

void LoadingQueueUI::update() {
    // TODO: Implement update
}

void LoadingQueueUI::onresize() {
    // TODO: Implement onresize
}

void LoadingQueueUI::render() {
    // Legacy render is now handled by ImGuiRender
    ImGuiRender();
}

void LoadingQueueUI::ImGuiRender() {
    if (!isVisible()) return;
    ImGui::Begin("Loading Queue", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
    ImGui::Text("%s", strLoadingQueue.c_str());
    ImGui::Text("%s", strQueuePlace.c_str());
    ImGui::End();
}

void LoadingQueueUI::setPlaceInQueue(int var1) {
    // TODO: Implement setPlaceInQueue
}

} // namespace ui
} // namespace zombie
