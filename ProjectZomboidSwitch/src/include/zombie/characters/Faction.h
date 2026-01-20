#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/GameWindow.h"
#include "zombie/chat/ChatSettings.h"
#include "zombie/chat/defaultChats/FactionChat.h"
#include "zombie/core/Rand.h"
#include "zombie/core/network/ByteBufferWriter.h"
#include "zombie/core/textures/ColorInfo.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/ServerOptions.h"
#include "zombie/network/chat/ChatServer.h"
#include <filesystem>

namespace zombie {
namespace characters {


class Faction {
public:
    std::string name;
    std::string owner;
    std::string tag;
    ColorInfo tagColor;
   private const std::vector<std::string> players = std::make_unique<std::vector<>>();
   public static std::vector<Faction> factions = std::make_unique<std::vector<>>();

    public Faction() {
   }

    public Faction(const std::string& var1, const std::string& var2) {
      this.setName(var1);
      this.setOwner(var2);
      this.tagColor = std::make_shared<ColorInfo>(Rand.Next(0.3F, 1.0F), Rand.Next(0.3F, 1.0F), Rand.Next(0.3F, 1.0F), 1.0F);
   }

    static Faction createFaction(const std::string& var0, const std::string& var1) {
      if (!factionExist(var0)) {
    Faction var2 = std::make_shared<Faction>(var0, var1);
         factions.push_back(var2);
         if (GameClient.bClient) {
            GameClient.sendFaction(var2, false);
         }

    return var2;
      } else {
    return nullptr;
      }
   }

   public static std::vector<Faction> getFactions() {
    return factions;
   }

    static bool canCreateFaction(IsoPlayer var0) {
    bool var1 = ServerOptions.instance.Faction.getValue();
      if (var1
         && ServerOptions.instance.FactionDaySurvivedToCreate.getValue() > 0
         && var0.getHoursSurvived() / 24.0 < ServerOptions.instance.FactionDaySurvivedToCreate.getValue()) {
         var1 = false;
      }

    return var1;
   }

    bool canCreateTag() {
      return this.players.size() + 1 >= ServerOptions.instance.FactionPlayersRequiredForTag.getValue();
   }

    static bool isAlreadyInFaction(const std::string& var0) {
      for (int var1 = 0; var1 < factions.size(); var1++) {
    Faction var2 = factions.get(var1);
         if (var2.getOwner() == var0)) {
    return true;
         }

         for (int var3 = 0; var3 < var2.getPlayers().size(); var3++) {
            if (var2.getPlayers().get(var3) == var0)) {
    return true;
            }
         }
      }

    return false;
   }

    static bool isAlreadyInFaction(IsoPlayer var0) {
    return isAlreadyInFaction();
   }

    void removePlayer(const std::string& var1) {
      this.getPlayers().remove(var1);
      if (GameClient.bClient) {
         GameClient.sendFaction(this, false);
      }
   }

    static bool factionExist(const std::string& var0) {
      for (int var1 = 0; var1 < factions.size(); var1++) {
         if (factions.get(var1).getName() == var0)) {
    return true;
         }
      }

    return false;
   }

    static bool tagExist(const std::string& var0) {
      for (int var1 = 0; var1 < factions.size(); var1++) {
         if (factions.get(var1).getTag() != nullptr && factions.get(var1).getTag() == var0)) {
    return true;
         }
      }

    return false;
   }

    static Faction getPlayerFaction(IsoPlayer var0) {
      for (int var1 = 0; var1 < factions.size(); var1++) {
    Faction var2 = factions.get(var1);
         if (var2.getOwner() == var0.getUsername())) {
    return var2;
         }

         for (int var3 = 0; var3 < var2.getPlayers().size(); var3++) {
            if (var2.getPlayers().get(var3) == var0.getUsername())) {
    return var2;
            }
         }
      }

    return nullptr;
   }

    static Faction getPlayerFaction(const std::string& var0) {
      for (int var1 = 0; var1 < factions.size(); var1++) {
    Faction var2 = factions.get(var1);
         if (var2.getOwner() == var0)) {
    return var2;
         }

         for (int var3 = 0; var3 < var2.getPlayers().size(); var3++) {
            if (var2.getPlayers().get(var3) == var0)) {
    return var2;
            }
         }
      }

    return nullptr;
   }

    static Faction getFaction(const std::string& var0) {
      for (int var1 = 0; var1 < factions.size(); var1++) {
         if (factions.get(var1).getName() == var0)) {
            return factions.get(var1);
         }
      }

    return nullptr;
   }

    void removeFaction() {
      getFactions().remove(this);
      if (GameClient.bClient) {
         GameClient.sendFaction(this, true);
      }
   }

    void syncFaction() {
      if (GameClient.bClient) {
         GameClient.sendFaction(this, false);
      }
   }

    bool isOwner(const std::string& var1) {
      return this.getOwner() == var1);
   }

    bool isPlayerMember(IsoPlayer var1) {
      return this.isMember(var1.getUsername());
   }

    bool isMember(const std::string& var1) {
      for (int var2 = 0; var2 < this.getPlayers().size(); var2++) {
         if (this.getPlayers().get(var2) == var1)) {
    return true;
         }
      }

    return false;
   }

    void writeToBuffer(ByteBufferWriter var1, bool var2) {
      var1.putUTF(this.getName());
      var1.putUTF(this.getOwner());
      var1.putInt(this.getPlayers().size());
      if (this.getTag() != nullptr) {
         var1.putByte((byte)1);
         var1.putUTF(this.getTag());
         var1.putFloat(this.getTagColor().r);
         var1.putFloat(this.getTagColor().g);
         var1.putFloat(this.getTagColor().b);
      } else {
         var1.putByte((byte)0);
      }

      for (std::string var4 : this.getPlayers()) {
         var1.putUTF(var4);
      }

      var1.putBoolean(var2);
   }

    void save(ByteBuffer var1) {
      GameWindow.WriteString(var1, this.getName());
      GameWindow.WriteString(var1, this.getOwner());
      var1.putInt(this.getPlayers().size());
      if (this.getTag() != nullptr) {
         var1.put((byte)1);
         GameWindow.WriteString(var1, this.getTag());
         var1.putFloat(this.getTagColor().r);
         var1.putFloat(this.getTagColor().g);
         var1.putFloat(this.getTagColor().b);
      } else {
         var1.put((byte)0);
      }

      for (std::string var3 : this.getPlayers()) {
         GameWindow.WriteString(var1, var3);
      }
   }

    void load(ByteBuffer var1, int var2) {
      this.setName(GameWindow.ReadString(var1));
      this.setOwner(GameWindow.ReadString(var1));
    int var3 = var1.getInt();
      if (var1.get() == 1) {
         this.setTag(GameWindow.ReadString(var1));
         this.setTagColor(std::make_shared<ColorInfo>(var1.getFloat(), var1.getFloat(), var1.getFloat(), 1.0F));
      } else {
         this.setTagColor(std::make_shared<ColorInfo>(Rand.Next(0.3F, 1.0F), Rand.Next(0.3F, 1.0F), Rand.Next(0.3F, 1.0F), 1.0F));
      }

      for (int var4 = 0; var4 < var3; var4++) {
         this.getPlayers().push_back(GameWindow.ReadString(var1));
      }

      if (ChatServer.isInited()) {
    FactionChat var6 = ChatServer.getInstance().createFactionChat(this.getName());
    ChatSettings var5 = FactionChat.getDefaultSettings();
         var5.setFontColor(this.tagColor.r, this.tagColor.g, this.tagColor.b, this.tagColor.a);
         var6.setSettings(var5);
      }
   }

    void addPlayer(const std::string& var1) {
      for (int var2 = 0; var2 < factions.size(); var2++) {
    Faction var3 = factions.get(var2);
         if (var3.getOwner() == var1)) {
            return;
         }

         for (int var4 = 0; var4 < var3.getPlayers().size(); var4++) {
            if (var3.getPlayers().get(var4) == var1)) {
               return;
            }
         }
      }

      this.players.push_back(var1);
      if (GameClient.bClient) {
         GameClient.sendFaction(this, false);
      }
   }

   public std::vector<std::string> getPlayers() {
      return this.players;
   }

    ColorInfo getTagColor() {
      return this.tagColor;
   }

    void setTagColor(ColorInfo var1) {
      if (var1.r < 0.19F) {
         var1.r = 0.19F;
      }

      if (var1.g < 0.19F) {
         var1.g = 0.19F;
      }

      if (var1.b < 0.19F) {
         var1.b = 0.19F;
      }

      this.tagColor = var1;
   }

    std::string getTag() {
      return this.tag;
   }

    void setTag(const std::string& var1) {
      this.tag = var1;
   }

    std::string getName() {
      return this.name;
   }

    void setName(const std::string& var1) {
      this.name = var1;
   }

    std::string getOwner() {
      return this.owner;
   }

    void setOwner(const std::string& var1) {
      if (this.owner == nullptr) {
         this.owner = var1;
      } else {
         if (!this.isMember(this.owner)) {
            this.getPlayers().push_back(this.owner);
            this.getPlayers().remove(var1);
         }

         this.owner = var1;
      }
   }
}
} // namespace characters
} // namespace zombie
