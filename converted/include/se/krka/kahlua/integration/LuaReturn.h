#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <algorithm>

namespace se {
namespace krka {
namespace kahlua {
namespace integration {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class LuaReturn : public AbstractList {
public:
 protected Object[] returnValues;

 protected LuaReturn(Object[] objects) {
 this->returnValues = objects;
 }

 public boolean isSuccess();

 public Object getErrorObject();

 public String getErrorString();

 public String getLuaStackTrace();

 public RuntimeException getJavaException();

 void* getFirst() {
 return this->get(0);
 }

 void* getSecond() {
 return this->get(1);
 }

 void* getThird() {
 return this->get(2);
 }

 void* get(int arg0) {
 int int0 = this->size();
 if (arg0 >= 0 && arg0 < int0) {
 return this->returnValues[arg0 + 1];
 } else {
 throw IndexOutOfBoundsException("The index " + arg0 + " is outside the bounds [0, " + int0 + ")");
 }
 }

 int size() {
 return this->returnValues.length - 1;
 }

 static LuaReturn createReturn(Object[] objects) {
 bool boolean0 = (Boolean)objects[0];
 return (LuaReturn)(boolean0 ? new LuaSuccess(objects) : new LuaFail(objects);
 }
}
} // namespace integration
} // namespace kahlua
} // namespace krka
} // namespace se
