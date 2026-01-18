#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/Color.h"
#include "zombie/core/Core.h"
#include "zombie/core/Translator.h"
#include "zombie/debug/DebugLog.h"

namespace zombie {
namespace radio {
namespace media {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


/**
 * TurboTuTone.
 */
class MediaData {
public:
 const std::string id;
 const std::string itemDisplayName;
 std::string title;
 std::string subtitle;
 std::string author;
 std::string extra;
 short index;
 std::string category;
 const int spawning;
 private ArrayList<MediaData.MediaLineData> lines = std::make_unique<ArrayList<>>();

 public MediaData(const std::string& _id, const std::string& _itemDisplayName, int _spawning) {
 this->itemDisplayName = _itemDisplayName;
 this->id = _id;
 this->spawning = _spawning;
 if (Core.bDebug) {
 if (_itemDisplayName == nullptr) {
 throw RuntimeException("ItemDisplayName may not be nullptr.");
 }

 if (_id == nullptr) {
 throw RuntimeException("Id may not be nullptr.");
 }
 }
 }

 void addLine(const std::string& text, float r, float g, float b, const std::string& codes) {
 MediaData.MediaLineData mediaLineData = new MediaData.MediaLineData(text, r, g, b, codes);
 this->lines.add(mediaLineData);
 }

 int getLineCount() {
 return this->lines.size();
 }

 std::string getTranslatedItemDisplayName() {
 return Translator.getText(this->itemDisplayName);
 }

 bool hasTitle() {
 return this->title != nullptr;
 }

 void setTitle(const std::string& _title) {
 this->title = _title;
 }

 std::string getTitleEN() {
 return this->title != nullptr ? Translator.getTextMediaEN(this->title) : nullptr;
 }

 std::string getTranslatedTitle() {
 return this->title != nullptr ? Translator.getText(this->title) : nullptr;
 }

 bool hasSubTitle() {
 return this->subtitle != nullptr;
 }

 void setSubtitle(const std::string& _subtitle) {
 this->subtitle = _subtitle;
 }

 std::string getSubtitleEN() {
 return this->subtitle != nullptr ? Translator.getTextMediaEN(this->subtitle) : nullptr;
 }

 std::string getTranslatedSubTitle() {
 return this->subtitle != nullptr ? Translator.getText(this->subtitle) : nullptr;
 }

 bool hasAuthor() {
 return this->author != nullptr;
 }

 void setAuthor(const std::string& _author) {
 this->author = _author;
 }

 std::string getAuthorEN() {
 return this->author != nullptr ? Translator.getTextMediaEN(this->author) : nullptr;
 }

 std::string getTranslatedAuthor() {
 return this->author != nullptr ? Translator.getText(this->author) : nullptr;
 }

 bool hasExtra() {
 return this->extra != nullptr;
 }

 void setExtra(const std::string& _extra) {
 this->extra = _extra;
 }

 std::string getExtraEN() {
 return this->extra != nullptr ? Translator.getTextMediaEN(this->extra) : nullptr;
 }

 std::string getTranslatedExtra() {
 return this->extra != nullptr ? Translator.getText(this->extra) : nullptr;
 }

 std::string getId() {
 return this->id;
 }

 short getIndex() {
 return this->index;
 }

 void setIndex(short short0) {
 this->index = short0;
 }

 std::string getCategory() {
 return this->category;
 }

 void setCategory(const std::string& string) {
 this->category = string;
 }

 int getSpawning() {
 return this->spawning;
 }

 uint8_t getMediaType() {
 if (this->category == nullptr) {
 DebugLog.log("Warning MediaData has no category set, mediadata = " + (this->itemDisplayName != nullptr ? this->itemDisplayName : "unknown"));
 }

 return RecordedMedia.getMediaTypeForCategory(this->category);
 }

 public MediaData.MediaLineData getLine(int _index) {
 return _index >= 0 && _index < this->lines.size() ? this->lines.get(_index) : nullptr;
 }

 public static class MediaLineData {
 const std::string text;
 const Color color;
 const std::string codes;

 public MediaLineData(const std::string& _text, float r, float g, float b, const std::string& _codes) {
 this->text = _text;
 this->codes = _codes;
 if (r == 0.0F && g == 0.0F && b == 0.0F) {
 r = 1.0F;
 g = 1.0F;
 b = 1.0F;
 }

 this->color = new Color(r, g, b);
 }

 std::string getTranslatedText() {
 return Translator.getText(this->text);
 }

 Color getColor() {
 return this->color;
 }

 float getR() {
 return this->color.r;
 }

 float getG() {
 return this->color.g;
 }

 float getB() {
 return this->color.b;
 }

 std::string getCodes() {
 return this->codes;
 }

 std::string getTextGuid() {
 return this->text;
 }
 }
}
} // namespace media
} // namespace radio
} // namespace zombie
