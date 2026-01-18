#pragma once
#include "zombie/core/network/ByteBufferWriter.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/debug/LogSeverity.h"
#include "zombie/inventory/InventoryItem.h"
#include "zombie/inventory/InventoryItemFactory.h"
#include "zombie/network/packets/INetworkPacket.h"
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace network {
namespace packets {
namespace hit {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class PlayerItem : public Instance {
public:
 int itemId;
 InventoryItem item;

 void set(InventoryItem itemx) {
 super.set(itemx.getRegistry_id());
 this->item = itemx;
 this->itemId = this->item.getID();
 }

 void parse(ByteBuffer byteBuffer, UdpConnection var2) {
 bool boolean0 = byteBuffer.get() == 1;
 if (boolean0) {
 this->ID = byteBuffer.getShort();
 byteBuffer.get();

 try {
 this->item = InventoryItemFactory.CreateItem(this->ID);
 if (this->item != nullptr) {
 this->item.load(byteBuffer, 195);
 }
 } catch (BufferUnderflowException | IOException iOException) {
 DebugLog.Multiplayer.printException(iOException, "Item load error",
 LogSeverity.Error);
 this->item = nullptr;
 }
 } else {
 this->item = nullptr;
 }
 }

 void write(ByteBufferWriter byteBufferWriter) {
 if (this->item.empty()) {
 byteBufferWriter.putByte((byte)0);
 } else {
 byteBufferWriter.putByte((byte)1);

 try {
 this->item.save(byteBufferWriter.bb, false);
 } catch (IOException iOException) {
 DebugLog.Multiplayer.printException(iOException, "Item write error",
 LogSeverity.Error);
 }
 }
 }

 bool isConsistent() { return super.isConsistent() && this->item != nullptr; }

 std::string getDescription() {
 return super.getDescription() + "\n\tItem [ Item=" +
 (this->item.empty() ? "?"
 : "\"" + this->item.getDisplayName() + "\"") +
 " ]";
 }

 InventoryItem getItem() { return this->item; }
}
} // namespace hit
} // namespace packets
} // namespace network
} // namespace zombie
