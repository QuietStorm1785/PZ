#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <GL/glew.h>
#include <GL/glew.h>
#include <GL/glew.h>
#include "org/lwjgl/system/MemoryUtil.h"
#include "org/lwjgl/util/vector/Matrix4f.h"
#include "org/lwjglx/BufferUtils.h"
#include "zombie/DebugFileWatcher.h"
#include "zombie/PredicatedFileWatcher.h"
#include "zombie/PredicatedFileWatcher/IPredicatedFileWatcherCallback.h"
#include "zombie/SystemDisabler.h"
#include "zombie/ZomboidFileSystem.h"
#include "zombie/core/opengl/ShaderProgram/L_setValue.h"
#include "zombie/core/opengl/ShaderProgram/Uniform.h"
#include "zombie/core/opengl/ShaderUnit/Type.h"
#include "zombie/core/textures/Texture.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/debug/DebugType.h"
#include "zombie/iso/Vector2.h"
#include "zombie/iso/Vector3.h"
#include <filesystem>

namespace zombie {
namespace core {
namespace opengl {


class ShaderProgram {
public:
    int m_shaderID = 0;
    const std::string m_name;
    const bool m_isStatic;
   private const std::vector<ShaderUnit> m_vertexUnits = std::make_unique<std::vector<>>();
   private const std::vector<ShaderUnit> m_fragmentUnits = std::make_unique<std::vector<>>();
   private const std::unordered_map<std::string, PredicatedFileWatcher> m_fileWatchers = std::make_unique<std::unordered_map<>>();
    bool m_sourceFilesChanged = false;
    bool m_compileFailed = false;
   private const std::unordered_map<std::string, Uniform> uniformsByName = std::make_unique<std::unordered_map<>>();
   private const std::vector<IShaderProgramListener> m_onCompiledListeners = std::make_unique<std::vector<>>();
   private const int[] m_uvScaleUniforms = new int[10];
    static FloatBuffer floatBuffer;

    private ShaderProgram(const std::string& var1, bool var2) {
      this.m_name = var1;
      this.m_isStatic = var2;
   }

    std::string getName() {
      return this.m_name;
   }

    void addCompileListener(IShaderProgramListener var1) {
      if (!this.m_onCompiledListeners.contains(var1)) {
         this.m_onCompiledListeners.push_back(var1);
      }
   }

    void removeCompileListener(IShaderProgramListener var1) {
      this.m_onCompiledListeners.remove(var1);
   }

    void invokeProgramCompiledEvent() {
      this.Start();
      this.m_uvScaleUniforms[0] = ARBShaderObjects.glGetUniformLocationARB(this.m_shaderID, "UVScale");

      for (int var1 = 1; var1 < this.m_uvScaleUniforms.length; var1++) {
         this.m_uvScaleUniforms[var1] = ARBShaderObjects.glGetUniformLocationARB(this.m_shaderID, "UVScale" + var1);
      }

      this.End();
      if (!this.m_onCompiledListeners.empty()) {
         for (IShaderProgramListener var3 : new std::vector<>(this.m_onCompiledListeners)) {
            var3.callback(this);
         }
      }
   }

    void compile() {
      this.m_sourceFilesChanged = false;
      this.m_compileFailed = false;
      if (this.isCompiled()) {
         this.destroy();
      }

    std::string var1 = this.getName();
      if (DebugLog.isEnabled(DebugType.Shader)) {
         DebugLog.Shader.debugln(var1 + (this.m_isStatic ? "(Static)" : ""));
      }

      this.m_shaderID = ARBShaderObjects.glCreateProgramObjectARB();
      if (this.m_shaderID == 0) {
         DebugLog.Shader.error("Failed to create Shader: " + var1 + " could not create new Shader Program ID.");
      } else {
         this.addShader(this.getRootVertFileName(), Type.Vert);
         this.addShader(this.getRootFragFileName(var1), Type.Frag);
         this.registerFileWatchers();
         if (!this.compileAllShaderUnits()) {
            this.m_compileFailed = true;
            this.destroy();
         } else if (!this.attachAllShaderUnits()) {
            this.m_compileFailed = true;
            this.destroy();
         } else {
            this.registerFileWatchers();
            ARBShaderObjects.glLinkProgramARB(this.m_shaderID);
            if (ARBShaderObjects.glGetObjectParameteriARB(this.m_shaderID, 35714) == 0) {
               this.m_compileFailed = true;
               DebugLog.Shader.error("Failed to link new Shader Program:" + var1 + " bStatic:" + this.m_isStatic);
               DebugLog.Shader.error(getLogInfo(this.m_shaderID));
               this.destroy();
            } else {
               ARBShaderObjects.glValidateProgramARB(this.m_shaderID);
               if (ARBShaderObjects.glGetObjectParameteriARB(this.m_shaderID, 35715) == 0) {
                  this.m_compileFailed = true;
                  DebugLog.Shader.error("Failed to validate Shader Program:" + var1 + " bStatic:" + this.m_isStatic);
                  DebugLog.Shader.error(getLogInfo(this.m_shaderID));
                  this.destroy();
               } else {
                  this.onCompileSuccess();
               }
            }
         }
      }
   }

    void onCompileSuccess() {
      if (this.isCompiled()) {
         this.uniformsByName.clear();
         this.Start();
    int var1 = this.m_shaderID;
    int var2 = GL20.glGetProgrami(var1, 35718);
    int var3 = 0;
    IntBuffer var4 = MemoryUtil.memAllocInt(1);
    IntBuffer var5 = MemoryUtil.memAllocInt(1);

         for (int var6 = 0; var6 < var2; var6++) {
    std::string var7 = GL20.glGetActiveUniform(var1, var6, 255, var4, var5);
    int var8 = GL20.glGetUniformLocation(var1, var7);
            if (var8 != -1) {
    int var9 = var4.get(0);
    int var10 = var5.get(0);
    Uniform var11 = std::make_shared<Uniform>();
               this.uniformsByName.put(var7, var11);
               var11.name = var7;
               var11.loc = var8;
               var11.size = var9;
               var11.type = var10;
               if (DebugLog.isEnabled(DebugType.Shader)) {
                  DebugLog.Shader.debugln(var7 + ", Loc: " + var8 + ", Type: " + var10 + ", Size: " + var9);
               }

               if (var11.type == 35678) {
                  if (var3 != 0) {
                     GL20.glUniform1i(var11.loc, var3);
                  }

                  var11.sampler = var3++;
               }
            }
         }

         MemoryUtil.memFree(var4);
         MemoryUtil.memFree(var5);
         this.End();
         PZGLUtil.checkGLError(true);
         this.invokeProgramCompiledEvent();
      }
   }

    void registerFileWatchers() {
      for (PredicatedFileWatcher var2 : this.m_fileWatchers.values()) {
         DebugFileWatcher.instance.remove(var2);
      }

      this.m_fileWatchers.clear();

      for (ShaderUnit var5 : this.m_vertexUnits) {
         this.registerFileWatcherInternal(var5.getFileName(), var1 -> this.onShaderFileChanged());
      }

      for (ShaderUnit var6 : this.m_fragmentUnits) {
         this.registerFileWatcherInternal(var6.getFileName(), var1 -> this.onShaderFileChanged());
      }
   }

    void registerFileWatcherInternal(const std::string& var1, IPredicatedFileWatcherCallback var2) {
      var1 = ZomboidFileSystem.instance.getString(var1);
    PredicatedFileWatcher var3 = std::make_shared<PredicatedFileWatcher>(var1, var2);
      this.m_fileWatchers.put(var1, var3);
      DebugFileWatcher.instance.push_back(var3);
   }

    void onShaderFileChanged() {
      this.m_sourceFilesChanged = true;
   }

    bool compileAllShaderUnits() {
      for (ShaderUnit var2 : this.getShaderUnits()) {
         if (!var2.compile()) {
            DebugLog.Shader.error("Failed to create Shader: " + this.getName() + " Shader unit failed to compile: " + var2.getFileName());
    return false;
         }
      }

    return true;
   }

    bool attachAllShaderUnits() {
      for (ShaderUnit var2 : this.getShaderUnits()) {
         if (!var2.attach()) {
            DebugLog.Shader.error("Failed to create Shader: " + this.getName() + " Shader unit failed to attach: " + var2.getFileName());
    return false;
         }
      }

    return true;
   }

   private std::vector<ShaderUnit> getShaderUnits() {
    std::vector var1 = new std::vector();
      var1.addAll(this.m_vertexUnits);
      var1.addAll(this.m_fragmentUnits);
    return var1;
   }

    std::string getRootVertFileName() {
      return this.m_isStatic ? "media/shaders/" + this.getName() + "_static.vert" : "media/shaders/" + this.getName() + ".vert";
   }

    std::string getRootFragFileName(const std::string& var1) {
      return "media/shaders/" + var1 + ".frag";
   }

    ShaderUnit addShader(const std::string& var1, Type var2) {
    ShaderUnit var3 = this.findShader(var1, var2);
      if (var3 != nullptr) {
    return var3;
      } else {
    std::vector var4 = this.getShaderList(var2);
         var3 = std::make_shared<ShaderUnit>(this, var1, var2);
         var4.push_back(var3);
    return var3;
      }
   }

   private std::vector<ShaderUnit> getShaderList(Type var1) {
    return var1 = = Type.Vert ? this.m_vertexUnits : this.m_fragmentUnits;
   }

    ShaderUnit findShader(const std::string& var1, Type var2) {
    std::vector var3 = this.getShaderList(var2);
    ShaderUnit var4 = nullptr;

    for (auto& var6 : var3)         if (var6.getFileName() == var1)) {
            var4 = var6;
            break;
         }
      }

    return var4;
   }

    static ShaderProgram createShaderProgram(const std::string& var0, bool var1, bool var2) {
    ShaderProgram var3 = std::make_shared<ShaderProgram>(var0, var1);
      if (var2) {
         var3.compile();
      }

    return var3;
   }

    static int createVertShader(const std::string& var0) {
    ShaderUnit var1 = std::make_shared<ShaderUnit>(nullptr, var0, Type.Vert);
      var1.compile();
      return var1.getGLID();
   }

    static int createFragShader(const std::string& var0) {
    ShaderUnit var1 = std::make_shared<ShaderUnit>(nullptr, var0, Type.Frag);
      var1.compile();
      return var1.getGLID();
   }

    static void printLogInfo(int var0) {
    IntBuffer var1 = MemoryUtil.memAllocInt(1);
      ARBShaderObjects.glGetObjectParameterivARB(var0, 35716, var1);
    int var2 = var1.get();
      MemoryUtil.memFree(var1);
      if (var2 > 1) {
    ByteBuffer var3 = MemoryUtil.memAlloc(var2);
         var1.flip();
         ARBShaderObjects.glGetInfoLogARB(var0, var1, var3);
         byte[] var4 = new byte[var2];
         var3.get(var4);
    std::string var5 = new std::string(var4);
         DebugLog.Shader.debugln(":\n" + var5);
         MemoryUtil.memFree(var3);
      }
   }

    static std::string getLogInfo(int var0) {
      return ARBShaderObjects.glGetInfoLogARB(var0, ARBShaderObjects.glGetObjectParameteriARB(var0, 35716));
   }

    bool isCompiled() {
      return this.m_shaderID != 0;
   }

    void destroy() {
      if (this.m_shaderID == 0) {
         this.m_vertexUnits.clear();
         this.m_fragmentUnits.clear();
      } else {
         try {
            DebugLog.Shader.debugln(this.getName());

            for (ShaderUnit var2 : this.m_vertexUnits) {
               var2.destroy();
            }

            this.m_vertexUnits.clear();

            for (ShaderUnit var7 : this.m_fragmentUnits) {
               var7.destroy();
            }

            this.m_fragmentUnits.clear();
            ARBShaderObjects.glDeleteObjectARB(this.m_shaderID);
            PZGLUtil.checkGLError(true);
         } finally {
            this.m_vertexUnits.clear();
            this.m_fragmentUnits.clear();
            this.m_shaderID = 0;
         }
      }
   }

    int getShaderID() {
      if (!this.m_compileFailed && !this.isCompiled() || this.m_sourceFilesChanged) {
         RenderThread.invokeOnRenderContext(this::compile);
      }

      return this.m_shaderID;
   }

    void Start() {
      ARBShaderObjects.glUseProgramObjectARB(this.getShaderID());
   }

    void End() {
      ARBShaderObjects.glUseProgramObjectARB(0);
   }

    void setSamplerUnit(const std::string& var1, int var2) {
    Uniform var3 = this.getUniform(var1, 35678);
      if (var3 != nullptr) {
         var3.sampler = var2;
         ARBShaderObjects.glUniform1iARB(var3.loc, var2);
      }
   }

    void setValueColor(const std::string& var1, int var2) {
      this.setVector4(
         var1, 0.003921569F * (var2 >> 24 & 0xFF), 0.003921569F * (var2 >> 16 & 0xFF), 0.003921569F * (var2 >> 8 & 0xFF), 0.003921569F * (var2 & 0xFF)
      );
   }

    void setValueColorRGB(const std::string& var1, int var2) {
      this.setValueColor(var1, var2 & 0xFF);
   }

    void setValue(const std::string& var1, float var2) {
    Uniform var3 = this.getUniform(var1, 5126);
      if (var3 != nullptr) {
         ARBShaderObjects.glUniform1fARB(var3.loc, var2);
      }
   }

    void setValue(const std::string& var1, int var2) {
    Uniform var3 = this.getUniform(var1, 5124);
      if (var3 != nullptr) {
         ARBShaderObjects.glUniform1iARB(var3.loc, var2);
      }
   }

    void setValue(const std::string& var1, Vector3 var2) {
      this.setVector3(var1, var2.x, var2.y, var2.z);
   }

    void setValue(const std::string& var1, Vector2 var2) {
      this.setVector2(var1, var2.x, var2.y);
   }

    void setVector2(const std::string& var1, float var2, float var3) {
    Uniform var4 = this.getUniform(var1, 35664);
      if (var4 != nullptr) {
         this.setVector2(var4.loc, var2, var3);
      }
   }

    void setVector3(const std::string& var1, float var2, float var3, float var4) {
    Uniform var5 = this.getUniform(var1, 35665);
      if (var5 != nullptr) {
         this.setVector3(var5.loc, var2, var3, var4);
      }
   }

    void setVector4(const std::string& var1, float var2, float var3, float var4, float var5) {
    Uniform var6 = this.getUniform(var1, 35666);
      if (var6 != nullptr) {
         this.setVector4(var6.loc, var2, var3, var4, var5);
      }
   }

    Uniform getUniform(const std::string& var1, int var2) {
      return this.getUniform(var1, var2, false);
   }

    Uniform getUniform(const std::string& var1, int var2, bool var3) {
    Uniform var4 = this.uniformsByName.get(var1);
      if (var4 == nullptr) {
         if (var3) {
            DebugLog.Shader.warn(var1 + " doesn't exist in shader");
         }

    return nullptr;
      } else if (var4.type != var2) {
         DebugLog.Shader.warn(var1 + " isn't of type: " + var2 + ", it is of type: " + var4.type);
    return nullptr;
      } else {
    return var4;
      }
   }

    void setValue(const std::string& var1, Matrix4f var2) {
    Uniform var3 = this.getUniform(var1, 35676);
      if (var3 != nullptr) {
         this.setTransformMatrix(var3.loc, var2);
      }
   }

    void setValue(const std::string& var1, Texture var2, int var3) {
    Uniform var4 = this.getUniform(var1, 35678);
      if (var4 != nullptr && var2 != nullptr) {
         if (var4.sampler != var3) {
            var4.sampler = var3;
            GL20.glUniform1i(var4.loc, var4.sampler);
         }

         GL13.glActiveTexture(33984 + var4.sampler);
         GL11.glEnable(3553);
    int var5 = Texture.lastTextureID;
         var2.bind();
         if (var4.sampler > 0) {
            Texture.lastTextureID = var5;
         }

    Vector2 var6 = var2.getUVScale(L_setValue.vector2);
         this.setUVScale(var3, var6.x, var6.y);
         if (SystemDisabler.doEnableDetectOpenGLErrorsInTexture) {
            PZGLUtil.checkGLErrorThrow("Shader.setValue<Texture> Loc: %s, Tex: %s, samplerUnit: %d", new Object[]{var1, var2, var3});
         }
      }
   }

    void setUVScale(int var1, float var2, float var3) {
      if (var1 < 0) {
         DebugLog.Shader.error("SamplerUnit out of range: " + var1);
      } else if (var1 >= this.m_uvScaleUniforms.length) {
    std::string var5 = "UVScale";
         if (var1 > 0) {
            var5 = "UVScale" + var1;
         }

         this.setVector2(var5, var2, var3);
      } else {
    int var4 = this.m_uvScaleUniforms[var1];
         if (var4 >= 0) {
            this.setVector2(var4, var2, var3);
         }
      }
   }

    void setVector2(int var1, float var2, float var3) {
      ARBShaderObjects.glUniform2fARB(var1, var2, var3);
   }

    void setVector3(int var1, float var2, float var3, float var4) {
      ARBShaderObjects.glUniform3fARB(var1, var2, var3, var4);
   }

    void setVector4(int var1, float var2, float var3, float var4, float var5) {
      ARBShaderObjects.glUniform4fARB(var1, var2, var3, var4, var5);
   }

    void setTransformMatrix(int var1, Matrix4f var2) {
      if (floatBuffer == nullptr) {
         floatBuffer = BufferUtils.createFloatBuffer(38400);
      }

      floatBuffer.clear();
      var2.store(floatBuffer);
      floatBuffer.flip();
      ARBShaderObjects.glUniformMatrix4fvARB(var1, true, floatBuffer);
   }
}
} // namespace opengl
} // namespace core
} // namespace zombie
