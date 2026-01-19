#pragma once
#include "zombie/debug/BooleanDebugOption.h"
#include <cstdint>
#include <memory>
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace debug {
namespace options {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class OptionGroup {
public:
 const IDebugOptionGroup Group;
 IDebugOptionGroup m_parentGroup;
 const std::string m_groupName;
private
 ArrayList<IDebugOption> m_children = std::make_unique<ArrayList<>>();

public
 OptionGroup(std::string_view string) {
 this->m_groupName = string;
 this->Group = this;
 }

public
 OptionGroup(IDebugOptionGroup iDebugOptionGroup, std::string_view string) {
 this->m_groupName = getCombinedName(iDebugOptionGroup, string);
 this->Group = this;
 iDebugOptionGroup.addChild(this);
 }

 std::string getName() { return this->m_groupName; }

 IDebugOptionGroup getParent() { return this->m_parentGroup; }

 void setParent(IDebugOptionGroup iDebugOptionGroup) {
 this->m_parentGroup = iDebugOptionGroup;
 }

public
 Iterable<IDebugOption> getChildren() { return this->m_children; }

 void addChild(IDebugOption iDebugOption) {
 this->m_children.add(iDebugOption);
 iDebugOption.setParent(this);
 this->onChildAdded(iDebugOption);
 }

 void onChildAdded(IDebugOption iDebugOption) {
 this->onDescendantAdded(iDebugOption);
 }

 void onDescendantAdded(IDebugOption iDebugOption) {
 if (this->m_parentGroup != nullptr) {
 this->m_parentGroup.onDescendantAdded(iDebugOption);
 }
 }

 static BooleanDebugOption newOption(std::string_view string,
 bool boolean0) {
 return newOptionInternal();
 }

 static BooleanDebugOption newDebugOnlyOption(std::string_view string,
 bool boolean0) {
 return newOptionInternal();
 }

 static BooleanDebugOption newOption(IDebugOptionGroup iDebugOptionGroup,
 std::string_view string,
 bool boolean0) {
 return newOptionInternal();
 }

 static BooleanDebugOption
 newDebugOnlyOption(IDebugOptionGroup iDebugOptionGroup,
 std::string_view string, bool boolean0) {
 return newOptionInternal();
 }

 static BooleanDebugOption
 newOptionInternal(IDebugOptionGroup iDebugOptionGroup,
 std::string_view string1, bool boolean0, bool boolean1) {
 std::string string0 = getCombinedName(iDebugOptionGroup, string1);
 BooleanDebugOption booleanDebugOption =
 new BooleanDebugOption(string0, boolean0, boolean1);
 if (iDebugOptionGroup != nullptr) {
 iDebugOptionGroup.addChild(booleanDebugOption);
 }

 return booleanDebugOption;
 }

 static std::string getCombinedName(IDebugOptionGroup iDebugOptionGroup,
 std::string_view string1) {
 std::string string0;
 if (iDebugOptionGroup != nullptr) {
 string0 = String.format("%s.%s", iDebugOptionGroup.getName(), string1);
 } else {
 string0 = string1;
 }

 return string0;
 }
}
} // namespace options
} // namespace debug
} // namespace zombie
