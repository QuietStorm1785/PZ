package zombie.core.opengl;

import java.nio.ByteBuffer;
import java.nio.FloatBuffer;
import java.nio.IntBuffer;
import java.util.ArrayList;
import java.util.HashMap;
import org.lwjgl.opengl.ARBShaderObjects;
import org.lwjgl.opengl.GL11;
import org.lwjgl.opengl.GL13;
import org.lwjgl.opengl.GL20;
import org.lwjgl.system.MemoryUtil;
import org.lwjgl.util.vector.Matrix4f;
import org.lwjglx.BufferUtils;
import zombie.DebugFileWatcher;
import zombie.PredicatedFileWatcher;
import zombie.SystemDisabler;
import zombie.ZomboidFileSystem;
import zombie.PredicatedFileWatcher.IPredicatedFileWatcherCallback;
import zombie.core.opengl.ShaderProgram.L_setValue;
import zombie.core.opengl.ShaderProgram.Uniform;
import zombie.core.opengl.ShaderUnit.Type;
import zombie.core.textures.Texture;
import zombie.debug.DebugLog;
import zombie.debug.DebugType;
import zombie.iso.Vector2;
import zombie.iso.Vector3;

public final class ShaderProgram {
   private int m_shaderID = 0;
   private final String m_name;
   private final boolean m_isStatic;
   private final ArrayList<ShaderUnit> m_vertexUnits = new ArrayList<>();
   private final ArrayList<ShaderUnit> m_fragmentUnits = new ArrayList<>();
   private final HashMap<String, PredicatedFileWatcher> m_fileWatchers = new HashMap<>();
   private boolean m_sourceFilesChanged = false;
   private boolean m_compileFailed = false;
   private final HashMap<String, Uniform> uniformsByName = new HashMap<>();
   private final ArrayList<IShaderProgramListener> m_onCompiledListeners = new ArrayList<>();
   private final int[] m_uvScaleUniforms = new int[10];
   private static FloatBuffer floatBuffer;

   private ShaderProgram(String var1, boolean var2) {
      this.m_name = var1;
      this.m_isStatic = var2;
   }

   public String getName() {
      return this.m_name;
   }

   public void addCompileListener(IShaderProgramListener var1) {
      if (!this.m_onCompiledListeners.contains(var1)) {
         this.m_onCompiledListeners.add(var1);
      }
   }

   public void removeCompileListener(IShaderProgramListener var1) {
      this.m_onCompiledListeners.remove(var1);
   }

   private void invokeProgramCompiledEvent() {
      this.Start();
      this.m_uvScaleUniforms[0] = ARBShaderObjects.glGetUniformLocationARB(this.m_shaderID, "UVScale");

      for (int var1 = 1; var1 < this.m_uvScaleUniforms.length; var1++) {
         this.m_uvScaleUniforms[var1] = ARBShaderObjects.glGetUniformLocationARB(this.m_shaderID, "UVScale" + var1);
      }

      this.End();
      if (!this.m_onCompiledListeners.isEmpty()) {
         for (IShaderProgramListener var3 : new ArrayList<>(this.m_onCompiledListeners)) {
            var3.callback(this);
         }
      }
   }

   public void compile() {
      this.m_sourceFilesChanged = false;
      this.m_compileFailed = false;
      if (this.isCompiled()) {
         this.destroy();
      }

      String var1 = this.getName();
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

   private void onCompileSuccess() {
      if (this.isCompiled()) {
         this.uniformsByName.clear();
         this.Start();
         int var1 = this.m_shaderID;
         int var2 = GL20.glGetProgrami(var1, 35718);
         int var3 = 0;
         IntBuffer var4 = MemoryUtil.memAllocInt(1);
         IntBuffer var5 = MemoryUtil.memAllocInt(1);

         for (int var6 = 0; var6 < var2; var6++) {
            String var7 = GL20.glGetActiveUniform(var1, var6, 255, var4, var5);
            int var8 = GL20.glGetUniformLocation(var1, var7);
            if (var8 != -1) {
               int var9 = var4.get(0);
               int var10 = var5.get(0);
               Uniform var11 = new Uniform();
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

   private void registerFileWatchers() {
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

   private void registerFileWatcherInternal(String var1, IPredicatedFileWatcherCallback var2) {
      var1 = ZomboidFileSystem.instance.getString(var1);
      PredicatedFileWatcher var3 = new PredicatedFileWatcher(var1, var2);
      this.m_fileWatchers.put(var1, var3);
      DebugFileWatcher.instance.add(var3);
   }

   private void onShaderFileChanged() {
      this.m_sourceFilesChanged = true;
   }

   private boolean compileAllShaderUnits() {
      for (ShaderUnit var2 : this.getShaderUnits()) {
         if (!var2.compile()) {
            DebugLog.Shader.error("Failed to create Shader: " + this.getName() + " Shader unit failed to compile: " + var2.getFileName());
            return false;
         }
      }

      return true;
   }

   private boolean attachAllShaderUnits() {
      for (ShaderUnit var2 : this.getShaderUnits()) {
         if (!var2.attach()) {
            DebugLog.Shader.error("Failed to create Shader: " + this.getName() + " Shader unit failed to attach: " + var2.getFileName());
            return false;
         }
      }

      return true;
   }

   private ArrayList<ShaderUnit> getShaderUnits() {
      ArrayList var1 = new ArrayList();
      var1.addAll(this.m_vertexUnits);
      var1.addAll(this.m_fragmentUnits);
      return var1;
   }

   private String getRootVertFileName() {
      return this.m_isStatic ? "media/shaders/" + this.getName() + "_static.vert" : "media/shaders/" + this.getName() + ".vert";
   }

   private String getRootFragFileName(String var1) {
      return "media/shaders/" + var1 + ".frag";
   }

   public ShaderUnit addShader(String var1, Type var2) {
      ShaderUnit var3 = this.findShader(var1, var2);
      if (var3 != null) {
         return var3;
      } else {
         ArrayList var4 = this.getShaderList(var2);
         var3 = new ShaderUnit(this, var1, var2);
         var4.add(var3);
         return var3;
      }
   }

   private ArrayList<ShaderUnit> getShaderList(Type var1) {
      return var1 == Type.Vert ? this.m_vertexUnits : this.m_fragmentUnits;
   }

   private ShaderUnit findShader(String var1, Type var2) {
      ArrayList var3 = this.getShaderList(var2);
      ShaderUnit var4 = null;

      for (ShaderUnit var6 : var3) {
         if (var6.getFileName().equals(var1)) {
            var4 = var6;
            break;
         }
      }

      return var4;
   }

   public static ShaderProgram createShaderProgram(String var0, boolean var1, boolean var2) {
      ShaderProgram var3 = new ShaderProgram(var0, var1);
      if (var2) {
         var3.compile();
      }

      return var3;
   }

   @Deprecated
   public static int createVertShader(String var0) {
      ShaderUnit var1 = new ShaderUnit(null, var0, Type.Vert);
      var1.compile();
      return var1.getGLID();
   }

   @Deprecated
   public static int createFragShader(String var0) {
      ShaderUnit var1 = new ShaderUnit(null, var0, Type.Frag);
      var1.compile();
      return var1.getGLID();
   }

   public static void printLogInfo(int var0) {
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
         String var5 = new String(var4);
         DebugLog.Shader.debugln(":\n" + var5);
         MemoryUtil.memFree(var3);
      }
   }

   public static String getLogInfo(int var0) {
      return ARBShaderObjects.glGetInfoLogARB(var0, ARBShaderObjects.glGetObjectParameteriARB(var0, 35716));
   }

   public boolean isCompiled() {
      return this.m_shaderID != 0;
   }

   public void destroy() {
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

   public int getShaderID() {
      if (!this.m_compileFailed && !this.isCompiled() || this.m_sourceFilesChanged) {
         RenderThread.invokeOnRenderContext(this::compile);
      }

      return this.m_shaderID;
   }

   public void Start() {
      ARBShaderObjects.glUseProgramObjectARB(this.getShaderID());
   }

   public void End() {
      ARBShaderObjects.glUseProgramObjectARB(0);
   }

   public void setSamplerUnit(String var1, int var2) {
      Uniform var3 = this.getUniform(var1, 35678);
      if (var3 != null) {
         var3.sampler = var2;
         ARBShaderObjects.glUniform1iARB(var3.loc, var2);
      }
   }

   public void setValueColor(String var1, int var2) {
      this.setVector4(
         var1, 0.003921569F * (var2 >> 24 & 0xFF), 0.003921569F * (var2 >> 16 & 0xFF), 0.003921569F * (var2 >> 8 & 0xFF), 0.003921569F * (var2 & 0xFF)
      );
   }

   public void setValueColorRGB(String var1, int var2) {
      this.setValueColor(var1, var2 & 0xFF);
   }

   public void setValue(String var1, float var2) {
      Uniform var3 = this.getUniform(var1, 5126);
      if (var3 != null) {
         ARBShaderObjects.glUniform1fARB(var3.loc, var2);
      }
   }

   public void setValue(String var1, int var2) {
      Uniform var3 = this.getUniform(var1, 5124);
      if (var3 != null) {
         ARBShaderObjects.glUniform1iARB(var3.loc, var2);
      }
   }

   public void setValue(String var1, Vector3 var2) {
      this.setVector3(var1, var2.x, var2.y, var2.z);
   }

   public void setValue(String var1, Vector2 var2) {
      this.setVector2(var1, var2.x, var2.y);
   }

   public void setVector2(String var1, float var2, float var3) {
      Uniform var4 = this.getUniform(var1, 35664);
      if (var4 != null) {
         this.setVector2(var4.loc, var2, var3);
      }
   }

   public void setVector3(String var1, float var2, float var3, float var4) {
      Uniform var5 = this.getUniform(var1, 35665);
      if (var5 != null) {
         this.setVector3(var5.loc, var2, var3, var4);
      }
   }

   public void setVector4(String var1, float var2, float var3, float var4, float var5) {
      Uniform var6 = this.getUniform(var1, 35666);
      if (var6 != null) {
         this.setVector4(var6.loc, var2, var3, var4, var5);
      }
   }

   public final Uniform getUniform(String var1, int var2) {
      return this.getUniform(var1, var2, false);
   }

   public Uniform getUniform(String var1, int var2, boolean var3) {
      Uniform var4 = this.uniformsByName.get(var1);
      if (var4 == null) {
         if (var3) {
            DebugLog.Shader.warn(var1 + " doesn't exist in shader");
         }

         return null;
      } else if (var4.type != var2) {
         DebugLog.Shader.warn(var1 + " isn't of type: " + var2 + ", it is of type: " + var4.type);
         return null;
      } else {
         return var4;
      }
   }

   public void setValue(String var1, Matrix4f var2) {
      Uniform var3 = this.getUniform(var1, 35676);
      if (var3 != null) {
         this.setTransformMatrix(var3.loc, var2);
      }
   }

   public void setValue(String var1, Texture var2, int var3) {
      Uniform var4 = this.getUniform(var1, 35678);
      if (var4 != null && var2 != null) {
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

   private void setUVScale(int var1, float var2, float var3) {
      if (var1 < 0) {
         DebugLog.Shader.error("SamplerUnit out of range: " + var1);
      } else if (var1 >= this.m_uvScaleUniforms.length) {
         String var5 = "UVScale";
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

   public void setVector2(int var1, float var2, float var3) {
      ARBShaderObjects.glUniform2fARB(var1, var2, var3);
   }

   public void setVector3(int var1, float var2, float var3, float var4) {
      ARBShaderObjects.glUniform3fARB(var1, var2, var3, var4);
   }

   public void setVector4(int var1, float var2, float var3, float var4, float var5) {
      ARBShaderObjects.glUniform4fARB(var1, var2, var3, var4, var5);
   }

   void setTransformMatrix(int var1, Matrix4f var2) {
      if (floatBuffer == null) {
         floatBuffer = BufferUtils.createFloatBuffer(38400);
      }

      floatBuffer.clear();
      var2.store(floatBuffer);
      floatBuffer.flip();
      ARBShaderObjects.glUniformMatrix4fvARB(var1, true, floatBuffer);
   }
}
