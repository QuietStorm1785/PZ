#pragma once
#include <sstream>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include "se/krka/kahlua/vm/KahluaTable.h"
#include "zombie/Lua/LuaManager.h"
#include "zombie/ZomboidFileSystem.h"
#include "zombie/core/Core.h"
#include "zombie/core/logger/ExceptionLogger.h"
#include "zombie/core/skinnedmodel/ModelManager.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/debug/DebugOptions.h"
#include "zombie/gameStates/GameState.h"
#include "zombie/gameStates/GameStateMachine/StateAction.h"
#include "zombie/input/GameKeyboard.h"
#include "zombie/scripting/ScriptManager.h"
#include "zombie/scripting/ScriptParser.h"
#include "zombie/scripting/ScriptParser/Block.h"
#include "zombie/scripting/objects/ModelAttachment.h"
#include "zombie/scripting/objects/VehicleScript.h"
#include "zombie/scripting/objects/VehicleScript/Area.h"
#include "zombie/scripting/objects/VehicleScript/Model.h"
#include "zombie/scripting/objects/VehicleScript/Passenger.h"
#include "zombie/scripting/objects/VehicleScript/PhysicsShape.h"
#include "zombie/scripting/objects/VehicleScript/Position.h"
#include "zombie/scripting/objects/VehicleScript/Wheel.h"
#include "zombie/ui/UIElement.h"
#include "zombie/ui/UIManager.h"
#include "zombie/util/list/PZArrayUtil.h"
#include "zombie/vehicles/EditVehicleState/LuaEnvironment.h"
#include <algorithm>
#include <fstream>
#include <iostream>

namespace zombie {
namespace vehicles {


class EditVehicleState : public GameState {
public:
    static EditVehicleState instance;
    LuaEnvironment m_luaEnv;
    bool bExit = false;
    std::string m_initialScript = nullptr;
   private const std::vector<UIElement> m_gameUI = std::make_unique<std::vector<>>();
   private const std::vector<UIElement> m_selfUI = std::make_unique<std::vector<>>();
    bool m_bSuspendUI;
    KahluaTable m_table = nullptr;

    public EditVehicleState() {
      instance = this;
   }

    void enter() {
      instance = this;
      if (this.m_luaEnv == nullptr) {
         this.m_luaEnv = std::make_shared<LuaEnvironment>(LuaManager.platform, LuaManager.converterManager, LuaManager.env);
      }

      this.saveGameUI();
      if (this.m_selfUI.size() == 0) {
         this.m_luaEnv.caller.pcall(this.m_luaEnv.thread, this.m_luaEnv.env.rawget("EditVehicleState_InitUI"), new Object[0]);
         if (this.m_table != nullptr && this.m_table.getMetatable() != nullptr) {
            this.m_table.getMetatable().rawset("_LUA_RELOADED_CHECK", bool.FALSE);
         }
      } else {
         UIManager.UI.addAll(this.m_selfUI);
         this.m_luaEnv.caller.pcall(this.m_luaEnv.thread, this.m_table.rawget("showUI"), this.m_table);
      }

      this.bExit = false;
   }

    void yield() {
      this.restoreGameUI();
   }

    void reenter() {
      this.saveGameUI();
   }

    void exit() {
      this.restoreGameUI();
   }

    void render() {
    uint8_t var1 = 0;
      Core.getInstance().StartFrame(var1, true);
      this.renderScene();
      Core.getInstance().EndFrame(var1);
      Core.getInstance().RenderOffScreenBuffer();
      if (Core.getInstance().StartFrameUI()) {
         this.renderUI();
      }

      Core.getInstance().EndFrameUI();
   }

    StateAction update() {
      if (!this.bExit && !GameKeyboard.isKeyPressed(65)) {
         this.updateScene();
         return StateAction.Remain;
      } else {
         return StateAction.Continue;
      }
   }

    static EditVehicleState checkInstance() {
      if (instance != nullptr) {
         if (instance.m_table != nullptr && instance.m_table.getMetatable() != nullptr) {
            if (instance.m_table.getMetatable().rawget("_LUA_RELOADED_CHECK") == nullptr) {
               instance = nullptr;
            }
         } else {
            instance = nullptr;
         }
      }

    return instance = = nullptr ? std::make_shared<EditVehicleState>() : instance;
   }

    void saveGameUI() {
      this.m_gameUI.clear();
      this.m_gameUI.addAll(UIManager.UI);
      UIManager.UI.clear();
      this.m_bSuspendUI = UIManager.bSuspend;
      UIManager.bSuspend = false;
      UIManager.setShowPausedMessage(false);
      UIManager.defaultthread = this.m_luaEnv.thread;
   }

    void restoreGameUI() {
      this.m_selfUI.clear();
      this.m_selfUI.addAll(UIManager.UI);
      UIManager.UI.clear();
      UIManager.UI.addAll(this.m_gameUI);
      UIManager.bSuspend = this.m_bSuspendUI;
      UIManager.setShowPausedMessage(true);
      UIManager.defaultthread = LuaManager.thread;
   }

    void updateScene() {
      ModelManager.instance.update();
      if (GameKeyboard.isKeyPressed(17)) {
         DebugOptions.instance.ModelRenderWireframe.setValue(!DebugOptions.instance.ModelRenderWireframe.getValue());
      }
   }

    void renderScene() {
   }

    void renderUI() {
      UIManager.render();
   }

    void setTable(KahluaTable var1) {
      this.m_table = var1;
   }

    void setScript(const std::string& var1) {
      if (this.m_table == nullptr) {
         this.m_initialScript = var1;
      } else {
         this.m_luaEnv.caller.pcall(this.m_luaEnv.thread, this.m_table.rawget("setScript"), new Object[]{this.m_table, var1});
      }
   }

    void* fromLua0(const std::string& var1) {
      switch (var1) {
         case "exit":
            this.bExit = true;
    return nullptr;
         case "getInitialScript":
            return this.m_initialScript;
         default:
            throw IllegalArgumentException("unhandled \"" + var1 + "\"");
      }
   }

    void* fromLua1(const std::string& var1, void* var2) {
    uint8_t var4 = -1;
      switch (var1.hashCode()) {
         case 1396535690:
            if (var1 == "writeScript")) {
               var4 = 0;
            }
         default:
            switch (var4) {
               case 0:
    VehicleScript var5 = ScriptManager.instance.getVehicle((std::string)var2);
                  if (var5 == nullptr) {
                     throw NullPointerException("vehicle script \"" + var2 + "\" not found");
                  }

    std::vector var6 = this.readScript(var5.getFileName());
                  if (var6 != nullptr) {
                     this.updateScript(var5.getFileName(), var6, var5);
                  }

    return nullptr;
               default:
                  throw IllegalArgumentException(std::string.format("unhandled \"%s\" \"%s\"", var1, var2));
            }
      }
   }

   private std::vector<std::string> readScript(std::string var1) {
    std::stringstream var2 = new std::stringstream();
      var1 = ZomboidFileSystem.instance.getString(var1);
    File var3 = std::make_shared<File>(var1);

      try (
    FileReader var4 = std::make_shared<FileReader>(var3);
    BufferedReader var5 = std::make_shared<BufferedReader>(var4);
      ) {
    std::string var6 = System.lineSeparator();

    std::string var7;
         while ((var7 = var5.readLine()) != nullptr) {
            var2.append(var7);
            var2.append(var6);
         }
      } catch (Throwable var12) {
         ExceptionLogger.logException(var12);
    return nullptr;
      }

    std::string var14 = ScriptParser.stripComments(var2);
      return ScriptParser.parseTokens(var14);
   }

    void updateScript(const std::string& var1, std::vector<std::string> var2, VehicleScript var3) {
      var1 = ZomboidFileSystem.instance.getString(var1);

      for (int var4 = var2.size() - 1; var4 >= 0; var4--) {
    std::string var5 = ((std::string)var2.get(var4)).trim();
    int var6 = var5.indexOf("{");
    int var7 = var5.lastIndexOf("}");
    std::string var8 = var5.substr(0, var6);
         if (var8.startsWith("module")) {
            var8 = var5.substr(0, var6).trim();
            std::string[] var9 = var8.split("\\s+");
    std::string var10 = var9.length > 1 ? var9[1].trim() : "";
            if (var10 == var3.getModule().getName())) {
    std::string var11 = var5.substr(var6 + 1, var7).trim();
    std::vector var12 = ScriptParser.parseTokens(var11);

               for (int var13 = var12.size() - 1; var13 >= 0; var13--) {
    std::string var14 = ((std::string)var12.get(var13)).trim();
                  if (var14.startsWith("vehicle")) {
                     var6 = var14.indexOf("{");
                     var8 = var14.substr(0, var6).trim();
                     var9 = var8.split("\\s+");
    std::string var15 = var9.length > 1 ? var9[1].trim() : "";
                     if (var15 == var3.getName())) {
                        var14 = this.vehicleScriptToText(var3, var14).trim();
                        var12.set(var13, var14);
    std::string var16 = System.lineSeparator();
    std::string var17 = std::string.join(var16 + "\t", var12);
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

    std::string vehicleScriptToText(VehicleScript var1, const std::string& var2) {
    float var3 = var1.getModelScale();
    Block var4 = ScriptParser.parse(var2);
      var4 = (Block)var4.children.get(0);
    Model var5 = var1.getModel();
    Block var6 = var4.getBlock("model", nullptr);
      if (var5 != nullptr && var6 != nullptr) {
    float var7 = var1.getModelScale();
         var6.setValue("scale", std::string.format(Locale.US, "%.4f", var7));
    Vector3f var8 = var1.getModel().getOffset();
         var6.setValue("offset", std::string.format(Locale.US, "%.4f %.4f %.4f", var8.x / var3, var8.y / var3, var8.z / var3));
      }

    std::vector var13 = new std::vector();

      for (int var14 = 0; var14 < var4.children.size(); var14++) {
    Block var27 = (Block)var4.children.get(var14);
         if ("physics" == var27.type)) {
            if (var13.size() == var1.getPhysicsShapeCount()) {
               var4.elements.remove(var27);
               var4.children.remove(var14);
               var14--;
            } else {
               var13.push_back(var27);
            }
         }
      }

      for (int var15 = 0; var15 < var1.getPhysicsShapeCount(); var15++) {
    PhysicsShape var28 = var1.getPhysicsShape(var15);
    bool var37 = var15 < var13.size();
    Block var9 = var37 ? (Block)var13.get(var15) : std::make_shared<Block>();
         var9.type = "physics";
         var9.id = var28.getTypeString();
         if (var37) {
            var9.elements.clear();
            var9.children.clear();
            var9.values.clear();
         }

         var9.setValue(
            "offset", std::string.format(Locale.US, "%.4f %.4f %.4f", var28.getOffset().x() / var3, var28.getOffset().y() / var3, var28.getOffset().z() / var3)
         );
         if (var28.type == 1) {
            var9.setValue(
               "extents",
               std::string.format(Locale.US, "%.4f %.4f %.4f", var28.getExtents().x() / var3, var28.getExtents().y() / var3, var28.getExtents().z() / var3)
            );
            var9.setValue("rotate", std::string.format(Locale.US, "%.4f %.4f %.4f", var28.getRotate().x(), var28.getRotate().y(), var28.getRotate().z()));
         }

         if (var28.type == 2) {
            var9.setValue("radius", std::string.format(Locale.US, "%.4f", var28.getRadius() / var3));
         }

         if (!var37) {
            var4.elements.push_back(var9);
            var4.children.push_back(var9);
         }
      }

      for (int var16 = var4.children.size() - 1; var16 >= 0; var16--) {
    Block var29 = (Block)var4.children.get(var16);
         if ("attachment" == var29.type)) {
            var4.elements.remove(var29);
            var4.children.remove(var16);
         }
      }

      for (int var17 = 0; var17 < var1.getAttachmentCount(); var17++) {
    ModelAttachment var30 = var1.getAttachment(var17);
    Block var38 = var4.getBlock("attachment", var30.getId());
         if (var38 == nullptr) {
            var38 = std::make_unique<Block>();
            var38.type = "attachment";
            var38.id = var30.getId();
            var4.elements.push_back(var38);
            var4.children.push_back(var38);
         }

         var38.setValue(
            "offset", std::string.format(Locale.US, "%.4f %.4f %.4f", var30.getOffset().x() / var3, var30.getOffset().y() / var3, var30.getOffset().z() / var3)
         );
         var38.setValue("rotate", std::string.format(Locale.US, "%.4f %.4f %.4f", var30.getRotate().x(), var30.getRotate().y(), var30.getRotate().z()));
         if (var30.getBone() != nullptr) {
            var38.setValue("bone", var30.getBone());
         }

         if (var30.getCanAttach() != nullptr) {
            var38.setValue("canAttach", PZArrayUtil.arrayToString(var30.getCanAttach(), "", "", ","));
         }

         if (var30.getZOffset() != 0.0F) {
            var38.setValue("zoffset", std::string.format(Locale.US, "%.4f", var30.getZOffset()));
         }

         if (!var30.isUpdateConstraint()) {
            var38.setValue("updateconstraint", "false");
         }
      }

    Vector3f var18 = var1.getExtents();
      var4.setValue("extents", std::string.format(Locale.US, "%.4f %.4f %.4f", var18.x / var3, var18.y / var3, var18.z / var3));
    Vector3f var19 = var1.getPhysicsChassisShape();
      var4.setValue("physicsChassisShape", std::string.format(Locale.US, "%.4f %.4f %.4f", var19.x / var3, var19.y / var3, var19.z / var3));
    Vector3f var20 = var1.getCenterOfMassOffset();
      var4.setValue("centerOfMassOffset", std::string.format(Locale.US, "%.4f %.4f %.4f", var20.x / var3, var20.y / var3, var20.z / var3));
    Vector2f var21 = var1.getShadowExtents();
    bool var31 = var4.getValue("shadowExtents") != nullptr;
      var4.setValue("shadowExtents", std::string.format(Locale.US, "%.4f %.4f", var21.x / var3, var21.y / var3));
      if (!var31) {
         var4.moveValueAfter("shadowExtents", "centerOfMassOffset");
      }

    Vector2f var22 = var1.getShadowOffset();
      var31 = var4.getValue("shadowOffset") != nullptr;
      var4.setValue("shadowOffset", std::string.format(Locale.US, "%.4f %.4f", var22.x / var3, var22.y / var3));
      if (!var31) {
         var4.moveValueAfter("shadowOffset", "shadowExtents");
      }

      for (int var23 = 0; var23 < var1.getAreaCount(); var23++) {
    Area var33 = var1.getArea(var23);
    Block var39 = var4.getBlock("area", var33.getId());
         if (var39 != nullptr) {
            var39.setValue(
               "xywh", std::string.format(Locale.US, "%.4f %.4f %.4f %.4f", var33.getX() / var3, var33.getY() / var3, var33.getW() / var3, var33.getH() / var3)
            );
         }
      }

      for (int var24 = 0; var24 < var1.getPassengerCount(); var24++) {
    Passenger var34 = var1.getPassenger(var24);
    Block var40 = var4.getBlock("passenger", var34.getId());
         if (var40 != nullptr) {
            for (Position var10 : var34.positions) {
    Block var11 = var40.getBlock("position", var10.id);
               if (var11 != nullptr) {
                  var11.setValue("offset", std::string.format(Locale.US, "%.4f %.4f %.4f", var10.offset.x / var3, var10.offset.y / var3, var10.offset.z / var3));
                  var11.setValue("rotate", std::string.format(Locale.US, "%.4f %.4f %.4f", var10.rotate.x / var3, var10.rotate.y / var3, var10.rotate.z / var3));
               }
            }
         }
      }

      for (int var25 = 0; var25 < var1.getWheelCount(); var25++) {
    Wheel var35 = var1.getWheel(var25);
    Block var41 = var4.getBlock("wheel", var35.getId());
         if (var41 != nullptr) {
            var41.setValue("offset", std::string.format(Locale.US, "%.4f %.4f %.4f", var35.offset.x / var3, var35.offset.y / var3, var35.offset.z / var3));
         }
      }

    std::stringstream var26 = new std::stringstream();
    std::string var36 = System.lineSeparator();
      var4.prettyPrint(1, var26, var36);
      return var26;
   }

    void writeScript(const std::string& var1, std::vector<std::string> var2) {
    std::string var3 = ZomboidFileSystem.instance.getString(var1);
    File var4 = std::make_shared<File>(var3);

      try (
    FileWriter var5 = std::make_shared<FileWriter>(var4);
    BufferedWriter var6 = std::make_shared<BufferedWriter>(var5);
      ) {
         DebugLog.General.printf("writing %s\n", new Object[]{var1});

    for (auto& var8 : var2)            var6.write(var8);
         }

         this.m_luaEnv.caller.pcall(this.m_luaEnv.thread, this.m_table.rawget("wroteScript"), new Object[]{this.m_table, var3});
      } catch (Throwable var13) {
         ExceptionLogger.logException(var13);
      }
   }
}
} // namespace vehicles
} // namespace zombie
