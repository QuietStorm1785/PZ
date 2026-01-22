#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/GameWindow.h"
#include "zombie/chat/ChatSettings/FontSize.h"
#include "zombie/core/Color.h"
#include "zombie/core/network/ByteBufferWriter.h"
#include "zombie/ui/UIFont.h"
#include <filesystem>

namespace zombie {
namespace chat {


class ChatSettings {
public:
    bool unique;
    Color fontColor;
    UIFont font;
    FontSize fontSize;
    bool bold;
    bool allowImages;
    bool allowChatIcons;
    bool allowColors;
    bool allowFonts;
    bool allowBBcode;
    bool equalizeLineHeights;
    bool showAuthor;
    bool showTimestamp;
    bool showChatTitle;
    bool useOnlyActiveTab;
    float range;
    float zombieAttractionRange;
    static const float infinityRange = -1.0F;

    public ChatSettings() {
      this.unique = true;
      this.fontColor = Color.white;
      this.font = UIFont.Dialogue;
      this.bold = true;
      this.showAuthor = true;
      this.showTimestamp = true;
      this.showChatTitle = true;
      this.range = -1.0F;
      this.zombieAttractionRange = -1.0F;
      this.useOnlyActiveTab = false;
      this.fontSize = FontSize.Medium;
   }

    public ChatSettings(ByteBuffer var1) {
      this.unique = var1.get() == 1;
      this.fontColor = std::make_shared<Color>(var1.getFloat(), var1.getFloat(), var1.getFloat(), var1.getFloat());
      this.font = UIFont.FromString(GameWindow.ReadString(var1));
      this.bold = var1.get() == 1;
      this.allowImages = var1.get() == 1;
      this.allowChatIcons = var1.get() == 1;
      this.allowColors = var1.get() == 1;
      this.allowFonts = var1.get() == 1;
      this.allowBBcode = var1.get() == 1;
      this.equalizeLineHeights = var1.get() == 1;
      this.showAuthor = var1.get() == 1;
      this.showTimestamp = var1.get() == 1;
      this.showChatTitle = var1.get() == 1;
      this.range = var1.getFloat();
      if (var1.get() == 1) {
         this.zombieAttractionRange = var1.getFloat();
      } else {
         this.zombieAttractionRange = this.range;
      }

      this.fontSize = FontSize.Medium;
   }

    bool isUnique() {
      return this.unique;
   }

    void setUnique(bool var1) {
      this.unique = var1;
   }

    Color getFontColor() {
      return this.fontColor;
   }

    void setFontColor(Color var1) {
      this.fontColor = var1;
   }

    void setFontColor(float var1, float var2, float var3, float var4) {
      this.fontColor = std::make_shared<Color>(var1, var2, var3, var4);
   }

    UIFont getFont() {
      return this.font;
   }

    void setFont(UIFont var1) {
      this.font = var1;
   }

    std::string getFontSize() {
      return this.fontSize.toLowerCase();
   }

    void setFontSize(const std::string& var1) {
      switch (var1) {
         case "small":
         case "Small":
            this.fontSize = FontSize.Small;
            break;
         case "medium":
         case "Medium":
            this.fontSize = FontSize.Medium;
            break;
         case "large":
         case "Large":
            this.fontSize = FontSize.Large;
            break;
         default:
            this.fontSize = FontSize.NotDefine;
      }
   }

    bool isBold() {
      return this.bold;
   }

    void setBold(bool var1) {
      this.bold = var1;
   }

    bool isShowAuthor() {
      return this.showAuthor;
   }

    void setShowAuthor(bool var1) {
      this.showAuthor = var1;
   }

    bool isShowTimestamp() {
      return this.showTimestamp;
   }

    void setShowTimestamp(bool var1) {
      this.showTimestamp = var1;
   }

    bool isShowChatTitle() {
      return this.showChatTitle;
   }

    void setShowChatTitle(bool var1) {
      this.showChatTitle = var1;
   }

    bool isAllowImages() {
      return this.allowImages;
   }

    void setAllowImages(bool var1) {
      this.allowImages = var1;
   }

    bool isAllowChatIcons() {
      return this.allowChatIcons;
   }

    void setAllowChatIcons(bool var1) {
      this.allowChatIcons = var1;
   }

    bool isAllowColors() {
      return this.allowColors;
   }

    void setAllowColors(bool var1) {
      this.allowColors = var1;
   }

    bool isAllowFonts() {
      return this.allowFonts;
   }

    void setAllowFonts(bool var1) {
      this.allowFonts = var1;
   }

    bool isAllowBBcode() {
      return this.allowBBcode;
   }

    void setAllowBBcode(bool var1) {
      this.allowBBcode = var1;
   }

    bool isEqualizeLineHeights() {
      return this.equalizeLineHeights;
   }

    void setEqualizeLineHeights(bool var1) {
      this.equalizeLineHeights = var1;
   }

    float getRange() {
      return this.range;
   }

    void setRange(float var1) {
      this.range = var1;
   }

    float getZombieAttractionRange() {
      return this.zombieAttractionRange == -1.0F ? this.range : this.zombieAttractionRange;
   }

    void setZombieAttractionRange(float var1) {
      this.zombieAttractionRange = var1;
   }

    bool isUseOnlyActiveTab() {
      return this.useOnlyActiveTab;
   }

    void setUseOnlyActiveTab(bool var1) {
      this.useOnlyActiveTab = var1;
   }

    void pack(ByteBufferWriter var1) {
      var1.putBoolean(this.unique);
      var1.putFloat(this.fontColor.r);
      var1.putFloat(this.fontColor.g);
      var1.putFloat(this.fontColor.b);
      var1.putFloat(this.fontColor.a);
      var1.putUTF(this.font);
      var1.putBoolean(this.bold);
      var1.putBoolean(this.allowImages);
      var1.putBoolean(this.allowChatIcons);
      var1.putBoolean(this.allowColors);
      var1.putBoolean(this.allowFonts);
      var1.putBoolean(this.allowBBcode);
      var1.putBoolean(this.equalizeLineHeights);
      var1.putBoolean(this.showAuthor);
      var1.putBoolean(this.showTimestamp);
      var1.putBoolean(this.showChatTitle);
      var1.putFloat(this.range);
      var1.putBoolean(this.range != this.zombieAttractionRange);
      if (this.range != this.zombieAttractionRange) {
         var1.putFloat(this.zombieAttractionRange);
      }
   }
}
} // namespace chat
} // namespace zombie
