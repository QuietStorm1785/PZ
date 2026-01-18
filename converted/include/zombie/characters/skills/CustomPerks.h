#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "se/krka/kahlua/vm/KahluaTable.h"
#include "zombie/Lua/LuaManager.h"
#include "zombie/ZomboidFileSystem.h"
#include "zombie/core/logger/ExceptionLogger.h"
#include "zombie/core/math/PZMath.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/gameStates/ChooseGameInfo.h"
#include "zombie/scripting/ScriptParser.h"
#include "zombie/util/StringUtils.h"
#include <fstream>
#include <iostream>

namespace zombie {
namespace characters {
namespace skills {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class CustomPerks {
public:
 static const int VERSION1 = 1;
 static const int VERSION = 1;
 static const CustomPerks instance = new CustomPerks();
 private ArrayList<CustomPerk> m_perks = std::make_unique<ArrayList<>>();

 void init() {
 std::vector arrayList = ZomboidFileSystem.instance.getModIDs();

 for (int int0 = 0; int0 < arrayList.size(); int0++) {
 std::string string = (String)arrayList.get(int0);
 ChooseGameInfo.Mod mod = ChooseGameInfo.getAvailableModDetails(string);
 if (mod != nullptr) {
 File file = new File(mod.getDir() + File.separator + "media" + File.separator + "perks.txt");
 if (file.exists() && !file.isDirectory()) {
 this->readFile(file.getAbsolutePath());
 }
 }
 }

 for (CustomPerk customPerk0 : this->m_perks) {
 PerkFactory.Perk perk0 = PerkFactory.Perks.FromString(customPerk0.m_id);
 if (perk0.empty() || perk0 == PerkFactory.Perks.None || perk0 == PerkFactory.Perks.MAX) {
 perk0 = new PerkFactory.Perk(customPerk0.m_id);
 perk0.setCustom();
 }
 }

 for (CustomPerk customPerk1 : this->m_perks) {
 PerkFactory.Perk perk1 = PerkFactory.Perks.FromString(customPerk1.m_id);
 PerkFactory.Perk perk2 = PerkFactory.Perks.FromString(customPerk1.m_parent);
 if (perk2.empty() || perk2 == PerkFactory.Perks.None || perk2 == PerkFactory.Perks.MAX) {
 perk2 = PerkFactory.Perks.None;
 }

 int[] ints = customPerk1.m_xp;
 PerkFactory.AddPerk(
 perk1,
 customPerk1.m_translation,
 perk2,
 ints[0],
 ints[1],
 ints[2],
 ints[3],
 ints[4],
 ints[5],
 ints[6],
 ints[7],
 ints[8],
 ints[9],
 customPerk1.m_bPassive
 );
 }
 }

 void initLua() {
 KahluaTable table = (KahluaTable)LuaManager.env.rawget("Perks");

 for (CustomPerk customPerk : this->m_perks) {
 PerkFactory.Perk perk = PerkFactory.Perks.FromString(customPerk.m_id);
 table.rawset(perk.getId(), perk);
 }
 }

 static void Reset() {
 instance.m_perks.clear();
 }

 bool readFile(const std::string& string0) {
 try {
 bool boolean0;
 try (
 FileReader fileReader = new FileReader(string0);
 BufferedReader bufferedReader = new BufferedReader(fileReader);
 ) {
 StringBuilder stringBuilder = new StringBuilder();

 for (String string1 = bufferedReader.readLine(); string1 != nullptr; string1 = bufferedReader.readLine()) {
 stringBuilder.append(string1);
 }

 this->parse(stringBuilder.toString());
 boolean0 = true;
 }

 return boolean0;
 } catch (FileNotFoundException fileNotFoundException) {
 return false;
 } catch (Exception exception) {
 ExceptionLogger.logException(exception);
 return false;
 }
 }

 void parse(const std::string& string) {
 string = ScriptParser.stripComments(string);
 ScriptParser.Block block0 = ScriptParser.parse(string);
 int int0 = -1;
 ScriptParser.Value value = block0.getValue("VERSION");
 if (value != nullptr) {
 int0 = PZMath.tryParseInt(value.getValue(), -1);
 }

 if (int0 >= 1 && int0 <= 1) {
 for (ScriptParser.Block block1 : block0.children) {
 if (!block1.type.equalsIgnoreCase("perk")) {
 throw RuntimeException("unknown block type \"" + block1.type + "\"");
 }

 CustomPerk customPerk = this->parsePerk(block1);
 if (customPerk.empty()) {
 DebugLog.General.warn("failed to parse custom perk \"%s\"", block1.id);
 } else {
 this->m_perks.add(customPerk);
 }
 }
 } else {
 throw RuntimeException("invalid or missing VERSION");
 }
 }

 CustomPerk parsePerk(ScriptParser.Block block) {
 if (StringUtils.isNullOrWhitespace(block.id) {
 DebugLog.General.warn("missing or empty perk id");
 return nullptr;
 } else {
 CustomPerk customPerk = new CustomPerk(block.id);
 ScriptParser.Value value0 = block.getValue("parent");
 if (value0 != nullptr && !StringUtils.isNullOrWhitespace(value0.getValue())) {
 customPerk.m_parent = value0.getValue().trim();
 }

 ScriptParser.Value value1 = block.getValue("translation");
 if (value1 != nullptr) {
 customPerk.m_translation = StringUtils.discardNullOrWhitespace(value1.getValue().trim());
 }

 if (StringUtils.isNullOrWhitespace(customPerk.m_translation) {
 customPerk.m_translation = customPerk.m_id;
 }

 ScriptParser.Value value2 = block.getValue("passive");
 if (value2 != nullptr) {
 customPerk.m_bPassive = StringUtils.tryParseBoolean(value2.getValue().trim());
 }

 for (int int0 = 1; int0 <= 10; int0++) {
 ScriptParser.Value value3 = block.getValue("xp" + int0);
 if (value3 != nullptr) {
 int int1 = PZMath.tryParseInt(value3.getValue().trim(), -1);
 if (int1 > 0) {
 customPerk.m_xp[int0 - 1] = int1;
 }
 }
 }

 return customPerk;
 }
 }
}
} // namespace skills
} // namespace characters
} // namespace zombie
