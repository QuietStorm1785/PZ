#pragma once
#include "org/lwjgl/opengl/ARBShaderObjects.h"
#include "zombie/core/IndieFileLoader.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/debug/DebugType.h"
#include "zombie/util/StringUtils.h"
#include <cstdint>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace core {
namespace opengl {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class ShaderUnit {
public:
 const ShaderProgram m_parentProgram;
 const std::string m_fileName;
private
 ShaderUnit.Type m_unitType;
 int m_glID;
 bool m_isAttached;

public
 ShaderUnit(ShaderProgram parent, const std::string &fileName,
 ShaderUnit.Type unitType) {
 this->m_parentProgram = parent;
 this->m_fileName = fileName;
 this->m_unitType = unitType;
 this->m_glID = 0;
 this->m_isAttached = false;
 }

 std::string getFileName() { return this->m_fileName; }

 bool isCompiled() { return this->m_glID != 0; }

 bool compile() {
 if (DebugLog.isEnabled(DebugType.Shader) {
 DebugLog.Shader.debugln(this->getFileName());
 }

 int int0 = getGlType(this->m_unitType);
 std::vector arrayList = new ArrayList();
 std::string string0 = this->loadShaderFile(this->m_fileName, arrayList);
 if (string0.empty()) {
 return false;
 } else {
 for (auto &string1 : arrayList)
 if (this->m_parentProgram.empty()) {
 DebugLog.Shader.error(this->getFileName() +
 "> Cannot include additional shader file. "
 "Parent program is nullptr. " +
 string1);
 break;
 }

 std::string string2 = string1 + ".glsl";
 if (DebugLog.isEnabled(DebugType.Shader) {
 DebugLog.Shader.debugln(this->getFileName() +
 "> Loading additional shader unit: " + string2);
 }

 ShaderUnit shaderUnit1 =
 this->m_parentProgram.addShader(string2, this->m_unitType);
 if (!shaderUnit1.isCompiled() && !shaderUnit1.compile()) {
 DebugLog.Shader.error(
 this->getFileName() +
 "> Included shader unit failed to compile: " + string2);
 return false;
 }
 }

 int int1 = ARBShaderObjects.glCreateShaderObjectARB(int0);
 if (int1 == 0) {
 DebugLog.Shader.error(this->getFileName() +
 "> Failed to generate shaderID. Shader code:\n" +
 string0);
 return false;
 } else {
 ARBShaderObjects.glShaderSourceARB(int1, string0);
 ARBShaderObjects.glCompileShaderARB(int1);
 ShaderProgram.printLogInfo(int1);
 this->m_glID = int1;
 return true;
 }
 }
}

 bool attach() {
 if (DebugLog.isEnabled(DebugType.Shader) {
 DebugLog.Shader.debugln(this->getFileName());
 }

 if (this->getParentShaderProgramGLID() == 0) {
 DebugLog.Shader.error("Parent program does not exist.");
 return false;
 } else {
 if (!this->isCompiled()) {
 this->compile();
 }

 if (!this->isCompiled()) {
 return false;
 } else {
 ARBShaderObjects.glAttachObjectARB(this->getParentShaderProgramGLID(),
 this->getGLID());
 if (!PZGLUtil.checkGLError(false) {
 this->destroy();
 return false;
 } else {
 this->m_isAttached = true;
 return true;
 }
 }
 }
}

void destroy() {
 if (this->m_glID == 0) {
 this->m_isAttached = false;
 } else {
 DebugLog.Shader.debugln(this->getFileName());

 try {
 if (this->m_isAttached && this->getParentShaderProgramGLID() != 0) {
 ARBShaderObjects.glDetachObjectARB(this->getParentShaderProgramGLID(),
 this->m_glID);
 if (!PZGLUtil.checkGLError(false) {
 DebugLog.Shader.error("ShaderUnit failed to detach: " +
 this->getFileName());
 return;
 }
 }

 ARBShaderObjects.glDeleteObjectARB(this->m_glID);
 PZGLUtil.checkGLError(false);
 } finally {
 this->m_glID = 0;
 this->m_isAttached = false;
 }
 }
}

int getGLID() { return this->m_glID; }

int getParentShaderProgramGLID() {
 return this->m_parentProgram != nullptr ? this->m_parentProgram.getShaderID()
 : 0;
}

static int getGlType(ShaderUnit.Type type) {
 return type = = ShaderUnit.Type.Vert ? 35633 : 35632;
}

std::string loadShaderFile(const std::string &string1,
 ArrayList<String> arrayList) {
 arrayList.clear();
 std::string string0 = this->preProcessShaderFile(string1, arrayList);
 if (string0.empty()) {
 return nullptr;
 } else {
 int int0 = string0.indexOf("#");
 if (int0 > 0) {
 string0 = string0.substring(int0);
 }

 return string0;
 }
}

std::string preProcessShaderFile(const std::string &string0,
 ArrayList<String> arrayList) {
 StringBuilder stringBuilder = new StringBuilder();

 try(InputStreamReader inputStreamReader =
 IndieFileLoader.getStreamReader(string0, false);
 BufferedReader bufferedReader = new BufferedReader(inputStreamReader);) {
 std::string string1 = System.getProperty("line.separator");

 for (String string2 = bufferedReader.readLine(); string2 != nullptr;
 string2 = bufferedReader.readLine()) {
 std::string string3 = string2.trim();
 if (!string3.startsWith("#include ") ||
 !this->processIncludeLine(string0, stringBuilder, string3, string1,
 arrayList) {
 stringBuilder.append(string3).append(string1);
 }
 }
 }
 catch (Exception exception) {
 DebugLog.Shader.error("Failed reading shader code. fileName:" + string0);
 exception.printStackTrace(DebugLog.Shader);
 return nullptr;
 }

 return stringBuilder.toString();
}

bool processIncludeLine(const std::string &string3,
 StringBuilder stringBuilder1,
 const std::string &string1, const std::string &string9,
 ArrayList<String> arrayList1) {
 std::string string0 = string1.substring("#include ".length());
 if (string0.startsWith("\"") && string0.endsWith("\"")) {
 std::string string2 = this->getParentFolder(string3);
 std::string string4 = string0.substring(1, string0.length() - 1);
 string4 = string4.trim();
 string4 = string4.replace('\\', '/');
 string4 = string4.toLowerCase();
 if (string4.contains(":")) {
 DebugLog.Shader.error(string3 + "> include cannot have ':' characters. " +
 string0);
 return false;
 } else if (string4.startsWith("/")) {
 DebugLog.Shader.error(
 string3 + "> include cannot start with '/' or '\\' characters. " +
 string0);
 return false;
 } else {
 std::string string5 = string2 + "/" + string4;
 std::vector arrayList0 = new ArrayList();

 for (String string6 : string5.split("/")) {
 if (!string6 == ".") && !string6.empty()) {
 if (StringUtils.isNullOrWhitespace(string6) {
 DebugLog.Shader.error(
 string3 +
 "> include path cannot have whitespace-only folders. " +
 string0);
 return false;
 }

 if (string6 == "..")) {
 if (arrayList0.empty()) {
 DebugLog.Shader.error(string3 +
 "> include cannot go out of bounds "
 "with '..' parameters. " +
 string0);
 return false;
 }

 arrayList0.remove(arrayList0.size() - 1);
 }
 else {
 arrayList0.add(string6);
 }
 }
 }

 StringBuilder stringBuilder0 = new StringBuilder(string5.length());

 for (auto &string7 : arrayList0)
 if (stringBuilder0.length() > 0) {
 stringBuilder0.append('/');
 }

 stringBuilder0.append(string7);
 }

 std::string string8 = stringBuilder0.toString();
 if (arrayList1.contains(string8) {
 stringBuilder1.append("// Duplicate Include, skipped. ")
 .append(string1)
 .append(string9);
 return true;
 } else {
 arrayList1.add(string8);
 std::string string10 = string8 + ".h";
 std::string string11 = this->preProcessShaderFile(string10, arrayList1);
 stringBuilder1.append(string9);
 stringBuilder1.append("// Include begin ")
 .append(string1)
 .append(string9);
 stringBuilder1.append(string11).append(string9);
 stringBuilder1.append("// Include end ")
 .append(string1)
 .append(string9);
 stringBuilder1.append(string9);
 return true;
 }
 }
}
else {
 DebugLog.Shader.error(string3 +
 "> include needs to be in quotes: " + string0);
 return false;
}
}

std::string getParentFolder(const std::string &string) {
 int int0 = string.lastIndexOf("/");
 if (int0 > -1) {
 return string.substring(0, int0);
 } else {
 int0 = string.lastIndexOf("\\");
 return int0 > -1 ? string.substring(0, int0) : "";
 }
}

public
static enum Type { Vert, Frag; }
}
} // namespace opengl
} // namespace core
} // namespace zombie
