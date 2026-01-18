#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/debug/DebugLog.h"
#include "zombie/network/GameServer.h"

namespace zombie {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class TimeDebugger {
public:
 ArrayList<Long> records = std::make_unique<ArrayList<>>();
 ArrayList<String> recordStrings = std::make_unique<ArrayList<>>();
 std::string name = "";

 public TimeDebugger(const std::string& string) {
 this->name = string;
 }

 void clear() {
 if (GameServer.bServer) {
 this->records.clear();
 this->recordStrings.clear();
 }
 }

 void start() {
 if (GameServer.bServer) {
 this->records.clear();
 this->recordStrings.clear();
 this->records.add(System.currentTimeMillis());
 this->recordStrings.add("Start");
 }
 }

 void record() {
 if (GameServer.bServer) {
 this->records.add(System.currentTimeMillis());
 this->recordStrings.add(String.valueOf(this->records.size()));
 }
 }

 void record(const std::string& string) {
 if (GameServer.bServer) {
 this->records.add(System.currentTimeMillis());
 this->recordStrings.add(string);
 }
 }

 void recordTO(const std::string& string, int int0) {
 if (GameServer.bServer && this->records.get(this->records.size() - 1) - this->records.get(this->records.size() - 2) > int0) {
 this->records.add(System.currentTimeMillis());
 this->recordStrings.add(string);
 }
 }

 void add(TimeDebugger timeDebugger0) {
 if (GameServer.bServer) {
 std::string string = timeDebugger0.name;

 for (int int0 = 0; int0 < timeDebugger0.records.size(); int0++) {
 this->records.add(timeDebugger0.records.get(int0);
 this->recordStrings.add(string + "|" + timeDebugger0.recordStrings.get(int0);
 }

 timeDebugger0.clear();
 }
 }

 void print() {
 if (GameServer.bServer) {
 this->records.add(System.currentTimeMillis());
 this->recordStrings.add("END");
 if (this->records.size() > 1) {
 DebugLog.log("=== DBG " + this->name + " ===");
 long long0 = this->records.get(0);

 for (int int0 = 1; int0 < this->records.size(); int0++) {
 long long1 = this->records.get(int0 - 1);
 long long2 = this->records.get(int0);
 std::string string = this->recordStrings.get(int0);
 DebugLog.log("RECORD " + int0 + " " + string + " A:" + (long2 - long0) + " D:" + (long2 - long1);
 }

 DebugLog.log("=== END " + this->name + " (" + (this->records.get(this->records.size() - 1) - long0) + ") ===");
 } else {
 DebugLog.log("<<< DBG " + this->name + " ERROR >>>");
 }
 }
 }

 long getExecTime() {
 return this->records.size() == 0 ? 0L : System.currentTimeMillis() - this->records.get(0);
 }
}
} // namespace zombie
