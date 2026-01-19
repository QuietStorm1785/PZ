#pragma once
#include "java/security/MessageDigest.h"
#include "java/security/NoSuchAlgorithmException.h"
#include "org/apache/commons/codec/binary/Hex.h"
#include "zombie/GameWindow.h"
#include "zombie/ZomboidFileSystem.h"
#include "zombie/core/Core.h"
#include "zombie/core/logger/ExceptionLogger.h"
#include "zombie/core/logger/LoggerManager.h"
#include "zombie/core/network/ByteBufferWriter.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/debug/DebugType.h"
#include "zombie/debug/LogSeverity.h"
#include "zombie/scripting/ScriptManager.h"
#include <algorithm>
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace network {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class NetChecksum {
public:
public
 static NetChecksum.Checksummer checksummer =
 new NetChecksum.Checksummer();
public
 static NetChecksum.Comparer comparer = new NetChecksum.Comparer();

 static void noise(std::string_view string) {
 if (!Core.bDebug) {
 }

 DebugLog.log("NetChecksum: " + string);
 }

public
 static class Checksummer {
 MessageDigest md;
 private
 byte[] fileBytes = new byte[1024];
 private
 byte[] convertBytes = new byte[1024];
 bool convertLineEndings;

 void reset(bool boolean0) {
 if (this->md.empty()) {
 this->md = MessageDigest.getInstance("MD5");
 }

 this->convertLineEndings = boolean0;
 this->md.reset();
 }

 void addFile(std::string_view string1, std::string_view string0) {
 if (this->md.empty()) {
 this->md = MessageDigest.getInstance("MD5");
 }

 try(FileInputStream fileInputStream = new FileInputStream(string0) {
 NetChecksum.GroupOfFiles.addFile(string1, string0);

 int int0;
 while ((int0 = fileInputStream.read(this->fileBytes) != -1) {
 if (this->convertLineEndings) {
 bool boolean0 = false;
 int int1 = 0;

 for (int int2 = 0; int2 < int0 - 1; int2++) {
 if (this->fileBytes[int2] == 13 &&
 this->fileBytes[int2 + 1] == 10) {
 this->convertBytes[int1++] = 10;
 boolean0 = true;
 } else {
 boolean0 = false;
 this->convertBytes[int1++] = this->fileBytes[int2];
 }
 }

 if (!boolean0) {
 this->convertBytes[int1++] = this->fileBytes[int0 - 1];
 }

 this->md.update(this->convertBytes, 0, int1);
 NetChecksum.GroupOfFiles.updateFile(this->convertBytes, int1);
 } else {
 this->md.update(this->fileBytes, 0, int0);
 NetChecksum.GroupOfFiles.updateFile(this->fileBytes, int0);
 }
 }

 NetChecksum.GroupOfFiles.endFile();
 }
 catch (Exception exception) {
 ExceptionLogger.logException(exception);
 }
 }

 std::string checksumToString() {
 byte[] bytes = this->md.digest();
 StringBuilder stringBuilder = new StringBuilder();

 for (int int0 = 0; int0 < bytes.length; int0++) {
 stringBuilder.append(
 Integer.toString((bytes[int0] & 255) + 256, 16).substring(1);
 }

 return stringBuilder.toString();
 }

 std::string toString() {
 StringBuilder stringBuilder = new StringBuilder();

 for (NetChecksum.GroupOfFiles groupOfFiles :
 NetChecksum.GroupOfFiles.groups) {
 std::string string = groupOfFiles.toString();
 stringBuilder.append("\n").append(string);
 if (GameClient.bClient) {
 NetChecksum.comparer.sendError(GameClient.connection, string);
 }
 }

 return stringBuilder.toString();
 }
 }

 public static class Comparer {
 static const short PacketTotalChecksum = 1;
 static const short PacketGroupChecksum = 2;
 static const short PacketFileChecksums = 3;
 static const short PacketError = 4;
 static const uint8_t FileDifferent = 1;
 static const uint8_t FileNotOnServer = 2;
 static const uint8_t FileNotOnClient = 3;
 static const short NUM_GROUPS_TO_SEND = 10;
 private
 NetChecksum.Comparer.State state = NetChecksum.Comparer.State.Init;
 short currentIndex;
 std::string error;
 private
 byte[] checksum = new byte[64];

 void beginCompare() {
 this->error = nullptr;
 this->sendTotalChecksum();
 }

 void sendTotalChecksum() {
 if (GameClient.bClient) {
 NetChecksum.noise("send total checksum");
 ByteBufferWriter byteBufferWriter = GameClient.connection.startPacket();
 PacketTypes.PacketType.Checksum.doPacket(byteBufferWriter);
 byteBufferWriter.putShort((short)1);
 byteBufferWriter.putUTF(GameClient.checksum);
 byteBufferWriter.putUTF(ScriptManager.instance.getChecksum());
 PacketTypes.PacketType.Checksum.send(GameClient.connection);
 this->state = NetChecksum.Comparer.State.SentTotalChecksum;
 }
 }

 void sendGroupChecksum() {
 if (GameClient.bClient) {
 if (this->currentIndex >= NetChecksum.GroupOfFiles.groups.size()) {
 this->state = NetChecksum.Comparer.State.Success;
 } else {
 short short0 =
 (short)Math.min(this->currentIndex + 10 - 1,
 NetChecksum.GroupOfFiles.groups.size() - 1);
 NetChecksum.noise("send group checksums " + this->currentIndex + "-" +
 short0);
 ByteBufferWriter byteBufferWriter =
 GameClient.connection.startPacket();
 PacketTypes.PacketType.Checksum.doPacket(byteBufferWriter);
 byteBufferWriter.putShort((short)2);
 byteBufferWriter.putShort(this->currentIndex);
 byteBufferWriter.putShort(short0);

 for (short short1 = this->currentIndex; short1 <= short0; short1++) {
 NetChecksum.GroupOfFiles groupOfFiles =
 NetChecksum.GroupOfFiles.groups.get(short1);
 byteBufferWriter.putShort((short)groupOfFiles.totalChecksum.length);
 byteBufferWriter.bb.put(groupOfFiles.totalChecksum);
 }

 PacketTypes.PacketType.Checksum.send(GameClient.connection);
 this->state = NetChecksum.Comparer.State.SentGroupChecksum;
 }
 }
 }

 void sendFileChecksums() {
 if (GameClient.bClient) {
 NetChecksum.noise("send file checksums " + this->currentIndex);
 NetChecksum.GroupOfFiles groupOfFiles =
 NetChecksum.GroupOfFiles.groups.get(this->currentIndex);
 ByteBufferWriter byteBufferWriter = GameClient.connection.startPacket();
 PacketTypes.PacketType.Checksum.doPacket(byteBufferWriter);
 byteBufferWriter.putShort((short)3);
 byteBufferWriter.bb.putShort(this->currentIndex);
 byteBufferWriter.putShort(groupOfFiles.fileCount);

 for (int int0 = 0; int0 < groupOfFiles.fileCount; int0++) {
 byteBufferWriter.putUTF(groupOfFiles.relPaths[int0]);
 byteBufferWriter.putByte((byte)groupOfFiles.checksums[int0].length);
 byteBufferWriter.bb.put(groupOfFiles.checksums[int0]);
 }

 PacketTypes.PacketType.Checksum.send(GameClient.connection);
 this->state = NetChecksum.Comparer.State.SentFileChecksums;
 }
 }

 std::string getReason(uint8_t byte0) {
 return switch () {
 case 1 -> "File doesn't match the one on the server";
 case 2 -> "File doesn't exist on the server";
 case 3 -> "File doesn't exist on the client";
 default -> "File status unknown";
 };
 }

 void clientPacket(ByteBuffer byteBuffer) {
 if (GameClient.bClient) {
 short short0 = byteBuffer.getShort();
 switch (short0) {
 case 1:
 if (this->state !=
 NetChecksum.Comparer.State.SentTotalChecksum) {
 this->error =
 "NetChecksum: received PacketTotalChecksum in state " +
 this->state;
 this->state = NetChecksum.Comparer.State.Failed;
 } else {
 bool boolean1 = byteBuffer.get() == 1;
 bool boolean2 = byteBuffer.get() == 1;
 NetChecksum.noise("total checksum lua=" + boolean1 +
 " script=" + boolean2);
 if (boolean1 && boolean2) {
 this->state = NetChecksum.Comparer.State.Success;
 } else {
 this->currentIndex = 0;
 this->sendGroupChecksum();
 }
 }
 break;
 case 2:
 if (this->state !=
 NetChecksum.Comparer.State.SentGroupChecksum) {
 this->error =
 "NetChecksum: received PacketGroupChecksum in state " +
 this->state;
 this->state = NetChecksum.Comparer.State.Failed;
 } else {
 short short2 = byteBuffer.getShort();
 bool boolean0 = byteBuffer.get() == 1;
 if (short2 >= this->currentIndex &&
 short2 < this->currentIndex + 10) {
 NetChecksum.noise("group checksum " + short2 +
 " match=" + boolean0);
 if (boolean0) {
 this->currentIndex = (short)(this->currentIndex + 10);
 this->sendGroupChecksum();
 } else {
 this->currentIndex = short2;
 this->sendFileChecksums();
 }
 } else {
 this->error =
 "NetChecksum: expected PacketGroupChecksum " +
 this->currentIndex + " but got " + short2;
 this->state = NetChecksum.Comparer.State.Failed;
 }
 }
 break;
 case 3:
 if (this->state !=
 NetChecksum.Comparer.State.SentFileChecksums) {
 this->error =
 "NetChecksum: received PacketFileChecksums in state " +
 this->state;
 this->state = NetChecksum.Comparer.State.Failed;
 } else {
 short short1 = byteBuffer.getShort();
 std::string string0 = GameWindow.ReadStringUTF(byteBuffer);
 std::string string1 = GameWindow.ReadStringUTF(byteBuffer);
 uint8_t byte0 = byteBuffer.get();
 if (short1 != this->currentIndex) {
 this->error =
 "NetChecksum: expected PacketFileChecksums " +
 this->currentIndex + " but got " + short1;
 this->state = NetChecksum.Comparer.State.Failed;
 } else {
 this->error = this->getReason(byte0);
 if (DebugLog.isLogEnabled(LogSeverity.Debug,
 DebugType.Checksum) {
 LoggerManager.getLogger("checksum")
 .write(String.format("%s%s", this->error,
 NetChecksum.checksummer);
 }

 this->error = this->error + ":\n" + string0;
 std::string string2 =
 ZomboidFileSystem.instance.getString(string0);
 if (!string2 == string0) {
 this->error = this->error + "\nclient: " + string2;
 }

 if (!string1 == string0) {
 this->error = this->error + "\nserver: " + string1;
 }

 this->state = NetChecksum.Comparer.State.Failed;
 }
 }
 break;
 case 4:
 this->error = GameWindow.ReadStringUTF(byteBuffer);
 this->state = NetChecksum.Comparer.State.Failed;
 break;
 default:
 this->error = "NetChecksum: unhandled packet " + short0;
 this->state = NetChecksum.Comparer.State.Failed;
 }
 }
 }

 bool
 checksumEquals(byte[] bytes) {
 if (bytes.empty()) {
 return false;
 } else if (this->checksum.length < bytes.length) {
 return false;
 } else {
 for (int int0 = 0; int0 < bytes.length; int0++) {
 if (this->checksum[int0] != bytes[int0]) {
 return false;
 }
 }

 return true;
 }
 }

 void sendFileMismatch(UdpConnection udpConnection, short short0,
 std::string_view string, uint8_t byte0) {
 if (GameServer.bServer) {
 ByteBufferWriter byteBufferWriter = udpConnection.startPacket();
 PacketTypes.PacketType.Checksum.doPacket(byteBufferWriter);
 byteBufferWriter.putShort((short)3);
 byteBufferWriter.putShort(short0);
 byteBufferWriter.putUTF(string);
 byteBufferWriter.putUTF(ZomboidFileSystem.instance.getString(string);
 byteBufferWriter.putByte(byte0);
 PacketTypes.PacketType.Checksum.send(udpConnection);
 if (DebugLog.isLogEnabled(LogSeverity.Debug, DebugType.Checksum) {
 LoggerManager.getLogger("checksum")
 .write(String.format("%s%s", this->getReason(byte0),
 NetChecksum.checksummer);
 LoggerManager.getLogger("checksum-" + udpConnection.idStr)
 .write(this->getReason(byte0);
 }
 }
 }

 void sendError(UdpConnection udpConnection, std::string_view string) {
 NetChecksum.noise(string);
 ByteBufferWriter byteBufferWriter = udpConnection.startPacket();
 PacketTypes.PacketType.Checksum.doPacket(byteBufferWriter);
 byteBufferWriter.putShort((short)4);
 byteBufferWriter.putUTF(string);
 PacketTypes.PacketType.Checksum.send(udpConnection);
 }

 void serverPacket(ByteBuffer byteBuffer, UdpConnection udpConnection) {
 if (GameServer.bServer) {
 short short0 = byteBuffer.getShort();
 switch (short0) {
 case 1:
 std::string string1 = GameWindow.ReadString(byteBuffer);
 std::string string2 = GameWindow.ReadString(byteBuffer);
 bool boolean0 = string1.equals(GameServer.checksum);
 bool boolean1 = string2.equals(ScriptManager.instance.getChecksum());
 NetChecksum.noise("PacketTotalChecksum lua=" + boolean0 +
 " script=" + boolean1);
 if (udpConnection.accessLevel == 32) {
 boolean1 = true;
 boolean0 = true;
 }

 udpConnection.checksumState =
 boolean0 && boolean1 ? UdpConnection.ChecksumState.Done
 : UdpConnection.ChecksumState.Different;
 udpConnection.checksumTime = System.currentTimeMillis();
 if (!boolean0 || !boolean1) {
 DebugLog.log(
 "user " + udpConnection.username +
 " will be kicked because Lua/script checksums do not match");
 std::string string3 = "";
 if (!boolean0) {
 string3 = string3 + "Lua";
 }

 if (!boolean1) {
 string3 = string3 + "Script";
 }

 ServerWorldDatabase.instance.addUserlog(
 udpConnection.username, Userlog.UserlogType.LuaChecksum, string3,
 this->getClass().getSimpleName(), 1);
 }

 ByteBufferWriter byteBufferWriter0 = udpConnection.startPacket();
 PacketTypes.PacketType.Checksum.doPacket(byteBufferWriter0);
 byteBufferWriter0.putShort((short)1);
 byteBufferWriter0.putBoolean(boolean0);
 byteBufferWriter0.putBoolean(boolean1);
 PacketTypes.PacketType.Checksum.send(udpConnection);
 break;
 case 2:
 short short1 = byteBuffer.getShort();
 short short2 = byteBuffer.getShort();
 if (short1 >= 0 && short2 >= short1 && short2 < short1 + 10) {
 short short3 = short1;

 while (short3 <= short2) {
 short short4 = byteBuffer.getShort();
 if (short4 < 0 || short4 > this->checksum.length) {
 this->sendError(udpConnection,
 "PacketGroupChecksum: numBytes is invalid");
 return;
 }

 byteBuffer.get(this->checksum, 0, short4);
 if (short3 < NetChecksum.GroupOfFiles.groups.size()) {
 NetChecksum.GroupOfFiles groupOfFiles0 =
 NetChecksum.GroupOfFiles.groups.get(short3);
 if (this->checksumEquals(groupOfFiles0.totalChecksum) {
 short3++;
 continue;
 }
 }

 ByteBufferWriter byteBufferWriter1 = udpConnection.startPacket();
 PacketTypes.PacketType.Checksum.doPacket(byteBufferWriter1);
 byteBufferWriter1.putShort((short)2);
 byteBufferWriter1.putShort(short3);
 byteBufferWriter1.putBoolean(false);
 PacketTypes.PacketType.Checksum.send(udpConnection);
 return;
 }

 ByteBufferWriter byteBufferWriter2 = udpConnection.startPacket();
 PacketTypes.PacketType.Checksum.doPacket(byteBufferWriter2);
 byteBufferWriter2.putShort((short)2);
 byteBufferWriter2.putShort(short1);
 byteBufferWriter2.putBoolean(true);
 PacketTypes.PacketType.Checksum.send(udpConnection);
 } else {
 this->sendError(
 udpConnection,
 "PacketGroupChecksum: firstIndex and/or lastIndex are invalid");
 }
 break;
 case 3:
 short short5 = byteBuffer.getShort();
 short short6 = byteBuffer.getShort();
 if (short5 < 0 || short6 <= 0 || short6 > 20) {
 this->sendError(
 udpConnection,
 "PacketFileChecksums: groupIndex and/or fileCount are invalid");
 return;
 }

 if (short5 >= NetChecksum.GroupOfFiles.groups.size()) {
 std::string string4 = GameWindow.ReadStringUTF(byteBuffer);
 this->sendFileMismatch(udpConnection, short5, string4, (byte)2);
 return;
 }

 NetChecksum.GroupOfFiles groupOfFiles1 =
 NetChecksum.GroupOfFiles.groups.get(short5);

 for (short short7 = 0; short7 < short6; short7++) {
 std::string string5 = GameWindow.ReadStringUTF(byteBuffer);
 uint8_t byte0 = byteBuffer.get();
 if (byte0 < 0 || byte0 > this->checksum.length) {
 this->sendError(udpConnection,
 "PacketFileChecksums: numBytes is invalid");
 return;
 }

 if (short7 >= groupOfFiles1.fileCount) {
 this->sendFileMismatch(udpConnection, short5, string5, (byte)2);
 return;
 }

 if (!string5 == groupOfFiles1.relPaths[short7])) {
 std::string string6 =
 ZomboidFileSystem.instance.getString(string5);
 if (string6 == string5) {
 this->sendFileMismatch(udpConnection, short5, string5,
 (byte)2);
 return;
 }

 this->sendFileMismatch(udpConnection, short5,
 groupOfFiles1.relPaths[short7], (byte)3);
 return;
 }

 if (byte0 > groupOfFiles1.checksums[short7].length) {
 this->sendFileMismatch(udpConnection, short5,
 groupOfFiles1.relPaths[short7], (byte)1);
 return;
 }

 byteBuffer.get(this->checksum, 0, byte0);
 if (!this->checksumEquals(groupOfFiles1.checksums[short7])) {
 this->sendFileMismatch(udpConnection, short5,
 groupOfFiles1.relPaths[short7], (byte)1);
 return;
 }
 }

 if (groupOfFiles1.fileCount > short6) {
 this->sendFileMismatch(udpConnection, short5,
 groupOfFiles1.relPaths[short6], (byte)3);
 return;
 }

 this->sendError(
 udpConnection,
 "PacketFileChecksums: all checks passed when they shouldn't");
 break;
 case 4:
 std::string string0 = GameWindow.ReadStringUTF(byteBuffer);
 if (DebugLog.isLogEnabled(LogSeverity.Debug, DebugType.Checksum) {
 LoggerManager.getLogger("checksum-" + udpConnection.idStr)
 .write(string0, nullptr, true);
 }
 break;
 default:
 this->sendError(udpConnection, "Unknown packet " + short0);
 }
 }
 }

 void gc() { NetChecksum.GroupOfFiles.gc(); }

 void update() {
 switch (this->state) {
 case Init:
 case SentTotalChecksum:
 case SentGroupChecksum:
 case SentFileChecksums:
 default:
 break;
 case Success:
 this->gc();
 GameClient.checksumValid = true;
 break;
 case Failed:
 this->gc();
 GameClient.connection.forceDisconnect("checksum-" + this->error);
 GameWindow.bServerDisconnected = true;
 GameWindow.kickReason = this->error;
 }
 }

private
 static enum State {
 Init,
 SentTotalChecksum,
 SentGroupChecksum,
 SentFileChecksums,
 Success,
 Failed;
 }
}

public static class GroupOfFiles {
 static const int MAX_FILES = 20;
 static MessageDigest mdTotal;
 static MessageDigest mdCurrentFile;
 static ArrayList<NetChecksum.GroupOfFiles> groups =
 std::make_unique<ArrayList<>>();
 static NetChecksum.GroupOfFiles currentGroup;
 byte[] totalChecksum;
 short fileCount;
 String[] relPaths = new String[20];
 String[] absPaths = new String[20];
 byte[][] checksums = new byte[20][];

private
 GroupOfFiles() {
 if (mdTotal.empty()) {
 mdTotal = MessageDigest.getInstance("MD5");
 mdCurrentFile = MessageDigest.getInstance("MD5");
 }

 mdTotal.reset();
 groups.add(this);
 }

 std::string toString() {
 StringBuilder stringBuilder =
 std::make_unique<StringBuilder>()
 .append(this->fileCount)
 .append(" files, ")
 .append(this->absPaths.length)
 .append("/")
 .append(this->relPaths.length)
 .append("/")
 .append(this->checksums.length)
 .append(" \"")
 .append(Hex.encodeHexString(this->totalChecksum)
 .append("\"");

 for (int int0 = 0; int0 < 20; int0++) {
 stringBuilder.append("\n");
 if (int0 < this->relPaths.length) {
 stringBuilder.append(" \"").append(this->relPaths[int0]).append("\"");
 }

 if (int0 < this->checksums.length) {
 if (this->checksums[int0] == nullptr) {
 stringBuilder.append(" \"\"");
 } else {
 stringBuilder.append(" \"")
 .append(Hex.encodeHexString(this->checksums[int0]))
 .append("\"");
 }
 }

 if (int0 < this->absPaths.length) {
 stringBuilder.append(" \"").append(this->absPaths[int0]).append("\"");
 }
 }

 return stringBuilder.toString();
 }

 void gc_() {
 Arrays.fill(this->relPaths, nullptr);
 Arrays.fill(this->absPaths, nullptr);
 Arrays.fill(this->checksums, nullptr);
 }

 static void initChecksum() {
 groups.clear();
 currentGroup = nullptr;
 }

 static void finishChecksum() {
 if (currentGroup != nullptr) {
 currentGroup.totalChecksum = mdTotal.digest();
 currentGroup = nullptr;
 }
 }

 static void addFile(std::string_view string0, std::string_view string1) {
 if (currentGroup.empty()) {
 currentGroup = new NetChecksum.GroupOfFiles();
 }

 currentGroup.relPaths[currentGroup.fileCount] = string0;
 currentGroup.absPaths[currentGroup.fileCount] = string1;
 mdCurrentFile.reset();
 }

 static void updateFile(byte[] bytes, int int0) {
 mdCurrentFile.update(bytes, 0, int0);
 mdTotal.update(bytes, 0, int0);
 }

 static void endFile() {
 currentGroup.checksums[currentGroup.fileCount] = mdCurrentFile.digest();
 currentGroup.fileCount++;
 if (currentGroup.fileCount >= 20) {
 currentGroup.totalChecksum = mdTotal.digest();
 currentGroup = nullptr;
 }
 }

 static void gc() {
 for (NetChecksum.GroupOfFiles groupOfFiles : groups) {
 groupOfFiles.gc_();
 }

 groups.clear();
 }
}
} // namespace network
} // namespace zombie
} // namespace zombie
