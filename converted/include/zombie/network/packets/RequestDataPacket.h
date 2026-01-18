#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/PersistentOutfits.h"
#include "zombie/SharedDescriptors.h"
#include "zombie/ZomboidFileSystem.h"
#include "zombie/core/Translator.h"
#include "zombie/core/logger/ExceptionLogger.h"
#include "zombie/core/network/ByteBufferWriter.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/debug/LogSeverity.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/network/ConnectionDetails.h"
#include "zombie/network/ConnectionManager.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/GameServer.h"
#include "zombie/network/PacketTypes.h"
#include "zombie/network/RequestDataManager.h"
#include "zombie/network/ServerWorldDatabase.h"
#include "zombie/radio/ZomboidRadio.h"
#include "zombie/radio/media/RecordedMedia.h"
#include <filesystem>
#include <fstream>
#include <iostream>

namespace zombie {
namespace network {
namespace packets {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class RequestDataPacket {
public:
 RequestDataPacket.RequestType type;
 RequestDataPacket.RequestID id;
 ByteBuffer buffer = nullptr;
 int dataSize;
 int dataSent;
 int partSize;
 static ByteBuffer large_file_bb = ByteBuffer.allocate(52428800);

 void setRequest() {
 this->type = RequestDataPacket.RequestType.Request;
 this->id = RequestDataPacket.RequestID.Descriptors;
 }

 void setRequest(RequestDataPacket.RequestID requestID) {
 this->type = RequestDataPacket.RequestType.Request;
 this->id = requestID;
 }

 void setPartData(RequestDataPacket.RequestID requestID, ByteBuffer byteBuffer) {
 this->type = RequestDataPacket.RequestType.PartData;
 this->buffer = byteBuffer;
 this->id = requestID;
 this->dataSize = byteBuffer.limit();
 }

 void setPartDataParameters(int int0, int int1) {
 this->dataSent = int0;
 this->partSize = int1;
 }

 void setACK(RequestDataPacket.RequestID requestID) {
 this->type = RequestDataPacket.RequestType.PartDataACK;
 this->id = requestID;
 }

 void sendConnectingDetails(UdpConnection udpConnection, ServerWorldDatabase.LogonResult logonResult) {
 if (GameServer.bServer) {
 this->id = RequestDataPacket.RequestID.ConnectionDetails;
 large_file_bb.clear();
 ConnectionDetails.write(udpConnection, logonResult, large_file_bb);
 this->doSendRequest(udpConnection);
 DebugLog.Multiplayer.debugln("%s %db", this->id.name(), large_file_bb.position());
 ConnectionManager.log("send-packet", "connection-details", udpConnection);
 }
 }

 void parse(ByteBuffer byteBuffer, UdpConnection var2) {
 try {
 this->type = RequestDataPacket.RequestType.values()[byteBuffer.get()];
 } catch (Exception exception) {
 DebugLog.Multiplayer.printException(exception, "RequestData packet parse failed", LogSeverity.Error);
 this->type = RequestDataPacket.RequestType.None;
 }

 this->id = RequestDataPacket.RequestID.values()[byteBuffer.get()];
 if (GameClient.bClient) {
 if (this->type == RequestDataPacket.RequestType.FullData) {
 int int0 = byteBuffer.limit() - byteBuffer.position();
 large_file_bb.clear();
 large_file_bb.limit(int0);
 large_file_bb.put(byteBuffer.array(), byteBuffer.position(), int0);
 this->buffer = large_file_bb;
 } else if (this->type == RequestDataPacket.RequestType.PartData) {
 this->dataSize = byteBuffer.getInt();
 this->dataSent = byteBuffer.getInt();
 this->partSize = byteBuffer.getInt();
 large_file_bb.clear();
 large_file_bb.limit(this->partSize);
 large_file_bb.put(byteBuffer.array(), byteBuffer.position(), this->partSize);
 this->buffer = large_file_bb;
 }
 }
 }

 void write(ByteBufferWriter byteBufferWriter) {
 byteBufferWriter.putByte((byte)this->type.ordinal());
 byteBufferWriter.putByte((byte)this->id.ordinal());
 if (GameServer.bServer) {
 if (this->type == RequestDataPacket.RequestType.FullData) {
 byteBufferWriter.bb.put(this->buffer.array(), 0, this->buffer.position());
 } else if (this->type == RequestDataPacket.RequestType.PartData) {
 byteBufferWriter.putInt(this->dataSize);
 byteBufferWriter.putInt(this->dataSent);
 byteBufferWriter.putInt(this->partSize);
 byteBufferWriter.bb.put(this->buffer.array(), this->dataSent, this->partSize);
 }
 }
 }

 void processServer(PacketTypes.PacketType var1, UdpConnection udpConnection) {
 if (!udpConnection.wasInLoadingQueue && this->id != RequestDataPacket.RequestID.ConnectionDetails) {
 GameServer.kick(udpConnection, "UI_Policy_Kick", "The server received an invalid request");
 }

 if (this->type == RequestDataPacket.RequestType.Request) {
 this->doProcessRequest(udpConnection);
 } else if (this->type == RequestDataPacket.RequestType.PartDataACK) {
 RequestDataManager.getInstance().ACKWasReceived(this->id, udpConnection, this->dataSent);
 }
 }

 void doSendRequest(UdpConnection udpConnection) {
 if (large_file_bb.position() < 1024) {
 this->type = RequestDataPacket.RequestType.FullData;
 this->buffer = large_file_bb;
 ByteBufferWriter byteBufferWriter = udpConnection.startPacket();
 PacketTypes.PacketType.RequestData.doPacket(byteBufferWriter);
 this->write(byteBufferWriter);
 PacketTypes.PacketType.RequestData.send(udpConnection);
 } else {
 RequestDataManager.getInstance().putDataForTransmit(this->id, udpConnection, large_file_bb);
 }
 }

 void doProcessRequest(UdpConnection udpConnection) {
 if (this->id == RequestDataPacket.RequestID.Descriptors) {
 try {
 large_file_bb.clear();
 PersistentOutfits.instance.save(large_file_bb);
 } catch (Exception exception0) {
 exception0.printStackTrace();
 }

 this->doSendRequest(udpConnection);
 }

 if (this->id == RequestDataPacket.RequestID.PlayerZombieDescriptors) {
 SharedDescriptors.Descriptor[] descriptors = SharedDescriptors.getPlayerZombieDescriptors();
 int int0 = 0;

 for (int int1 = 0; int1 < descriptors.length; int1++) {
 if (descriptors[int1] != nullptr) {
 int0++;
 }
 }

 if (int0 * 2 * 1024 > large_file_bb.capacity()) {
 large_file_bb = ByteBuffer.allocate(int0 * 2 * 1024);
 }

 try {
 large_file_bb.clear();
 large_file_bb.putShort((short)int0);

 for (SharedDescriptors.Descriptor descriptor : descriptors) {
 if (descriptor != nullptr) {
 descriptor.save(large_file_bb);
 }
 }

 this->doSendRequest(udpConnection);
 } catch (Exception exception1) {
 exception1.printStackTrace();
 }
 }

 if (this->id == RequestDataPacket.RequestID.MetaGrid) {
 try {
 large_file_bb.clear();
 IsoWorld.instance.MetaGrid.savePart(large_file_bb, 0, true);
 IsoWorld.instance.MetaGrid.savePart(large_file_bb, 1, true);
 this->doSendRequest(udpConnection);
 } catch (Exception exception2) {
 DebugLog.Multiplayer.printException(exception2, "map_meta.bin could not be saved", LogSeverity.Error);
 GameServer.kick(udpConnection, "You have been kicked from this server because map_meta.bin could not be saved.", nullptr);
 udpConnection.forceDisconnect("save-map-meta-bin");
 GameServer.addDisconnect(udpConnection);
 }
 }

 if (this->id == RequestDataPacket.RequestID.MapZone) {
 try {
 large_file_bb.clear();
 IsoWorld.instance.MetaGrid.saveZone(large_file_bb);
 this->doSendRequest(udpConnection);
 } catch (Exception exception3) {
 DebugLog.Multiplayer.printException(exception3, "map_zone.bin could not be saved", LogSeverity.Error);
 GameServer.kick(udpConnection, "You have been kicked from this server because map_zone.bin could not be saved.", nullptr);
 udpConnection.forceDisconnect("save-map-zone-bin");
 GameServer.addDisconnect(udpConnection);
 }
 }

 if (this->id == RequestDataPacket.RequestID.RadioData) {
 large_file_bb.clear();
 ZomboidRadio.getInstance().getRecordedMedia().sendRequestData(large_file_bb);
 this->doSendRequest(udpConnection);
 }

 DebugLog.Multiplayer.debugln("%s %db", this->id.name(), large_file_bb.position());
 }

 void process(UdpConnection var1) {
 if (this->type == RequestDataPacket.RequestType.FullData) {
 large_file_bb.position(0);
 this->doProcessData(large_file_bb);
 } else if (this->type == RequestDataPacket.RequestType.PartData) {
 large_file_bb.position(0);
 this->doProcessPart(large_file_bb);
 }
 }

 void doProcessPart(ByteBuffer byteBuffer1) {
 ByteBuffer byteBuffer0 = RequestDataManager.getInstance().receiveClientData(this->id, byteBuffer1, this->dataSize, this->dataSent);
 if (byteBuffer0 != nullptr) {
 this->doProcessData(byteBuffer0);
 }
 }

 void doProcessData(ByteBuffer byteBuffer) {
 if (this->id == RequestDataPacket.RequestID.ConnectionDetails) {
 ConnectionDetails.parse(byteBuffer);
 }

 if (this->id == RequestDataPacket.RequestID.Descriptors) {
 try {
 DebugLog.Multiplayer.debugln("received zombie descriptors");
 PersistentOutfits.instance.load(byteBuffer);
 } catch (IOException iOException) {
 DebugLog.Multiplayer.printException(iOException, "PersistentOutfits loading IO error", LogSeverity.Error);
 ExceptionLogger.logException(iOException);
 } catch (Exception exception0) {
 DebugLog.Multiplayer.printException(exception0, "PersistentOutfits loading error", LogSeverity.Error);
 }
 }

 if (this->id == RequestDataPacket.RequestID.PlayerZombieDescriptors) {
 try {
 this->receivePlayerZombieDescriptors(byteBuffer);
 } catch (Exception exception1) {
 DebugLog.Multiplayer.printException(exception1, "Player zombie descriptors loading error", LogSeverity.Error);
 ExceptionLogger.logException(exception1);
 }
 }

 if (this->id == RequestDataPacket.RequestID.MetaGrid) {
 this->saveToFile(byteBuffer, "map_meta.bin");
 }

 if (this->id == RequestDataPacket.RequestID.MapZone) {
 this->saveToFile(byteBuffer, "map_zone.bin");
 }

 if (this->id == RequestDataPacket.RequestID.RadioData) {
 try {
 RecordedMedia.receiveRequestData(byteBuffer);
 } catch (Exception exception2) {
 DebugLog.Multiplayer.printException(exception2, "Radio data loading error", LogSeverity.Error);
 ExceptionLogger.logException(exception2);
 }
 }

 this->sendNextRequest(this->id);
 }

 void sendNextRequest(RequestDataPacket.RequestID requestID) {
 switch (requestID) {
 case Descriptors:
 this->setRequest(RequestDataPacket.RequestID.MetaGrid);
 break;
 case MetaGrid:
 this->setRequest(RequestDataPacket.RequestID.MapZone);
 break;
 case MapZone:
 this->setRequest(RequestDataPacket.RequestID.PlayerZombieDescriptors);
 break;
 case PlayerZombieDescriptors:
 this->setRequest(RequestDataPacket.RequestID.RadioData);
 break;
 case RadioData:
 GameClient.instance.setRequest(GameClient.RequestState.Complete);
 }

 if (requestID != RequestDataPacket.RequestID.RadioData) {
 ByteBufferWriter byteBufferWriter = GameClient.connection.startPacket();
 PacketTypes.PacketType.RequestData.doPacket(byteBufferWriter);
 this->write(byteBufferWriter);
 PacketTypes.PacketType.RequestData.send(GameClient.connection);
 }
 }

 void saveToFile(ByteBuffer byteBuffer, const std::string& string) {
 File file = new File(ZomboidFileSystem.instance.getFileNameInCurrentSave(string);

 try (
 FileOutputStream fileOutputStream = new FileOutputStream(file, false);
 BufferedOutputStream bufferedOutputStream = new BufferedOutputStream(fileOutputStream);
 ) {
 bufferedOutputStream.write(byteBuffer.array(), 0, byteBuffer.limit());
 bufferedOutputStream.flush();
 } catch (IOException iOException) {
 DebugLog.Multiplayer.printException(iOException, "Save to the " + string + " file error", LogSeverity.Error);
 }
 }

 void receivePlayerZombieDescriptors(ByteBuffer byteBuffer) {
 short short0 = byteBuffer.getShort();
 DebugLog.Multiplayer.debugln("received " + short0 + " player-zombie descriptors");

 for (short short1 = 0; short1 < short0; short1++) {
 SharedDescriptors.Descriptor descriptor = new SharedDescriptors.Descriptor();
 descriptor.load(byteBuffer, 195);
 SharedDescriptors.registerPlayerZombieDescriptor(descriptor);
 }
 }

 bool isConsistent() {
 return this->type != RequestDataPacket.RequestType.None;
 }

 std::string getDescription() {
 std::string string = "\n\tRequestDataPacket [";
 string = string + "type=" + this->type.name() + " | ";
 if (this->type == RequestDataPacket.RequestType.Request || this->type == RequestDataPacket.RequestType.PartDataACK) {
 string = string + "id=" + this->id.name() + "] ";
 }

 if (this->type == RequestDataPacket.RequestType.FullData) {
 string = string + "id=" + this->id.name() + " | ";
 string = string + "data=(size:" + this->buffer.limit() + ", data=";
 this->buffer.position(0);

 for (int int0 = 0; int0 < Math.min(15, this->buffer.limit()); int0++) {
 string = string + " 0x" + Integer.toHexString(this->buffer.get() & 255);
 }

 string = string + ".. ] ";
 }

 if (this->type == RequestDataPacket.RequestType.PartData) {
 string = string + "id=" + this->id.name() + " | ";
 string = string + "dataSize=" + this->dataSize + " | ";
 string = string + "dataSent=" + this->dataSent + " | ";
 string = string + "partSize=" + this->partSize + " | ";
 string = string + "data=(size:" + this->buffer.limit() + ", data=";
 if (this->buffer.limit() >= this->dataSize) {
 this->buffer.position(this->dataSent);
 } else {
 this->buffer.position(0);
 }

 for (int int1 = 0; int1 < Math.min(15, this->buffer.limit() - this->buffer.position()); int1++) {
 string = string + " " + Integer.toHexString(this->buffer.get() & 255);
 }

 string = string + ".. ] ";
 }

 return string;
 }

 public static enum RequestID {
 ConnectionDetails,
 Descriptors,
 MetaGrid,
 MapZone,
 PlayerZombieDescriptors,
 RadioData;

 std::string getDescriptor() {
 return Translator.getText("IGUI_RequestID_" + this->name());
 }
 }

 static enum RequestType {
 None,
 Request,
 FullData,
 PartData,
 PartDataACK;
 }
}
} // namespace packets
} // namespace network
} // namespace zombie
