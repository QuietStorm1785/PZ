#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/Core.h"
#include "zombie/core/Translator.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/radio/media/MediaData/MediaLineData.h"

namespace zombie {
namespace radio {
namespace media {


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
   private const std::vector<MediaLineData> lines = std::make_unique<std::vector<>>();

    public MediaData(const std::string& var1, const std::string& var2, int var3) {
      this.itemDisplayName = var2;
      this.id = var1;
      this.spawning = var3;
      if (Core.bDebug) {
         if (var2 == nullptr) {
            throw RuntimeException("ItemDisplayName may not be nullptr.");
         }

         if (var1 == nullptr) {
            throw RuntimeException("Id may not be nullptr.");
         }
      }
   }

    void addLine(const std::string& var1, float var2, float var3, float var4, const std::string& var5) {
    MediaLineData var6 = std::make_shared<MediaLineData>(var1, var2, var3, var4, var5);
      this.lines.push_back(var6);
   }

    int getLineCount() {
      return this.lines.size();
   }

    std::string getTranslatedItemDisplayName() {
      return Translator.getText(this.itemDisplayName);
   }

    bool hasTitle() {
      return this.title != nullptr;
   }

    void setTitle(const std::string& var1) {
      this.title = var1;
   }

    std::string getTitleEN() {
      return this.title != nullptr ? Translator.getTextMediaEN(this.title) : nullptr;
   }

    std::string getTranslatedTitle() {
      return this.title != nullptr ? Translator.getText(this.title) : nullptr;
   }

    bool hasSubTitle() {
      return this.subtitle != nullptr;
   }

    void setSubtitle(const std::string& var1) {
      this.subtitle = var1;
   }

    std::string getSubtitleEN() {
      return this.subtitle != nullptr ? Translator.getTextMediaEN(this.subtitle) : nullptr;
   }

    std::string getTranslatedSubTitle() {
      return this.subtitle != nullptr ? Translator.getText(this.subtitle) : nullptr;
   }

    bool hasAuthor() {
      return this.author != nullptr;
   }

    void setAuthor(const std::string& var1) {
      this.author = var1;
   }

    std::string getAuthorEN() {
      return this.author != nullptr ? Translator.getTextMediaEN(this.author) : nullptr;
   }

    std::string getTranslatedAuthor() {
      return this.author != nullptr ? Translator.getText(this.author) : nullptr;
   }

    bool hasExtra() {
      return this.extra != nullptr;
   }

    void setExtra(const std::string& var1) {
      this.extra = var1;
   }

    std::string getExtraEN() {
      return this.extra != nullptr ? Translator.getTextMediaEN(this.extra) : nullptr;
   }

    std::string getTranslatedExtra() {
      return this.extra != nullptr ? Translator.getText(this.extra) : nullptr;
   }

    std::string getId() {
      return this.id;
   }

    short getIndex() {
      return this.index;
   }

    void setIndex(short var1) {
      this.index = var1;
   }

    std::string getCategory() {
      return this.category;
   }

    void setCategory(const std::string& var1) {
      this.category = var1;
   }

    int getSpawning() {
      return this.spawning;
   }

    uint8_t getMediaType() {
      if (this.category == nullptr) {
         DebugLog.log("Warning MediaData has no category set, mediadata = " + (this.itemDisplayName != nullptr ? this.itemDisplayName : "unknown"));
      }

      return RecordedMedia.getMediaTypeForCategory(this.category);
   }

    MediaLineData getLine(int var1) {
      return var1 >= 0 && var1 < this.lines.size() ? this.lines.get(var1) : nullptr;
   }
}
} // namespace media
} // namespace radio
} // namespace zombie
