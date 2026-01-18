#pragma once
#include "java/net/InetSocketAddress.h"
#include "java/net/ServerSocket.h"
#include "java/net/Socket.h"
#include "java/net/SocketException.h"
#include "zombie/debug/DebugLog.h"
#include <algorithm>
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
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class RCONServer {
public:
 static const int SERVERDATA_RESPONSE_VALUE = 0;
 static const int SERVERDATA_AUTH_RESPONSE = 2;
 static const int SERVERDATA_EXECCOMMAND = 2;
 static const int SERVERDATA_AUTH = 3;
 static RCONServer instance;
 ServerSocket welcomeSocket;
private
 RCONServer.ServerThread thread;
 std::string password;
private
 ConcurrentLinkedQueue<RCONServer.ExecCommand> toMain =
 std::make_unique<ConcurrentLinkedQueue<>>();

private
 RCONServer(int int0, const std::string &string, bool boolean0) {
 this->password = string;

 try {
 this->welcomeSocket = std::make_unique<ServerSocket>();
 if (boolean0) {
 this->welcomeSocket.bind(new InetSocketAddress("127.0.0.1", int0);
 } else if (GameServer.IPCommandline != nullptr) {
 this->welcomeSocket.bind(
 new InetSocketAddress(GameServer.IPCommandline, int0);
 } else {
 this->welcomeSocket.bind(new InetSocketAddress(int0);
 }

 DebugLog.log("RCON: listening on port " + int0);
 } catch (IOException iOException0) {
 DebugLog.log("RCON: error creating socket on port " + int0);
 iOException0.printStackTrace();

 try {
 this->welcomeSocket.close();
 this->welcomeSocket = nullptr;
 } catch (IOException iOException1) {
 iOException1.printStackTrace();
 }

 return;
 }

 this->thread = new RCONServer.ServerThread();
 this->thread.start();
 }

 void updateMain() {
 for (RCONServer.ExecCommand execCommand = this->toMain.poll();
 execCommand != nullptr; execCommand = this->toMain.poll()) {
 execCommand.update();
 }
 }

 void quit() {
 if (this->welcomeSocket != nullptr) {
 try {
 this->welcomeSocket.close();
 } catch (IOException iOException) {
 }

 this->welcomeSocket = nullptr;
 this->thread.quit();
 this->thread = nullptr;
 }
 }

 static void init(int int0, const std::string &string, bool boolean0) {
 instance = new RCONServer(int0, string, boolean0);
 }

 static void update() {
 if (instance != nullptr) {
 instance.updateMain();
 }
 }

 static void shutdown() {
 if (instance != nullptr) {
 instance.quit();
 }
 }

private
 static class ClientThread extends Thread {
 Socket socket;
 bool bAuth;
 bool bQuit;
 std::string password;
 InputStream in;
 OutputStream out;
 private
 ConcurrentLinkedQueue<RCONServer.ExecCommand> toThread =
 std::make_unique<ConcurrentLinkedQueue<>>();
 int pendingCommands;

 public
 ClientThread(Socket socketx, const std::string &string) {
 this->socket = socketx;
 this->password = string;

 try {
 this->in = socketx.getInputStream();
 this->out = socketx.getOutputStream();
 } catch (IOException iOException) {
 iOException.printStackTrace();
 }

 this->setName("RCONClient" + socketx.getLocalPort());
 }

 void run() {
 if (this->in != nullptr) {
 if (this->out != nullptr) {
 while (!this->bQuit) {
 try {
 this->runInner();
 } catch (SocketException socketException) {
 this->bQuit = true;
 } catch (Exception exception) {
 exception.printStackTrace();
 }
 }

 try {
 this->socket.close();
 } catch (IOException iOException) {
 iOException.printStackTrace();
 }

 DebugLog.log("RCON: connection closed " + this->socket.toString());
 }
 }
 }

 void runInner() {
 byte[] bytes0 = new byte[4];
 int int0 = this->in.read(bytes0, 0, 4);
 if (int0 < 0) {
 this->bQuit = true;
 } else {
 ByteBuffer byteBuffer = ByteBuffer.wrap(bytes0);
 byteBuffer.order(ByteOrder.LITTLE_ENDIAN);
 int int1 = byteBuffer.getInt();
 int int2 = int1;
 byte[] bytes1 = new byte[int1];

 do {
 int0 = this->in.read(bytes1, int1 - int2, int2);
 if (int0 < 0) {
 this->bQuit = true;
 return;
 }

 int2 -= int0;
 } while (int2 > 0);

 byteBuffer = ByteBuffer.wrap(bytes1);
 byteBuffer.order(ByteOrder.LITTLE_ENDIAN);
 int int3 = byteBuffer.getInt();
 int int4 = byteBuffer.getInt();
 std::string string =
 new String(byteBuffer.array(), byteBuffer.position(),
 byteBuffer.limit() - byteBuffer.position() - 2);
 this->handlePacket(int3, int4, string);
 }
 }

 void handlePacket(int int1, int int0, const std::string &string) {
 if (!"players" == string) {
 DebugLog.log("RCON: ID=" + int1 + " Type=" + int0 + " Body='" +
 string + "' " + this->socket.toString());
 }

 switch (int0) {
 case 0:
 if (this->checkAuth()) {
 ByteBuffer byteBuffer0 = ByteBuffer.allocate(14);
 byteBuffer0.order(ByteOrder.LITTLE_ENDIAN);
 byteBuffer0.putInt(byteBuffer0.capacity() - 4);
 byteBuffer0.putInt(int1);
 byteBuffer0.putInt(0);
 byteBuffer0.putShort((short)0);
 this->out.write(byteBuffer0.array());
 this->out.write(byteBuffer0.array());
 }
 break;
 case 1:
 default:
 DebugLog.log("RCON: unknown packet Type=" + int0);
 break;
 case 2:
 if (!this->checkAuth()) {
 break;
 }

 RCONServer.ExecCommand execCommand =
 new RCONServer.ExecCommand(int1, string, this);
 this->pendingCommands++;
 RCONServer.instance.toMain.add(execCommand);

 while (this->pendingCommands > 0) {
 execCommand = this->toThread.poll();
 if (execCommand != nullptr) {
 this->pendingCommands--;
 this->handleResponse(execCommand);
 } else {
 try {
 Thread.sleep(50L);
 } catch (InterruptedException interruptedException) {
 if (this->bQuit) {
 return;
 }
 }
 }
 }
 break;
 case 3:
 this->bAuth = string == this->password);
 if (!this->bAuth) {
 DebugLog.log("RCON: password doesn't match");
 this->bQuit = true;
 }

 ByteBuffer byteBuffer1 = ByteBuffer.allocate(14);
 byteBuffer1.order(ByteOrder.LITTLE_ENDIAN);
 byteBuffer1.putInt(byteBuffer1.capacity() - 4);
 byteBuffer1.putInt(int1);
 byteBuffer1.putInt(0);
 byteBuffer1.putShort((short)0);
 this->out.write(byteBuffer1.array());
 byteBuffer1.clear();
 byteBuffer1.putInt(byteBuffer1.capacity() - 4);
 byteBuffer1.putInt(this->bAuth ? int1 : -1);
 byteBuffer1.putInt(2);
 byteBuffer1.putShort((short)0);
 this->out.write(byteBuffer1.array());
 }
 }

 void handleResponse(RCONServer.ExecCommand execCommand) {
 std::string string = execCommand.response;
 if (string.empty()) {
 string = "";
 }

 ByteBuffer byteBuffer = ByteBuffer.allocate(12 + string.length() + 2);
 byteBuffer.order(ByteOrder.LITTLE_ENDIAN);
 byteBuffer.putInt(byteBuffer.capacity() - 4);
 byteBuffer.putInt(execCommand.ID);
 byteBuffer.putInt(0);
 byteBuffer.put(string.getBytes());
 byteBuffer.putShort((short)0);

 try {
 this->out.write(byteBuffer.array());
 } catch (IOException iOException) {
 iOException.printStackTrace();
 }
 }

 bool checkAuth() {
 if (this->bAuth) {
 return true;
 } else {
 this->bQuit = true;
 ByteBuffer byteBuffer = ByteBuffer.allocate(14);
 byteBuffer.order(ByteOrder.LITTLE_ENDIAN);
 byteBuffer.putInt(byteBuffer.capacity() - 4);
 byteBuffer.putInt(-1);
 byteBuffer.putInt(2);
 byteBuffer.putShort((short)0);
 this->out.write(byteBuffer.array());
 return false;
 }
 }

 void quit() {
 if (this->socket != nullptr) {
 try {
 this->socket.close();
 } catch (IOException iOException) {
 }
 }

 this->bQuit = true;
 this->interrupt();

 while (this->isAlive()) {
 try {
 Thread.sleep(50L);
 } catch (InterruptedException interruptedException) {
 interruptedException.printStackTrace();
 }
 }
 }
 }

 private static class ExecCommand {
 int ID;
 std::string command;
 std::string response;
 public
 RCONServer.ClientThread thread;

 public
 ExecCommand(int int0, const std::string &string,
 RCONServer.ClientThread clientThread) {
 this->ID = int0;
 this->command = string;
 this->thread = clientThread;
 }

 void update() {
 this->response = GameServer.rcon(this->command);
 if (this->thread.isAlive()) {
 this->thread.toThread.add(this);
 }
 }
 }

 class ServerThread extends Thread {
 private
 ArrayList<RCONServer.ClientThread> connections =
 std::make_unique<ArrayList<>>();
 bool bQuit;

 public
 ServerThread() { this->setName("RCONServer"); }

 void run() {
 while (!this->bQuit) {
 this->runInner();
 }
 }

 void runInner() {
 try {
 Socket socket = RCONServer.this->welcomeSocket.accept();

 for (int int0 = 0; int0 < this->connections.size(); int0++) {
 RCONServer.ClientThread clientThread0 = this->connections.get(int0);
 if (!clientThread0.isAlive()) {
 this->connections.remove(int0--);
 }
 }

 if (this->connections.size() >= 5) {
 socket.close();
 return;
 }

 DebugLog.log("RCON: new connection " + socket.toString());
 RCONServer.ClientThread clientThread1 =
 new RCONServer.ClientThread(socket, RCONServer.this->password);
 this->connections.add(clientThread1);
 clientThread1.start();
 } catch (IOException iOException) {
 if (!this->bQuit) {
 iOException.printStackTrace();
 }
 }
 }

 void quit() {
 this->bQuit = true;

 while (this->isAlive()) {
 try {
 Thread.sleep(50L);
 } catch (InterruptedException interruptedException) {
 interruptedException.printStackTrace();
 }
 }

 for (int int0 = 0; int0 < this->connections.size(); int0++) {
 RCONServer.ClientThread clientThread = this->connections.get(int0);
 clientThread.quit();
 }
 }
 }
}
} // namespace network
} // namespace zombie
