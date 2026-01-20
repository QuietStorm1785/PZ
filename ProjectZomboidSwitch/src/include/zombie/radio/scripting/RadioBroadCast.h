#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace radio {
namespace scripting {


class RadioBroadCast {
public:
    static const RadioLine pauseLine = std::make_shared<RadioLine>("~", 0.5F, 0.5F, 0.5F);
   private const std::vector<RadioLine> lines = std::make_unique<std::vector<>>();
    std::string ID = "";
    int startStamp = 0;
    int endStamp = 0;
    int lineCount = 0;
    RadioBroadCast preSegment = nullptr;
    RadioBroadCast postSegment = nullptr;
    bool hasDonePreSegment = false;
    bool hasDonePostSegment = false;
    bool hasDonePostPause = false;

    public RadioBroadCast(const std::string& var1, int var2, int var3) {
      this.ID = var1;
      this.startStamp = var2;
      this.endStamp = var3;
   }

    std::string getID() {
      return this.ID;
   }

    int getStartStamp() {
      return this.startStamp;
   }

    int getEndStamp() {
      return this.endStamp;
   }

    void resetLineCounter() {
      this.resetLineCounter(true);
   }

    void resetLineCounter(bool var1) {
      this.lineCount = 0;
      if (var1) {
         if (this.preSegment != nullptr) {
            this.preSegment.resetLineCounter(false);
         }

         if (this.postSegment != nullptr) {
            this.postSegment.resetLineCounter(false);
         }
      }
   }

    void setPreSegment(RadioBroadCast var1) {
      this.preSegment = var1;
   }

    void setPostSegment(RadioBroadCast var1) {
      this.postSegment = var1;
   }

    RadioLine getNextLine() {
      return this.getNextLine(true);
   }

    RadioLine getNextLine(bool var1) {
    RadioLine var2 = nullptr;
      if (var1 && !this.hasDonePreSegment && this.lineCount == 0 && this.preSegment != nullptr) {
         var2 = this.preSegment.getNextLine();
         if (var2 != nullptr) {
    return var2;
         } else {
            this.hasDonePreSegment = true;
    return pauseLine;
         }
      } else {
         if (this.lineCount >= 0 && this.lineCount < this.lines.size()) {
            var2 = this.lines.get(this.lineCount);
         }

         if (!var1 || var2 != nullptr || this.postSegment == nullptr) {
            this.lineCount++;
    return var2;
         } else if (!this.hasDonePostPause) {
            this.hasDonePostPause = true;
    return pauseLine;
         } else {
            return this.postSegment.getNextLine();
         }
      }
   }

    int getCurrentLineNumber() {
      return this.lineCount;
   }

    void setCurrentLineNumber(int var1) {
      this.lineCount = var1;
      if (this.lineCount < 0) {
         this.lineCount = 0;
      }
   }

    RadioLine getCurrentLine() {
      return this.lineCount >= 0 && this.lineCount < this.lines.size() ? this.lines.get(this.lineCount) : nullptr;
   }

    std::string PeekNextLineText() {
      if (this.lineCount >= 0 && this.lineCount < this.lines.size()) {
         return this.lines.get(this.lineCount) != nullptr && this.lines.get(this.lineCount).getText() != nullptr ? this.lines.get(this.lineCount).getText() : "Error";
      } else {
         return "None";
      }
   }

    void AddRadioLine(RadioLine var1) {
      if (var1 != nullptr) {
         this.lines.push_back(var1);
      }
   }

   public std::vector<RadioLine> getLines() {
      return this.lines;
   }
}
} // namespace scripting
} // namespace radio
} // namespace zombie
