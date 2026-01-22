#pragma once
#include <sstream>
#include <stack>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "org/lwjgl/opengl/ARBShaderObjects.h"
#include "zombie/core/IndieFileLoader.h"
#include "zombie/core/opengl/ShaderUnit/Type.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/debug/DebugType.h"
#include "zombie/util/StringUtils.h"
#include <fstream>
#include <iostream>

namespace zombie {
namespace core {
namespace opengl {


class ShaderUnit {
public:
    const ShaderProgram m_parentProgram;
    const std::string m_fileName;
    const Type m_unitType;
    int m_glID;
    bool m_isAttached;

    public ShaderUnit(ShaderProgram var1, const std::string& var2, Type var3) {
      this.m_parentProgram = var1;
      this.m_fileName = var2;
      this.m_unitType = var3;
      this.m_glID = 0;
      this.m_isAttached = false;
   }

    std::string getFileName() {
      return this.m_fileName;
   }

    bool isCompiled() {
      return this.m_glID != 0;
   }

    bool compile() {
      if (DebugLog.isEnabled(DebugType.Shader)) {
         DebugLog.Shader.debugln(this.getFileName());
      }

    int var1 = getGlType(this.m_unitType);
    std::vector var2 = new std::vector();
    std::string var3 = this.loadShaderFile(this.m_fileName, var2);
      if (var3 == nullptr) {
    return false;
      } else {
    for (auto& var5 : var2)            if (this.m_parentProgram == nullptr) {
               DebugLog.Shader.error(this.getFileName() + "> Cannot include additional shader file. Parent program is nullptr. " + var5);
               break;
            }

    std::string var6 = var5 + ".glsl";
            if (DebugLog.isEnabled(DebugType.Shader)) {
               DebugLog.Shader.debugln(this.getFileName() + "> Loading additional shader unit: " + var6);
            }

    ShaderUnit var7 = this.m_parentProgram.addShader(var6, this.m_unitType);
            if (!var7.isCompiled() && !var7.compile()) {
               DebugLog.Shader.error(this.getFileName() + "> Included shader unit failed to compile: " + var6);
    return false;
            }
         }

    int var8 = ARBShaderObjects.glCreateShaderObjectARB(var1);
         if (var8 == 0) {
            DebugLog.Shader.error(this.getFileName() + "> Failed to generate shaderID. Shader code:\n" + var3);
    return false;
         } else {
            ARBShaderObjects.glShaderSourceARB(var8, var3);
            ARBShaderObjects.glCompileShaderARB(var8);
            ShaderProgram.printLogInfo(var8);
            this.m_glID = var8;
    return true;
         }
      }
   }

    bool attach() {
      if (DebugLog.isEnabled(DebugType.Shader)) {
         DebugLog.Shader.debugln(this.getFileName());
      }

      if (this.getParentShaderProgramGLID() == 0) {
         DebugLog.Shader.error("Parent program does not exist.");
    return false;
      } else {
         if (!this.isCompiled()) {
            this.compile();
         }

         if (!this.isCompiled()) {
    return false;
         } else {
            ARBShaderObjects.glAttachObjectARB(this.getParentShaderProgramGLID(), this.getGLID());
            if (!PZGLUtil.checkGLError(false)) {
               this.destroy();
    return false;
            } else {
               this.m_isAttached = true;
    return true;
            }
         }
      }
   }

    void destroy() {
      if (this.m_glID == 0) {
         this.m_isAttached = false;
      } else {
         DebugLog.Shader.debugln(this.getFileName());

         try {
            if (this.m_isAttached && this.getParentShaderProgramGLID() != 0) {
               ARBShaderObjects.glDetachObjectARB(this.getParentShaderProgramGLID(), this.m_glID);
               if (!PZGLUtil.checkGLError(false)) {
                  DebugLog.Shader.error("ShaderUnit failed to detach: " + this.getFileName());
                  return;
               }
            }

            ARBShaderObjects.glDeleteObjectARB(this.m_glID);
            PZGLUtil.checkGLError(false);
         } finally {
            this.m_glID = 0;
            this.m_isAttached = false;
         }
      }
   }

    int getGLID() {
      return this.m_glID;
   }

    int getParentShaderProgramGLID() {
      return this.m_parentProgram != nullptr ? this.m_parentProgram.getShaderID() : 0;
   }

    static int getGlType(Type var0) {
    return var0 = = Type.Vert ? 35633 : 35632;
   }

    std::string loadShaderFile(const std::string& var1, std::vector<std::string> var2) {
      var2.clear();
    std::string var3 = this.preProcessShaderFile(var1, var2);
      if (var3 == nullptr) {
    return nullptr;
      } else {
    int var4 = var3.indexOf("#");
         if (var4 > 0) {
            var3 = var3.substr(var4);
         }

    return var3;
      }
   }

    std::string preProcessShaderFile(const std::string& var1, std::vector<std::string> var2) {
    std::stringstream var3 = new std::stringstream();

      try (
    InputStreamReader var4 = IndieFileLoader.getStreamReader(var1, false);
    BufferedReader var5 = std::make_shared<BufferedReader>(var4);
      ) {
    std::string var6 = System.getProperty("line.separator");

         for (std::string var7 = var5.readLine(); var7 != nullptr; var7 = var5.readLine()) {
    std::string var8 = var7.trim();
            if (!var8.startsWith("#include ") || !this.processIncludeLine(var1, var3, var8, var6, var2)) {
               var3.append(var8).append(var6);
            }
         }
      } catch (Exception var13) {
         DebugLog.Shader.error("Failed reading shader code. fileName:" + var1);
         var13.printStackTrace(DebugLog.Shader);
    return nullptr;
      }

      return var3;
   }

    bool processIncludeLine(const std::string& var1, std::stringstream var2, const std::string& var3, const std::string& var4, std::vector<std::string> var5) {
    std::string var6 = var3.substr("#include ".length());
      if (var6.startsWith("\"") && var6.endsWith("\"")) {
    std::string var7 = this.getParentFolder(var1);
    std::string var8 = var6.substr(1, var6.length() - 1);
         var8 = var8.trim();
         var8 = var8.replace('\\', '/');
         var8 = var8.toLowerCase();
         if (var8.contains(":")) {
            DebugLog.Shader.error(var1 + "> include cannot have ':' characters. " + var6);
    return false;
         } else if (var8.startsWith("/")) {
            DebugLog.Shader.error(var1 + "> include cannot start with '/' or '\\' characters. " + var6);
    return false;
         } else {
    std::string var9 = var7 + "/" + var8;
    std::vector var10 = new std::vector();

            for (std::string var14 : var9.split("/")) {
               if (!var14 == ".") && !var14.empty()) {
                  if (StringUtils.isNullOrWhitespace(var14)) {
                     DebugLog.Shader.error(var1 + "> include path cannot have whitespace-only folders. " + var6);
    return false;
                  }

                  if (var14 == "..")) {
                     if (var10.empty()) {
                        DebugLog.Shader.error(var1 + "> include cannot go out of bounds with '..' parameters. " + var6);
    return false;
                     }

                     var10.remove(var10.size() - 1);
                  } else {
                     var10.push_back(var14);
                  }
               }
            }

    std::stringstream var18 = new std::stringstream(var9.length());

    for (auto& var21 : var10)               if (var18.length() > 0) {
                  var18.append('/');
               }

               var18.append(var21);
            }

    std::string var20 = var18;
            if (var5.contains(var20)) {
               var2.append("// Duplicate Include, skipped. ").append(var3).append(var4);
    return true;
            } else {
               var5.push_back(var20);
    std::string var22 = var20 + ".h";
    std::string var23 = this.preProcessShaderFile(var22, var5);
               var2.append(var4);
               var2.append("// Include begin ").append(var3).append(var4);
               var2.append(var23).append(var4);
               var2.append("// Include end   ").append(var3).append(var4);
               var2.append(var4);
    return true;
            }
         }
      } else {
         DebugLog.Shader.error(var1 + "> include needs to be in quotes: " + var6);
    return false;
      }
   }

    std::string getParentFolder(const std::string& var1) {
    int var2 = var1.lastIndexOf("/");
      if (var2 > -1) {
         return var1.substr(0, var2);
      } else {
         var2 = var1.lastIndexOf("\\");
         return var2 > -1 ? var1.substr(0, var2) : "";
      }
   }
}
} // namespace opengl
} // namespace core
} // namespace zombie
