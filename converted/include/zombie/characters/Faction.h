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
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class Faction {
public:
 std::string name;
 std::string owner;
 std::string tag;
 ColorInfo tagColor;
 private ArrayList<String> players = std::make_unique<ArrayList<>>();
 public static ArrayList<Faction> factions = std::make_unique<ArrayList<>>();

 public Faction() {
 }

 public Faction(const std::string& _name, const std::string& _owner) {
 this->setName(_name);
 this->setOwner(_owner);
 this->tagColor = new ColorInfo(Rand.Next(0.3F, 1.0F), Rand.Next(0.3F, 1.0F), Rand.Next(0.3F, 1.0F), 1.0F);
 }

 static Faction createFaction(const std::string& _name, const std::string& _owner) {
 if (!factionExist(_name) {
 Faction faction = new Faction(_name, _owner);
 factions.add(faction);
 if (GameClient.bClient) {
 GameClient.sendFaction(faction, false);
 }

 return faction;
 } else {
 return nullptr;
 }
 }

 public static ArrayList<Faction> getFactions() {
 return factions;
 }

 static bool canCreateFaction(IsoPlayer player) {
 bool boolean0 = ServerOptions.instance.Faction.getValue();
 if (boolean0
 && ServerOptions.instance.FactionDaySurvivedToCreate.getValue() > 0
 && player.getHoursSurvived() / 24.0 < ServerOptions.instance.FactionDaySurvivedToCreate.getValue()) {
 boolean0 = false;
 }

 return boolean0;
 }

 bool canCreateTag() {
 return this->players.size() + 1 >= ServerOptions.instance.FactionPlayersRequiredForTag.getValue();
 }

 static bool isAlreadyInFaction(const std::string& username) {
 for (int int0 = 0; int0 < factions.size(); int0++) {
 Faction faction = factions.get(int0);
 if (faction.getOwner() == username) {
 return true;
 }

 for (int int1 = 0; int1 < faction.getPlayers().size(); int1++) {
 if (faction.getPlayers().get(int1) == username) {
 return true;
 }
 }
 }

 return false;
 }

 static bool isAlreadyInFaction(IsoPlayer player) {
 return isAlreadyInFaction();
 }

 void removePlayer(const std::string& player) {
 this->getPlayers().remove(player);
 if (GameClient.bClient) {
 GameClient.sendFaction(this, false);
 }
 }

 static bool factionExist(const std::string& _name) {
 for (int int0 = 0; int0 < factions.size(); int0++) {
 if (factions.get(int0).getName() == _name) {
 return true;
 }
 }

 return false;
 }

 static bool tagExist(const std::string& _name) {
 for (int int0 = 0; int0 < factions.size(); int0++) {
 if (factions.get(int0).getTag() != nullptr && factions.get(int0).getTag() == _name) {
 return true;
 }
 }

 return false;
 }

 static Faction getPlayerFaction(IsoPlayer player) {
 for (int int0 = 0; int0 < factions.size(); int0++) {
 Faction faction = factions.get(int0);
 if (faction.getOwner() == player.getUsername())) {
 return faction;
 }

 for (int int1 = 0; int1 < faction.getPlayers().size(); int1++) {
 if (faction.getPlayers().get(int1) == player.getUsername())) {
 return faction;
 }
 }
 }

 return nullptr;
 }

 static Faction getPlayerFaction(const std::string& username) {
 for (int int0 = 0; int0 < factions.size(); int0++) {
 Faction faction = factions.get(int0);
 if (faction.getOwner() == username) {
 return faction;
 }

 for (int int1 = 0; int1 < faction.getPlayers().size(); int1++) {
 if (faction.getPlayers().get(int1) == username) {
 return faction;
 }
 }
 }

 return nullptr;
 }

 static Faction getFaction(const std::string& _name) {
 for (int int0 = 0; int0 < factions.size(); int0++) {
 if (factions.get(int0).getName() == _name) {
 return factions.get(int0);
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

 bool isOwner(const std::string& _name) {
 return this->getOwner() == _name);
 }

 bool isPlayerMember(IsoPlayer player) {
 return this->isMember(player.getUsername());
 }

 bool isMember(const std::string& _name) {
 for (int int0 = 0; int0 < this->getPlayers().size(); int0++) {
 if (this->getPlayers().get(int0) == _name) {
 return true;
 }
 }

 return false;
 }

 void writeToBuffer(ByteBufferWriter bb, bool remove) {
 bb.putUTF(this->getName());
 bb.putUTF(this->getOwner());
 bb.putInt(this->getPlayers().size());
 if (this->getTag() != nullptr) {
 bb.putByte((byte)1);
 bb.putUTF(this->getTag());
 bb.putFloat(this->getTagColor().r);
 bb.putFloat(this->getTagColor().g);
 bb.putFloat(this->getTagColor().b);
 } else {
 bb.putByte((byte)0);
 }

 for (String string : this->getPlayers()) {
 bb.putUTF(string);
 }

 bb.putBoolean(remove);
 }

 void save(ByteBuffer output) {
 GameWindow.WriteString(output, this->getName());
 GameWindow.WriteString(output, this->getOwner());
 output.putInt(this->getPlayers().size());
 if (this->getTag() != nullptr) {
 output.put((byte)1);
 GameWindow.WriteString(output, this->getTag());
 output.putFloat(this->getTagColor().r);
 output.putFloat(this->getTagColor().g);
 output.putFloat(this->getTagColor().b);
 } else {
 output.put((byte)0);
 }

 for (String string : this->getPlayers()) {
 GameWindow.WriteString(output, string);
 }
 }

 void load(ByteBuffer input, int WorldVersion) {
 this->setName(GameWindow.ReadString(input);
 this->setOwner(GameWindow.ReadString(input);
 int int0 = input.getInt();
 if (input.get() == 1) {
 this->setTag(GameWindow.ReadString(input);
 this->setTagColor(new ColorInfo(input.getFloat(), input.getFloat(), input.getFloat(), 1.0F);
 } else {
 this->setTagColor(new ColorInfo(Rand.Next(0.3F, 1.0F), Rand.Next(0.3F, 1.0F), Rand.Next(0.3F, 1.0F), 1.0F);
 }

 for (int int1 = 0; int1 < int0; int1++) {
 this->getPlayers().add(GameWindow.ReadString(input);
 }

 if (ChatServer.isInited()) {
 FactionChat factionChat = ChatServer.getInstance().createFactionChat(this->getName());
 ChatSettings chatSettings = FactionChat.getDefaultSettings();
 chatSettings.setFontColor(this->tagColor.r, this->tagColor.g, this->tagColor.b, this->tagColor.a);
 factionChat.setSettings(chatSettings);
 }
 }

 void addPlayer(const std::string& pName) {
 for (int int0 = 0; int0 < factions.size(); int0++) {
 Faction faction = factions.get(int0);
 if (faction.getOwner() == pName) {
 return;
 }

 for (int int1 = 0; int1 < faction.getPlayers().size(); int1++) {
 if (faction.getPlayers().get(int1) == pName) {
 return;
 }
 }
 }

 this->players.add(pName);
 if (GameClient.bClient) {
 GameClient.sendFaction(this, false);
 }
 }

 public ArrayList<String> getPlayers() {
 return this->players;
 }

 ColorInfo getTagColor() {
 return this->tagColor;
 }

 void setTagColor(ColorInfo _tagColor) {
 if (_tagColor.r < 0.19F) {
 _tagColor.r = 0.19F;
 }

 if (_tagColor.g < 0.19F) {
 _tagColor.g = 0.19F;
 }

 if (_tagColor.b < 0.19F) {
 _tagColor.b = 0.19F;
 }

 this->tagColor = _tagColor;
 }

 std::string getTag() {
 return this->tag;
 }

 void setTag(const std::string& _tag) {
 this->tag = _tag;
 }

 std::string getName() {
 return this->name;
 }

 void setName(const std::string& _name) {
 this->name = _name;
 }

 std::string getOwner() {
 return this->owner;
 }

 void setOwner(const std::string& _owner) {
 if (this->owner.empty()) {
 this->owner = _owner;
 } else {
 if (!this->isMember(this->owner) {
 this->getPlayers().add(this->owner);
 this->getPlayers().remove(_owner);
 }

 this->owner = _owner;
 }
 }
}
} // namespace characters
} // namespace zombie
