#pragma once
#include "se/krka/kahlua/integration/expose/MethodDebugInformation.h"
#include "se/krka/kahlua/integration/expose/MethodParameter.h"
#include <cstdint>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace se {
namespace krka {
namespace kahlua {
namespace integration {
namespace doc {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class DokuWikiPrinter {
public:
 const ApiInformation information;
 const PrintWriter writer;

public
 DokuWikiPrinter(File file, ApiInformation apiInformation) {
 this(new FileWriter(file), apiInformation);
 }

public
 DokuWikiPrinter(Writer writerx, ApiInformation apiInformation) {
 this->information = apiInformation;
 this->writer = new PrintWriter(writerx);
 }

 void process() {
 this->printClassHierarchy();
 this->printFunctions();
 this->writer.close();
 }

 void printFunctions() {
 this->writer.println("====== Global functions ======");

 for (Class clazz : this->information.getAllClasses()) {
 this->printClassFunctions(clazz);
 }
 }

 void printClassFunctions(Class<?> clazz) {
 std::vector list = this->information.getFunctionsForClass(clazz);
 if (list.size() > 0) {
 this->writer.printf("===== %s ====\n", clazz.getSimpleName());
 this->writer.printf("In package: %s\n", clazz.getPackage().getName());

 for (auto &methodDebugInformation : list)
 this->printFunction(methodDebugInformation, "====");
 }

 this->writer.printf("\n----\n\n");
 }
}

 void printFunction(MethodDebugInformation methodDebugInformation, std::string_view string0) {
 this->writer.printf("%s %s %s\n", string0, methodDebugInformation.getLuaName(),
 string0);
 this->writer.printf("<code lua>%s</code>\n",
 methodDebugInformation.getLuaDescription());

 for (MethodParameter methodParameter :
 methodDebugInformation.getParameters()) {
 std::string string1 = methodParameter.getName();
 std::string string2 = methodParameter.getType();
 std::string string3 = methodParameter.getDescription();
 if (string3.empty()) {
 this->writer.printf(" - **''%s''** ''%s''\n", string2, string1);
 } else {
 this->writer.printf(" - **''%s''** ''%s'': %s\n", string2, string1,
 string3);
 }
 }

 std::string string4 = methodDebugInformation.getReturnDescription();
 if (string4.empty()) {
 this->writer.printf(" * returns ''%s''\n",
 methodDebugInformation.getReturnType());
 } else {
 this->writer.printf(" * returns ''%s'': %s\n",
 methodDebugInformation.getReturnType(), string4);
 }
}

void printClassHierarchy() {
 this->writer.println("====== Class hierarchy ======");

 for (Class clazz : this->information.getRootClasses()) {
 this->printClassHierarchy(clazz, nullptr);
 }
}

 void printClassHierarchy(Class<?> clazz0, Class<?> clazz1) {
 std::vector list0 = this->information.getChildrenForClass(clazz0);
 std::vector list1 = this->information.getMethodsForClass(clazz0);
 if (list0.size() > 0 || list1.size() > 0 || clazz1 != nullptr) {
 this->writer.printf("===== %s =====\n", clazz0.getSimpleName());
 this->writer.printf("In package: ''%s''\n",
 clazz0.getPackage().getName());
 if (clazz1 != nullptr) {
 this->writer.printf("\nSubclass of [[#%s|%s]]\n",
 clazz1.getSimpleName(), clazz1.getSimpleName());
 }

 if (list0.size() > 0) {
 this->writer.printf("\nChildren: ");
 bool boolean0 = false;

 for (auto &clazz2 : list0)
 if (boolean0) {
 this->writer.print(", ");
 } else {
 boolean0 = true;
 }

 this->writer.printf("[[#%s|%s]]", clazz2.getSimpleName(),
 clazz2.getSimpleName());
 }
 }

 this->printMethods(clazz0);
 this->writer.printf("\n----\n\n");

 for (auto &clazz3 : list0)
 this->printClassHierarchy(clazz3, clazz0);
 }
 }
 }

 void printMethods(Class<?> clazz) {
 std::vector list = this->information.getMethodsForClass(clazz);
 if (list.size() > 0) {
 for (auto &methodDebugInformation : list)
 this->printFunction(methodDebugInformation, "====");
 }
 }
 }
 }
 } // namespace doc
 } // namespace integration
 } // namespace kahlua
 } // namespace krka
 } // namespace se
