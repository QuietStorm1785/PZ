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
#include "zombie/ui/UIServerToolbox/1.h"
#include "zombie/ui/UIServerToolbox/2.h"
#include <algorithm>

namespace zombie {
namespace ui {


class UIServerToolbox : public NewWindow {
public:
    static UIServerToolbox instance;
    ScrollBar ScrollBarV;
    UITextBox2 OutputLog;
   private const std::vector<std::string> incomingConnections = std::make_unique<std::vector<>>();
    DialogButton buttonAccept;
    DialogButton buttonReject;
    std::string externalAddress = nullptr;
    std::string steamID = nullptr;
    bool autoAccept = false;

    public UIServerToolbox(int var1, int var2) {
      super(var1, var2, 10, 10, true);
      this.ResizeToFitY = false;
      this.visible = true;
      if (instance != nullptr) {
         instance.shutdown();
      }

      instance = this;
      this.width = 340.0F;
      this.height = 325.0F;
    uint8_t var3 = 6;
    uint8_t var4 = 37;
      this.OutputLog = std::make_shared<UITextBox2>(UIFont.Small, 5, 33, 330, 260, Translator.getText("IGUI_ServerToolBox_Status"), true);
      this.OutputLog.multipleLine = true;
      this.ScrollBarV = std::make_shared<ScrollBar>(
         "ServerToolboxScrollbar",
         this,
         (int)(this.OutputLog.getX() + this.OutputLog.getWidth()) - 14,
         this.OutputLog.getY().intValue() + 4,
         this.OutputLog.getHeight().intValue() - 8,
         true
      );
      this.ScrollBarV.SetParentTextBox(this.OutputLog);
      this.AddChild(this.OutputLog);
      this.AddChild(this.ScrollBarV);
      this.buttonAccept = std::make_shared<DialogButton>(this, 30, 225, Translator.getText("IGUI_ServerToolBox_acccept"), "accept");
      this.buttonReject = std::make_shared<DialogButton>(this, 80, 225, Translator.getText("IGUI_ServerToolBox_reject"), "reject");
      this.AddChild(this.buttonAccept);
      this.AddChild(this.buttonReject);
      this.buttonAccept.setVisible(false);
      this.buttonReject.setVisible(false);
      this.PrintLine("\n");
      if (CoopMaster.instance != nullptr && CoopMaster.instance.isRunning()) {
         CoopMaster.instance.addListener(this);
         CoopMaster.instance.invokeServer("get-parameter", "external-ip", std::make_shared<1>(this));
         if (SteamUtils.isSteamModeEnabled()) {
            CoopMaster.instance.invokeServer("get-parameter", "steam-id", std::make_shared<2>(this));
         }
      }
   }

    void render() {
      if (this.isVisible()) {
         super.render();
         this.DrawTextCentre(Translator.getText("IGUI_ServerToolBox_Title"), this.getWidth() / 2.0, 2.0, 1.0, 1.0, 1.0, 1.0);
    std::string var1 = "nullptr" == this.externalAddress) ? Translator.getText("IGUI_ServerToolBox_IPUnknown") : this.externalAddress;
         this.DrawText(Translator.getText("IGUI_ServerToolBox_ExternalIP", var1), 7.0, 19.0, 0.7F, 0.7F, 1.0, 1.0);
         if (!this.incomingConnections.empty()) {
    std::string var2 = this.incomingConnections.get(0);
            if (var2 != nullptr) {
               this.DrawText(Translator.getText("IGUI_ServerToolBox_UserConnecting", var2), 10.0, 205.0, 0.7F, 0.7F, 1.0, 1.0);
            }
         }
      }
   }

    void update() {
      if (this.isVisible()) {
         if (this.incomingConnections.empty()) {
            this.buttonReject.setVisible(false);
            this.buttonAccept.setVisible(false);
         } else {
            this.buttonReject.setVisible(true);
            this.buttonAccept.setVisible(true);
         }

         super.update();
      }
   }

    void UpdateViewPos() {
      this.OutputLog.TopLineIndex = this.OutputLog.Lines.size() - this.OutputLog.NumVisibleLines;
      if (this.OutputLog.TopLineIndex < 0) {
         this.OutputLog.TopLineIndex = 0;
      }

      this.ScrollBarV.scrollToBottom();
   }

   public /* synchronized - TODO: add std::mutex */ void OnCoopServerMessage(std::string var1, std::string var2, std::string var3) {
      if (Objects == var1, "login-attempt")) {
         this.PrintLine(var3 + " is connecting");
         if (this.autoAccept) {
            this.PrintLine("Accepted connection from " + var3);
            CoopMaster.instance.sendMessage("approve-login-attempt", var3);
         } else {
            this.incomingConnections.push_back(var3);
            this.setVisible(true);
         }
      }
   }

    void PrintLine(const std::string& var1) {
      this.OutputLog.SetText(this.OutputLog.Text + var1 + "\n");
      this.UpdateViewPos();
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

    void Selected(const std::string& var1, int var2, int var3) {
      if (Objects == var1, "accept")) {
    std::string var4 = this.incomingConnections.get(0);
         this.incomingConnections.remove(0);
         this.PrintLine("Accepted connection from " + var4);
         CoopMaster.instance.sendMessage("approve-login-attempt", var4);
      }

      if (Objects == var1, "reject")) {
    std::string var5 = this.incomingConnections.get(0);
         this.incomingConnections.remove(0);
         this.PrintLine("Rejected connection from " + var5);
         CoopMaster.instance.sendMessage("reject-login-attempt", var5);
      }
   }
}
} // namespace ui
} // namespace zombie
