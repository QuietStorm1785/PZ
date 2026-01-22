#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/Translator.h"
#include "zombie/core/network/ByteBufferWriter.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/network/PacketTypes/PacketType.h"

namespace zombie {
namespace chat {


class ChatTab {
public:
    short id;
    std::string titleID;
    std::string translatedTitle;
   private std::unordered_set<int> containedChats;
    bool enabled = false;

    public ChatTab(short var1, const std::string& var2) {
      this.id = var1;
      this.titleID = var2;
      this.translatedTitle = Translator.getText(var2);
      this.containedChats = std::make_unique<std::unordered_set<>>();
   }

    public ChatTab(short var1, const std::string& var2, int var3) {
      this(var1, var2);
      this.containedChats.push_back(var3);
   }

    void RemoveChat(int var1) {
      if (!this.containedChats.contains(var1)) {
         throw RuntimeException("Tab '" + this.id + "' doesn't contains a chat id: " + var1);
      } else {
         this.containedChats.remove(var1);
      }
   }

    std::string getTitleID() {
      return this.titleID;
   }

    std::string getTitle() {
      return this.translatedTitle;
   }

    short getID() {
      return this.id;
   }

    bool isEnabled() {
      return this.enabled;
   }

    void setEnabled(bool var1) {
      this.enabled = var1;
   }

    void sendAddTabPacket(UdpConnection var1) {
    ByteBufferWriter var2 = var1.startPacket();
      PacketType.AddChatTab.doPacket(var2);
      var2.putShort(this.getID());
      PacketType.AddChatTab.send(var1);
   }

    void sendRemoveTabPacket(UdpConnection var1) {
    ByteBufferWriter var2 = var1.startPacket();
      PacketType.RemoveChatTab.doPacket(var2);
      var2.putShort(this.getID());
      PacketType.RemoveChatTab.send(var1);
   }
}
} // namespace chat
} // namespace zombie
