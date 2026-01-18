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


class ReplaceProviderLua : public ReplaceProvider {
public:
 private static ConcurrentLinkedDeque<ReplaceSingle> pool_single = std::make_unique<ConcurrentLinkedDeque<>>();
 private static ConcurrentLinkedDeque<ReplaceList> pool_list = std::make_unique<ConcurrentLinkedDeque<>>();
 private static ConcurrentLinkedDeque<ReplaceProviderLua> pool = std::make_unique<ConcurrentLinkedDeque<>>();

 static ReplaceSingle alloc_single() {
 ReplaceSingle replaceSingle = pool_single.poll();
 if (replaceSingle == nullptr) {
 replaceSingle = std::make_unique<ReplaceSingle>();
 }

 return replaceSingle;
 }

 static void release_single(ReplaceSingle replaceSingle) {
 pool_single.offer(replaceSingle);
 }

 static ReplaceList alloc_list() {
 ReplaceList replaceList = pool_list.poll();
 if (replaceList == nullptr) {
 replaceList = std::make_unique<ReplaceList>();
 }

 return replaceList;
 }

 static void release_list(ReplaceList replaceList) {
 replaceList.getReplacements().clear();
 pool_list.offer(replaceList);
 }

 static ReplaceProviderLua Alloc() {
 ReplaceProviderLua replaceProviderLua = pool.poll();
 if (replaceProviderLua == nullptr) {
 replaceProviderLua = std::make_unique<ReplaceProviderLua>();
 }

 replaceProviderLua.reset();
 return replaceProviderLua;
 }

 void reset() {
 for (Entry entry : this->m_keys.entrySet()) {
 if (entry.getValue() instanceof ReplaceList) {
 release_list((ReplaceList)entry.getValue());
 } else {
 release_single((ReplaceSingle)entry.getValue());
 }
 }

 this->m_keys.clear();
 }

 void release() {
 this->reset();
 pool.offer(this);
 }

 void fromLuaTable(KahluaTableImpl kahluaTableImpl0) {
 for (Entry entry : kahluaTableImpl0.delegate.entrySet()) {
 if (entry.getKey() instanceof String) {
 if (entry.getValue() instanceof String) {
 this->addKey((String)entry.getKey(), (String)entry.getValue());
 } else if (entry.getValue() instanceof KahluaTableImpl) {
 KahluaTableImpl kahluaTableImpl1 = (KahluaTableImpl)entry.getValue();
 ReplaceList replaceList = alloc_list();

 for (int int0 = 1; int0 < kahluaTableImpl1.len() + 1; int0++) {
 replaceList.getReplacements().add((String)kahluaTableImpl1.rawget(int0);
 }

 if (replaceList.getReplacements().size() > 0) {
 this->addReplacer((String)entry.getKey(), replaceList);
 } else {
 DebugLog.log("ReplaceProvider -> key '" + entry.getKey() + "' contains no entries, ignoring.");
 release_list(replaceList);
 }
 }
 }
 }
 }

 void addKey(const std::string& string1, const std::string& string0) {
 ReplaceSingle replaceSingle = alloc_single();
 replaceSingle.setValue(string0);
 this->addReplacer(string1, replaceSingle);
 }
}
} // namespace templating
} // namespace text
} // namespace zombie
