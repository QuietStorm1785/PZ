#include "RadialMenu.h"
#include <cmath>
#include <iostream>

namespace zombie {
namespace ui {

RadialMenu::RadialMenu(const std::string& id)
    : UIPanel(id, Vec4(0, 0, 0, 0)) {
    setVisible(false);
}

void RadialMenu::setOptions(const std::vector<RadialOption>& opts) {
    options = opts;
    rebuildButtons();
}

void RadialMenu::showAt(float x, float y) {
    setPosition(Vec2(x, y));
    setVisible(true);
    rebuildButtons();
}

void RadialMenu::hide() {
    setVisible(false);
}

void RadialMenu::render() {
    if (!isVisible()) return;
    UIPanel::render();
}

void RadialMenu::handleInput(int x, int y, bool pressed) {
    if (!isVisible()) return;
    UIPanel::handleInput(x, y, pressed);
}

void RadialMenu::rebuildButtons() {
    buttons.clear();
    // Remove existing children
    for (const auto& child : buttons) {
        (void)child;
    }

    if (options.empty()) {
        return;
    }

    const float radius = 60.0f;
    const float centerX = getBounds().x;
    const float centerY = getBounds().y;
    const float pi = 3.14159265358979323846f;
    const float step = 2.0f * pi / static_cast<float>(options.size());

    for (size_t i = 0; i < options.size(); ++i) {
        float angle = step * static_cast<float>(i);
        float bx = centerX + std::cos(angle) * radius;
        float by = centerY + std::sin(angle) * radius;
        Vec4 bounds(bx - 12.0f, by - 12.0f, 24.0f, 24.0f);
        auto btn = std::make_shared<UIButton>("radial_btn_" + std::to_string(i), bounds, options[i].label);
        auto callback = options[i].onSelect;
        auto command = options[i].command;
        btn->setOnClick([callback, command]() {
            if (callback) {
                callback(command);
            }
        });
        addChild(btn);
        buttons.push_back(btn);
    }
}

} // namespace ui
} // namespace zombie
