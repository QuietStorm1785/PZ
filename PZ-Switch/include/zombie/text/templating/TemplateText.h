#pragma once
#include "se/krka/kahlua/j2se/KahluaTableImpl.h"
#include "zombie/Lua/LuaEventManager.h"
#include "zombie/characters/SurvivorFactory.h"
#include <algorithm>
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
 * TurboTuTone.
 */
class TemplateText {
public:
 static const ITemplateBuilder builder = new TemplateTextBuilder();
 static const Random m_random = new Random(4397238L);

 static std::string Build(const std::string &input) {
 return builder.Build(input);
 }

 static std::string Build(const std::string &input,
 IReplaceProvider replaceProvider) {
 return builder.Build(input, replaceProvider);
 }

 static std::string Build(const std::string &input, KahluaTableImpl table) {
 try {
 return builder.Build(input, table);
 } catch (Exception exception) {
 exception.printStackTrace();
 return input;
 }
 }

 static void RegisterKey(const std::string &key, KahluaTableImpl table) {
 builder.RegisterKey(key, table);
 }

 static void RegisterKey(const std::string &key, IReplace replace) {
 builder.RegisterKey(key, replace);
 }

 static void Initialize() {
 builder.RegisterKey("lastname", std::make_unique<IReplace>() {
 std::string getString() {
 return SurvivorFactory.getRandomSurname();
 }
 });
 builder.RegisterKey("firstname", std::make_unique<IReplace>() {
 std::string getString() {
 return TemplateText.RandNext(100) > 50 ? SurvivorFactory.getRandomForename(true) : SurvivorFactory.getRandomForename(false);
 } // namespace templating
 } // namespace text
);
 builder.RegisterKey("maleName", std::make_unique<IReplace>() {
 std::string getString() {
 return SurvivorFactory.getRandomForename(false);
 } // namespace zombie
 });
 builder.RegisterKey("femaleName", std::make_unique<IReplace>() {
 std::string getString() {
 return SurvivorFactory.getRandomForename(true);
 }
 });
 LuaEventManager.triggerEvent("OnTemplateTextInit");
 }

 static void Reset() { builder.Reset(); }

 static float RandNext(float min, float max) {
 if (min == max) {
 return min;
 } else {
 if (min > max) {
 min = max;
 max = max;
 }

 return min + m_random.nextFloat() * (max - min);
 }
 }

 static float RandNext(float bound) {
 return m_random.nextFloat() * bound;
 }

 static int RandNext(int min, int max) {
 if (min == max) {
 return min;
 } else {
 if (min > max) {
 min = max;
 max = max;
 }

 return min + m_random.nextInt(max - min);
 }
 }

 static int RandNext(int bound) { return m_random.nextInt(bound); }
 }
 } // namespace templating
 } // namespace text
 } // namespace zombie
