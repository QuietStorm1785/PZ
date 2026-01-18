#include "UI.h"

namespace zombie {
namespace ui {

UIElement::UIElement(const std::string& id, Vec4 bounds)
    : id(id), bounds(bounds), visible(true) {
}

void UIElement::setPosition(Vec2 pos) {
    bounds.x = pos.x;
    bounds.y = pos.y;
}

void UIElement::setSize(Vec2 size) {
    bounds.z = size.x;
    bounds.w = size.y;
}

bool UIElement::isMouseOver(int x, int y) const {
    return x >= bounds.x && x <= bounds.x + bounds.z &&
           y >= bounds.y && y <= bounds.y + bounds.w;
}

UIButton::UIButton(const std::string& id, Vec4 bounds, const std::string& label)
    : UIElement(id, bounds), label(label), hovered(false) {
}

void UIButton::render() {
    if (!visible) return;
    // Button rendering will be implemented
}

void UIButton::handleInput(int x, int y, bool pressed) {
    if (isMouseOver(x, y) && pressed && onClickCallback) {
        onClickCallback();
    }
}

UIPanel::UIPanel(const std::string& id, Vec4 bounds)
    : UIElement(id, bounds) {
}

void UIPanel::render() {
    if (!visible) return;
    for (auto& child : children) {
        if (child) child->render();
    }
}

void UIPanel::update(float deltaTime) {
    for (auto& child : children) {
        if (child) child->update(deltaTime);
    }
}

void UIPanel::addChild(std::shared_ptr<UIElement> child) {
    if (child) {
        children.push_back(child);
    }
}

void UIPanel::removeChild(const std::string& childId) {
    auto it = std::remove_if(children.begin(), children.end(),
        [&childId](const std::shared_ptr<UIElement>& e) { return e->getId() == childId; });
    children.erase(it, children.end());
}

UITextBox::UITextBox(const std::string& id, Vec4 bounds)
    : UIElement(id, bounds), focused(false) {
}

void UITextBox::render() {
    if (!visible) return;
    // TextBox rendering will be implemented
}

void UITextBox::handleInput(int x, int y, bool pressed) {
    if (isMouseOver(x, y)) {
        focused = pressed;
    }
}

void UIManager::initialize() {
}

void UIManager::shutdown() {
    elements.clear();
}

void UIManager::addElement(std::shared_ptr<UIElement> element) {
    if (element) {
        elements.push_back(element);
    }
}

void UIManager::removeElement(const std::string& id) {
    auto it = std::remove_if(elements.begin(), elements.end(),
        [&id](const std::shared_ptr<UIElement>& e) { return e->getId() == id; });
    elements.erase(it, elements.end());
}

std::shared_ptr<UIElement> UIManager::getElement(const std::string& id) {
    for (auto& element : elements) {
        if (element && element->getId() == id) {
            return element;
        }
    }
    return nullptr;
}

void UIManager::render() {
    for (auto& element : elements) {
        if (element) element->render();
    }
}

void UIManager::update(float deltaTime) {
    for (auto& element : elements) {
        if (element) element->update(deltaTime);
    }
}

void UIManager::handleInput(int x, int y, bool pressed) {
    for (auto& element : elements) {
        if (element) element->handleInput(x, y, pressed);
    }
}

bool UIManager::isUIElementUnderMouse(int x, int y) {
    for (auto& element : elements) {
        if (element && element->isMouseOver(x, y)) {
            return true;
        }
    }
    return false;
}

} // namespace ui
} // namespace zombie
