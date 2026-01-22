#pragma once
#include <sstream>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "se/krka/kahlua/vm/KahluaTable.h"
#include "zombie/Lua/LuaManager.h"
#include "zombie/ZomboidFileSystem.h"
#include "zombie/core/Core.h"
#include "zombie/core/logger/ExceptionLogger.h"
#include "zombie/core/skinnedmodel/ModelManager.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/debug/DebugOptions.h"
#include "zombie/gameStates/GameStateMachine/StateAction.h"
#include "zombie/input/GameKeyboard.h"
#include "zombie/scripting/ScriptManager.h"
#include "zombie/scripting/ScriptParser.h"
#include "zombie/scripting/ScriptParser/Block.h"
#include "zombie/scripting/objects/ModelAttachment.h"
#include "zombie/scripting/objects/ModelScript.h"
#include "zombie/ui/UIElement.h"
#include "zombie/ui/UIManager.h"
#include "zombie/vehicles/EditVehicleState/LuaEnvironment.h"
#include <algorithm>
#include <fstream>
#include <iostream>

namespace zombie {
namespace gameStates {


class AttachmentEditorState : public GameState {
public:
    static AttachmentEditorState instance;
    LuaEnvironment m_luaEnv;
    bool bExit = false;
   private const std::vector<UIElement> m_gameUI = std::make_unique<std::vector<>>();
   private const std::vector<UIElement> m_selfUI = std::make_unique<std::vector<>>();
    bool m_bSuspendUI;
    KahluaTable m_table = nullptr;

    void enter() {
      instance = this;
      if (this.m_luaEnv == nullptr) {
         this.m_luaEnv = std::make_shared<LuaEnvironment>(LuaManager.platform, LuaManager.converterManager, LuaManager.env);
      }

      this.saveGameUI();
      if (this.m_selfUI.size() == 0) {
         this.m_luaEnv.caller.pcall(this.m_luaEnv.thread, this.m_luaEnv.env.rawget("AttachmentEditorState_InitUI"), new Object[0]);
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

    static AttachmentEditorState checkInstance() {
      if (instance != nullptr) {
         if (instance.m_table != nullptr && instance.m_table.getMetatable() != nullptr) {
            if (instance.m_table.getMetatable().rawget("_LUA_RELOADED_CHECK") == nullptr) {
               instance = nullptr;
            }
         } else {
            instance = nullptr;
         }
      }

    return instance = = nullptr ? std::make_shared<AttachmentEditorState>() : instance;
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

    void* fromLua0(const std::string& var1) {
    uint8_t var3 = -1;
      switch (var1.hashCode()) {
         case 3127582:
            if (var1 == "exit")) {
               var3 = 0;
            }
         default:
            switch (var3) {
               case 0:
                  this.bExit = true;
    return nullptr;
               default:
                  throw IllegalArgumentException("unhandled \"" + var1 + "\"");
            }
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
    ModelScript var5 = ScriptManager.instance.getModelScript((std::string)var2);
                  if (var5 == nullptr) {
                     throw NullPointerException("model script \"" + var2 + "\" not found");
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

    void updateScript(const std::string& var1, std::vector<std::string> var2, ModelScript var3) {
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
                  if (var14.startsWith("model")) {
                     var6 = var14.indexOf("{");
                     var8 = var14.substr(0, var6).trim();
                     var9 = var8.split("\\s+");
    std::string var15 = var9.length > 1 ? var9[1].trim() : "";
                     if (var15 == var3.getName())) {
                        var14 = this.modelScriptToText(var3, var14).trim();
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

    std::string modelScriptToText(ModelScript var1, const std::string& var2) {
    Block var3 = ScriptParser.parse(var2);
      var3 = (Block)var3.children.get(0);

      for (int var4 = var3.children.size() - 1; var4 >= 0; var4--) {
    Block var5 = (Block)var3.children.get(var4);
         if ("attachment" == var5.type)) {
            var3.elements.remove(var5);
            var3.children.remove(var4);
         }
      }

      for (int var8 = 0; var8 < var1.getAttachmentCount(); var8++) {
    ModelAttachment var10 = var1.getAttachment(var8);
    Block var6 = var3.getBlock("attachment", var10.getId());
         if (var6 == nullptr) {
            var6 = std::make_unique<Block>();
            var6.type = "attachment";
            var6.id = var10.getId();
            var6.setValue("offset", std::string.format(Locale.US, "%.4f %.4f %.4f", var10.getOffset().x(), var10.getOffset().y(), var10.getOffset().z()));
            var6.setValue("rotate", std::string.format(Locale.US, "%.4f %.4f %.4f", var10.getRotate().x(), var10.getRotate().y(), var10.getRotate().z()));
            if (var10.getBone() != nullptr) {
               var6.setValue("bone", var10.getBone());
            }

            var3.elements.push_back(var6);
            var3.children.push_back(var6);
         } else {
            var6.setValue("offset", std::string.format(Locale.US, "%.4f %.4f %.4f", var10.getOffset().x(), var10.getOffset().y(), var10.getOffset().z()));
            var6.setValue("rotate", std::string.format(Locale.US, "%.4f %.4f %.4f", var10.getRotate().x(), var10.getRotate().y(), var10.getRotate().z()));
         }
      }

    std::stringstream var9 = new std::stringstream();
    std::string var11 = System.lineSeparator();
      var3.prettyPrint(1, var9, var11);
      return var9;
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
} // namespace gameStates
} // namespace zombie
