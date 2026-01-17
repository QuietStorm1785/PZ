#pragma once
#include <string>
#include <vector>
#include <memory>
#include <functional>
#include <algorithm>

namespace zombie {
namespace ui {

struct Vec2 {
    float x, y;
    Vec2(float x = 0, float y = 0) : x(x), y(y) {}
};

struct Vec4 {
    float x, y, z, w;
    Vec4(float x = 0, float y = 0, float z = 0, float w = 0) : x(x), y(y), z(z), w(w) {}
};

class UIElement {
public:
    UIElement(const std::string& id, Vec4 bounds);
    virtual ~UIElement() = default;
    
    virtual void render() = 0;
    virtual void update(float deltaTime) {}
    virtual void handleInput(int x, int y, bool pressed) {}
    
    void setPosition(Vec2 pos);
    void setSize(Vec2 size);
    Vec4 getBounds() const { return bounds; }
    
    bool isMouseOver(int x, int y) const;
    bool isVisible() const { return visible; }
    void setVisible(bool v) { visible = v; }
    
    std::string getId() const { return id; }

protected:
    std::string id;
    Vec4 bounds; // x, y, width, height
    bool visible;
};

class UIButton : public UIElement {
public:
    UIButton(const std::string& id, Vec4 bounds, const std::string& label);
    
    void render() override;
    void handleInput(int x, int y, bool pressed) override;
    
    void setOnClick(std::function<void()> callback) { onClickCallback = callback; }
    void setLabel(const std::string& text) { label = text; }
    const std::string& getLabel() const { return label; }
    
private:
    std::string label;
    bool hovered;
    std::function<void()> onClickCallback;
};

class UIPanel : public UIElement {
public:
    UIPanel(const std::string& id, Vec4 bounds);
    
    void render() override;
    void update(float deltaTime) override;
    
    void addChild(std::shared_ptr<UIElement> child);
    void removeChild(const std::string& childId);
    
private:
    std::vector<std::shared_ptr<UIElement>> children;
};

class UITextBox : public UIElement {
public:
    UITextBox(const std::string& id, Vec4 bounds);
    
    void render() override;
    void handleInput(int x, int y, bool pressed) override;
    
    void setText(const std::string& text) { content = text; }
    const std::string& getText() const { return content; }
    
private:
    std::string content;
    bool focused;
};

class UIManager {
public:
    static UIManager& getInstance() {
        static UIManager instance;
        return instance;
    }
    
    void initialize();
    void shutdown();
    
    void addElement(std::shared_ptr<UIElement> element);
    void removeElement(const std::string& id);
    std::shared_ptr<UIElement> getElement(const std::string& id);
    
    void render();
    void update(float deltaTime);
    void handleInput(int x, int y, bool pressed);
    
    bool isUIElementUnderMouse(int x, int y);
    
private:
    UIManager() = default;
    ~UIManager() = default;
    
    std::vector<std::shared_ptr<UIElement>> elements;
};

} // namespace ui
} // namespace zombie
