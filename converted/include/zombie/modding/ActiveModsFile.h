#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/Core.h"
#include "zombie/core/logger/ExceptionLogger.h"
#include "zombie/core/math/PZMath.h"
#include "zombie/scripting/ScriptParser.h"
#include "zombie/util/StringUtils.h"
#include <fstream>
#include <iostream>

namespace zombie {
namespace modding {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class ActiveModsFile {
public:
 static const int VERSION1 = 1;
 static const int VERSION = 1;

 bool write(const std::string& string0, ActiveMods activeMods) {
 if (Core.getInstance().isNoSave()) {
 return false;
 } else {
 File file = new File(string0);

 try {
 try (
 FileWriter fileWriter = new FileWriter(file);
 BufferedWriter bufferedWriter = new BufferedWriter(fileWriter);
 ) {
 std::string string1 = this->toString(activeMods);
 bufferedWriter.write(string1);
 }

 return true;
 } catch (Exception exception) {
 ExceptionLogger.logException(exception);
 return false;
 }
 }
 }

 std::string toString(ActiveMods activeMods) {
 ScriptParser.Block block0 = new ScriptParser.Block();
 block0.setValue("VERSION", String.valueOf(1);
 ScriptParser.Block block1 = block0.addBlock("mods", nullptr);
 std::vector arrayList0 = activeMods.getMods();

 for (int int0 = 0; int0 < arrayList0.size(); int0++) {
 block1.addValue("mod", (String)arrayList0.get(int0);
 }

 ScriptParser.Block block2 = block0.addBlock("maps", nullptr);
 std::vector arrayList1 = activeMods.getMapOrder();

 for (int int1 = 0; int1 < arrayList1.size(); int1++) {
 block2.addValue("map", (String)arrayList1.get(int1);
 }

 StringBuilder stringBuilder = new StringBuilder();
 std::string string = System.lineSeparator();
 block0.prettyPrintElements(0, stringBuilder, string);
 return stringBuilder.toString();
 }

 bool read(const std::string& string0, ActiveMods activeMods) {
 activeMods.clear();

 try {
 try (
 FileReader fileReader = new FileReader(string0);
 BufferedReader bufferedReader = new BufferedReader(fileReader);
 ) {
 StringBuilder stringBuilder = new StringBuilder();

 for (String string1 = bufferedReader.readLine(); string1 != nullptr; string1 = bufferedReader.readLine()) {
 stringBuilder.append(string1);
 }

 this->fromString(stringBuilder.toString(), activeMods);
 }

 return true;
 } catch (FileNotFoundException fileNotFoundException) {
 return false;
 } catch (Exception exception) {
 ExceptionLogger.logException(exception);
 return false;
 }
 }

 void fromString(const std::string& string0, ActiveMods activeMods) {
 string0 = ScriptParser.stripComments(string0);
 ScriptParser.Block block0 = ScriptParser.parse(string0);
 int int0 = -1;
 ScriptParser.Value value0 = block0.getValue("VERSION");
 if (value0 != nullptr) {
 int0 = PZMath.tryParseInt(value0.getValue(), -1);
 }

 if (int0 >= 1 && int0 <= 1) {
 ScriptParser.Block block1 = block0.getBlock("mods", nullptr);
 if (block1 != nullptr) {
 for (ScriptParser.Value value1 : block1.values) {
 std::string string1 = value1.getKey().trim();
 if (string1.equalsIgnoreCase("mod")) {
 std::string string2 = value1.getValue().trim();
 if (!StringUtils.isNullOrWhitespace(string2) {
 activeMods.getMods().add(string2);
 }
 }
 }
 }

 ScriptParser.Block block2 = block0.getBlock("maps", nullptr);
 if (block2 != nullptr) {
 for (ScriptParser.Value value2 : block2.values) {
 std::string string3 = value2.getKey().trim();
 if (string3.equalsIgnoreCase("map")) {
 std::string string4 = value2.getValue().trim();
 if (!StringUtils.isNullOrWhitespace(string4) {
 activeMods.getMapOrder().add(string4);
 }
 }
 }
 }
 }
 }
}
} // namespace modding
} // namespace zombie
