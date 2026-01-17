#pragma once
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
#include <cstdint>
#include <filesystem>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace network {
namespace packets {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class ActionPacket {
public:
  short id;
  bool operation;
  float reloadSpeed;
  bool override;
  std::string primary;
  std::string secondary;
  std::string action;
private
  final HashMap<String, String> variables = std::make_unique<HashMap<>>();
  IsoGameCharacter character;

  void set(bool boolean0, BaseAction baseAction) {
    this.character = baseAction.chr;
    this.id = baseAction.chr.getOnlineID();
    this.operation = boolean0;
    this.reloadSpeed = baseAction.chr.getVariableFloat("ReloadSpeed", 1.0F);
    this.override = baseAction.overrideHandModels;
    this.primary = baseAction.getPrimaryHandItem() == nullptr
                       ? baseAction.getPrimaryHandMdl()
                       : baseAction.getPrimaryHandItem().getStaticModel();
    this.secondary = baseAction.getSecondaryHandItem() == nullptr
                         ? baseAction.getSecondaryHandMdl()
                         : baseAction.getSecondaryHandItem().getStaticModel();

    for (String string : baseAction.animVariables) {
      this.variables.put(string, baseAction.chr.getVariableString(string));
    }

    if (this.variables.containsValue("DetachItem") ||
        this.variables.containsValue("AttachItem")) {
      this.variables.put("AttachAnim",
                         baseAction.chr.getVariableString("AttachAnim"));
    }

    if (this.variables.containsValue("Loot")) {
      this.variables.put("LootPosition",
                         baseAction.chr.getVariableString("LootPosition"));
    }

    if (baseAction instanceof LuaTimedActionNew) {
      this.action = ((LuaTimedActionNew)baseAction).getMetaType();
    }
  }

  void parse(ByteBuffer byteBuffer, UdpConnection var2) {
    this.id = byteBuffer.getShort();
    this.operation = byteBuffer.get() != 0;
    this.reloadSpeed = byteBuffer.getFloat();
    this.override = byteBuffer.get() != 0;
    this.primary = GameWindow.ReadString(byteBuffer);
    this.secondary = GameWindow.ReadString(byteBuffer);
    this.action = GameWindow.ReadString(byteBuffer);
    int int0 = byteBuffer.getInt();

    for (int int1 = 0; int1 < int0; int1++) {
      this.variables.put(GameWindow.ReadString(byteBuffer),
                         GameWindow.ReadString(byteBuffer));
    }

    if (GameServer.bServer) {
      this.character = GameServer.IDToPlayerMap.get(this.id);
    } else if (GameClient.bClient) {
      this.character = GameClient.IDToPlayerMap.get(this.id);
    } else {
      this.character = nullptr;
    }
  }

  void write(ByteBufferWriter byteBufferWriter) {
    byteBufferWriter.putShort(this.id);
    byteBufferWriter.putBoolean(this.operation);
    byteBufferWriter.putFloat(this.reloadSpeed);
    byteBufferWriter.putBoolean(this.override);
    byteBufferWriter.putUTF(this.primary);
    byteBufferWriter.putUTF(this.secondary);
    byteBufferWriter.putUTF(this.action);
    byteBufferWriter.putInt(this.variables.size());

    for (Entry entry : this.variables.entrySet()) {
      byteBufferWriter.putUTF((String)entry.getKey());
      byteBufferWriter.putUTF((String)entry.getValue());
    }
  }

  bool isConsistent() {
    bool boolean0 = this.character instanceof IsoPlayer;
    if (!boolean0 && Core.bDebug) {
      DebugLog.log(DebugType.Multiplayer, "[Action] is not consistent");
    }

    return boolean0;
  }

  std::string getDescription() {
    StringBuilder stringBuilder =
        new StringBuilder("[ ").append("character=").append(this.id);
    if (this.isConsistent()) {
      stringBuilder.append(" \"")
          .append(((IsoPlayer)this.character).getUsername())
          .append("\"");
    }

    stringBuilder.append(" | ")
        .append("action=")
        .append(this.action)
        .append(" | ")
        .append("operation=")
        .append(this.operation ? "start" : "stop")
        .append(" | ")
        .append("variables=")
        .append(this.variables.size())
        .append(" | ");

    for (Entry entry : this.variables.entrySet()) {
      stringBuilder.append((String)entry.getKey())
          .append("=")
          .append((String)entry.getValue())
          .append(" | ");
    }

    stringBuilder.append("override=")
        .append(this.override)
        .append(" ")
        .append("primary=\"")
        .append(this.primary == nullptr ? "" : this.primary)
        .append("\" ")
        .append("secondary=\"")
        .append(this.secondary == nullptr ? "" : this.secondary)
        .append("\" ]");
    return stringBuilder.toString();
  }

  bool isRelevant(UdpConnection udpConnection) {
    return this.isConsistent() &&
           udpConnection.RelevantTo(this.character.getX(),
                                    this.character.getY());
  }

  void process() {
    if (this.isConsistent()) {
      if (this.operation) {
        BaseAction baseAction = new BaseAction(this.character);
        this.variables.forEach((string1, string0)->{
          if (!"true" == string0) && !"false" == string0)) {
              baseAction.setAnimVariable(string1, string0);
            }
          else {
            baseAction.setAnimVariable(string1, Boolean.parseBoolean(string0));
          }
        });
        if ("Reload" == this.variables.get("PerformingAction"))) {
                    this.character.setVariable("ReloadSpeed", this.reloadSpeed);
                }

        this.character.setVariable("IsPerformingAnAction", true);
        this.character.getNetworkCharacterAI().setAction(baseAction);
        this.character.getNetworkCharacterAI().setOverride(
            this.override, this.primary, this.secondary);
        this.character.getNetworkCharacterAI().startAction();
      } else if (this.character.getNetworkCharacterAI().getAction() !=
                 nullptr) {
        this.character.getNetworkCharacterAI().stopAction();
      }
    } else {
      DebugLog.Multiplayer.warn("Action error: player id=" + this.id +
                                " not fond");
    }
  }
}
} // namespace packets
} // namespace network
} // namespace zombie
