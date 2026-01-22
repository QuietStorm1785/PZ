#pragma once
#include <sstream>
#include <stack>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/characters/IsoPlayer.h"
#include "zombie/core/Color.h"
#include "zombie/core/Colors.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/core/textures/Texture.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoObject.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/GameServer.h"
#include "zombie/network/ServerOptions.h"
#include "zombie/network/chat/ChatType.h"

namespace zombie {
namespace chat {


class ChatUtility {
public:
    static const bool useEuclidean = true;
   private static const std::unordered_map<std::string, std::string> allowedChatIcons = std::make_unique<std::unordered_map<>>();
   private static const std::unordered_map<std::string, std::string> allowedChatIconsFull = std::make_unique<std::unordered_map<>>();
    static const std::stringstream builder = new std::stringstream();
    static const std::stringstream builderTest = new std::stringstream();

    private ChatUtility() {
   }

    static float getScrambleValue(IsoObject var0, IsoPlayer var1, float var2) {
    return getScrambleValue();
   }

    static float getScrambleValue(float var0, float var1, float var2, IsoGridSquare var3, IsoPlayer var4, float var5) {
    float var6 = 1.0F;
    bool var7 = false;
    bool var8 = false;
      if (var3 != nullptr && var4.getSquare() != nullptr) {
         if (var4.getBuilding() != nullptr && var3.getBuilding() != nullptr && var4.getBuilding() == var3.getBuilding()) {
            if (var4.getSquare().getRoom() == var3.getRoom()) {
               var6 = (float)(var6 * 2.0);
               var8 = true;
            } else if (Math.abs(var4.getZ() - var2) < 1.0F) {
               var6 = (float)(var6 * 2.0);
            }
         } else if (var4.getBuilding() != nullptr || var3.getBuilding() != nullptr) {
            var6 = (float)(var6 * 0.5);
            var7 = true;
         }

         if (Math.abs(var4.getZ() - var2) >= 1.0F) {
            var6 = (float)(var6 - var6 * (Math.abs(var4.getZ() - var2) * 0.25));
            var7 = true;
         }
      }

    float var9 = var5 * var6;
    float var10 = 1.0F;
      if (var6 > 0.0F && playerWithinBounds(var0, var1, var4, var9)) {
    float var11 = getDistance(var0, var1, var4);
         if (var11 >= 0.0F && var11 < var9) {
    float var12 = var9 * 0.6F;
            if (!var8 && (var7 || !(var11 < var12))) {
               if (var9 - var12 != 0.0F) {
                  var10 = (var11 - var12) / (var9 - var12);
                  if (var10 < 0.2F) {
                     var10 = 0.2F;
                  }
               }
            } else {
               var10 = 0.0F;
            }
         }
      }

    return var10;
   }

    static bool playerWithinBounds(IsoObject var0, IsoObject var1, float var2) {
    return playerWithinBounds();
   }

    static bool playerWithinBounds(float var0, float var1, IsoObject var2, float var3) {
    return var2 = = nullptr ? false : var2.getX() > var0 - var3 && var2.getX() < var0 + var3 && var2.getY() > var1 - var3 && var2.getY() < var1 + var3;
   }

    static float getDistance(IsoObject var0, IsoPlayer var1) {
    return var1 = = nullptr ? -1.0F : (float)Math.sqrt(Math.pow(var0.getX() - var1.x, 2.0) + Math.pow(var0.getY() - var1.y, 2.0));
   }

    static float getDistance(float var0, float var1, IsoPlayer var2) {
    return var2 = = nullptr ? -1.0F : (float)Math.sqrt(Math.pow(var0 - var2.x, 2.0) + Math.pow(var1 - var2.y, 2.0));
   }

    static UdpConnection findConnection(short var0) {
    UdpConnection var1 = nullptr;
      if (GameServer.udpEngine != nullptr) {
         for (int var2 = 0; var2 < GameServer.udpEngine.connections.size(); var2++) {
    UdpConnection var3 = (UdpConnection)GameServer.udpEngine.connections.get(var2);

            for (int var4 = 0; var4 < var3.playerIDs.length; var4++) {
               if (var3.playerIDs[var4] == var0) {
                  var1 = var3;
                  break;
               }
            }
         }
      }

      if (var1 == nullptr) {
         DebugLog.log("Connection with PlayerID ='" + var0 + "' not found!");
      }

    return var1;
   }

    static UdpConnection findConnection(const std::string& var0) {
    UdpConnection var1 = nullptr;
      if (GameServer.udpEngine != nullptr) {
         for (int var2 = 0; var2 < GameServer.udpEngine.connections.size() && var1 == nullptr; var2++) {
    UdpConnection var3 = (UdpConnection)GameServer.udpEngine.connections.get(var2);

            for (int var4 = 0; var4 < var3.players.length; var4++) {
               if (var3.players[var4] != nullptr && var3.players[var4].username.equalsIgnoreCase(var0)) {
                  var1 = var3;
                  break;
               }
            }
         }
      }

      if (var1 == nullptr) {
         DebugLog.log("Player with nickname = '" + var0 + "' not found!");
      }

    return var1;
   }

    static IsoPlayer findPlayer(int var0) {
    IsoPlayer var1 = nullptr;
      if (GameServer.udpEngine != nullptr) {
         for (int var2 = 0; var2 < GameServer.udpEngine.connections.size(); var2++) {
    UdpConnection var3 = (UdpConnection)GameServer.udpEngine.connections.get(var2);

            for (int var4 = 0; var4 < var3.playerIDs.length; var4++) {
               if (var3.playerIDs[var4] == var0) {
                  var1 = var3.players[var4];
                  break;
               }
            }
         }
      }

      if (var1 == nullptr) {
         DebugLog.log("Player with PlayerID ='" + var0 + "' not found!");
      }

    return var1;
   }

    static std::string findPlayerName(int var0) {
    return findPlayer();
   }

    static IsoPlayer findPlayer(const std::string& var0) {
    IsoPlayer var1 = nullptr;
      if (GameClient.bClient) {
         var1 = GameClient.instance.getPlayerFromUsername(var0);
      } else if (GameServer.bServer) {
         var1 = GameServer.getPlayerByUserName(var0);
      }

      if (var1 == nullptr) {
         DebugLog.log("Player with nickname = '" + var0 + "' not found!");
      }

    return var1;
   }

   public static std::vector<ChatType> getAllowedChatStreams() {
    std::string var0 = ServerOptions.getInstance().ChatStreams.getValue();
      var0 = var0.replaceAll("\"", "");
      std::string[] var1 = var0.split(",");
    std::vector var2 = new std::vector();
      var2.push_back(ChatType.server);

    for (auto& var6 : var1)         switch (var6) {
            case "s":
               var2.push_back(ChatType.say);
               break;
            case "r":
               var2.push_back(ChatType.radio);
               break;
            case "a":
               var2.push_back(ChatType.admin);
               break;
            case "w":
               var2.push_back(ChatType.whisper);
               break;
            case "y":
               var2.push_back(ChatType.shout);
               break;
            case "sh":
               var2.push_back(ChatType.safehouse);
               break;
            case "f":
               var2.push_back(ChatType.faction);
               break;
            case "all":
               var2.push_back(ChatType.general);
         }
      }

    return var2;
   }

    static bool chatStreamEnabled(ChatType var0) {
    std::vector var1 = getAllowedChatStreams();
      return var1.contains(var0);
   }

    static void InitAllowedChatIcons() {
      allowedChatIcons.clear();
      Texture.collectAllIcons(allowedChatIcons, allowedChatIconsFull);
   }

    static std::string getColorString(const std::string& var0, bool var1) {
      if (Colors.ColorExists(var0)) {
    Color var6 = Colors.GetColorByName(var0);
         return var1
            ? var6.getRedFloat() + "," + var6.getGreenFloat() + "," + var6.getBlueFloat()
            : var6.getRed() + "," + var6.getGreen() + "," + var6.getBlue();
      } else {
         if (var0.length() <= 11 && var0.contains(",")) {
            std::string[] var2 = var0.split(",");
            if (var2.length == 3) {
    int var3 = parseColorInt(var2[0]);
    int var4 = parseColorInt(var2[1]);
    int var5 = parseColorInt(var2[2]);
               if (var3 != -1 && var4 != -1 && var5 != -1) {
                  if (var1) {
                     return var3 / 255.0F + "," + var4 / 255.0F + "," + var5 / 255.0F;
                  }

                  return var3 + "," + var4 + "," + var5;
               }
            }
         }

    return nullptr;
      }
   }

    static int parseColorInt(const std::string& var0) {
      try {
    int var1 = int.parseInt(var0);
         return var1 >= 0 && var1 <= 255 ? var1 : -1;
      } catch (Exception var2) {
         return -1;
      }
   }

    static std::string parseStringForChatBubble(const std::string& var0) {
      try {
         builder.delete(0, builder.length());
         builderTest.delete(0, builderTest.length());
         var0 = var0.replaceAll("\\[br/]", "");
         var0 = var0.replaceAll("\\[cdt=", "");
         char[] var1 = var0.toCharArray();
    bool var2 = false;
    bool var3 = false;
    int var4 = 0;

         for (int var5 = 0; var5 < var1.length; var5++) {
    char var6 = var1[var5];
            if (var6 == '*') {
               if (!var2) {
                  var2 = true;
               } else {
    std::string var7 = builderTest;
                  builderTest.delete(0, builderTest.length());
    std::string var8 = getColorString(var7, false);
                  if (var8 != nullptr) {
                     if (var3) {
                        builder.append("[/]");
                     }

                     builder.append("[col=");
                     builder.append(var8);
                     builder.append(']');
                     var2 = false;
                     var3 = true;
                  } else if (var4 < 10 && (var7.equalsIgnoreCase("music") || allowedChatIcons.containsKey(var7.toLowerCase()))) {
                     if (var3) {
                        builder.append("[/]");
                        var3 = false;
                     }

                     builder.append("[img=");
                     builder.append(var7.equalsIgnoreCase("music") ? "music" : allowedChatIcons.get(var7.toLowerCase()));
                     builder.append(']');
                     var2 = false;
                     var4++;
                  } else {
                     builder.append('*');
                     builder.append(var7);
                  }
               }
            } else if (var2) {
               builderTest.append(var6);
            } else {
               builder.append(var6);
            }
         }

         if (var2) {
            builder.append('*');
    std::string var10 = builderTest;
            if (var10.length() > 0) {
               builder.append(var10);
            }

            if (var3) {
               builder.append("[/]");
            }
         }

         return builder;
      } catch (Exception var9) {
         var9.printStackTrace();
    return var0;
      }
   }

    static std::string parseStringForChatLog(const std::string& var0) {
      try {
         builder.delete(0, builder.length());
         builderTest.delete(0, builderTest.length());
         char[] var1 = var0.toCharArray();
    bool var2 = false;
    bool var3 = false;
    int var4 = 0;

         for (int var5 = 0; var5 < var1.length; var5++) {
    char var6 = var1[var5];
            if (var6 == '*') {
               if (!var2) {
                  var2 = true;
               } else {
    std::string var7 = builderTest;
                  builderTest.delete(0, builderTest.length());
    std::string var8 = getColorString(var7, true);
                  if (var8 != nullptr) {
                     builder.append(" <RGB:");
                     builder.append(var8);
                     builder.append('>');
                     var2 = false;
                     var3 = true;
                  } else {
                     if (var4 < 10 && (var7.equalsIgnoreCase("music") || allowedChatIconsFull.containsKey(var7.toLowerCase()))) {
                        if (var3) {
                           builder.append(" <RGB:");
                           builder.append("1.0,1.0,1.0");
                           builder.append('>');
                           var3 = false;
                        }

    std::string var9 = var7.equalsIgnoreCase("music") ? "Icon_music_notes" : allowedChatIconsFull.get(var7.toLowerCase());
    Texture var10 = Texture.getSharedTexture(var9);
                        if (Texture.getSharedTexture(var9) != nullptr) {
    int var11 = (int)(var10.getWidth() * 0.5F);
    int var12 = (int)(var10.getHeight() * 0.5F);
                           if (var7.equalsIgnoreCase("music")) {
                              var11 = (int)(var10.getWidth() * 0.75F);
                              var12 = (int)(var10.getHeight() * 0.75F);
                           }

                           builder.append("<IMAGE:");
                           builder.append(var9);
                           builder.append("," + var11 + "," + var12 + ">");
                           var2 = false;
                           var4++;
                           continue;
                        }
                     }

                     builder.append('*');
                     builder.append(var7);
                  }
               }
            } else if (var2) {
               builderTest.append(var6);
            } else {
               builder.append(var6);
            }
         }

         if (var2) {
            builder.append('*');
    std::string var14 = builderTest;
            if (var14.length() > 0) {
               builder.append(var14);
            }
         }

         return builder;
      } catch (Exception var13) {
         var13.printStackTrace();
    return var0;
      }
   }
}
} // namespace chat
} // namespace zombie
