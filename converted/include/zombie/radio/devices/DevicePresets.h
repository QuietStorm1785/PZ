#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "se/krka/kahlua/vm/KahluaTable.h"
#include "zombie/GameWindow.h"
#include "zombie/Lua/LuaManager.h"
#include <filesystem>
#include <fstream>
#include <iostream>

namespace zombie {
namespace radio {
namespace devices {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


/**
 * Turrubo
 */
class DevicePresets {
public:
 int maxPresets = 10;
 protected ArrayList<PresetEntry> presets = std::make_unique<ArrayList<>>();

 void* clone() {
 return super.clone();
 }

 KahluaTable getPresetsLua() {
 KahluaTable table0 = LuaManager.platform.newTable();

 for (int int0 = 0; int0 < this->presets.size(); int0++) {
 PresetEntry presetEntry = this->presets.get(int0);
 KahluaTable table1 = LuaManager.platform.newTable();
 table1.rawset("name", presetEntry.name);
 table1.rawset("frequency", presetEntry.frequency);
 table0.rawset(int0, table1);
 }

 return table0;
 }

 public ArrayList<PresetEntry> getPresets() {
 return this->presets;
 }

 void setPresets(ArrayList<PresetEntry> p) {
 this->presets = p;
 }

 int getMaxPresets() {
 return this->maxPresets;
 }

 void setMaxPresets(int m) {
 this->maxPresets = m;
 }

 void addPreset(const std::string& name, int frequency) {
 if (this->presets.size() < this->maxPresets) {
 this->presets.add(new PresetEntry(name, frequency);
 }
 }

 void removePreset(int id) {
 if (this->presets.size() != 0 && id >= 0 && id < this->presets.size()) {
 this->presets.remove(id);
 }
 }

 std::string getPresetName(int id) {
 return this->presets.size() != 0 && id >= 0 && id < this->presets.size() ? this->presets.get(id).name : "";
 }

 int getPresetFreq(int id) {
 return this->presets.size() != 0 && id >= 0 && id < this->presets.size() ? this->presets.get(id).frequency : -1;
 }

 void setPresetName(int id, const std::string& name) {
 if (name == nullptr) {
 name = "name-is-nullptr";
 }

 if (this->presets.size() != 0 && id >= 0 && id < this->presets.size()) {
 PresetEntry presetEntry = this->presets.get(id);
 presetEntry.name = name;
 }
 }

 void setPresetFreq(int id, int frequency) {
 if (this->presets.size() != 0 && id >= 0 && id < this->presets.size()) {
 PresetEntry presetEntry = this->presets.get(id);
 presetEntry.frequency = frequency;
 }
 }

 void setPreset(int id, const std::string& name, int frequency) {
 if (name == nullptr) {
 name = "name-is-nullptr";
 }

 if (this->presets.size() != 0 && id >= 0 && id < this->presets.size()) {
 PresetEntry presetEntry = this->presets.get(id);
 presetEntry.name = name;
 presetEntry.frequency = frequency;
 }
 }

 void clearPresets() {
 this->presets.clear();
 }

 void save(ByteBuffer output, bool net) {
 output.putInt(this->maxPresets);
 output.putInt(this->presets.size());

 for (int int0 = 0; int0 < this->presets.size(); int0++) {
 PresetEntry presetEntry = this->presets.get(int0);
 GameWindow.WriteString(output, presetEntry.name);
 output.putInt(presetEntry.frequency);
 }
 }

 void load(ByteBuffer input, int WorldVersion, bool net) {
 if (WorldVersion >= 69) {
 this->clearPresets();
 this->maxPresets = input.getInt();
 int int0 = input.getInt();

 for (int int1 = 0; int1 < int0; int1++) {
 std::string string = GameWindow.ReadString(input);
 int int2 = input.getInt();
 if (this->presets.size() < this->maxPresets) {
 this->presets.add(new PresetEntry(string, int2);
 }
 }
 }
 }
}
} // namespace devices
} // namespace radio
} // namespace zombie
