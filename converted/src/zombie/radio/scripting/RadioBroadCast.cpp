#include "zombie/radio/scripting/RadioBroadCast.h"

namespace zombie {
namespace radio {
namespace scripting {

public RadioBroadCast::RadioBroadCast(const std::string& id, int startstamp, int endstamp) {
 // TODO: Implement RadioBroadCast
 return nullptr;
}

std::string RadioBroadCast::getID() {
 // TODO: Implement getID
 return "";
}

int RadioBroadCast::getStartStamp() {
 // TODO: Implement getStartStamp
 return 0;
}

int RadioBroadCast::getEndStamp() {
 // TODO: Implement getEndStamp
 return 0;
}

void RadioBroadCast::resetLineCounter() {
 // TODO: Implement resetLineCounter
}

void RadioBroadCast::resetLineCounter(bool doChildren) {
 // TODO: Implement resetLineCounter
}

void RadioBroadCast::setPreSegment(RadioBroadCast broadCast) {
 // TODO: Implement setPreSegment
}

void RadioBroadCast::setPostSegment(RadioBroadCast broadCast) {
 // TODO: Implement setPostSegment
}

RadioLine RadioBroadCast::getNextLine() {
 // TODO: Implement getNextLine
 return nullptr;
}

RadioLine RadioBroadCast::getNextLine(bool doChildren) {
 // TODO: Implement getNextLine
 return nullptr;
}

int RadioBroadCast::getCurrentLineNumber() {
 // TODO: Implement getCurrentLineNumber
 return 0;
}

void RadioBroadCast::setCurrentLineNumber(int n) {
 // TODO: Implement setCurrentLineNumber
}

RadioLine RadioBroadCast::getCurrentLine() {
 // TODO: Implement getCurrentLine
 return nullptr;
}

std::string RadioBroadCast::PeekNextLineText() {
 // TODO: Implement PeekNextLineText
 return "";
}

void RadioBroadCast::AddRadioLine(RadioLine radioLine) {
 // TODO: Implement AddRadioLine
}

} // namespace scripting
} // namespace radio
} // namespace zombie
