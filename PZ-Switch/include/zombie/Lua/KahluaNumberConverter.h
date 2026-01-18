#pragma once
#include "se/krka/kahlua/converter/JavaToLuaConverter.h"
#include "se/krka/kahlua/converter/KahluaConverterManager.h"
#include "se/krka/kahlua/converter/LuaToJavaConverter.h"
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace Lua {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class KahluaNumberConverter {
public:
private
 KahluaNumberConverter() {}

 static void install(KahluaConverterManager kahluaConverterManager) {
 kahluaConverterManager.addLuaConverter(new LuaToJavaConverter<Double, Long>() {
 long fromLuaToJava(double double0, Class<Long> var2) {
 return double0.longValue();
 }

public
 Class<Long> getJavaType() { return Long.class; }

public
 Class<Double> getLuaType() { return Double.class; }
 });
 kahluaConverterManager.addLuaConverter(new LuaToJavaConverter<Double, Integer>() {
 int fromLuaToJava(double double0, Class<Integer> var2) {
 return double0.intValue();
 } // namespace Lua

 public
 Class<Integer> getJavaType() { return Integer.class; }

 public
 Class<Double> getLuaType() { return Double.class; }
 } // namespace zombie
);
 kahluaConverterManager.addLuaConverter(new LuaToJavaConverter<Double, Float>() {
 float fromLuaToJava(double double0, Class<Float> var2) {
 return new Float(double0.floatValue());
 }

 public
 Class<Float> getJavaType() { return Float.class; }

 public
 Class<Double> getLuaType() { return Double.class; }
 });
 kahluaConverterManager.addLuaConverter(new LuaToJavaConverter<Double, Byte>() {
 uint8_t fromLuaToJava(double double0, Class<Byte> var2) {
 return double0.byteValue();
 }

 public
 Class<Byte> getJavaType() { return Byte.class; }

 public
 Class<Double> getLuaType() { return Double.class; }
 });
 kahluaConverterManager.addLuaConverter(new LuaToJavaConverter<Double, Character>() {
 char fromLuaToJava(double double0, Class<Character> var2) {
 return (char)double0.intValue();
 }

 public
 Class<Character> getJavaType() { return Character.class; }

 public
 Class<Double> getLuaType() { return Double.class; }
 });
 kahluaConverterManager.addLuaConverter(new LuaToJavaConverter<Double, Short>() {
 short fromLuaToJava(double double0, Class<Short> var2) {
 return double0.shortValue();
 }

 public
 Class<Short> getJavaType() { return Short.class; }

 public
 Class<Double> getLuaType() { return Double.class; }
 });
 kahluaConverterManager.addJavaConverter(
 new KahluaNumberConverter.NumberToLuaConverter<>(Double.class);
 kahluaConverterManager.addJavaConverter(
 new KahluaNumberConverter.NumberToLuaConverter<>(Float.class);
 kahluaConverterManager.addJavaConverter(
 new KahluaNumberConverter.NumberToLuaConverter<>(Integer.class);
 kahluaConverterManager.addJavaConverter(
 new KahluaNumberConverter.NumberToLuaConverter<>(Long.class);
 kahluaConverterManager.addJavaConverter(
 new KahluaNumberConverter.NumberToLuaConverter<>(Short.class);
 kahluaConverterManager.addJavaConverter(
 new KahluaNumberConverter.NumberToLuaConverter<>(Byte.class);
 kahluaConverterManager.addJavaConverter(
 new KahluaNumberConverter.NumberToLuaConverter(Character.class);
 kahluaConverterManager.addJavaConverter(
 new KahluaNumberConverter.NumberToLuaConverter<>(double.class);
 kahluaConverterManager.addJavaConverter(
 new KahluaNumberConverter.NumberToLuaConverter<>(float.class);
 kahluaConverterManager.addJavaConverter(
 new KahluaNumberConverter.NumberToLuaConverter<>(int.class);
 kahluaConverterManager.addJavaConverter(
 new KahluaNumberConverter.NumberToLuaConverter<>(long.class);
 kahluaConverterManager.addJavaConverter(
 new KahluaNumberConverter.NumberToLuaConverter<>(short.class);
 kahluaConverterManager.addJavaConverter(
 new KahluaNumberConverter.NumberToLuaConverter<>(byte.class);
 kahluaConverterManager.addJavaConverter(
 new KahluaNumberConverter.NumberToLuaConverter(char.class);
 kahluaConverterManager.addJavaConverter(std::make_unique<JavaToLuaConverter<Boolean>>() {
 void* fromJavaToLua(bool boolean0) {
 return boolean0;
 }

 public
 Class<Boolean> getJavaType() { return Boolean.class; }
 });
 }

 private
 static class DoubleCache {
 static const int low = -128;
 static const int high = 10000;
 static Double[] cache = new Double[10129];

 static double valueOf(double double0) {
 return double0 = =
 (int)double0 && double0 >= -128.0 && double0 <= 10000.0
 ? cache[(int)(double0 + 128.0)]
 : new Double(double0);
 }

 static {
 int int0 = -128;

 for (int int1 = 0; int1 < cache.length; int1++) {
 cache[int1] = new Double(int0++);
 }
 }
 }

 private static class NumberToLuaConverter<T extends Number>
 implements JavaToLuaConverter<T> {
 private
 Class<T> clazz;

 public
 NumberToLuaConverter(Class<T> clazzx) { this->clazz = clazzx; }

 void *fromJavaToLua(T number) {
 return number instanceof
 Double ? number
 : KahluaNumberConverter.DoubleCache.valueOf(
 number.doubleValue());
 }

 public
 Class<T> getJavaType() { return this->clazz; }
 }
 }
 } // namespace Lua
 } // namespace zombie
