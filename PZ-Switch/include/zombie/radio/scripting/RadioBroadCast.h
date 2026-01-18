#pragma once
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace radio {
namespace scripting {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

/**
 * Turbo
 */
class RadioBroadCast {
public:
 static const RadioLine pauseLine = new RadioLine("~", 0.5F, 0.5F, 0.5F);
private
 ArrayList<RadioLine> lines = std::make_unique<ArrayList<>>();
 std::string ID = "";
 int startStamp = 0;
 int endStamp = 0;
 int lineCount = 0;
 RadioBroadCast preSegment = nullptr;
 RadioBroadCast postSegment = nullptr;
 bool hasDonePreSegment = false;
 bool hasDonePostSegment = false;
 bool hasDonePostPause = false;

public
 RadioBroadCast(const std::string &id, int startstamp, int endstamp) {
 this->ID = id;
 this->startStamp = startstamp;
 this->endStamp = endstamp;
 }

 std::string getID() { return this->ID; }

 int getStartStamp() { return this->startStamp; }

 int getEndStamp() { return this->endStamp; }

 void resetLineCounter() { this->resetLineCounter(true); }

 void resetLineCounter(bool doChildren) {
 this->lineCount = 0;
 if (doChildren) {
 if (this->preSegment != nullptr) {
 this->preSegment.resetLineCounter(false);
 }

 if (this->postSegment != nullptr) {
 this->postSegment.resetLineCounter(false);
 }
 }
 }

 void setPreSegment(RadioBroadCast broadCast) { this->preSegment = broadCast; }

 void setPostSegment(RadioBroadCast broadCast) {
 this->postSegment = broadCast;
 }

 RadioLine getNextLine() { return this->getNextLine(true); }

 RadioLine getNextLine(bool doChildren) {
 RadioLine radioLine = nullptr;
 if (doChildren && !this->hasDonePreSegment && this->lineCount == 0 &&
 this->preSegment != nullptr) {
 radioLine = this->preSegment.getNextLine();
 if (radioLine != nullptr) {
 return radioLine;
 } else {
 this->hasDonePreSegment = true;
 return pauseLine;
 }
 } else {
 if (this->lineCount >= 0 && this->lineCount < this->lines.size()) {
 radioLine = this->lines.get(this->lineCount);
 }

 if (!doChildren || radioLine != nullptr || this->postSegment.empty()) {
 this->lineCount++;
 return radioLine;
 } else if (!this->hasDonePostPause) {
 this->hasDonePostPause = true;
 return pauseLine;
 } else {
 return this->postSegment.getNextLine();
 }
 }
 }

 int getCurrentLineNumber() { return this->lineCount; }

 void setCurrentLineNumber(int n) {
 this->lineCount = n;
 if (this->lineCount < 0) {
 this->lineCount = 0;
 }
 }

 RadioLine getCurrentLine() {
 return this->lineCount >= 0 && this->lineCount < this->lines.size()
 ? this->lines.get(this->lineCount)
 : nullptr;
 }

 std::string PeekNextLineText() {
 if (this->lineCount >= 0 && this->lineCount < this->lines.size()) {
 return this->lines.get(this->lineCount) != nullptr &&
 this->lines.get(this->lineCount).getText() != nullptr
 ? this->lines.get(this->lineCount).getText()
 : "Error";
 } else {
 return "None";
 }
 }

 void AddRadioLine(RadioLine radioLine) {
 if (radioLine != nullptr) {
 this->lines.add(radioLine);
 }
 }

public
 ArrayList<RadioLine> getLines() { return this->lines; }
}
} // namespace scripting
} // namespace radio
} // namespace zombie
