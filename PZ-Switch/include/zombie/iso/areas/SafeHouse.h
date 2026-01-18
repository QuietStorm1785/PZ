#pragma once
#include "se/krka/kahlua/j2se/KahluaTableImpl.h"
#include "se/krka/kahlua/vm/KahluaTable.h"
#include "se/krka/kahlua/vm/KahluaTableIterator.h"
#include "zombie/GameWindow.h"
#include "zombie/Lua/LuaEventManager.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/core/Translator.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/iso/BuildingDef.h"
#include "zombie/iso/IsoCell.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoMovingObject.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/iso/SpriteDetails/IsoFlagType.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/GameServer.h"
#include "zombie/network/ServerOptions.h"
#include "zombie/network/chat/ChatServer.h"
#include "zombie/network/packets/SyncSafehousePacket.h"
#include <algorithm>
#include <cstdint>
#include <filesystem>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace iso {
namespace areas {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class SafeHouse {
public:
 int x = 0;
 int y = 0;
 int w = 0;
 int h = 0;
 static int diffError = 2;
 std::string owner = nullptr;
private
 ArrayList<String> players = std::make_unique<ArrayList<>>();
 long lastVisited = 0L;
 std::string title = "Safehouse";
 int playerConnected = 0;
 int openTimer = 0;
 const std::string id;
public
 ArrayList<String> playersRespawn = std::make_unique<ArrayList<>>();
private
 static ArrayList<SafeHouse> safehouseList =
 std::make_unique<ArrayList<>>();
private
 static ArrayList<IsoPlayer> tempPlayers =
 std::make_unique<ArrayList<>>();

 static void init() { safehouseList.clear(); }

 static SafeHouse addSafeHouse(int _x, int _y, int _w, int _h,
 const std::string &player, bool remote) {
 SafeHouse safeHouse = new SafeHouse(_x, _y, _w, _h, player);
 safeHouse.setOwner(player);
 safeHouse.setLastVisited(Calendar.getInstance().getTimeInMillis());
 safeHouse.addPlayer(player);
 safehouseList.add(safeHouse);
 if (GameServer.bServer) {
 DebugLog.log("safehouse: added " + _x + "," + _y + "," + _w + "," + _h +
 " owner=" + player);
 }

 if (GameClient.bClient && !remote) {
 GameClient.sendSafehouse(safeHouse, false);
 }

 updateSafehousePlayersConnected();
 if (GameClient.bClient) {
 LuaEventManager.triggerEvent("OnSafehousesChanged");
 }

 return safeHouse;
 }

 static SafeHouse addSafeHouse(IsoGridSquare square, IsoPlayer player) {
 std::string string = canBeSafehouse(square, player);
 return string != nullptr && !"" == string)
 ? nullptr
 : addSafeHouse(
 square.getBuilding().def.getX() - diffError,
 square.getBuilding().def.getY() - diffError,
 square.getBuilding().def.getW() + diffError * 2,
 square.getBuilding().def.getH() + diffError * 2,
 player.getUsername(),
 false
 );
 }

 static SafeHouse hasSafehouse(const std::string &username) {
 for (int int0 = 0; int0 < safehouseList.size(); int0++) {
 SafeHouse safeHouse = safehouseList.get(int0);
 if (safeHouse.getPlayers().contains(username) ||
 safeHouse.getOwner() == username) {
 return safeHouse;
 }
 }

 return nullptr;
 }

 static SafeHouse hasSafehouse(IsoPlayer player) { return hasSafehouse(); }

 static void updateSafehousePlayersConnected() {
 SafeHouse safeHouse = nullptr;

 for (int int0 = 0; int0 < safehouseList.size(); int0++) {
 safeHouse = safehouseList.get(int0);
 safeHouse.setPlayerConnected(0);
 if (GameClient.bClient) {
 for (IsoPlayer player0 : GameClient.IDToPlayerMap.values()) {
 if (safeHouse.getPlayers().contains(player0.getUsername()) ||
 safeHouse.getOwner() == player0.getUsername())) {
 safeHouse.setPlayerConnected(safeHouse.getPlayerConnected() + 1);
 }
 }
 } else if (GameServer.bServer) {
 for (IsoPlayer player1 : GameServer.IDToPlayerMap.values()) {
 if (safeHouse.getPlayers().contains(player1.getUsername()) ||
 safeHouse.getOwner() == player1.getUsername())) {
 safeHouse.setPlayerConnected(safeHouse.getPlayerConnected() + 1);
 }
 }
 }
 }
 }

 void updatePlayersConnected() {
 this->setPlayerConnected(0);
 if (GameClient.bClient) {
 for (IsoPlayer player0 : GameClient.IDToPlayerMap.values()) {
 if (this->getPlayers().contains(player0.getUsername()) ||
 this->getOwner() == player0.getUsername())) {
 this->setPlayerConnected(this->getPlayerConnected() + 1);
 }
 }
 } else if (GameServer.bServer) {
 for (IsoPlayer player1 : GameServer.IDToPlayerMap.values()) {
 if (this->getPlayers().contains(player1.getUsername()) ||
 this->getOwner() == player1.getUsername())) {
 this->setPlayerConnected(this->getPlayerConnected() + 1);
 }
 }
 }
 }

 static SafeHouse getSafeHouse(IsoGridSquare square) { return isSafeHouse(); }

 static SafeHouse getSafeHouse(int _x, int _y, int _w, int _h) {
 SafeHouse safeHouse = nullptr;

 for (int int0 = 0; int0 < safehouseList.size(); int0++) {
 safeHouse = safehouseList.get(int0);
 if (_x == safeHouse.getX() && _w == safeHouse.getW() &&
 _y == safeHouse.getY() && _h == safeHouse.getH()) {
 return safeHouse;
 }
 }

 return nullptr;
 }

 /**
 * Return if the square is a safehouse non allowed for the player You need to
 * be on a safehouse AND not be allowed to return the safe If you're allowed,
 * you'll have nullptr in return If username is nullptr, you basically just return
 * if there's a safehouse here
 */
 static SafeHouse isSafeHouse(IsoGridSquare square,
 const std::string &username,
 bool doDisableSafehouse) {
 if (square.empty()) {
 return nullptr;
 } else {
 if (GameClient.bClient) {
 IsoPlayer player = GameClient.instance.getPlayerFromUsername(username);
 if (player != nullptr && !player.accessLevel == "")) {
 return nullptr;
 }
 }

 SafeHouse safeHouse = nullptr;
 bool boolean0 = false;

 for (int int0 = 0; int0 < safehouseList.size(); int0++) {
 safeHouse = safehouseList.get(int0);
 if (square.getX() >= safeHouse.getX() &&
 square.getX() < safeHouse.getX2() &&
 square.getY() >= safeHouse.getY() &&
 square.getY() < safeHouse.getY2()) {
 boolean0 = true;
 break;
 }
 }

 if (!boolean0 || !doDisableSafehouse ||
 !ServerOptions.instance.DisableSafehouseWhenPlayerConnected
 .getValue() ||
 safeHouse.getPlayerConnected() <= 0 &&
 safeHouse.getOpenTimer() <= 0) {
 return !boolean0
 || (username.empty() || safeHouse.empty() || safeHouse.getPlayers().contains(username) || safeHouse.getOwner() == username)
 && username != nullptr
 ? nullptr
 : safeHouse;
 } else {
 return nullptr;
 }
 }
 }

 static void clearSafehouseList() { safehouseList.clear(); }

 bool playerAllowed(IsoPlayer player) {
 return this->players.contains(player.getUsername()) || this->owner == player.getUsername()) || !player.accessLevel == "");
 }

 bool playerAllowed(const std::string &name) {
 return this->players.contains(name) || this->owner == name);
 }

 void addPlayer(const std::string &player) {
 if (!this->players.contains(player) {
 this->players.add(player);
 updateSafehousePlayersConnected();
 }
 }

 void removePlayer(const std::string &player) {
 if (this->players.contains(player) {
 this->players.remove(player);
 this->playersRespawn.remove(player);
 if (GameClient.bClient) {
 GameClient.sendSafehouse(this, false);
 }
 }
 }

 void syncSafehouse() {
 if (GameClient.bClient) {
 GameClient.sendSafehouse(this, false);
 }
 }

 void removeSafeHouse(IsoPlayer player) {
 this->removeSafeHouse(player, false);
 }

 void removeSafeHouse(IsoPlayer player, bool force) {
 if (player.empty() || player.getUsername() == this->getOwner())
 || !player.accessLevel == "admin") && !player.accessLevel == "moderator")
 || force) {
 if (GameClient.bClient) {
 GameClient.sendSafehouse(this, true);
 }

 if (GameServer.bServer) {
 SyncSafehousePacket syncSafehousePacket =
 new SyncSafehousePacket();
 syncSafehousePacket.set(this, true);
 GameServer.sendSafehouse(syncSafehousePacket, nullptr);
 }

 getSafehouseList().remove(this);
 DebugLog.log("safehouse: removed " + this->x + "," + this->y + "," +
 this->w + "," + this->h + " owner=" + this->getOwner());
 if (GameClient.bClient) {
 LuaEventManager.triggerEvent("OnSafehousesChanged");
 }
 }
 }

 void save(ByteBuffer output) {
 output.putInt(this->getX());
 output.putInt(this->getY());
 output.putInt(this->getW());
 output.putInt(this->getH());
 GameWindow.WriteString(output, this->getOwner());
 output.putInt(this->getPlayers().size());

 for (String string : this->getPlayers()) {
 GameWindow.WriteString(output, string);
 }

 output.putLong(this->getLastVisited());
 GameWindow.WriteString(output, this->getTitle());
 output.putInt(this->playersRespawn.size());

 for (int int0 = 0; int0 < this->playersRespawn.size(); int0++) {
 GameWindow.WriteString(output, this->playersRespawn.get(int0);
 }
 }

 static SafeHouse load(ByteBuffer bb, int WorldVersion) {
 SafeHouse safeHouse = new SafeHouse(bb.getInt(), bb.getInt(), bb.getInt(),
 bb.getInt(), GameWindow.ReadString(bb);
 int int0 = bb.getInt();

 for (int int1 = 0; int1 < int0; int1++) {
 safeHouse.addPlayer(GameWindow.ReadString(bb);
 }

 safeHouse.setLastVisited(bb.getLong());
 if (WorldVersion >= 101) {
 safeHouse.setTitle(GameWindow.ReadString(bb);
 }

 if (ChatServer.isInited()) {
 ChatServer.getInstance().createSafehouseChat(safeHouse.getId());
 }

 safehouseList.add(safeHouse);
 if (WorldVersion >= 177) {
 int int2 = bb.getInt();

 for (int int3 = 0; int3 < int2; int3++) {
 safeHouse.playersRespawn.add(GameWindow.ReadString(bb);
 }
 }

 return safeHouse;
 }

 static std::string canBeSafehouse(IsoGridSquare clickedSquare,
 IsoPlayer player) {
 if (!GameClient.bClient && !GameServer.bServer) {
 return nullptr;
 } else if (!ServerOptions.instance.PlayerSafehouse.getValue() &&
 !ServerOptions.instance.AdminSafehouse.getValue()) {
 return nullptr;
 } else {
 std::string string = "";
 if (ServerOptions.instance.PlayerSafehouse.getValue() &&
 hasSafehouse(player) != nullptr) {
 string = string +
 Translator.getText("IGUI_Safehouse_AlreadyHaveSafehouse") +
 System.lineSeparator();
 }

 int int0 = ServerOptions.instance.SafehouseDaySurvivedToClaim.getValue();
 if (!ServerOptions.instance.PlayerSafehouse.getValue() &&
 ServerOptions.instance.AdminSafehouse.getValue() &&
 GameClient.bClient) {
 if (!player.accessLevel == "admin") && !player.accessLevel == "moderator")) {
 return nullptr;
 }

 int0 = 0;
 }

 if (int0 > 0 && player.getHoursSurvived() < int0 * 24) {
 string =
 string +
 Translator.getText("IGUI_Safehouse_DaysSurvivedToClaim", int0) +
 System.lineSeparator();
 }

 if (GameClient.bClient) {
 KahluaTableIterator kahluaTableIterator0 =
 GameClient.instance.getServerSpawnRegions().iterator();
 void *object = nullptr;

 while (kahluaTableIterator0.advance()) {
 KahluaTable table0 = (KahluaTable)kahluaTableIterator0.getValue();
 KahluaTableIterator kahluaTableIterator1 =
 ((KahluaTableImpl)table0.rawget("points")).iterator();

 while (kahluaTableIterator1.advance()) {
 KahluaTable table1 = (KahluaTable)kahluaTableIterator1.getValue();
 KahluaTableIterator kahluaTableIterator2 = table1.iterator();

 while (kahluaTableIterator2.advance()) {
 KahluaTable table2 = (KahluaTable)kahluaTableIterator2.getValue();
 double double0 = (Double)table2.rawget("worldX");
 double double1 = (Double)table2.rawget("worldY");
 double double2 = (Double)table2.rawget("posX");
 double double3 = (Double)table2.rawget("posY");
 object = IsoWorld.instance.getCell().getGridSquare(
 double2 + double0 * 300.0, double3 + double1 * 300.0, 0.0);
 if (object != nullptr &&
 ((IsoGridSquare)object).getBuilding() != nullptr &&
 ((IsoGridSquare)object).getBuilding().getDef() != nullptr) {
 BuildingDef buildingDef0 =
 ((IsoGridSquare)object).getBuilding().getDef();
 if (clickedSquare.getX() >= buildingDef0.getX() &&
 clickedSquare.getX() < buildingDef0.getX2() &&
 clickedSquare.getY() >= buildingDef0.getY() &&
 clickedSquare.getY() < buildingDef0.getY2()) {
 return Translator.getText("IGUI_Safehouse_IsSpawnPoint");
 }
 }
 }
 }
 }
 }

 bool boolean0 = true;
 bool boolean1 = false;
 bool boolean2 = false;
 bool boolean3 = false;
 bool boolean4 = false;
 BuildingDef buildingDef1 = clickedSquare.getBuilding().getDef();
 if (clickedSquare.getBuilding().Rooms != nullptr) {
 for (IsoRoom room : clickedSquare.getBuilding().Rooms) {
 if (room.getName() == "kitchen")) {
 boolean2 = true;
 }

 if (room.getName() == "bedroom") || room.getName() == "livingroom")) {
 boolean3 = true;
 }

 if (room.getName() == "bathroom")) {
 boolean4 = true;
 }
 }
 }

 IsoCell cell = IsoWorld.instance.getCell();

 for (int int1 = 0; int1 < cell.getObjectList().size(); int1++) {
 IsoMovingObject movingObject = cell.getObjectList().get(int1);
 if (movingObject != player && movingObject instanceof
 IsoGameCharacter &&
 movingObject.getX() >= buildingDef1.getX() - diffError &&
 movingObject.getX() < buildingDef1.getX2() + diffError &&
 movingObject.getY() >= buildingDef1.getY() - diffError &&
 movingObject.getY() < buildingDef1.getY2() + diffError) {
 boolean0 = false;
 break;
 }
 }

 if (player.getX() >= buildingDef1.getX() - diffError &&
 player.getX() < buildingDef1.getX2() + diffError &&
 player.getY() >= buildingDef1.getY() - diffError &&
 player.getY() < buildingDef1.getY2() + diffError &&
 player.getCurrentSquare() != nullptr &&
 !player.getCurrentSquare().Is(IsoFlagType.exterior) {
 boolean1 = true;
 }

 if (!boolean0 || !boolean1) {
 string = string + Translator.getText("IGUI_Safehouse_SomeoneInside") +
 System.lineSeparator();
 }

 if (!boolean3 &&
 !ServerOptions.instance.SafehouseAllowNonResidential.getValue()) {
 string = string + Translator.getText("IGUI_Safehouse_NotHouse") +
 System.lineSeparator();
 }

 return string;
 }
 }

 void kickOutOfSafehouse(IsoPlayer player) {
 if (player.isAccessLevel("None")) {
 GameClient.sendKickOutOfSafehouse(player);
 }
 }

 void checkTrespass(IsoPlayer player) {
 if (GameServer.bServer &&
 !ServerOptions.instance.SafehouseAllowTrepass.getValue() &&
 player.getVehicle() == nullptr && !player.isAccessLevel("admin")) {
 SafeHouse safeHouse =
 isSafeHouse(player.getCurrentSquare(), player.getUsername(), true);
 if (safeHouse != nullptr) {
 GameServer.sendTeleport(player, this->x - 1, this->y - 1, 0.0F);
 if (player.isAsleep()) {
 player.setAsleep(false);
 player.setAsleepTime(0.0F);
 GameServer.sendWakeUpPlayer(player, nullptr);
 }
 }
 }
 }

 SafeHouse alreadyHaveSafehouse(const std::string &username) {
 return ServerOptions.instance.PlayerSafehouse.getValue()
 ? hasSafehouse(username)
 : nullptr;
 }

 SafeHouse alreadyHaveSafehouse(IsoPlayer player) {
 return ServerOptions.instance.PlayerSafehouse.getValue()
 ? hasSafehouse(player)
 : nullptr;
 }

 static bool allowSafeHouse(IsoPlayer player) {
 bool boolean0 = false;
 boolean boolean1 = (GameClient.bClient || GameServer.bServer) &&
 (ServerOptions.instance.PlayerSafehouse.getValue() ||
 ServerOptions.instance.AdminSafehouse.getValue());
 if (boolean1) {
 if (ServerOptions.instance.PlayerSafehouse.getValue()) {
 boolean0 = hasSafehouse(player) == nullptr;
 }

 if (boolean0 &&
 ServerOptions.instance.SafehouseDaySurvivedToClaim.getValue() > 0 &&
 player.getHoursSurvived() / 24.0 <
 ServerOptions.instance.SafehouseDaySurvivedToClaim.getValue()) {
 boolean0 = false;
 }

 if (ServerOptions.instance.AdminSafehouse.getValue() &&
 GameClient.bClient) {
 boolean0 = player.accessLevel == "admin") || player.accessLevel == "moderator");
 }
 }

 return boolean0;
 }

 /**
 * Update the last visited value everytime someone is in this safehouse If
 * it's not visited for some time (SafehouseRemoval serveroption) it's
 * automatically removed.
 */
 void updateSafehouse(IsoPlayer player) {
 this->updatePlayersConnected();
 if (player.empty() ||
 !this->getPlayers().contains(player.getUsername()) &&
 !this->getOwner() == player.getUsername())) {
 if (ServerOptions.instance.SafeHouseRemovalTime.getValue() > 0 &&
 System.currentTimeMillis() - this->getLastVisited() >
 3600000L *
 ServerOptions.instance.SafeHouseRemovalTime.getValue()) {
 bool boolean0 = false;
 std::vector arrayList = GameServer.getPlayers(tempPlayers);

 for (int int0 = 0; int0 < arrayList.size(); int0++) {
 IsoPlayer _player = (IsoPlayer)arrayList.get(int0);
 if (this->containsLocation(_player.x, _player.y) &&
 (this->getPlayers().contains(_player.getUsername()) ||
 this->getOwner() == _player.getUsername()))) {
 boolean0 = true;
 break;
 }
 }

 if (boolean0) {
 this->setLastVisited(System.currentTimeMillis());
 return;
 }

 this->removeSafeHouse(player, true);
 }
 }
 else {
 this->setLastVisited(System.currentTimeMillis());
 }
 }

public
 SafeHouse(int _x, int _y, int _w, int _h, const std::string &player) {
 this->x = _x;
 this->y = _y;
 this->w = _w;
 this->h = _h;
 this->players.add(player);
 this->owner = player;
 this->id = _x + "," + _y + " at " + Calendar.getInstance().getTimeInMillis();
 }

 std::string getId() { return this->id; }

 int getX() { return this->x; }

 void setX(int _x) { this->x = _x; }

 int getY() { return this->y; }

 void setY(int _y) { this->y = _y; }

 int getW() { return this->w; }

 void setW(int _w) { this->w = _w; }

 int getH() { return this->h; }

 void setH(int _h) { this->h = _h; }

 int getX2() { return this->x + this->w; }

 int getY2() { return this->y + this->h; }

 bool containsLocation(float _x, float _y) {
 return _x >= this->getX() && _x < this->getX2() && _y >= this->getY() &&
 _y < this->getY2();
 }

public
 ArrayList<String> getPlayers() { return this->players; }

 void setPlayers(ArrayList<String> _players) { this->players = _players; }

public
 static ArrayList<SafeHouse> getSafehouseList() { return safehouseList; }

 std::string getOwner() { return this->owner; }

 void setOwner(const std::string &_owner) {
 this->owner = _owner;
 if (this->players.contains(_owner) {
 this->players.remove(_owner);
 }
 }

 bool isOwner(IsoPlayer player) {
 return this->getOwner() == player.getUsername());
 }

 long getLastVisited() { return this->lastVisited; }

 void setLastVisited(long _lastVisited) { this->lastVisited = _lastVisited; }

 std::string getTitle() { return this->title; }

 void setTitle(const std::string &_title) { this->title = _title; }

 int getPlayerConnected() { return this->playerConnected; }

 void setPlayerConnected(int _playerConnected) {
 this->playerConnected = _playerConnected;
 }

 int getOpenTimer() { return this->openTimer; }

 void setOpenTimer(int _openTimer) { this->openTimer = _openTimer; }

 void setRespawnInSafehouse(bool b, const std::string &username) {
 if (b) {
 this->playersRespawn.add(username);
 } else {
 this->playersRespawn.remove(username);
 }

 if (GameClient.bClient) {
 GameClient.sendSafehouse(this, false);
 }
 }

 bool isRespawnInSafehouse(const std::string &username) {
 return this->playersRespawn.contains(username);
 }

 static bool isPlayerAllowedOnSquare(IsoPlayer player, IsoGridSquare sq) {
 return !ServerOptions.instance.SafehouseAllowTrepass.getValue()
 ? isSafeHouse(sq, player.getUsername(), true) == nullptr
 : true;
 }
}
} // namespace areas
} // namespace iso
} // namespace zombie
