#pragma once
#include "zombie/SandboxOptions.h"
#include "zombie/ZomboidFileSystem.h"
#include "zombie/core/logger/ExceptionLogger.h"
#include "zombie/core/math/PZMath.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/gameStates/ChooseGameInfo.h"
#include "zombie/scripting/ScriptParser.h"
#include "zombie/util/StringUtils.h"
#include <cstdint>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace sandbox {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class CustomSandboxOptions {
public:
 static const int VERSION1 = 1;
 static const int VERSION = 1;
 static const CustomSandboxOptions instance = new CustomSandboxOptions();
private
 ArrayList<CustomSandboxOption> m_options =
 std::make_unique<ArrayList<>>();

 void init() {
 std::vector arrayList = ZomboidFileSystem.instance.getModIDs();

 for (int int0 = 0; int0 < arrayList.size(); int0++) {
 std::string string = (String)arrayList.get(int0);
 ChooseGameInfo.Mod mod = ChooseGameInfo.getAvailableModDetails(string);
 if (mod != nullptr) {
 File file = new File(mod.getDir() + File.separator + "media" +
 File.separator + "sandbox-options.txt");
 if (file.exists() && !file.isDirectory()) {
 this->readFile(file.getAbsolutePath());
 }
 }
 }
 }

 static void Reset() { instance.m_options.clear(); }

 void initInstance(SandboxOptions sandboxOptions) {
 for (int int0 = 0; int0 < this->m_options.size(); int0++) {
 CustomSandboxOption customSandboxOption = this->m_options.get(int0);
 sandboxOptions.newCustomOption(customSandboxOption);
 }
 }

 bool readFile(const std::string &string0) {
 try {
 bool boolean0;
 try(FileReader fileReader = new FileReader(string0);
 BufferedReader bufferedReader = new BufferedReader(fileReader);) {
 StringBuilder stringBuilder = new StringBuilder();

 for (String string1 = bufferedReader.readLine(); string1 != nullptr;
 string1 = bufferedReader.readLine()) {
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

 void parse(const std::string &string) {
 string = ScriptParser.stripComments(string);
 ScriptParser.Block block0 = ScriptParser.parse(string);
 int int0 = -1;
 ScriptParser.Value value = block0.getValue("VERSION");
 if (value != nullptr) {
 int0 = PZMath.tryParseInt(value.getValue(), -1);
 }

 if (int0 >= 1 && int0 <= 1) {
 for (ScriptParser.Block block1 : block0.children) {
 if (!block1.type.equalsIgnoreCase("option")) {
 throw RuntimeException("unknown block type \"" + block1.type +
 "\"");
 }

 CustomSandboxOption customSandboxOption = this->parseOption(block1);
 if (customSandboxOption.empty()) {
 DebugLog.General.warn("failed to parse custom sandbox option \"%s\"",
 block1.id);
 } else {
 this->m_options.add(customSandboxOption);
 }
 }
 } else {
 throw RuntimeException("invalid or missing VERSION");
 }
 }

 CustomSandboxOption parseOption(ScriptParser.Block block) {
 if (StringUtils.isNullOrWhitespace(block.id) {
 DebugLog.General.warn("missing or empty option id");
 return nullptr;
 } else {
 ScriptParser.Value value = block.getValue("type");
 if (value != nullptr &&
 !StringUtils.isNullOrWhitespace(value.getValue())) {
 std::string string = value.getValue().trim();
 switch (string) {
 case "boolean":
 return CustomBooleanSandboxOption.parse(block);
 case "double":
 return CustomDoubleSandboxOption.parse(block);
 case "enum":
 return CustomEnumSandboxOption.parse(block);
 case "integer":
 return CustomIntegerSandboxOption.parse(block);
 case "string":
 return CustomStringSandboxOption.parse(block);
 default:
 DebugLog.General.warn("unknown option type \"%s\"",
 value.getValue().trim());
 return nullptr;
 }
 } else {
 DebugLog.General.warn("missing or empty value \"type\"");
 return nullptr;
 }
 }
 }
}
} // namespace sandbox
} // namespace zombie
