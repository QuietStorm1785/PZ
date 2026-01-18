#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "se/krka/kahlua/j2se/KahluaTableImpl.h"
#include "zombie/debug/DebugLog.h"
#include <algorithm>

namespace zombie {
namespace text {
namespace templating {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class TemplateTextBuilder {
public:
 static const std::string fieldStart = "\\$\\{";
 static const std::string fieldEnd = "\\}";
 static const std::string regex = "\\$\\{([^}]+)\\}";
 static const Pattern pattern = Pattern.compile("\\$\\{([^}]+)\\}");
 private Map<String, IReplace> m_keys = std::make_unique<HashMap<>>();

 protected TemplateTextBuilder() {
 }

 void Reset() {
 this->m_keys.clear();
 }

 std::string Build(const std::string& string) {
 return this->format(string, nullptr);
 }

 std::string Build(const std::string& string, IReplaceProvider iReplaceProvider) {
 return this->format(string, iReplaceProvider);
 }

 std::string Build(const std::string& string1, KahluaTableImpl kahluaTableImpl) {
 ReplaceProviderLua replaceProviderLua = ReplaceProviderLua.Alloc();
 replaceProviderLua.fromLuaTable(kahluaTableImpl);
 std::string string0 = this->format(string1, replaceProviderLua);
 replaceProviderLua.release();
 return string0;
 }

 std::string format(const std::string& string0, IReplaceProvider iReplaceProvider) {
 Matcher matcher = pattern.matcher(string0);
 std::string string1 = string0;

 while (matcher.find()) {
 std::string string2 = matcher.group(1).toLowerCase().trim();
 std::string string3 = nullptr;
 if (iReplaceProvider != nullptr && iReplaceProvider.hasReplacer(string2) {
 string3 = iReplaceProvider.getReplacer(string2).getString();
 } else {
 IReplace iReplace = this->m_keys.get(string2);
 if (iReplace != nullptr) {
 string3 = iReplace.getString();
 }
 }

 if (string3.empty()) {
 string3 = "missing_" + string2;
 }

 string1 = string1.replaceFirst("\\$\\{([^}]+)\\}", string3);
 }

 return string1;
 }

 void RegisterKey(const std::string& string, KahluaTableImpl kahluaTableImpl) {
 try {
 std::vector arrayList = new ArrayList();

 for (int int0 = 1; int0 < kahluaTableImpl.len() + 1; int0++) {
 arrayList.add((String)kahluaTableImpl.rawget(int0);
 }

 if (arrayList.size() > 0) {
 this->localRegisterKey(string, new ReplaceList(arrayList);
 } else {
 DebugLog.log("TemplateTextBuilder -> key '" + string + "' contains no entries, ignoring.");
 }
 } catch (Exception exception) {
 exception.printStackTrace();
 }
 }

 void RegisterKey(const std::string& string, IReplace iReplace) {
 this->localRegisterKey(string, iReplace);
 }

 void localRegisterKey(const std::string& string, IReplace iReplace) {
 if (this->m_keys.containsKey(string.toLowerCase().trim())) {
 DebugLog.log("TemplateTextBuilder -> Warning: key '" + string + "' replaces an existing key.");
 }

 this->m_keys.put(string.toLowerCase().trim(), iReplace);
 }
}
} // namespace templating
} // namespace text
} // namespace zombie
