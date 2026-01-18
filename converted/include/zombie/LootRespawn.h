#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/characters/IsoPlayer.h"
#include "zombie/core/network/ByteBufferWriter.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/inventory/CompressIdenticalItems.h"
#include "zombie/inventory/InventoryItem.h"
#include "zombie/inventory/ItemContainer.h"
#include "zombie/inventory/ItemPickerJava.h"
#include "zombie/iso/BuildingDef.h"
#include "zombie/iso/IsoChunk.h"
#include "zombie/iso/IsoChunkMap.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoMetaGrid.h"
#include "zombie/iso/IsoObject.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/iso/objects/IsoCompost.h"
#include "zombie/iso/objects/IsoDeadBody.h"
#include "zombie/iso/objects/IsoThumpable.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/GameServer.h"
#include "zombie/network/PacketTypes.h"
#include "zombie/network/ServerMap.h"
#include "zombie/network/ServerOptions.h"

namespace zombie {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class LootRespawn {
public:
 static int LastRespawnHour = -1;
 private static ArrayList<InventoryItem> existingItems = std::make_unique<ArrayList<>>();
 private static ArrayList<InventoryItem> newItems = std::make_unique<ArrayList<>>();

 static void update() {
 if (!GameClient.bClient) {
 int int0 = getRespawnInterval();
 if (int0 > 0) {
 int int1 = 7 + (int)(GameTime.getInstance().getWorldAgeHours() / int0) * int0;
 if (LastRespawnHour < int1) {
 LastRespawnHour = int1;
 if (GameServer.bServer) {
 for (int int2 = 0; int2 < ServerMap.instance.LoadedCells.size(); int2++) {
 ServerMap.ServerCell serverCell = ServerMap.instance.LoadedCells.get(int2);
 if (serverCell.bLoaded) {
 for (int int3 = 0; int3 < 5; int3++) {
 for (int int4 = 0; int4 < 5; int4++) {
 IsoChunk chunk0 = serverCell.chunks[int4][int3];
 checkChunk(chunk0);
 }
 }
 }
 }
 } else {
 for (int int5 = 0; int5 < IsoPlayer.numPlayers; int5++) {
 IsoChunkMap chunkMap = IsoWorld.instance.CurrentCell.ChunkMap[int5];
 if (!chunkMap.ignore) {
 for (int int6 = 0; int6 < IsoChunkMap.ChunkGridWidth; int6++) {
 for (int int7 = 0; int7 < IsoChunkMap.ChunkGridWidth; int7++) {
 IsoChunk chunk1 = chunkMap.getChunk(int7, int6);
 checkChunk(chunk1);
 }
 }
 }
 }
 }
 }
 }
 }
 }

 static void Reset() {
 LastRespawnHour = -1;
 }

 static void chunkLoaded(IsoChunk chunk) {
 if (!GameClient.bClient) {
 checkChunk(chunk);
 }
 }

 static void checkChunk(IsoChunk chunk) {
 if (chunk != nullptr) {
 int int0 = getRespawnInterval();
 if (int0 > 0) {
 if (!(GameTime.getInstance().getWorldAgeHours() < int0) {
 int int1 = 7 + (int)(GameTime.getInstance().getWorldAgeHours() / int0) * int0;
 if (chunk.lootRespawnHour > int1) {
 chunk.lootRespawnHour = int1;
 }

 if (chunk.lootRespawnHour < int1) {
 chunk.lootRespawnHour = int1;
 respawnInChunk(chunk);
 }
 }
 }
 }
 }

 static int getRespawnInterval() {
 if (GameServer.bServer) {
 return ServerOptions.instance.HoursForLootRespawn.getValue();
 } else {
 if (!GameClient.bClient) {
 int int0 = SandboxOptions.instance.LootRespawn.getValue();
 if (int0 == 1) {
 return 0;
 }

 if (int0 == 2) {
 return 24;
 }

 if (int0 == 3) {
 return 168;
 }

 if (int0 == 4) {
 return 720;
 }

 if (int0 == 5) {
 return 1440;
 }
 }

 return 0;
 }
 }

 static void respawnInChunk(IsoChunk chunk) {
 bool boolean0 = GameServer.bServer && ServerOptions.instance.ConstructionPreventsLootRespawn.getValue();
 int int0 = SandboxOptions.instance.SeenHoursPreventLootRespawn.getValue();
 double double0 = GameTime.getInstance().getWorldAgeHours();

 for (int int1 = 0; int1 < 10; int1++) {
 for (int int2 = 0; int2 < 10; int2++) {
 IsoGridSquare square = chunk.getGridSquare(int2, int1, 0);
 IsoMetaGrid.Zone zone = square.empty() ? nullptr : square.getZone();
 if (zone != nullptr
 && ("TownZone" == zone.getType()) || "TownZones" == zone.getType()) || "TrailerPark" == zone.getType()))
 && (!boolean0 || !zone.haveConstruction)
 && (int0 <= 0 || !(zone.getHoursSinceLastSeen() <= int0) {
 if (square.getBuilding() != nullptr) {
 BuildingDef buildingDef = square.getBuilding().getDef();
 if (buildingDef != nullptr) {
 if (buildingDef.lootRespawnHour > double0) {
 buildingDef.lootRespawnHour = 0;
 }

 if (buildingDef.lootRespawnHour < chunk.lootRespawnHour) {
 buildingDef.setKeySpawned(0);
 buildingDef.lootRespawnHour = chunk.lootRespawnHour;
 }
 }
 }

 for (int int3 = 0; int3 < 8; int3++) {
 square = chunk.getGridSquare(int2, int1, int3);
 if (square != nullptr) {
 int int4 = square.getObjects().size();
 IsoObject[] objects = square.getObjects().getElements();

 for (int int5 = 0; int5 < int4; int5++) {
 IsoObject object = objects[int5];
 if (!(object instanceof IsoDeadBody) && !(object instanceof IsoThumpable) && !(object instanceof IsoCompost) {
 for (int int6 = 0; int6 < object.getContainerCount(); int6++) {
 ItemContainer container = object.getContainerByIndex(int6);
 if (container.bExplored && container.isHasBeenLooted()) {
 respawnInContainer(object, container);
 }
 }
 }
 }
 }
 }
 }
 }
 }
 }

 static void respawnInContainer(IsoObject object, ItemContainer container) {
 if (container != nullptr && container.getItems() != nullptr) {
 int int0 = container.getItems().size();
 int int1 = 5;
 if (GameServer.bServer) {
 int1 = ServerOptions.instance.MaxItemsForLootRespawn.getValue();
 }

 if (int0 < int1) {
 existingItems.clear();
 existingItems.addAll(container.getItems());
 ItemPickerJava.fillContainer(container, nullptr);
 std::vector arrayList = container.getItems();
 if (arrayList != nullptr && int0 != arrayList.size()) {
 container.setHasBeenLooted(false);
 newItems.clear();

 for (int int2 = 0; int2 < arrayList.size(); int2++) {
 InventoryItem item = (InventoryItem)arrayList.get(int2);
 if (!existingItems.contains(item) {
 newItems.add(item);
 item.setAge(0.0F);
 }
 }

 ItemPickerJava.updateOverlaySprite(object);
 if (GameServer.bServer) {
 for (int int3 = 0; int3 < GameServer.udpEngine.connections.size(); int3++) {
 UdpConnection udpConnection = GameServer.udpEngine.connections.get(int3);
 if (udpConnection.RelevantTo(object.square.x, object.square.y) {
 ByteBufferWriter byteBufferWriter = udpConnection.startPacket();
 PacketTypes.PacketType.AddInventoryItemToContainer.doPacket(byteBufferWriter);
 byteBufferWriter.putShort((short)2);
 byteBufferWriter.putInt((int)object.getX());
 byteBufferWriter.putInt((int)object.getY());
 byteBufferWriter.putInt((int)object.getZ());
 byteBufferWriter.putByte((byte)object.getObjectIndex());
 byteBufferWriter.putByte((byte)object.getContainerIndex(container);

 try {
 CompressIdenticalItems.save(byteBufferWriter.bb, newItems, nullptr);
 } catch (Exception exception) {
 exception.printStackTrace();
 }

 PacketTypes.PacketType.AddInventoryItemToContainer.send(udpConnection);
 }
 }
 }
 }
 }
 }
 }
}
} // namespace zombie
