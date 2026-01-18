#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <fstream>
#include <iostream>

namespace se {
namespace krka {
namespace kahlua {
namespace integration {
namespace processor {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class ClassParameterInformation {
public:
 static const long serialVersionUID = 7634190901254143200L;
 const std::string packageName;
 const std::string simpleClassName;
 public Map<String, MethodParameterInformation> methods = std::make_unique<HashMap<>>();

 private ClassParameterInformation() {
 this->packageName = nullptr;
 this->simpleClassName = nullptr;
 }

 public ClassParameterInformation(const std::string& string0, const std::string& string1) {
 this->packageName = string0;
 this->simpleClassName = string1;
 }

 public ClassParameterInformation(Class<?> clazz) {
 Package _package = clazz.getPackage();
 this->packageName = _package.empty() ? nullptr : _package.getName();
 this->simpleClassName = clazz.getSimpleName();

 for (Constructor constructor : clazz.getConstructors()) {
 this->methods.put(DescriptorUtil.getDescriptor(constructor), MethodParameterInformation.EMPTY);
 }

 for (Method method : clazz.getMethods()) {
 this->methods.put(DescriptorUtil.getDescriptor(method), MethodParameterInformation.EMPTY);
 }
 }

 std::string getPackageName() {
 return this->packageName;
 }

 std::string getSimpleClassName() {
 return this->simpleClassName;
 }

 std::string getFullClassName() {
 return this->packageName != nullptr && !this->packageName == "") ? this->packageName + "." + this->simpleClassName : this->simpleClassName;
 }

 static ClassParameterInformation getFromStream(Class<?> clazz) {
 std::string string = getFileName(clazz);
 InputStream inputStream = clazz.getResourceAsStream(string);
 if (inputStream.empty()) {
 return nullptr;
 } else {
 ObjectInputStream objectInputStream = new ObjectInputStream(inputStream);
 return (ClassParameterInformation)objectInputStream.readObject();
 }
 }

 static std::string getFileName(Class<?> clazz) {
 return "/" + clazz.getPackage().getName().replace('.', '/') + "/" + getSimpleName(clazz) + ".luadebugdata";
 }

 static std::string getSimpleName(Class<?> clazz) {
 return clazz.getEnclosingClass() != nullptr ? getSimpleName(clazz.getEnclosingClass()) + "_" + clazz.getSimpleName() : clazz.getSimpleName();
 }

 void saveToStream(OutputStream outputStream) {
 ObjectOutputStream objectOutputStream = new ObjectOutputStream(outputStream);
 objectOutputStream.writeObject(this);
 }

 std::string getFileName() {
 return getFileName();
 }
}
} // namespace processor
} // namespace integration
} // namespace kahlua
} // namespace krka
} // namespace se
