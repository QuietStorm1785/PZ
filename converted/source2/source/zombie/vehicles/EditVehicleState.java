package zombie.vehicles;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileReader;
import java.io.FileWriter;
import java.util.ArrayList;
import java.util.Locale;
import org.joml.Vector2f;
import org.joml.Vector3f;
import se.krka.kahlua.vm.KahluaTable;
import zombie.ZomboidFileSystem;
import zombie.Lua.LuaManager;
import zombie.core.Core;
import zombie.core.logger.ExceptionLogger;
import zombie.core.skinnedmodel.ModelManager;
import zombie.debug.DebugLog;
import zombie.debug.DebugOptions;
import zombie.gameStates.GameState;
import zombie.gameStates.GameStateMachine.StateAction;
import zombie.input.GameKeyboard;
import zombie.scripting.ScriptManager;
import zombie.scripting.ScriptParser;
import zombie.scripting.ScriptParser.Block;
import zombie.scripting.objects.ModelAttachment;
import zombie.scripting.objects.VehicleScript;
import zombie.scripting.objects.VehicleScript.Area;
import zombie.scripting.objects.VehicleScript.Model;
import zombie.scripting.objects.VehicleScript.Passenger;
import zombie.scripting.objects.VehicleScript.PhysicsShape;
import zombie.scripting.objects.VehicleScript.Position;
import zombie.scripting.objects.VehicleScript.Wheel;
import zombie.ui.UIElement;
import zombie.ui.UIManager;
import zombie.util.list.PZArrayUtil;
import zombie.vehicles.EditVehicleState.LuaEnvironment;

public final class EditVehicleState extends GameState {
   public static EditVehicleState instance;
   private LuaEnvironment m_luaEnv;
   private boolean bExit = false;
   private String m_initialScript = null;
   private final ArrayList<UIElement> m_gameUI = new ArrayList<>();
   private final ArrayList<UIElement> m_selfUI = new ArrayList<>();
   private boolean m_bSuspendUI;
   private KahluaTable m_table = null;

   public EditVehicleState() {
      instance = this;
   }

   public void enter() {
      instance = this;
      if (this.m_luaEnv == null) {
         this.m_luaEnv = new LuaEnvironment(LuaManager.platform, LuaManager.converterManager, LuaManager.env);
      }

      this.saveGameUI();
      if (this.m_selfUI.size() == 0) {
         this.m_luaEnv.caller.pcall(this.m_luaEnv.thread, this.m_luaEnv.env.rawget("EditVehicleState_InitUI"), new Object[0]);
         if (this.m_table != null && this.m_table.getMetatable() != null) {
            this.m_table.getMetatable().rawset("_LUA_RELOADED_CHECK", Boolean.FALSE);
         }
      } else {
         UIManager.UI.addAll(this.m_selfUI);
         this.m_luaEnv.caller.pcall(this.m_luaEnv.thread, this.m_table.rawget("showUI"), this.m_table);
      }

      this.bExit = false;
   }

   public void yield() {
      this.restoreGameUI();
   }

   public void reenter() {
      this.saveGameUI();
   }

   public void exit() {
      this.restoreGameUI();
   }

   public void render() {
      byte var1 = 0;
      Core.getInstance().StartFrame(var1, true);
      this.renderScene();
      Core.getInstance().EndFrame(var1);
      Core.getInstance().RenderOffScreenBuffer();
      if (Core.getInstance().StartFrameUI()) {
         this.renderUI();
      }

      Core.getInstance().EndFrameUI();
   }

   public StateAction update() {
      if (!this.bExit && !GameKeyboard.isKeyPressed(65)) {
         this.updateScene();
         return StateAction.Remain;
      } else {
         return StateAction.Continue;
      }
   }

   public static EditVehicleState checkInstance() {
      if (instance != null) {
         if (instance.m_table != null && instance.m_table.getMetatable() != null) {
            if (instance.m_table.getMetatable().rawget("_LUA_RELOADED_CHECK") == null) {
               instance = null;
            }
         } else {
            instance = null;
         }
      }

      return instance == null ? new EditVehicleState() : instance;
   }

   private void saveGameUI() {
      this.m_gameUI.clear();
      this.m_gameUI.addAll(UIManager.UI);
      UIManager.UI.clear();
      this.m_bSuspendUI = UIManager.bSuspend;
      UIManager.bSuspend = false;
      UIManager.setShowPausedMessage(false);
      UIManager.defaultthread = this.m_luaEnv.thread;
   }

   private void restoreGameUI() {
      this.m_selfUI.clear();
      this.m_selfUI.addAll(UIManager.UI);
      UIManager.UI.clear();
      UIManager.UI.addAll(this.m_gameUI);
      UIManager.bSuspend = this.m_bSuspendUI;
      UIManager.setShowPausedMessage(true);
      UIManager.defaultthread = LuaManager.thread;
   }

   private void updateScene() {
      ModelManager.instance.update();
      if (GameKeyboard.isKeyPressed(17)) {
         DebugOptions.instance.ModelRenderWireframe.setValue(!DebugOptions.instance.ModelRenderWireframe.getValue());
      }
   }

   private void renderScene() {
   }

   private void renderUI() {
      UIManager.render();
   }

   public void setTable(KahluaTable var1) {
      this.m_table = var1;
   }

   public void setScript(String var1) {
      if (this.m_table == null) {
         this.m_initialScript = var1;
      } else {
         this.m_luaEnv.caller.pcall(this.m_luaEnv.thread, this.m_table.rawget("setScript"), new Object[]{this.m_table, var1});
      }
   }

   public Object fromLua0(String var1) {
      switch (var1) {
         case "exit":
            this.bExit = true;
            return null;
         case "getInitialScript":
            return this.m_initialScript;
         default:
            throw new IllegalArgumentException("unhandled \"" + var1 + "\"");
      }
   }

   public Object fromLua1(String var1, Object var2) {
      byte var4 = -1;
      switch (var1.hashCode()) {
         case 1396535690:
            if (var1.equals("writeScript")) {
               var4 = 0;
            }
         default:
            switch (var4) {
               case 0:
                  VehicleScript var5 = ScriptManager.instance.getVehicle((String)var2);
                  if (var5 == null) {
                     throw new NullPointerException("vehicle script \"" + var2 + "\" not found");
                  }

                  ArrayList var6 = this.readScript(var5.getFileName());
                  if (var6 != null) {
                     this.updateScript(var5.getFileName(), var6, var5);
                  }

                  return null;
               default:
                  throw new IllegalArgumentException(String.format("unhandled \"%s\" \"%s\"", var1, var2));
            }
      }
   }

   private ArrayList<String> readScript(String var1) {
      StringBuilder var2 = new StringBuilder();
      var1 = ZomboidFileSystem.instance.getString(var1);
      File var3 = new File(var1);

      try (
         FileReader var4 = new FileReader(var3);
         BufferedReader var5 = new BufferedReader(var4);
      ) {
         String var6 = System.lineSeparator();

         String var7;
         while ((var7 = var5.readLine()) != null) {
            var2.append(var7);
            var2.append(var6);
         }
      } catch (Throwable var12) {
         ExceptionLogger.logException(var12);
         return null;
      }

      String var14 = ScriptParser.stripComments(var2.toString());
      return ScriptParser.parseTokens(var14);
   }

   private void updateScript(String var1, ArrayList<String> var2, VehicleScript var3) {
      var1 = ZomboidFileSystem.instance.getString(var1);

      for (int var4 = var2.size() - 1; var4 >= 0; var4--) {
         String var5 = ((String)var2.get(var4)).trim();
         int var6 = var5.indexOf("{");
         int var7 = var5.lastIndexOf("}");
         String var8 = var5.substring(0, var6);
         if (var8.startsWith("module")) {
            var8 = var5.substring(0, var6).trim();
            String[] var9 = var8.split("\\s+");
            String var10 = var9.length > 1 ? var9[1].trim() : "";
            if (var10.equals(var3.getModule().getName())) {
               String var11 = var5.substring(var6 + 1, var7).trim();
               ArrayList var12 = ScriptParser.parseTokens(var11);

               for (int var13 = var12.size() - 1; var13 >= 0; var13--) {
                  String var14 = ((String)var12.get(var13)).trim();
                  if (var14.startsWith("vehicle")) {
                     var6 = var14.indexOf("{");
                     var8 = var14.substring(0, var6).trim();
                     var9 = var8.split("\\s+");
                     String var15 = var9.length > 1 ? var9[1].trim() : "";
                     if (var15.equals(var3.getName())) {
                        var14 = this.vehicleScriptToText(var3, var14).trim();
                        var12.set(var13, var14);
                        String var16 = System.lineSeparator();
                        String var17 = String.join(var16 + "\t", var12);
                        var17 = "module " + var10 + var16 + "{" + var16 + "\t" + var17 + var16 + "}" + var16;
                        var2.set(var4, var17);
                        this.writeScript(var1, var2);
                        return;
                     }
                  }
               }
            }
         }
      }
   }

   private String vehicleScriptToText(VehicleScript var1, String var2) {
      float var3 = var1.getModelScale();
      Block var4 = ScriptParser.parse(var2);
      var4 = (Block)var4.children.get(0);
      Model var5 = var1.getModel();
      Block var6 = var4.getBlock("model", null);
      if (var5 != null && var6 != null) {
         float var7 = var1.getModelScale();
         var6.setValue("scale", String.format(Locale.US, "%.4f", var7));
         Vector3f var8 = var1.getModel().getOffset();
         var6.setValue("offset", String.format(Locale.US, "%.4f %.4f %.4f", var8.x / var3, var8.y / var3, var8.z / var3));
      }

      ArrayList var13 = new ArrayList();

      for (int var14 = 0; var14 < var4.children.size(); var14++) {
         Block var27 = (Block)var4.children.get(var14);
         if ("physics".equals(var27.type)) {
            if (var13.size() == var1.getPhysicsShapeCount()) {
               var4.elements.remove(var27);
               var4.children.remove(var14);
               var14--;
            } else {
               var13.add(var27);
            }
         }
      }

      for (int var15 = 0; var15 < var1.getPhysicsShapeCount(); var15++) {
         PhysicsShape var28 = var1.getPhysicsShape(var15);
         boolean var37 = var15 < var13.size();
         Block var9 = var37 ? (Block)var13.get(var15) : new Block();
         var9.type = "physics";
         var9.id = var28.getTypeString();
         if (var37) {
            var9.elements.clear();
            var9.children.clear();
            var9.values.clear();
         }

         var9.setValue(
            "offset", String.format(Locale.US, "%.4f %.4f %.4f", var28.getOffset().x() / var3, var28.getOffset().y() / var3, var28.getOffset().z() / var3)
         );
         if (var28.type == 1) {
            var9.setValue(
               "extents",
               String.format(Locale.US, "%.4f %.4f %.4f", var28.getExtents().x() / var3, var28.getExtents().y() / var3, var28.getExtents().z() / var3)
            );
            var9.setValue("rotate", String.format(Locale.US, "%.4f %.4f %.4f", var28.getRotate().x(), var28.getRotate().y(), var28.getRotate().z()));
         }

         if (var28.type == 2) {
            var9.setValue("radius", String.format(Locale.US, "%.4f", var28.getRadius() / var3));
         }

         if (!var37) {
            var4.elements.add(var9);
            var4.children.add(var9);
         }
      }

      for (int var16 = var4.children.size() - 1; var16 >= 0; var16--) {
         Block var29 = (Block)var4.children.get(var16);
         if ("attachment".equals(var29.type)) {
            var4.elements.remove(var29);
            var4.children.remove(var16);
         }
      }

      for (int var17 = 0; var17 < var1.getAttachmentCount(); var17++) {
         ModelAttachment var30 = var1.getAttachment(var17);
         Block var38 = var4.getBlock("attachment", var30.getId());
         if (var38 == null) {
            var38 = new Block();
            var38.type = "attachment";
            var38.id = var30.getId();
            var4.elements.add(var38);
            var4.children.add(var38);
         }

         var38.setValue(
            "offset", String.format(Locale.US, "%.4f %.4f %.4f", var30.getOffset().x() / var3, var30.getOffset().y() / var3, var30.getOffset().z() / var3)
         );
         var38.setValue("rotate", String.format(Locale.US, "%.4f %.4f %.4f", var30.getRotate().x(), var30.getRotate().y(), var30.getRotate().z()));
         if (var30.getBone() != null) {
            var38.setValue("bone", var30.getBone());
         }

         if (var30.getCanAttach() != null) {
            var38.setValue("canAttach", PZArrayUtil.arrayToString(var30.getCanAttach(), "", "", ","));
         }

         if (var30.getZOffset() != 0.0F) {
            var38.setValue("zoffset", String.format(Locale.US, "%.4f", var30.getZOffset()));
         }

         if (!var30.isUpdateConstraint()) {
            var38.setValue("updateconstraint", "false");
         }
      }

      Vector3f var18 = var1.getExtents();
      var4.setValue("extents", String.format(Locale.US, "%.4f %.4f %.4f", var18.x / var3, var18.y / var3, var18.z / var3));
      Vector3f var19 = var1.getPhysicsChassisShape();
      var4.setValue("physicsChassisShape", String.format(Locale.US, "%.4f %.4f %.4f", var19.x / var3, var19.y / var3, var19.z / var3));
      Vector3f var20 = var1.getCenterOfMassOffset();
      var4.setValue("centerOfMassOffset", String.format(Locale.US, "%.4f %.4f %.4f", var20.x / var3, var20.y / var3, var20.z / var3));
      Vector2f var21 = var1.getShadowExtents();
      boolean var31 = var4.getValue("shadowExtents") != null;
      var4.setValue("shadowExtents", String.format(Locale.US, "%.4f %.4f", var21.x / var3, var21.y / var3));
      if (!var31) {
         var4.moveValueAfter("shadowExtents", "centerOfMassOffset");
      }

      Vector2f var22 = var1.getShadowOffset();
      var31 = var4.getValue("shadowOffset") != null;
      var4.setValue("shadowOffset", String.format(Locale.US, "%.4f %.4f", var22.x / var3, var22.y / var3));
      if (!var31) {
         var4.moveValueAfter("shadowOffset", "shadowExtents");
      }

      for (int var23 = 0; var23 < var1.getAreaCount(); var23++) {
         Area var33 = var1.getArea(var23);
         Block var39 = var4.getBlock("area", var33.getId());
         if (var39 != null) {
            var39.setValue(
               "xywh", String.format(Locale.US, "%.4f %.4f %.4f %.4f", var33.getX() / var3, var33.getY() / var3, var33.getW() / var3, var33.getH() / var3)
            );
         }
      }

      for (int var24 = 0; var24 < var1.getPassengerCount(); var24++) {
         Passenger var34 = var1.getPassenger(var24);
         Block var40 = var4.getBlock("passenger", var34.getId());
         if (var40 != null) {
            for (Position var10 : var34.positions) {
               Block var11 = var40.getBlock("position", var10.id);
               if (var11 != null) {
                  var11.setValue("offset", String.format(Locale.US, "%.4f %.4f %.4f", var10.offset.x / var3, var10.offset.y / var3, var10.offset.z / var3));
                  var11.setValue("rotate", String.format(Locale.US, "%.4f %.4f %.4f", var10.rotate.x / var3, var10.rotate.y / var3, var10.rotate.z / var3));
               }
            }
         }
      }

      for (int var25 = 0; var25 < var1.getWheelCount(); var25++) {
         Wheel var35 = var1.getWheel(var25);
         Block var41 = var4.getBlock("wheel", var35.getId());
         if (var41 != null) {
            var41.setValue("offset", String.format(Locale.US, "%.4f %.4f %.4f", var35.offset.x / var3, var35.offset.y / var3, var35.offset.z / var3));
         }
      }

      StringBuilder var26 = new StringBuilder();
      String var36 = System.lineSeparator();
      var4.prettyPrint(1, var26, var36);
      return var26.toString();
   }

   private void writeScript(String var1, ArrayList<String> var2) {
      String var3 = ZomboidFileSystem.instance.getString(var1);
      File var4 = new File(var3);

      try (
         FileWriter var5 = new FileWriter(var4);
         BufferedWriter var6 = new BufferedWriter(var5);
      ) {
         DebugLog.General.printf("writing %s\n", new Object[]{var1});

         for (String var8 : var2) {
            var6.write(var8);
         }

         this.m_luaEnv.caller.pcall(this.m_luaEnv.thread, this.m_table.rawget("wroteScript"), new Object[]{this.m_table, var3});
      } catch (Throwable var13) {
         ExceptionLogger.logException(var13);
      }
   }
}
