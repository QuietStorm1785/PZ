#pragma once
#include "UI.h"
#include <string>
#include <vector>
#include <functional>
#include <memory>

namespace zombie {
namespace ui {

struct RadialOption {
 std::string command;
 std::string label;
 std::string hover;
 std::function<void(const std::string&)> onSelect;
};

class RadialMenu : public UIPanel {
public:
 explicit RadialMenu(const std::string& id);

 // Supply options; they are laid out evenly in a ring.
 void setOptions(const std::vector<RadialOption>& opts);

 // Show menu centered at screen-space position.
 void showAt(float x, float y);
 void hide();

 // UIElement overrides
 void render() override;
 void handleInput(int x, int y, bool pressed) override;

private:
 void rebuildButtons();

 std::vector<RadialOption> options;
 std::vector<std::shared_ptr<UIButton>> buttons;
};

} // namespace ui
} // namespace zombie
