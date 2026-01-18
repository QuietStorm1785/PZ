#pragma once
#include "se/krka/kahlua/j2se/KahluaTableImpl.h"
#include "zombie/debug/DebugLog.h"
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace text {
namespace templating {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

/**
 * TurboTuTone. A generic non-pooled ReplaceProvider that can be used for
 * example in scripting, where the provider could provide forced overrides for
 * certain template keys.
 */
class ReplaceProvider {
public:
protected
 Map<String, IReplace> m_keys = std::make_unique<HashMap<>>();

 void addKey(const std::string &key, String) {
 this->addReplacer(key, std::make_unique<IReplace>() {
 std::string getString() {
 return value;
 }
 });
 } // namespace templating

 void addKey(const std::string &key, KahluaTableImpl table) {
 try {
 std::vector arrayList = new ArrayList();

 for (int int0 = 1; int0 < table.len() + 1; int0++) {
 arrayList.add((String)table.rawget(int0);
 }

 if (arrayList.size() > 0) {
 this->addReplacer(key, new ReplaceList(arrayList);
 } else {
 DebugLog.log("ReplaceProvider -> key '" + key +
 "' contains no entries, ignoring.");
 }
 } catch (Exception exception) {
 exception.printStackTrace();
 }
 }

 void addReplacer(const std::string &key, IReplace replace) {
 if (this->m_keys.containsKey(key.toLowerCase())) {
 DebugLog.log("ReplaceProvider -> Warning: key '" + key +
 "' replaces an existing key.");
 }

 this->m_keys.put(key.toLowerCase(), replace);
 }

 bool hasReplacer(const std::string &key) {
 return this->m_keys.containsKey(key);
 }

 IReplace getReplacer(const std::string &key) {
 return this->m_keys.get(key);
 }
 } // namespace text
 } // namespace zombie
 } // namespace text
 } // namespace zombie
