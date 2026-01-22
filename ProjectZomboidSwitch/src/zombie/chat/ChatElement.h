#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/GameTime.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/characters/Talker.h"
#include "zombie/chat/ChatElement/PlayerLines.h"
#include "zombie/chat/ChatElement/PlayerLinesList.h"
#include "zombie/iso/objects/IsoRadio.h"
#include "zombie/iso/objects/IsoTelevision.h"
#include "zombie/network/GameServer.h"
#include "zombie/radio/ZomboidRadio.h"
#include "zombie/ui/TextDrawObject.h"
#include "zombie/ui/UIFont.h"
#include "zombie/vehicles/VehiclePart.h"

namespace zombie {
namespace chat {


class ChatElement {
public:
   protected PlayerLines[] playerLines = new PlayerLines[4];
    ChatElementOwner owner;
    float historyVal = 1.0F;
    bool historyInRange = false;
    float historyRange = 15.0F;
    bool useEuclidean = true;
    bool hasChatToDisplay = false;
    int maxChatLines = -1;
    int maxCharsPerLine = -1;
    std::string sayLine = nullptr;
    std::string sayLineTag = nullptr;
    TextDrawObject sayLineObject = nullptr;
    bool Speaking = false;
    std::string talkerType = "unknown";
    static bool doBackDrop = true;
    static NineGridTexture backdropTexture;
    int bufferX = 0;
    int bufferY = 0;
   private static PlayerLinesList[] renderBatch = new PlayerLinesList[4];
   private static std::unordered_set<std::string> noLogText = std::make_unique<std::unordered_set<>>();

    public ChatElement(ChatElementOwner var1, int var2, const std::string& var3) {
      this.owner = var1;
      this.setMaxChatLines(var2);
      this.setMaxCharsPerLine(75);
      this.talkerType = var3 != nullptr ? var3 : this.talkerType;
      if (backdropTexture == nullptr) {
         backdropTexture = std::make_shared<NineGridTexture>("NineGridBlack", 5);
      }
   }

    void setMaxChatLines(int var1) {
      var1 = var1 < 1 ? 1 : (var1 > 10 ? 10 : var1);
      if (var1 != this.maxChatLines) {
         this.maxChatLines = var1;

         for (int var2 = 0; var2 < this.playerLines.length; var2++) {
            this.playerLines[var2] = std::make_shared<PlayerLines>(this, this.maxChatLines);
         }
      }
   }

    int getMaxChatLines() {
      return this.maxChatLines;
   }

    void setMaxCharsPerLine(int var1) {
      for (int var2 = 0; var2 < this.playerLines.length; var2++) {
         this.playerLines[var2].setMaxCharsPerLine(var1);
      }

      this.maxCharsPerLine = var1;
   }

    bool IsSpeaking() {
      return this.Speaking;
   }

    std::string getTalkerType() {
      return this.talkerType;
   }

    void setTalkerType(const std::string& var1) {
      this.talkerType = var1 == nullptr ? "" : var1;
   }

    std::string getSayLine() {
      return this.sayLine;
   }

    std::string getSayLineTag() {
      return this.Speaking && this.sayLineTag != nullptr ? this.sayLineTag : "";
   }

    void setHistoryRange(float var1) {
      this.historyRange = var1;
   }

    void setUseEuclidean(bool var1) {
      this.useEuclidean = var1;
   }

    bool getHasChatToDisplay() {
      return this.hasChatToDisplay;
   }

    float getDistance(IsoPlayer var1) {
      if (var1 == nullptr) {
         return -1.0F;
      } else {
         return this.useEuclidean
            ? (float)Math.sqrt(Math.pow(this.owner.getX() - var1.x, 2.0) + Math.pow(this.owner.getY() - var1.y, 2.0))
            : Math.abs(this.owner.getX() - var1.x) + Math.abs(this.owner.getY() - var1.y);
      }
   }

    bool playerWithinBounds(IsoPlayer var1, float var2) {
      return var1 == nullptr
         ? false
         : var1.getX() > this.owner.getX() - var2
            && var1.getX() < this.owner.getX() + var2
            && var1.getY() > this.owner.getY() - var2
            && var1.getY() < this.owner.getY() + var2;
   }

    void SayDebug(int var1, const std::string& var2) {
      if (!GameServer.bServer && var1 >= 0 && var1 < this.maxChatLines) {
         for (int var3 = 0; var3 < IsoPlayer.numPlayers; var3++) {
    IsoPlayer var4 = IsoPlayer.players[var3];
            if (var4 != nullptr) {
    PlayerLines var5 = this.playerLines[var3];
               if (var1 < var5.chatLines.length) {
                  if (var5.chatLines[var1].getOriginal() != nullptr && var5.chatLines[var1].getOriginal() == var2)) {
                     var5.chatLines[var1].setInternalTickClock(var5.lineDisplayTime);
                  } else {
                     var5.chatLines[var1].setSettings(true, true, true, true, true, true);
                     var5.chatLines[var1].setInternalTickClock(var5.lineDisplayTime);
                     var5.chatLines[var1].setCustomTag("default");
                     var5.chatLines[var1].setDefaultColors(1.0F, 1.0F, 1.0F, 1.0F);
                     var5.chatLines[var1].ReadString(UIFont.Medium, var2, this.maxCharsPerLine);
                  }
               }
            }
         }

         this.sayLine = var2;
         this.sayLineTag = "default";
         this.hasChatToDisplay = true;
      }
   }

    void Say(const std::string& var1) {
      this.addChatLine(var1, 1.0F, 1.0F, 1.0F, UIFont.Dialogue, 25.0F, "default", false, false, false, false, false, true);
   }

    void addChatLine(const std::string& var1, float var2, float var3, float var4, float var5) {
      this.addChatLine(var1, var2, var3, var4, UIFont.Dialogue, var5, "default", false, false, false, false, false, true);
   }

    void addChatLine(const std::string& var1, float var2, float var3, float var4) {
      this.addChatLine(var1, var2, var3, var4, UIFont.Dialogue, 25.0F, "default", false, false, false, false, false, true);
   }

   public void addChatLine(
      std::string var1,
      float var2,
      float var3,
      float var4,
      UIFont var5,
      float var6,
      std::string var7,
      boolean var8,
      boolean var9,
      boolean var10,
      boolean var11,
      boolean var12,
      boolean var13
   ) {
      if (!GameServer.bServer) {
         for (int var14 = 0; var14 < IsoPlayer.numPlayers; var14++) {
    IsoPlayer var15 = IsoPlayer.players[var14];
            if (var15 != nullptr
               && (
                  !var15.Traits.Deaf.isSet()
                     || (
                        this.dynamic_cast<IsoTelevision*>(owner) != nullptr
                           ? ((IsoTelevision)this.owner).isFacing(var15)
                           : !(this.dynamic_cast<IsoRadio*>(owner) != nullptr) && !(this.dynamic_cast<VehiclePart*>(owner) != nullptr)
                     )
               )) {
    float var16 = this.getScrambleValue(var15, var6);
               if (var16 < 1.0F) {
    PlayerLines var17 = this.playerLines[var14];
    TextDrawObject var18 = var17.getNewLineObject();
                  if (var18 != nullptr) {
                     var18.setSettings(var8, var9, var10, var11, var12, var13);
                     var18.setInternalTickClock(var17.lineDisplayTime);
                     var18.setCustomTag(var7);
    std::string var19;
                     if (var16 > 0.0F) {
                        var19 = ZomboidRadio.getInstance().scrambleString(var1, (int)(100.0F * var16), true, "...");
                        var18.setDefaultColors(0.5F, 0.5F, 0.5F, 1.0F);
                     } else {
                        var19 = var1;
                        var18.setDefaultColors(var2, var3, var4, 1.0F);
                     }

                     var18.ReadString(var5, var19, this.maxCharsPerLine);
                     this.sayLine = var1;
                     this.sayLineTag = var7;
                     this.hasChatToDisplay = true;
                  }
               }
            }
         }
      }
   }

    float getScrambleValue(IsoPlayer var1, float var2) {
      if (this.owner == var1) {
         return 0.0F;
      } else {
    float var3 = 1.0F;
    bool var4 = false;
    bool var5 = false;
         if (this.owner.getSquare() != nullptr && var1.getSquare() != nullptr) {
            if (var1.getBuilding() != nullptr && this.owner.getSquare().getBuilding() != nullptr && var1.getBuilding() == this.owner.getSquare().getBuilding()) {
               if (var1.getSquare().getRoom() == this.owner.getSquare().getRoom()) {
                  var3 = (float)(var3 * 2.0);
                  var5 = true;
               } else if (Math.abs(var1.getZ() - this.owner.getZ()) < 1.0F) {
                  var3 = (float)(var3 * 2.0);
               }
            } else if (var1.getBuilding() != nullptr || this.owner.getSquare().getBuilding() != nullptr) {
               var3 = (float)(var3 * 0.5);
               var4 = true;
            }

            if (Math.abs(var1.getZ() - this.owner.getZ()) >= 1.0F) {
               var3 = (float)(var3 - var3 * (Math.abs(var1.getZ() - this.owner.getZ()) * 0.25));
               var4 = true;
            }
         }

    float var6 = var2 * var3;
    float var7 = 1.0F;
         if (var3 > 0.0F && this.playerWithinBounds(var1, var6)) {
    float var8 = this.getDistance(var1);
            if (var8 >= 0.0F && var8 < var6) {
    float var9 = var6 * 0.6F;
               if (!var5 && (var4 || !(var8 < var9))) {
                  if (var6 - var9 != 0.0F) {
                     var7 = (var8 - var9) / (var6 - var9);
                     if (var7 < 0.2F) {
                        var7 = 0.2F;
                     }
                  }
               } else {
                  var7 = 0.0F;
               }
            }
         }

    return var7;
      }
   }

    void updateChatLines() {
      this.Speaking = false;
    bool var1 = false;
      if (this.hasChatToDisplay) {
         this.hasChatToDisplay = false;

         for (int var2 = 0; var2 < IsoPlayer.numPlayers; var2++) {
    float var3 = 1.25F * GameTime.getInstance().getMultiplier();
    int var6 = this.playerLines[var2].lineDisplayTime;

            for (TextDrawObject var10 : this.playerLines[var2].chatLines) {
    float var4 = var10.updateInternalTickClock(var3);
               if (!(var4 <= 0.0F)) {
                  this.hasChatToDisplay = true;
                  if (!var1 && !var10.getCustomTag() == "radio")) {
    float var5 = var4 / (var6 / 2.0F);
                     if (var5 >= 1.0F) {
                        this.Speaking = true;
                     }

                     var1 = true;
                  }

                  var3 *= 1.2F;
               }
            }
         }
      }

      if (!this.Speaking) {
         this.sayLine = nullptr;
         this.sayLineTag = nullptr;
      }
   }

    void updateHistory() {
      if (this.hasChatToDisplay) {
         this.historyInRange = false;
    IsoPlayer var1 = IsoPlayer.getInstance();
         if (var1 != nullptr) {
            if (var1 == this.owner) {
               this.historyVal = 1.0F;
            } else {
               if (this.playerWithinBounds(var1, this.historyRange)) {
                  this.historyInRange = true;
               } else {
                  this.historyInRange = false;
               }

               if (this.historyInRange && this.historyVal != 1.0F) {
                  this.historyVal += 0.04F;
                  if (this.historyVal > 1.0F) {
                     this.historyVal = 1.0F;
                  }
               }

               if (!this.historyInRange && this.historyVal != 0.0F) {
                  this.historyVal -= 0.04F;
                  if (this.historyVal < 0.0F) {
                     this.historyVal = 0.0F;
                  }
               }
            }
         }
      } else if (this.historyVal != 0.0F) {
         this.historyVal = 0.0F;
      }
   }

    void update() {
      if (!GameServer.bServer) {
         this.updateChatLines();
         this.updateHistory();
      }
   }

    void renderBatched(int var1, int var2, int var3) {
      this.renderBatched(var1, var2, var3, false);
   }

    void renderBatched(int var1, int var2, int var3, bool var4) {
      if (var1 < this.playerLines.length && this.hasChatToDisplay && !GameServer.bServer) {
         this.playerLines[var1].renderX = var2;
         this.playerLines[var1].renderY = var3;
         this.playerLines[var1].ignoreRadioLines = var4;
         if (renderBatch[var1] == nullptr) {
            renderBatch[var1] = std::make_shared<PlayerLinesList>(this);
         }

         renderBatch[var1].push_back(this.playerLines[var1]);
      }
   }

    void clear(int var1) {
      this.playerLines[var1].clear();
   }

    static void RenderBatch(int var0) {
      if (renderBatch[var0] != nullptr && renderBatch[var0].size() > 0) {
         for (int var1 = 0; var1 < renderBatch[var0].size(); var1++) {
    PlayerLines var2 = (PlayerLines)renderBatch[var0].get(var1);
            var2.render();
         }

         renderBatch[var0].clear();
      }
   }

    static void NoRender(int var0) {
      if (renderBatch[var0] != nullptr) {
         renderBatch[var0].clear();
      }
   }

    static void addNoLogText(const std::string& var0) {
      if (var0 != nullptr && !var0.empty()) {
         noLogText.push_back(var0);
      }
   }
}
} // namespace chat
} // namespace zombie
