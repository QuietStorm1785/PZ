#pragma once
#include <cstdint>
#include <memory>
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace util {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class ExecuteTimeAnalyse {
public:
 std::string caption;
 ExecuteTimeAnalyse.TimeStamp[] list;
 int listIndex = 0;

public
 ExecuteTimeAnalyse(std::string_view string, int int0) {
 this->caption = string;
 this->list = new ExecuteTimeAnalyse.TimeStamp[int0];

 for (int int1 = 0; int1 < int0; int1++) {
 this->list[int1] = new ExecuteTimeAnalyse.TimeStamp();
 }
 }

 void reset() { this->listIndex = 0; }

 void add(std::string_view string) {
 this->list[this->listIndex].time = System.nanoTime();
 this->list[this->listIndex].comment = string;
 this->listIndex++;
 }

 long getNanoTime() {
 return this->listIndex == 0 ? 0L : System.nanoTime() - this->list[0].time;
 }

 int getMsTime() {
 return this->listIndex == 0
 ? 0
 : (int)((System.nanoTime() - this->list[0].time) / 1000000L);
 }

 void print() {
 long long0 = this->list[0].time;
 System.out.println("========== START === " + this->caption +
 " =============");

 for (int int0 = 1; int0 < this->listIndex; int0++) {
 System.out.println(int0 + " " + this->list[int0].comment + ": " +
 (this->list[int0].time - long0) / 1000000L);
 long0 = this->list[int0].time;
 }

 System.out.println("END: " +
 (System.nanoTime() - this->list[0].time) / 1000000L);
 System.out.println("========== END === " + this->caption +
 " =============");
 }

 static class TimeStamp {
 long time;
 std::string comment;

 public
 TimeStamp(std::string_view string) {
 this->comment = string;
 this->time = System.nanoTime();
 }

 public
 TimeStamp() {}
 }
}
} // namespace util
} // namespace zombie
