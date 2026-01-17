#pragma once
#include "zombie/GameWindow.h"
#include "zombie/core/Color.h"
#include "zombie/core/network/ByteBufferWriter.h"
#include "zombie/ui/UIFont.h"
#include <cstdint>
#include <filesystem>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace chat {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class ChatSettings {
public:
  bool unique;
  Color fontColor;
  UIFont font;
private
  ChatSettings.FontSize fontSize;
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

public
  ChatSettings() {
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
    this.fontSize = ChatSettings.FontSize.Medium;
  }

public
  ChatSettings(ByteBuffer bb) {
    this.unique = bb.get() == 1;
    this.fontColor =
        new Color(bb.getFloat(), bb.getFloat(), bb.getFloat(), bb.getFloat());
    this.font = UIFont.FromString(GameWindow.ReadString(bb));
    this.bold = bb.get() == 1;
    this.allowImages = bb.get() == 1;
    this.allowChatIcons = bb.get() == 1;
    this.allowColors = bb.get() == 1;
    this.allowFonts = bb.get() == 1;
    this.allowBBcode = bb.get() == 1;
    this.equalizeLineHeights = bb.get() == 1;
    this.showAuthor = bb.get() == 1;
    this.showTimestamp = bb.get() == 1;
    this.showChatTitle = bb.get() == 1;
    this.range = bb.getFloat();
    if (bb.get() == 1) {
      this.zombieAttractionRange = bb.getFloat();
    } else {
      this.zombieAttractionRange = this.range;
    }

    this.fontSize = ChatSettings.FontSize.Medium;
  }

  bool isUnique() { return this.unique; }

  void setUnique(bool _unique) { this.unique = _unique; }

  Color getFontColor() { return this.fontColor; }

  void setFontColor(Color _fontColor) { this.fontColor = _fontColor; }

  void setFontColor(float r, float g, float b, float a) {
    this.fontColor = new Color(r, g, b, a);
  }

  UIFont getFont() { return this.font; }

  void setFont(UIFont _font) { this.font = _font; }

  std::string getFontSize() { return this.fontSize.toString().toLowerCase(); }

  void setFontSize(const std::string &_fontSize) {
    switch (_fontSize) {
    case "small":
    case "Small":
      this.fontSize = ChatSettings.FontSize.Small;
      break;
    case "medium":
    case "Medium":
      this.fontSize = ChatSettings.FontSize.Medium;
      break;
    case "large":
    case "Large":
      this.fontSize = ChatSettings.FontSize.Large;
      break;
    default:
      this.fontSize = ChatSettings.FontSize.NotDefine;
    }
  }

  bool isBold() { return this.bold; }

  void setBold(bool _bold) { this.bold = _bold; }

  bool isShowAuthor() { return this.showAuthor; }

  void setShowAuthor(bool _showAuthor) { this.showAuthor = _showAuthor; }

  bool isShowTimestamp() { return this.showTimestamp; }

  void setShowTimestamp(bool _showTimestamp) {
    this.showTimestamp = _showTimestamp;
  }

  bool isShowChatTitle() { return this.showChatTitle; }

  void setShowChatTitle(bool _showChatTitle) {
    this.showChatTitle = _showChatTitle;
  }

  bool isAllowImages() { return this.allowImages; }

  void setAllowImages(bool _allowImages) { this.allowImages = _allowImages; }

  bool isAllowChatIcons() { return this.allowChatIcons; }

  void setAllowChatIcons(bool _allowChatIcons) {
    this.allowChatIcons = _allowChatIcons;
  }

  bool isAllowColors() { return this.allowColors; }

  void setAllowColors(bool _allowColors) { this.allowColors = _allowColors; }

  bool isAllowFonts() { return this.allowFonts; }

  void setAllowFonts(bool _allowFonts) { this.allowFonts = _allowFonts; }

  bool isAllowBBcode() { return this.allowBBcode; }

  void setAllowBBcode(bool _allowBBcode) { this.allowBBcode = _allowBBcode; }

  bool isEqualizeLineHeights() { return this.equalizeLineHeights; }

  void setEqualizeLineHeights(bool _equalizeLineHeights) {
    this.equalizeLineHeights = _equalizeLineHeights;
  }

  float getRange() { return this.range; }

  void setRange(float _range) { this.range = _range; }

  float getZombieAttractionRange() {
    return this.zombieAttractionRange == -1.0F ? this.range
                                               : this.zombieAttractionRange;
  }

  void setZombieAttractionRange(float _zombieAttractionRange) {
    this.zombieAttractionRange = _zombieAttractionRange;
  }

  bool isUseOnlyActiveTab() { return this.useOnlyActiveTab; }

  void setUseOnlyActiveTab(bool _useOnlyActiveTab) {
    this.useOnlyActiveTab = _useOnlyActiveTab;
  }

  void pack(ByteBufferWriter bb) {
    bb.putBoolean(this.unique);
    bb.putFloat(this.fontColor.r);
    bb.putFloat(this.fontColor.g);
    bb.putFloat(this.fontColor.b);
    bb.putFloat(this.fontColor.a);
    bb.putUTF(this.font.toString());
    bb.putBoolean(this.bold);
    bb.putBoolean(this.allowImages);
    bb.putBoolean(this.allowChatIcons);
    bb.putBoolean(this.allowColors);
    bb.putBoolean(this.allowFonts);
    bb.putBoolean(this.allowBBcode);
    bb.putBoolean(this.equalizeLineHeights);
    bb.putBoolean(this.showAuthor);
    bb.putBoolean(this.showTimestamp);
    bb.putBoolean(this.showChatTitle);
    bb.putFloat(this.range);
    bb.putBoolean(this.range != this.zombieAttractionRange);
    if (this.range != this.zombieAttractionRange) {
      bb.putFloat(this.zombieAttractionRange);
    }
  }

public
  static enum FontSize { NotDefine, Small, Medium, Large; }
}
} // namespace chat
} // namespace zombie
