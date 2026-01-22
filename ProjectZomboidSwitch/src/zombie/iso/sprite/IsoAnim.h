#pragma once
#include <sstream>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/textures/Texture.h"
#include "zombie/iso/sprite/IsoAnim/1.h"
#include "zombie/network/GameServer.h"
#include "zombie/network/ServerGUI.h"

namespace zombie {
namespace iso {
namespace sprite {


class IsoAnim {
public:
   public static const std::unordered_map<std::string, IsoAnim> GlobalAnimMap = std::make_unique<std::unordered_map<>>();
    short FinishUnloopedOnFrame = 0;
    short FrameDelay = 0;
    short LastFrame = 0;
   public const std::vector<IsoDirectionFrame> Frames = new std::vector<>(8);
    std::string name;
    bool looped = true;
    int ID = 0;
   private static const ThreadLocal<std::stringstream> tlsStrBuf = std::make_unique<1>();
   public IsoDirectionFrame[] FramesArray = new IsoDirectionFrame[0];

    static void DisposeAll() {
      GlobalAnimMap.clear();
   }

    void LoadExtraFrame(const std::string& var1, const std::string& var2, int var3) {
      this.name = var2;
    std::string var4 = var1 + "_";
    std::string var5 = "_" + var2 + "_";
    int var6 = std::make_shared<int>(var3);
      IsoDirectionFrame var7 = std::make_shared<IsoDirectionFrame>(
         Texture.getSharedTexture(var4 + "8" + var5 + var6 + ".png"),
         Texture.getSharedTexture(var4 + "9" + var5 + var6 + ".png"),
         Texture.getSharedTexture(var4 + "6" + var5 + var6 + ".png"),
         Texture.getSharedTexture(var4 + "3" + var5 + var6 + ".png"),
         Texture.getSharedTexture(var4 + "2" + var5 + var6 + ".png")
      );
      this.Frames.push_back(var7);
      this.FramesArray = this.Frames.toArray(this.FramesArray);
   }

    void LoadFramesReverseAltName(const std::string& var1, const std::string& var2, const std::string& var3, int var4) {
      this.name = var3;
    std::stringstream var5 = tlsStrBuf.get();
      var5.setLength(0);
      var5.append(var1);
      var5.append("_%_");
      var5.append(var2);
      var5.append("_^");
    int var6 = var5.lastIndexOf("^");
    int var7 = var5.indexOf("_%_") + 1;
      var5.setCharAt(var7, '9');
      var5.setCharAt(var6, '0');
      if (GameServer.bServer && !ServerGUI.isCreated()) {
         for (int var8 = 0; var8 < var4; var8++) {
            this.Frames.push_back(std::make_shared<IsoDirectionFrame>(nullptr));
         }

         this.FinishUnloopedOnFrame = (short)(this.Frames.size() - 1);
         this.FramesArray = this.Frames.toArray(this.FramesArray);
      }

    Texture var22 = Texture.getSharedTexture(var5);
      if (var22 != nullptr) {
         for (int var9 = 0; var9 < var4; var9++) {
            if (var9 == 10) {
               var5.setLength(0);
               var5.append(var1);
               var5.append("_1_");
               var5.append(var2);
               var5.append("_10");
            }

    int var10 = var9;
    void* var11 = nullptr;
    std::string var12 = var10;
            if (var22 == nullptr) {
               var5.setCharAt(var7, '8');

               try {
                  var5.setCharAt(var6, var10.charAt(0));
               } catch (Exception var21) {
                  this.LoadFramesReverseAltName(var1, var2, var3, var4);
               }

    std::string var25 = var5;
               var5.setCharAt(var7, '9');
    std::string var26 = var5;
               var5.setCharAt(var7, '6');
    std::string var27 = var5;
               var5.setCharAt(var7, '3');
    std::string var28 = var5;
               var5.setCharAt(var7, '2');
    std::string var29 = var5;
               var11 = std::make_shared<IsoDirectionFrame>(
                  Texture.getSharedTexture(var25),
                  Texture.getSharedTexture(var26),
                  Texture.getSharedTexture(var27),
                  Texture.getSharedTexture(var28),
                  Texture.getSharedTexture(var29)
               );
            } else {
               var5.setCharAt(var7, '9');

               for (int var13 = 0; var13 < var12.length(); var13++) {
                  var5.setCharAt(var6 + var13, var12.charAt(var13));
               }

    std::string var24 = var5;
               var5.setCharAt(var7, '6');
    std::string var14 = var5;
               var5.setCharAt(var7, '3');
    std::string var15 = var5;
               var5.setCharAt(var7, '2');
    std::string var16 = var5;
               var5.setCharAt(var7, '1');
    std::string var17 = var5;
               var5.setCharAt(var7, '4');
    std::string var18 = var5;
               var5.setCharAt(var7, '7');
    std::string var19 = var5;
               var5.setCharAt(var7, '8');
    std::string var20 = var5;
               var11 = std::make_shared<IsoDirectionFrame>(
                  Texture.getSharedTexture(var24),
                  Texture.getSharedTexture(var14),
                  Texture.getSharedTexture(var15),
                  Texture.getSharedTexture(var16),
                  Texture.getSharedTexture(var17),
                  Texture.getSharedTexture(var18),
                  Texture.getSharedTexture(var19),
                  Texture.getSharedTexture(var20)
               );
            }

            this.Frames.push_back(0, (IsoDirectionFrame)var11);
         }

         this.FinishUnloopedOnFrame = (short)(this.Frames.size() - 1);
         this.FramesArray = this.Frames.toArray(this.FramesArray);
      }
   }

    void LoadFrames(const std::string& var1, const std::string& var2, int var3) {
      this.name = var2;
    std::stringstream var4 = tlsStrBuf.get();
      var4.setLength(0);
      var4.append(var1);
      var4.append("_%_");
      var4.append(var2);
      var4.append("_^");
    int var5 = var4.indexOf("_%_") + 1;
    int var6 = var4.lastIndexOf("^");
      var4.setCharAt(var5, '9');
      var4.setCharAt(var6, '0');
      if (GameServer.bServer && !ServerGUI.isCreated()) {
         for (int var7 = 0; var7 < var3; var7++) {
            this.Frames.push_back(std::make_shared<IsoDirectionFrame>(nullptr));
         }

         this.FinishUnloopedOnFrame = (short)(this.Frames.size() - 1);
      }

    Texture var22 = Texture.getSharedTexture(var4);
      if (var22 != nullptr) {
         for (int var8 = 0; var8 < var3; var8++) {
            if (var8 % 10 == 0 && var8 > 0) {
               var4.setLength(0);
               var4.append(var1);
               var4.append("_%_");
               var4.append(var2);
               var4.append("_^_");
               var5 = var4.indexOf("_%_") + 1;
               var6 = var4.lastIndexOf("^");
            }

    int var9 = var8;
    void* var10 = nullptr;
    std::string var11 = var9;
            if (var22 != nullptr) {
               var4.setCharAt(var5, '9');

               for (int var25 = 0; var25 < var11.length(); var25++) {
                  var4.setCharAt(var6 + var25, var11.charAt(var25));
               }

    std::string var26 = var4;
               var4.setCharAt(var5, '6');
    std::string var27 = var4;
               var4.setCharAt(var5, '3');
    std::string var28 = var4;
               var4.setCharAt(var5, '2');
    std::string var29 = var4;
               var4.setCharAt(var5, '1');
    std::string var30 = var4;
               var4.setCharAt(var5, '4');
    std::string var17 = var4;
               var4.setCharAt(var5, '7');
    std::string var18 = var4;
               var4.setCharAt(var5, '8');
    std::string var19 = var4;
               var10 = std::make_shared<IsoDirectionFrame>(
                  Texture.getSharedTexture(var26),
                  Texture.getSharedTexture(var27),
                  Texture.getSharedTexture(var28),
                  Texture.getSharedTexture(var29),
                  Texture.getSharedTexture(var30),
                  Texture.getSharedTexture(var17),
                  Texture.getSharedTexture(var18),
                  Texture.getSharedTexture(var19)
               );
            } else {
               try {
                  var4.setCharAt(var5, '8');
               } catch (Exception var21) {
                  this.LoadFrames(var1, var2, var3);
               }

               for (int var12 = 0; var12 < var11.length(); var12++) {
                  try {
                     var4.setCharAt(var6 + var12, var9.charAt(var12));
                  } catch (Exception var20) {
                     this.LoadFrames(var1, var2, var3);
                  }
               }

    std::string var24 = var4;
               var4.setCharAt(var5, '9');
    std::string var13 = var4;
               var4.setCharAt(var5, '6');
    std::string var14 = var4;
               var4.setCharAt(var5, '3');
    std::string var15 = var4;
               var4.setCharAt(var5, '2');
    std::string var16 = var4;
               var10 = std::make_shared<IsoDirectionFrame>(
                  Texture.getSharedTexture(var24),
                  Texture.getSharedTexture(var13),
                  Texture.getSharedTexture(var14),
                  Texture.getSharedTexture(var15),
                  Texture.getSharedTexture(var16)
               );
            }

            this.Frames.push_back((IsoDirectionFrame)var10);
         }

         this.FinishUnloopedOnFrame = (short)(this.Frames.size() - 1);
         this.FramesArray = this.Frames.toArray(this.FramesArray);
      }
   }

    void LoadFramesUseOtherFrame(const std::string& var1, const std::string& var2, const std::string& var3, const std::string& var4, int var5, const std::string& var6) {
      this.name = var3;
    std::string var7 = var4 + "_" + var2 + "_";
    std::string var8 = "_";
    std::string var9 = "";
      if (var6 != nullptr) {
         var9 = "_" + var6;
      }

      for (int var10 = 0; var10 < 1; var10++) {
    int var11 = std::make_shared<int>(var5);
         IsoDirectionFrame var12 = std::make_shared<IsoDirectionFrame>(
            Texture.getSharedTexture(var7 + "8" + var8 + var11 + var9 + ".png"),
            Texture.getSharedTexture(var7 + "9" + var8 + var11 + var9 + ".png"),
            Texture.getSharedTexture(var7 + "6" + var8 + var11 + var9 + ".png"),
            Texture.getSharedTexture(var7 + "3" + var8 + var11 + var9 + ".png"),
            Texture.getSharedTexture(var7 + "2" + var8 + var11 + var9 + ".png")
         );
         this.Frames.push_back(var12);
      }

      this.FinishUnloopedOnFrame = (short)(this.Frames.size() - 1);
      this.FramesArray = this.Frames.toArray(this.FramesArray);
   }

    void LoadFramesBits(const std::string& var1, const std::string& var2, const std::string& var3, int var4) {
      this.name = var3;
    std::string var5 = var3 + "_" + var2 + "_";
    std::string var6 = "_";

      for (int var7 = 0; var7 < var4; var7++) {
    int var8 = std::make_shared<int>(var7);
         IsoDirectionFrame var9 = std::make_shared<IsoDirectionFrame>(
            Texture.getSharedTexture(var5 + "8" + var6 + var8 + ".png"),
            Texture.getSharedTexture(var5 + "9" + var6 + var8 + ".png"),
            Texture.getSharedTexture(var5 + "6" + var6 + var8 + ".png"),
            Texture.getSharedTexture(var5 + "3" + var6 + var8 + ".png"),
            Texture.getSharedTexture(var5 + "2" + var6 + var8 + ".png")
         );
         this.Frames.push_back(var9);
      }

      this.FinishUnloopedOnFrame = (short)(this.Frames.size() - 1);
      this.FramesArray = this.Frames.toArray(this.FramesArray);
   }

    void LoadFramesBits(const std::string& var1, const std::string& var2, int var3) {
      this.name = var2;
    std::string var4 = var1 + "_" + var2 + "_";
    std::string var5 = "_";

      for (int var6 = 0; var6 < var3; var6++) {
    int var7 = std::make_shared<int>(var6);
         IsoDirectionFrame var8 = std::make_shared<IsoDirectionFrame>(
            Texture.getSharedTexture(var4 + "8" + var5 + var7 + ".png"),
            Texture.getSharedTexture(var4 + "9" + var5 + var7 + ".png"),
            Texture.getSharedTexture(var4 + "6" + var5 + var7 + ".png"),
            Texture.getSharedTexture(var4 + "3" + var5 + var7 + ".png"),
            Texture.getSharedTexture(var4 + "2" + var5 + var7 + ".png")
         );
         this.Frames.push_back(var8);
      }

      this.FinishUnloopedOnFrame = (short)(this.Frames.size() - 1);
      this.FramesArray = this.Frames.toArray(this.FramesArray);
   }

    void LoadFramesBitRepeatFrame(const std::string& var1, const std::string& var2, int var3) {
      this.name = var2;
    std::string var5 = "_";
    std::string var6 = "";
    int var8 = std::make_shared<int>(var3);
      IsoDirectionFrame var9 = std::make_shared<IsoDirectionFrame>(
         Texture.getSharedTexture(var2 + "8" + var5 + var8 + var6 + ".png"),
         Texture.getSharedTexture(var2 + "9" + var5 + var8 + var6 + ".png"),
         Texture.getSharedTexture(var2 + "6" + var5 + var8 + var6 + ".png"),
         Texture.getSharedTexture(var2 + "3" + var5 + var8 + var6 + ".png"),
         Texture.getSharedTexture(var2 + "2" + var5 + var8 + var6 + ".png")
      );
      this.Frames.push_back(var9);
      this.FinishUnloopedOnFrame = (short)(this.Frames.size() - 1);
      this.FramesArray = this.Frames.toArray(this.FramesArray);
   }

    void LoadFramesBitRepeatFrame(const std::string& var1, const std::string& var2, const std::string& var3, int var4, const std::string& var5) {
      this.name = var3;
    std::string var6 = var3 + "_" + var2 + "_";
    std::string var7 = "_";
    std::string var8 = "";
      if (var5 != nullptr) {
         var8 = "_" + var5;
      }

    int var10 = std::make_shared<int>(var4);
      IsoDirectionFrame var11 = std::make_shared<IsoDirectionFrame>(
         Texture.getSharedTexture(var6 + "8" + var7 + var10 + var8 + ".png"),
         Texture.getSharedTexture(var6 + "9" + var7 + var10 + var8 + ".png"),
         Texture.getSharedTexture(var6 + "6" + var7 + var10 + var8 + ".png"),
         Texture.getSharedTexture(var6 + "3" + var7 + var10 + var8 + ".png"),
         Texture.getSharedTexture(var6 + "2" + var7 + var10 + var8 + ".png")
      );
      this.Frames.push_back(var11);
      this.FinishUnloopedOnFrame = (short)(this.Frames.size() - 1);
      this.FramesArray = this.Frames.toArray(this.FramesArray);
   }

    void LoadFramesBits(const std::string& var1, const std::string& var2, const std::string& var3, int var4, const std::string& var5) {
      this.name = var3;
    std::string var6 = var3 + "_" + var2 + "_";
    std::string var7 = "_";
    std::string var8 = "";
      if (var5 != nullptr) {
         var8 = "_" + var5;
      }

      for (int var9 = 0; var9 < var4; var9++) {
    int var10 = std::make_shared<int>(var9);
         IsoDirectionFrame var11 = std::make_shared<IsoDirectionFrame>(
            Texture.getSharedTexture(var6 + "8" + var7 + var10 + var8 + ".png"),
            Texture.getSharedTexture(var6 + "9" + var7 + var10 + var8 + ".png"),
            Texture.getSharedTexture(var6 + "6" + var7 + var10 + var8 + ".png"),
            Texture.getSharedTexture(var6 + "3" + var7 + var10 + var8 + ".png"),
            Texture.getSharedTexture(var6 + "2" + var7 + var10 + var8 + ".png")
         );
         this.Frames.push_back(var11);
      }

      this.FinishUnloopedOnFrame = (short)(this.Frames.size() - 1);
      this.FramesArray = this.Frames.toArray(this.FramesArray);
   }

    void LoadFramesPcx(const std::string& var1, const std::string& var2, int var3) {
      this.name = var2;
    std::string var4 = var1 + "_";
    std::string var5 = "_" + var2 + "_";

      for (int var6 = 0; var6 < var3; var6++) {
    int var7 = std::make_shared<int>(var6);
         IsoDirectionFrame var8 = std::make_shared<IsoDirectionFrame>(
            Texture.getSharedTexture(var4 + "8" + var5 + var7 + ".pcx"),
            Texture.getSharedTexture(var4 + "9" + var5 + var7 + ".pcx"),
            Texture.getSharedTexture(var4 + "6" + var5 + var7 + ".pcx"),
            Texture.getSharedTexture(var4 + "3" + var5 + var7 + ".pcx"),
            Texture.getSharedTexture(var4 + "2" + var5 + var7 + ".pcx")
         );
         this.Frames.push_back(var8);
      }

      this.FinishUnloopedOnFrame = (short)(this.Frames.size() - 1);
      this.FramesArray = this.Frames.toArray(this.FramesArray);
   }

    void Dispose() {
      for (int var1 = 0; var1 < this.Frames.size(); var1++) {
    IsoDirectionFrame var2 = this.Frames.get(var1);
         var2.SetAllDirections(nullptr);
      }
   }

    Texture LoadFrameExplicit(const std::string& var1) {
    Texture var2 = Texture.getSharedTexture(var1);
    IsoDirectionFrame var3 = std::make_shared<IsoDirectionFrame>(var2);
      this.Frames.push_back(var3);
      this.FramesArray = this.Frames.toArray(this.FramesArray);
    return var2;
   }

    void LoadFramesNoDir(const std::string& var1, const std::string& var2, int var3) {
      this.name = var2;
    std::string var4 = "media/" + var1;
    std::string var5 = "_" + var2 + "_";

      for (int var6 = 0; var6 < var3; var6++) {
    int var7 = std::make_shared<int>(var6);
    IsoDirectionFrame var8 = std::make_shared<IsoDirectionFrame>(Texture.getSharedTexture(var4 + var5 + var7 + ".png"));
         this.Frames.push_back(var8);
      }

      this.FinishUnloopedOnFrame = (short)(this.Frames.size() - 1);
      this.FramesArray = this.Frames.toArray(this.FramesArray);
   }

    void LoadFramesNoDirPage(const std::string& var1, const std::string& var2, int var3) {
      this.name = var2;
    std::string var4 = var1;
    std::string var5 = "_" + var2 + "_";

      for (int var6 = 0; var6 < var3; var6++) {
    int var7 = std::make_shared<int>(var6);
    IsoDirectionFrame var8 = std::make_shared<IsoDirectionFrame>(Texture.getSharedTexture(var4 + var5 + var7));
         this.Frames.push_back(var8);
      }

      this.FinishUnloopedOnFrame = (short)(this.Frames.size() - 1);
      this.FramesArray = this.Frames.toArray(this.FramesArray);
   }

    void LoadFramesNoDirPageDirect(const std::string& var1, const std::string& var2, int var3) {
      this.name = var2;
    std::string var4 = var1;
    std::string var5 = "_" + var2 + "_";

      for (int var6 = 0; var6 < var3; var6++) {
    int var7 = std::make_shared<int>(var6);
    IsoDirectionFrame var8 = std::make_shared<IsoDirectionFrame>(Texture.getSharedTexture(var4 + var5 + var7 + ".png"));
         this.Frames.push_back(var8);
      }

      this.FramesArray = this.Frames.toArray(this.FramesArray);
      this.FinishUnloopedOnFrame = (short)(this.Frames.size() - 1);
   }

    void LoadFramesNoDirPage(const std::string& var1) {
      this.name = "default";
    std::string var2 = var1;

      for (int var3 = 0; var3 < 1; var3++) {
    IsoDirectionFrame var4 = std::make_shared<IsoDirectionFrame>(Texture.getSharedTexture(var2));
         this.Frames.push_back(var4);
      }

      this.FinishUnloopedOnFrame = (short)(this.Frames.size() - 1);
      this.FramesArray = this.Frames.toArray(this.FramesArray);
   }

    void LoadFramesPageSimple(const std::string& var1, const std::string& var2, const std::string& var3, const std::string& var4) {
      this.name = "default";

      for (int var5 = 0; var5 < 1; var5++) {
    std::make_shared<int>();
         IsoDirectionFrame var7 = std::make_shared<IsoDirectionFrame>(
            Texture.getSharedTexture(var1), Texture.getSharedTexture(var2), Texture.getSharedTexture(var3), Texture.getSharedTexture(var4)
         );
         this.Frames.push_back(var7);
      }

      this.FinishUnloopedOnFrame = (short)(this.Frames.size() - 1);
      this.FramesArray = this.Frames.toArray(this.FramesArray);
   }

    void LoadFramesNoDirPalette(const std::string& var1, const std::string& var2, int var3, const std::string& var4) {
      this.name = var2;
    std::string var5 = "media/characters/" + var1;
    std::string var6 = "_" + var2 + "_";

      for (int var7 = 0; var7 < var3; var7++) {
    int var8 = std::make_shared<int>(var7);
    IsoDirectionFrame var9 = std::make_shared<IsoDirectionFrame>(Texture.getSharedTexture(var5 + var6 + var8 + ".pcx", var4));
         this.Frames.push_back(var9);
      }

      this.FinishUnloopedOnFrame = (short)(this.Frames.size() - 1);
      this.FramesArray = this.Frames.toArray(this.FramesArray);
   }

    void LoadFramesPalette(const std::string& var1, const std::string& var2, int var3, const std::string& var4) {
      this.name = var2;
    std::string var5 = var1 + "_";
    std::string var6 = "_" + var2 + "_";

      for (int var7 = 0; var7 < var3; var7++) {
    int var8 = std::make_shared<int>(var7);
         IsoDirectionFrame var9 = std::make_shared<IsoDirectionFrame>(
            Texture.getSharedTexture(var5 + "8" + var6 + var8 + "_" + var4),
            Texture.getSharedTexture(var5 + "9" + var6 + var8 + "_" + var4),
            Texture.getSharedTexture(var5 + "6" + var6 + var8 + "_" + var4),
            Texture.getSharedTexture(var5 + "3" + var6 + var8 + "_" + var4),
            Texture.getSharedTexture(var5 + "2" + var6 + var8 + "_" + var4)
         );
         this.Frames.push_back(var9);
      }

      this.FinishUnloopedOnFrame = (short)(this.Frames.size() - 1);
      this.FramesArray = this.Frames.toArray(this.FramesArray);
   }

    void DupeFrame() {
      for (int var1 = 0; var1 < 8; var1++) {
    IsoDirectionFrame var2 = std::make_shared<IsoDirectionFrame>();
         var2.directions[var1] = this.Frames.get(0).directions[var1];
         var2.bDoFlip = this.Frames.get(0).bDoFlip;
         this.Frames.push_back(var2);
      }

      this.FramesArray = this.Frames.toArray(this.FramesArray);
   }
}
} // namespace sprite
} // namespace iso
} // namespace zombie
