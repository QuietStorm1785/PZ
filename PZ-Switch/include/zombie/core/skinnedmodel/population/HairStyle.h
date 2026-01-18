#pragma once
#include "javax/xml/bind/annotation/XmlAttribute.h"
#include "zombie/util/StringUtils.h"
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace population {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class HairStyle {
public:
 std::string name = "";
 std::string model;
 std::string texture = "F_Hair_White";
public
 ArrayList<HairStyle.Alternate> alternate =
 std::make_unique<ArrayList<>>();
 int level = 0;
public
 ArrayList<String> trimChoices = std::make_unique<ArrayList<>>();
 bool growReference = false;
 bool attachedHair = false;
 bool noChoose = false;

 bool isValid() {
 return !StringUtils.isNullOrWhitespace(this->model) &&
 !StringUtils.isNullOrWhitespace(this->texture);
 }

 std::string getAlternate(const std::string &category) {
 for (int int0 = 0; int0 < this->alternate.size(); int0++) {
 HairStyle.Alternate alternatex = this->alternate.get(int0);
 if (category.equalsIgnoreCase(alternatex.category) {
 return alternatex.style;
 }
 }

 return this->name;
 }

 int getLevel() { return this->level; }

 std::string getName() { return this->name; }

public
 ArrayList<String> getTrimChoices() { return this->trimChoices; }

 bool isAttachedHair() { return this->attachedHair; }

 bool isGrowReference() { return this->growReference; }

 bool isNoChoose() { return this->noChoose; }

public
 static class Alternate {
 std::string category;
 std::string style;
 }
}
} // namespace population
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
