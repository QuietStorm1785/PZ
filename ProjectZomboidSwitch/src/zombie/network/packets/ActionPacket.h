#pragma once
#include <sstream>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/GameWindow.h"
#include "zombie/characters/CharacterTimedActions/BaseAction.h"
#include "zombie/characters/CharacterTimedActions/LuaTimedActionNew.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/core/Core.h"
#include "zombie/core/network/ByteBufferWriter.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/debug/DebugType.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/GameServer.h"
#include <algorithm>
#include <filesystem>

namespace zombie {
namespace network {
namespace packets {


class ActionPacket {
public:
    short id;
    bool operation;
    float reloadSpeed;
    bool override;
    std::string primary;
    std::string secondary;
    std::string action;
   private const std::unordered_map<std::string, std::string> variables = std::make_unique<std::unordered_map<>>();
    IsoGameCharacter character;

    void set(bool var1, BaseAction var2) {
      this.character = var2.chr;
      this.id = var2.chr.getOnlineID();
      this.operation = var1;
      this.reloadSpeed = var2.chr.getVariableFloat("ReloadSpeed", 1.0F);
      this.override = var2.overrideHandModels;
      this.primary = var2.getPrimaryHandItem() == nullptr ? var2.getPrimaryHandMdl() : var2.getPrimaryHandItem().getStaticModel();
      this.secondary = var2.getSecondaryHandItem() == nullptr ? var2.getSecondaryHandMdl() : var2.getSecondaryHandItem().getStaticModel();

      for (std::string var4 : var2.animVariables) {
         this.variables.put(var4, var2.chr.getVariableString(var4));
      }

      if (this.variables.containsValue("DetachItem") || this.variables.containsValue("AttachItem")) {
         this.variables.put("AttachAnim", var2.chr.getVariableString("AttachAnim"));
      }

      if (this.variables.containsValue("Loot")) {
         this.variables.put("LootPosition", var2.chr.getVariableString("LootPosition"));
      }

      if (dynamic_cast<LuaTimedActionNew*>(var2) != nullptr) {
         this.action = ((LuaTimedActionNew)var2).getMetaType();
      }
   }

    void parse(ByteBuffer var1, UdpConnection var2) {
      this.id = var1.getShort();
      this.operation = var1.get() != 0;
      this.reloadSpeed = var1.getFloat();
      this.override = var1.get() != 0;
      this.primary = GameWindow.ReadString(var1);
      this.secondary = GameWindow.ReadString(var1);
      this.action = GameWindow.ReadString(var1);
    int var3 = var1.getInt();

      for (int var4 = 0; var4 < var3; var4++) {
         this.variables.put(GameWindow.ReadString(var1), GameWindow.ReadString(var1));
      }

      if (GameServer.bServer) {
         this.character = (IsoGameCharacter)GameServer.IDToPlayerMap.get(this.id);
      } else if (GameClient.bClient) {
         this.character = (IsoGameCharacter)GameClient.IDToPlayerMap.get(this.id);
      } else {
         this.character = nullptr;
      }
   }

    void write(ByteBufferWriter var1) {
      var1.putShort(this.id);
      var1.putBoolean(this.operation);
      var1.putFloat(this.reloadSpeed);
      var1.putBoolean(this.override);
      var1.putUTF(this.primary);
      var1.putUTF(this.secondary);
      var1.putUTF(this.action);
      var1.putInt(this.variables.size());

      for (Entry var3 : this.variables.entrySet()) {
         var1.putUTF((std::string)var3.getKey());
         var1.putUTF((std::string)var3.getValue());
      }
   }

    bool isConsistent() {
    bool var1 = this.dynamic_cast<IsoPlayer*>(character) != nullptr;
      if (!var1 && Core.bDebug) {
         DebugLog.log(DebugType.Multiplayer, "[Action] is not consistent");
      }

    return var1;
   }

    std::string getDescription() {
    std::stringstream var1 = new std::stringstream("[ ").append("character=").append(this.id);
      if (this.isConsistent()) {
         var1.append(" \"").append(((IsoPlayer)this.character).getUsername()).append("\"");
      }

      var1.append(" | ")
         .append("action=")
         .append(this.action)
         .append(" | ")
         .append("operation=")
         .append(this.operation ? "start" : "stop")
         .append(" | ")
         .append("variables=")
         .append(this.variables.size())
         .append(" | ");

      for (Entry var3 : this.variables.entrySet()) {
         var1.append((std::string)var3.getKey()).append("=").append((std::string)var3.getValue()).append(" | ");
      }

      var1.append("override=")
         .append(this.override)
         .append(" ")
         .append("primary=\"")
         .append(this.primary == nullptr ? "" : this.primary)
         .append("\" ")
         .append("secondary=\"")
         .append(this.secondary == nullptr ? "" : this.secondary)
         .append("\" ]");
      return var1;
   }

    bool isRelevant(UdpConnection var1) {
      return this.isConsistent() && var1.RelevantTo(this.character.getX(), this.character.getY());
   }

    void process() {
      if (this.isConsistent()) {
         if (this.operation) {
    BaseAction var1 = std::make_shared<BaseAction>(this.character);
            this.variables.forEach((var1x, var2) -> {
               if (!"true" == var2) && !"false" == var2)) {
                  var1.setAnimVariable(var1x, var2);
               } else {
                  var1.setAnimVariable(var1x, bool.parseBoolean(var2));
               }
            });
            if ("Reload" == this.variables.get("PerformingAction"))) {
               this.character.setVariable("ReloadSpeed", this.reloadSpeed);
            }

            this.character.setVariable("IsPerformingAnAction", true);
            this.character.getNetworkCharacterAI().setAction(var1);
            this.character.getNetworkCharacterAI().setOverride(this.override, this.primary, this.secondary);
            this.character.getNetworkCharacterAI().startAction();
         } else if (this.character.getNetworkCharacterAI().getAction() != nullptr) {
            this.character.getNetworkCharacterAI().stopAction();
         }
      } else {
         DebugLog.Multiplayer.warn("Action error: player id=" + this.id + " not fond");
      }
   }
}
} // namespace packets
} // namespace network
} // namespace zombie
