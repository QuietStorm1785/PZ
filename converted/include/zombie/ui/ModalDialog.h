#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/GameTime.h"
#include "zombie/GameWindow.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/core/Core.h"
#include "zombie/gameStates/IngameState.h"
#include <algorithm>
#include <fstream>
#include <iostream>

namespace zombie {
namespace ui {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class ModalDialog : public NewWindow {
public:
 bool bYes = false;
 std::string Name;
 UIEventHandler handler = nullptr;
 bool Clicked = false;

 public ModalDialog(const std::string& name, const std::string& help, bool bYesNo) {
 super(Core.getInstance().getOffscreenWidth(0) / 2, Core.getInstance().getOffscreenHeight(0) / 2, 470, 10, false);
 this->Name = name;
 this->ResizeToFitY = false;
 this->IgnoreLossControl = true;
 TextBox textBox = new TextBox(UIFont.Medium, 0, 0, 450, help);
 textBox.Centred = true;
 textBox.ResizeParent = true;
 textBox.update();
 this->Nest(textBox, 20, 10, 20, 10);
 this->update();
 this->height *= 1.3F;
 if (bYesNo) {
 this->AddChild(new DialogButton(this, (float)(this->getWidth().intValue() / 2 - 40), (float)(this->getHeight().intValue() - 18), "Yes", "Yes"));
 this->AddChild(new DialogButton(this, (float)(this->getWidth().intValue() / 2 + 40), (float)(this->getHeight().intValue() - 18), "No", "No"));
 } else {
 this->AddChild(new DialogButton(this, (float)(this->getWidth().intValue() / 2), (float)(this->getHeight().intValue() - 18), "Ok", "Ok"));
 }

 this->x = this->x - this->width / 2.0F;
 this->y = this->y - this->height / 2.0F;
 }

 void ButtonClicked(const std::string& name) {
 if (this->handler != nullptr) {
 this->handler.ModalClick(this->Name, name);
 this->setVisible(false);
 } else {
 if (name == "Ok")) {
 UIManager.getSpeedControls().SetCurrentGameSpeed(4);
 this->Clicked(name);
 this->Clicked = true;
 this->bYes = true;
 this->setVisible(false);
 IngameState.instance.Paused = false;
 }

 if (name == "Yes")) {
 UIManager.getSpeedControls().SetCurrentGameSpeed(4);
 this->Clicked(name);
 this->Clicked = true;
 this->bYes = true;
 this->setVisible(false);
 IngameState.instance.Paused = false;
 }

 if (name == "No")) {
 UIManager.getSpeedControls().SetCurrentGameSpeed(4);
 this->Clicked(name);
 this->Clicked = true;
 this->bYes = false;
 this->setVisible(false);
 IngameState.instance.Paused = false;
 }
 }
 }

 void Clicked(const std::string& name) {
 if (this->Name == "Sleep") && name == "Yes")) {
 float float0 = 12.0F * IsoPlayer.getInstance().getStats().fatigue;
 if (float0 < 7.0F) {
 float0 = 7.0F;
 }

 float0 += GameTime.getInstance().getTimeOfDay();
 if (float0 >= 24.0F) {
 float0 -= 24.0F;
 }

 IsoPlayer.getInstance().setForceWakeUpTime((int)float0);
 IsoPlayer.getInstance().setAsleepTime(0.0F);
 TutorialManager.instance.StealControl = true;
 IsoPlayer.getInstance().setAsleep(true);
 UIManager.setbFadeBeforeUI(true);
 UIManager.FadeOut(4.0);
 UIManager.getSpeedControls().SetCurrentGameSpeed(3);

 try {
 GameWindow.save(true);
 } catch (FileNotFoundException fileNotFoundException) {
 Logger.getLogger(ModalDialog.class.getName()).log(Level.SEVERE, nullptr, fileNotFoundException);
 } catch (IOException iOException) {
 Logger.getLogger(ModalDialog.class.getName()).log(Level.SEVERE, nullptr, iOException);
 }
 }

 UIManager.Modal.setVisible(false);
 }
}
} // namespace ui
} // namespace zombie
