#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/Translator.h"
#include "zombie/core/znet/SteamUtils.h"
#include "zombie/network/CoopMaster.h"
#include "zombie/network/ICoopServerMessageListener.h"
#include <algorithm>

namespace zombie {
namespace ui {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class UIServerToolbox : public NewWindow {
public:
 static UIServerToolbox instance;
 ScrollBar ScrollBarV;
 UITextBox2 OutputLog;
 private ArrayList<String> incomingConnections = std::make_unique<ArrayList<>>();
 DialogButton buttonAccept;
 DialogButton buttonReject;
 std::string externalAddress = nullptr;
 std::string steamID = nullptr;
 bool autoAccept = false;

 public UIServerToolbox(int int0, int int1) {
 super(int0, int1, 10, 10, true);
 this->ResizeToFitY = false;
 this->visible = true;
 if (instance != nullptr) {
 instance.shutdown();
 }

 instance = this;
 this->width = 340.0F;
 this->height = 325.0F;
 uint8_t byte0 = 6;
 uint8_t byte1 = 37;
 this->OutputLog = new UITextBox2(UIFont.Small, 5, 33, 330, 260, Translator.getText("IGUI_ServerToolBox_Status"), true);
 this->OutputLog.multipleLine = true;
 this->ScrollBarV = new ScrollBar(
 "ServerToolboxScrollbar",
 this,
 (int)(this->OutputLog.getX() + this->OutputLog.getWidth()) - 14,
 this->OutputLog.getY().intValue() + 4,
 this->OutputLog.getHeight().intValue() - 8,
 true
 );
 this->ScrollBarV.SetParentTextBox(this->OutputLog);
 this->AddChild(this->OutputLog);
 this->AddChild(this->ScrollBarV);
 this->buttonAccept = new DialogButton(this, 30, 225, Translator.getText("IGUI_ServerToolBox_acccept"), "accept");
 this->buttonReject = new DialogButton(this, 80, 225, Translator.getText("IGUI_ServerToolBox_reject"), "reject");
 this->AddChild(this->buttonAccept);
 this->AddChild(this->buttonReject);
 this->buttonAccept.setVisible(false);
 this->buttonReject.setVisible(false);
 this->PrintLine("\n");
 if (CoopMaster.instance != nullptr && CoopMaster.instance.isRunning()) {
 CoopMaster.instance.addListener(this);
 CoopMaster.instance
 .invokeServer(
 "get-parameter",
 "external-ip",
 new ICoopServerMessageListener() {
 void OnCoopServerMessage(const std::string& var1, const std::string& var2, const std::string& string0) {
 UIServerToolbox.this->externalAddress = string0;
 String string1 = "nullptr" == UIServerToolbox.this->externalAddress)
 ? Translator.getText("IGUI_ServerToolBox_IPUnknown")
 : UIServerToolbox.this->externalAddress;
 UIServerToolbox.this->PrintLine(Translator.getText("IGUI_ServerToolBox_ServerAddress", string1);
 UIServerToolbox.this->PrintLine("");
 }
 }
 );
 if (SteamUtils.isSteamModeEnabled()) {
 CoopMaster.instance.invokeServer("get-parameter", "steam-id", std::make_unique<ICoopServerMessageListener>() {
 void OnCoopServerMessage(const std::string& var1, const std::string& var2, const std::string& string) {
 UIServerToolbox.this->steamID = string;
 UIServerToolbox.this->PrintLine(Translator.getText("IGUI_ServerToolBox_SteamID", UIServerToolbox.this->steamID);
 UIServerToolbox.this->PrintLine("");
 UIServerToolbox.this->PrintLine(Translator.getText("IGUI_ServerToolBox_Invite1"));
 UIServerToolbox.this->PrintLine("");
 UIServerToolbox.this->PrintLine(Translator.getText("IGUI_ServerToolBox_Invite2"));
 UIServerToolbox.this->PrintLine(Translator.getText("IGUI_ServerToolBox_Invite3"));
 UIServerToolbox.this->PrintLine("");
 UIServerToolbox.this->PrintLine(Translator.getText("IGUI_ServerToolBox_Invite4"));
 UIServerToolbox.this->PrintLine("");
 UIServerToolbox.this->PrintLine(Translator.getText("IGUI_ServerToolBox_Invite5"));
 }
 });
 }
 }
 }

 void render() {
 if (this->isVisible()) {
 super.render();
 this->DrawTextCentre(Translator.getText("IGUI_ServerToolBox_Title"), this->getWidth() / 2.0, 2.0, 1.0, 1.0, 1.0, 1.0);
 std::string string0 = "nullptr".equals(this->externalAddress) ? Translator.getText("IGUI_ServerToolBox_IPUnknown") : this->externalAddress;
 this->DrawText(Translator.getText("IGUI_ServerToolBox_ExternalIP", string0), 7.0, 19.0, 0.7F, 0.7F, 1.0, 1.0);
 if (!this->incomingConnections.empty()) {
 std::string string1 = this->incomingConnections.get(0);
 if (string1 != nullptr) {
 this->DrawText(Translator.getText("IGUI_ServerToolBox_UserConnecting", string1), 10.0, 205.0, 0.7F, 0.7F, 1.0, 1.0);
 }
 }
 }
 }

 void update() {
 if (this->isVisible()) {
 if (this->incomingConnections.empty()) {
 this->buttonReject.setVisible(false);
 this->buttonAccept.setVisible(false);
 } else {
 this->buttonReject.setVisible(true);
 this->buttonAccept.setVisible(true);
 }

 super.update();
 }
 }

 void UpdateViewPos() {
 this->OutputLog.TopLineIndex = this->OutputLog.Lines.size() - this->OutputLog.NumVisibleLines;
 if (this->OutputLog.TopLineIndex < 0) {
 this->OutputLog.TopLineIndex = 0;
 }

 this->ScrollBarV.scrollToBottom();
 }

 public synchronized void OnCoopServerMessage(String string0, String var2, String string1) {
 if (Objects == string0, "login-attempt")) {
 this->PrintLine(string1 + " is connecting");
 if (this->autoAccept) {
 this->PrintLine("Accepted connection from " + string1);
 CoopMaster.instance.sendMessage("approve-login-attempt", string1);
 } else {
 this->incomingConnections.add(string1);
 this->setVisible(true);
 }
 }
 }

 void PrintLine(const std::string& string) {
 this->OutputLog.SetText(this->OutputLog.Text + string + "\n");
 this->UpdateViewPos();
 }

 void shutdown() {
 if (CoopMaster.instance != nullptr) {
 CoopMaster.instance.removeListener(this);
 }
 }

 void DoubleClick(const std::string& var1, int var2, int var3) {
 }

 void ModalClick(const std::string& var1, const std::string& var2) {
 }

 void Selected(const std::string& string0, int var2, int var3) {
 if (Objects == string0, "accept")) {
 std::string string1 = this->incomingConnections.get(0);
 this->incomingConnections.remove(0);
 this->PrintLine("Accepted connection from " + string1);
 CoopMaster.instance.sendMessage("approve-login-attempt", string1);
 }

 if (Objects == string0, "reject")) {
 std::string string2 = this->incomingConnections.get(0);
 this->incomingConnections.remove(0);
 this->PrintLine("Rejected connection from " + string2);
 CoopMaster.instance.sendMessage("reject-login-attempt", string2);
 }
 }
}
} // namespace ui
} // namespace zombie
