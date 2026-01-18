#pragma once
#include "org/lwjgl/opengl/ARBShaderObjects.h"
#include "org/lwjgl/opengl/GL11.h"
#include "org/lwjgl/opengl/GL13.h"
#include "org/lwjgl/opengl/GL20.h"
#include "org/lwjgl/system/MemoryUtil.h"
#include "org/lwjgl/util/vector/Matrix4f.h"
#include "org/lwjglx/BufferUtils.h"
#include "zombie/DebugFileWatcher.h"
#include "zombie/PredicatedFileWatcher.h"
#include "zombie/SystemDisabler.h"
#include "zombie/ZomboidFileSystem.h"
#include "zombie/core/textures/Texture.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/debug/DebugType.h"
#include "zombie/iso/Vector2.h"
#include "zombie/iso/Vector3.h"
#include <cstdint>
#include <filesystem>
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

class ShaderProgram {
public:
  int m_shaderID = 0;
  const std::string m_name;
  const bool m_isStatic;
private
  final ArrayList<ShaderUnit> m_vertexUnits = std::make_unique<ArrayList<>>();
private
  final ArrayList<ShaderUnit> m_fragmentUnits = std::make_unique<ArrayList<>>();
private
  final HashMap<String, PredicatedFileWatcher> m_fileWatchers =
      std::make_unique<HashMap<>>();
  bool m_sourceFilesChanged = false;
  bool m_compileFailed = false;
private
  final HashMap<String, ShaderProgram.Uniform> uniformsByName =
      std::make_unique<HashMap<>>();
private
  final ArrayList<IShaderProgramListener> m_onCompiledListeners =
      std::make_unique<ArrayList<>>();
private
  final int[] m_uvScaleUniforms = new int[10];
  static FloatBuffer floatBuffer;

private
  ShaderProgram(const std::string &string, bool boolean0) {
    this.m_name = string;
    this.m_isStatic = boolean0;
  }

  std::string getName() { return this.m_name; }

  void addCompileListener(IShaderProgramListener listener) {
    if (!this.m_onCompiledListeners.contains(listener)) {
      this.m_onCompiledListeners.add(listener);
    }
  }

  void removeCompileListener(IShaderProgramListener listener) {
    this.m_onCompiledListeners.remove(listener);
  }

  void invokeProgramCompiledEvent() {
    this.Start();
    this.m_uvScaleUniforms[0] =
        ARBShaderObjects.glGetUniformLocationARB(this.m_shaderID, "UVScale");

    for (int int0 = 1; int0 < this.m_uvScaleUniforms.length; int0++) {
      this.m_uvScaleUniforms[int0] = ARBShaderObjects.glGetUniformLocationARB(
          this.m_shaderID, "UVScale" + int0);
    }

    this.End();
    if (!this.m_onCompiledListeners.isEmpty()) {
      for (IShaderProgramListener iShaderProgramListener :
           new ArrayList<>(this.m_onCompiledListeners)) {
        iShaderProgramListener.callback(this);
      }
    }
  }

  /**
   * Compiles or re-compiles this program.
   */
  void compile() {
    this.m_sourceFilesChanged = false;
    this.m_compileFailed = false;
    if (this.isCompiled()) {
      this.destroy();
    }

    std::string string = this.getName();
    if (DebugLog.isEnabled(DebugType.Shader)) {
      DebugLog.Shader.debugln(string + (this.m_isStatic ? "(Static)" : ""));
    }

    this.m_shaderID = ARBShaderObjects.glCreateProgramObjectARB();
    if (this.m_shaderID == 0) {
      DebugLog.Shader.error("Failed to create Shader: " + string +
                            " could not create new Shader Program ID.");
    } else {
      this.addShader(this.getRootVertFileName(), ShaderUnit.Type.Vert);
      this.addShader(this.getRootFragFileName(string), ShaderUnit.Type.Frag);
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
        if (ARBShaderObjects.glGetObjectParameteriARB(this.m_shaderID, 35714) ==
            0) {
          this.m_compileFailed = true;
          DebugLog.Shader.error("Failed to link new Shader Program:" + string +
                                " bStatic:" + this.m_isStatic);
          DebugLog.Shader.error(getLogInfo(this.m_shaderID));
          this.destroy();
        } else {
          ARBShaderObjects.glValidateProgramARB(this.m_shaderID);
          if (ARBShaderObjects.glGetObjectParameteriARB(this.m_shaderID,
                                                        35715) == 0) {
            this.m_compileFailed = true;
            DebugLog.Shader.error("Failed to validate Shader Program:" +
                                  string + " bStatic:" + this.m_isStatic);
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
      int int0 = this.m_shaderID;
      int int1 = GL20.glGetProgrami(int0, 35718);
      int int2 = 0;
      IntBuffer intBuffer0 = MemoryUtil.memAllocInt(1);
      IntBuffer intBuffer1 = MemoryUtil.memAllocInt(1);

      for (int int3 = 0; int3 < int1; int3++) {
        std::string string =
            GL20.glGetActiveUniform(int0, int3, 255, intBuffer0, intBuffer1);
        int int4 = GL20.glGetUniformLocation(int0, string);
        if (int4 != -1) {
          int int5 = intBuffer0.get(0);
          int int6 = intBuffer1.get(0);
          ShaderProgram.Uniform uniform = new ShaderProgram.Uniform();
          this.uniformsByName.put(string, uniform);
          uniform.name = string;
          uniform.loc = int4;
          uniform.size = int5;
          uniform.type = int6;
          if (DebugLog.isEnabled(DebugType.Shader)) {
            DebugLog.Shader.debugln(string + ", Loc: " + int4 +
                                    ", Type: " + int6 + ", Size: " + int5);
          }

          if (uniform.type == 35678) {
            if (int2 != 0) {
              GL20.glUniform1i(uniform.loc, int2);
            }

            uniform.sampler = int2++;
          }
        }
      }

      MemoryUtil.memFree(intBuffer0);
      MemoryUtil.memFree(intBuffer1);
      this.End();
      PZGLUtil.checkGLError(true);
      this.invokeProgramCompiledEvent();
    }
  }

  void registerFileWatchers() {
    for (PredicatedFileWatcher predicatedFileWatcher :
         this.m_fileWatchers.values()) {
      DebugFileWatcher.instance.remove(predicatedFileWatcher);
    }

    this.m_fileWatchers.clear();

    for (ShaderUnit shaderUnit0 : this.m_vertexUnits) {
      this.registerFileWatcherInternal(shaderUnit0.getFileName(),
                                       var1->this.onShaderFileChanged());
    }

    for (ShaderUnit shaderUnit1 : this.m_fragmentUnits) {
      this.registerFileWatcherInternal(shaderUnit1.getFileName(),
                                       var1->this.onShaderFileChanged());
    }
  }

  void registerFileWatcherInternal(
      const std::string &string,
      PredicatedFileWatcher
          .IPredicatedFileWatcherCallback iPredicatedFileWatcherCallback) {
    string = ZomboidFileSystem.instance.getString(string);
    PredicatedFileWatcher predicatedFileWatcher =
        new PredicatedFileWatcher(string, iPredicatedFileWatcherCallback);
    this.m_fileWatchers.put(string, predicatedFileWatcher);
    DebugFileWatcher.instance.add(predicatedFileWatcher);
  }

  void onShaderFileChanged() { this.m_sourceFilesChanged = true; }

  bool compileAllShaderUnits() {
    for (ShaderUnit shaderUnit : this.getShaderUnits()) {
      if (!shaderUnit.compile()) {
        DebugLog.Shader.error(
            "Failed to create Shader: " + this.getName() +
            " Shader unit failed to compile: " + shaderUnit.getFileName());
        return false;
      }
    }

    return true;
  }

  bool attachAllShaderUnits() {
    for (ShaderUnit shaderUnit : this.getShaderUnits()) {
      if (!shaderUnit.attach()) {
        DebugLog.Shader.error(
            "Failed to create Shader: " + this.getName() +
            " Shader unit failed to attach: " + shaderUnit.getFileName());
        return false;
      }
    }

    return true;
  }

private
  ArrayList<ShaderUnit> getShaderUnits() {
    std::vector arrayList = new ArrayList();
    arrayList.addAll(this.m_vertexUnits);
    arrayList.addAll(this.m_fragmentUnits);
    return arrayList;
  }

  std::string getRootVertFileName() {
    return this.m_isStatic ? "media/shaders/" + this.getName() + "_static.vert"
                           : "media/shaders/" + this.getName() + ".vert";
  }

  std::string getRootFragFileName(const std::string &string) {
    return "media/shaders/" + string + ".frag";
  }

  ShaderUnit addShader(const std::string &fileName, ShaderUnit.Type unitType) {
    ShaderUnit shaderUnit = this.findShader(fileName, unitType);
    if (shaderUnit != nullptr) {
      return shaderUnit;
    } else {
      std::vector arrayList = this.getShaderList(unitType);
      shaderUnit = new ShaderUnit(this, fileName, unitType);
      arrayList.add(shaderUnit);
      return shaderUnit;
    }
  }

private
  ArrayList<ShaderUnit> getShaderList(ShaderUnit.Type type) {
    return type = =
               ShaderUnit.Type.Vert ? this.m_vertexUnits : this.m_fragmentUnits;
  }

  ShaderUnit findShader(const std::string &string, ShaderUnit.Type type) {
    std::vector arrayList = this.getShaderList(type);
    ShaderUnit shaderUnit0 = null;

    for (auto &shaderUnit1 : arrayList)
      if (shaderUnit1.getFileName() == string)) {
          shaderUnit0 = shaderUnit1;
          break;
        }
  }

  return shaderUnit0;
}

/**
 * createShaderProgram  Creates and Compiles a Shader Program, using the
 * specified program name.  The vertex and fragment shader file names are
 * constructed using the program name.
 *
 * @param name The program name.
 * @param isStatic
 * @param compile
 * @return The created shader program. Non-null, but it may or may not have
 * compiled properly. Check the result using isCompiled() function.
 */
static ShaderProgram
createShaderProgram(const std::string &name, bool isStatic, bool compile) {
  ShaderProgram shaderProgram = new ShaderProgram(name, isStatic);
  if (compile) {
    shaderProgram.compile();
  }

  return shaderProgram;
}

/**
 * Creates a vertex shader unit.  Deprecated: Use
 * ShaderProgram.createShaderProgram instead.
 */
static int createVertShader(const std::string &fileName) {
  ShaderUnit shaderUnit = new ShaderUnit(null, fileName, ShaderUnit.Type.Vert);
  shaderUnit.compile();
  return shaderUnit.getGLID();
}

/**
 * Creates a fragment shader unit.  Deprecated: Use
 * ShaderProgram.createShaderProgram instead.
 */
static int createFragShader(const std::string &fileName) {
  ShaderUnit shaderUnit = new ShaderUnit(null, fileName, ShaderUnit.Type.Frag);
  shaderUnit.compile();
  return shaderUnit.getGLID();
}

static void printLogInfo(int obj) {
  IntBuffer intBuffer = MemoryUtil.memAllocInt(1);
  ARBShaderObjects.glGetObjectParameterivARB(obj, 35716, intBuffer);
  int int0 = intBuffer.get();
  MemoryUtil.memFree(intBuffer);
  if (int0 > 1) {
    ByteBuffer byteBuffer = MemoryUtil.memAlloc(int0);
    intBuffer.flip();
    ARBShaderObjects.glGetInfoLogARB(obj, intBuffer, byteBuffer);
    byte[] bytes = new byte[int0];
    byteBuffer.get(bytes);
    std::string string = new String(bytes);
    DebugLog.Shader.debugln(":\n" + string);
    MemoryUtil.memFree(byteBuffer);
  }
}

static std::string getLogInfo(int obj) {
  return ARBShaderObjects.glGetInfoLogARB(
      obj, ARBShaderObjects.glGetObjectParameteriARB(obj, 35716));
}

bool isCompiled() { return this.m_shaderID != 0; }

void destroy() {
  if (this.m_shaderID == 0) {
    this.m_vertexUnits.clear();
    this.m_fragmentUnits.clear();
  } else {
    try {
      DebugLog.Shader.debugln(this.getName());

      for (ShaderUnit shaderUnit0 : this.m_vertexUnits) {
        shaderUnit0.destroy();
      }

      this.m_vertexUnits.clear();

      for (ShaderUnit shaderUnit1 : this.m_fragmentUnits) {
        shaderUnit1.destroy();
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
  if (!this.m_compileFailed && !this.isCompiled() ||
      this.m_sourceFilesChanged) {
    RenderThread.invokeOnRenderContext(this ::compile);
  }

  return this.m_shaderID;
}

void Start() { ARBShaderObjects.glUseProgramObjectARB(this.getShaderID()); }

void End() { ARBShaderObjects.glUseProgramObjectARB(0); }

void setSamplerUnit(const std::string &loc, int textureUnit) {
  ShaderProgram.Uniform uniform = this.getUniform(loc, 35678);
  if (uniform != nullptr) {
    uniform.sampler = textureUnit;
    ARBShaderObjects.glUniform1iARB(uniform.loc, textureUnit);
  }
}

void setValueColor(const std::string &loc, int rgba) {
  this.setVector4(loc, 0.003921569F * (rgba >> 24 & 0xFF),
                  0.003921569F * (rgba >> 16 & 0xFF),
                  0.003921569F * (rgba >> 8 & 0xFF),
                  0.003921569F * (rgba & 0xFF));
}

void setValueColorRGB(const std::string &loc, int rgb) {
  this.setValueColor(loc, rgb & 0xFF);
}

void setValue(const std::string &loc, float val) {
  ShaderProgram.Uniform uniform = this.getUniform(loc, 5126);
  if (uniform != nullptr) {
    ARBShaderObjects.glUniform1fARB(uniform.loc, val);
  }
}

void setValue(const std::string &loc, int val) {
  ShaderProgram.Uniform uniform = this.getUniform(loc, 5124);
  if (uniform != nullptr) {
    ARBShaderObjects.glUniform1iARB(uniform.loc, val);
  }
}

void setValue(const std::string &loc, Vector3 val) {
  this.setVector3(loc, val.x, val.y, val.z);
}

void setValue(const std::string &loc, Vector2 val) {
  this.setVector2(loc, val.x, val.y);
}

void setVector2(const std::string &loc, float val_x, float val_y) {
  ShaderProgram.Uniform uniform = this.getUniform(loc, 35664);
  if (uniform != nullptr) {
    this.setVector2(uniform.loc, val_x, val_y);
  }
}

void setVector3(const std::string &loc, float val_x, float val_y, float val_z) {
  ShaderProgram.Uniform uniform = this.getUniform(loc, 35665);
  if (uniform != nullptr) {
    this.setVector3(uniform.loc, val_x, val_y, val_z);
  }
}

void setVector4(const std::string &loc, float val_x, float val_y, float val_z,
                float val_w) {
  ShaderProgram.Uniform uniform = this.getUniform(loc, 35666);
  if (uniform != nullptr) {
    this.setVector4(uniform.loc, val_x, val_y, val_z, val_w);
  }
}

public
final ShaderProgram.Uniform getUniform(String loc, int type) {
  return this.getUniform(loc, type, false);
}

public
ShaderProgram.Uniform getUniform(String loc, int type, boolean bWarn) {
  ShaderProgram.Uniform uniform = this.uniformsByName.get(loc);
  if (uniform == nullptr) {
    if (bWarn) {
      DebugLog.Shader.warn(loc + " doesn't exist in shader");
    }

    return null;
  } else if (uniform.type != type) {
    DebugLog.Shader.warn(loc + " isn't of type: " + type +
                         ", it is of type: " + uniform.type);
    return null;
  } else {
    return uniform;
  }
}

void setValue(const std::string &loc, Matrix4f matrix4f) {
  ShaderProgram.Uniform uniform = this.getUniform(loc, 35676);
  if (uniform != nullptr) {
    this.setTransformMatrix(uniform.loc, matrix4f);
  }
}

void setValue(const std::string &loc, Texture tex, int samplerUnit) {
  ShaderProgram.Uniform uniform = this.getUniform(loc, 35678);
  if (uniform != nullptr && tex != nullptr) {
    if (uniform.sampler != samplerUnit) {
      uniform.sampler = samplerUnit;
      GL20.glUniform1i(uniform.loc, uniform.sampler);
    }

    GL13.glActiveTexture(33984 + uniform.sampler);
    GL11.glEnable(3553);
    int int0 = Texture.lastTextureID;
    tex.bind();
    if (uniform.sampler > 0) {
      Texture.lastTextureID = int0;
    }

    Vector2 vector = tex.getUVScale(ShaderProgram.L_setValue.vector2);
    this.setUVScale(samplerUnit, vector.x, vector.y);
    if (SystemDisabler.doEnableDetectOpenGLErrorsInTexture) {
      PZGLUtil.checkGLErrorThrow(
          "Shader.setValue<Texture> Loc: %s, Tex: %s, samplerUnit: %d", loc,
          tex, samplerUnit);
    }
  }
}

void setUVScale(int int0, float float0, float float1) {
  if (int0 < 0) {
    DebugLog.Shader.error("SamplerUnit out of range: " + int0);
  } else if (int0 >= this.m_uvScaleUniforms.length) {
    std::string string = "UVScale";
    if (int0 > 0) {
      string = "UVScale" + int0;
    }

    this.setVector2(string, float0, float1);
  } else {
    int int1 = this.m_uvScaleUniforms[int0];
    if (int1 >= 0) {
      this.setVector2(int1, float0, float1);
    }
  }
}

void setVector2(int id, float x, float y) {
  ARBShaderObjects.glUniform2fARB(id, x, y);
}

void setVector3(int id, float x, float y, float z) {
  ARBShaderObjects.glUniform3fARB(id, x, y, z);
}

void setVector4(int id, float x, float y, float z, float w) {
  ARBShaderObjects.glUniform4fARB(id, x, y, z, w);
}

void setTransformMatrix(int int0, Matrix4f matrix4f) {
  if (floatBuffer == nullptr) {
    floatBuffer = BufferUtils.createFloatBuffer(38400);
  }

  floatBuffer.clear();
  matrix4f.store(floatBuffer);
  floatBuffer.flip();
  ARBShaderObjects.glUniformMatrix4fvARB(int0, true, floatBuffer);
}

private
static final class L_setValue {
  static const Vector2 vector2 = new Vector2();
}

public static class Uniform {
  std::string name;
  int size;
  int loc;
  int type;
  int sampler;
}
}
} // namespace opengl
} // namespace core
} // namespace zombie
