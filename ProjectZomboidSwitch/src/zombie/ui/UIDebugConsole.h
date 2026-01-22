#pragma once
#include <sstream>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "se/krka/kahlua/integration/LuaReturn.h"
#include "se/krka/kahlua/luaj/compiler/LuaCompiler.h"
#include "se/krka/kahlua/stdlib/BaseLib.h"
#include "se/krka/kahlua/vm/KahluaException.h"
#include "se/krka/kahlua/vm/LuaClosure.h"
#include "zombie/Lua/LuaManager.h"
#include "zombie/Lua/LuaManager/GlobalObject.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/core/Core.h"
#include "zombie/debug/DebugOptions.h"
#include "zombie/ui/UIDebugConsole/CommandEntry.h"
#include <algorithm>
#include <filesystem>

namespace zombie {
namespace ui {


class UIDebugConsole : public NewWindow {
public:
    static UIDebugConsole instance;
    IsoGameCharacter ParentChar;
    ScrollBar ScrollBarV;
    UITextBox2 OutputLog;
    UITextBox2 CommandLine;
    UITextBox2 autosuggest;
    std::string ConsoleVersion = "v1.1.0";
    int inputlength = 0;
   private const std::vector<std::string> Previous = std::make_unique<std::vector<>>();
   private const std::vector<Method> globalLuaMethods = std::make_unique<std::vector<>>();
    int PreviousIndex = 0;
    Method prevSuggestion = nullptr;
   std::string[] AvailableCommands = new std::string[]{"?", "help", "commands", "clr", "AddInvItem", "SpawnZombie"};
   std::string[] AvailableCommandsHelp = new std::string[]{
      "'?' - Shows available commands",
      "'help' - Shows available commands",
      "'commands' - Shows available commands",
      "'clr' - Clears the command log",
      "'AddInvItem' - Adds an item to player inventory. USAGE - AddInvItem 'ItemName' [ammount]",
      "'SpawnZombie' - Spawn a zombie at a map location. USAGE - SpawnZombie X,Y,Z (integers)"
   };
    bool bDebounceUp = false;
    bool bDebounceDown = false;
    static const void* outputLock = "DebugConsole Output Lock";
    static const ByteBuffer outputBB = ByteBuffer.allocate(8192);
    static bool outputChanged = false;
    static CharsetDecoder outputDecoder;
   private static char[] outputChars;
    static CharBuffer outputCharBuf = nullptr;

    public UIDebugConsole(int var1, int var2) {
      super(var1, var2, 10, 10, true);
      this.ResizeToFitY = false;
      this.visible = true;
      instance = this;
      this.width = 640.0F;
    int var3 = TextManager.instance.getFontHeight(UIFont.DebugConsole);
    uint8_t var4 = 11;
    uint8_t var5 = 5;
      this.OutputLog = std::make_shared<UITextBox2>(
         UIFont.DebugConsole,
         5,
         33,
         630,
         var3 * var4 + var5 * 2,
         "Project Zomboid - "
            + Core.getInstance().getVersion()
            + "\nDebug Console - "
            + this.ConsoleVersion
            + "\n(C) Indie Stone Studios 2021\n---------------------------------------------------------------------------------------------------------------------------\n\n",
         true
      );
      this.OutputLog.multipleLine = true;
      this.OutputLog.bAlwaysPaginate = false;
      this.CommandLine = std::make_shared<CommandEntry>(this, UIFont.DebugConsole, 5, (int)(this.OutputLog.getY() + this.OutputLog.getHeight()) + 15, 630, 24, "", true);
      this.CommandLine.IsEditable = true;
      this.CommandLine.TextEntryMaxLength = 256;
      this.autosuggest = std::make_shared<UITextBox2>(UIFont.DebugConsole, 5, 180, 15, 25, "", true);
      this.height = (int)(this.CommandLine.getY() + this.CommandLine.getHeight()) + 6;
      this.ScrollBarV = std::make_shared<ScrollBar>(
         "UIDebugConsoleScrollbar",
         nullptr,
         (int)(this.OutputLog.getX() + this.OutputLog.getWidth()) - 14,
         this.OutputLog.getY().intValue() + 4,
         this.OutputLog.getHeight().intValue() - 8,
         true
      );
      this.ScrollBarV.SetParentTextBox(this.OutputLog);
      this.AddChild(this.OutputLog);
      this.AddChild(this.ScrollBarV);
      this.AddChild(this.CommandLine);
      this.AddChild(this.autosuggest);
      this.InitSuggestionEngine();
      if (Core.bDebug) {
         BaseLib.setPrintCallback(this::SpoolText);
      }
   }

    void render() {
      if (this.isVisible()) {
         super.render();
         this.DrawTextCentre(UIFont.DebugConsole, "Command Console", this.getWidth() / 2.0, 2.0, 1.0, 1.0, 1.0, 1.0);
         this.DrawText(UIFont.DebugConsole, "Output Log", 7.0, 19.0, 0.7F, 0.7F, 1.0, 1.0);
         this.DrawText(UIFont.DebugConsole, "Lua Command Line", 7.0, this.OutputLog.getY() + this.OutputLog.getHeight() + 1.0, 0.7F, 0.7F, 1.0, 1.0);
      }
   }

    void update() {
      if (this.isVisible()) {
         this.handleOutput();
         super.update();
         if (this.CommandLine.getText().length() != this.inputlength && this.CommandLine.getText().length() != 0) {
            this.inputlength = this.CommandLine.getText().length();
            std::string[] var1 = this.CommandLine.getText().split(":");
    std::string var2 = "";
            if (var1.length > 0) {
               var2 = var1[var1.length - 1];
               if (var1[var1.length - 1].empty() && this.autosuggest.isVisible()) {
                  this.autosuggest.setVisible(false);
                  return;
               }
            }

    Method var3 = nullptr;
            if (var1.length > 1 && var1[0].indexOf(")") > 0 && !var1[var1.length - 1].contains("(")) {
    std::vector var5 = new std::vector<>(this.globalLuaMethods);

               for (int var6 = 0; var6 < var1.length; var6++) {
    std::string var7 = var1[var6];
                  if (var7.indexOf(")") > 0) {
                     var7 = var7.split("\\(", 0)[0];

    for (auto& var9 : var5)                        if (var9.getName() == var7)) {
                           var5.clear();

                           for (Class var10 = var9.getReturnType(); var10 != nullptr; var10 = var10.getSuperclass()) {
                              for (Method var14 : var10.getDeclaredMethods()) {
                                 if (Modifier.isPublic(var14.getModifiers())) {
                                    var5.push_back(var14);
                                 }
                              }
                           }
                           break;
                        }
                     }
                  }
               }

               var3 = this.SuggestionEngine(var2, var5);
            } else if (var1.length == 1) {
               var3 = this.SuggestionEngine(var2);
            }

    std::string var4 = "void";
            if (var3 != nullptr) {
               if (!var3.getReturnType() == "void")) {
                  std::string[] var15 = var3.getReturnType().split("\\.");
                  var4 = var15[var15.length - 1];
               }

               if (!this.autosuggest.isVisible()) {
                  this.autosuggest.setVisible(true);
               }

               this.autosuggest.SetText("<" + var4 + "> " + var3.getName());
               this.autosuggest.setX(5 * this.CommandLine.getText().length());
               this.autosuggest.setWidth(15 * (var4.length() + var3.getName().length()));
               this.autosuggest.Frame.width = 10 * (var4.length() + var3.getName().length());
            }
         } else if (this.CommandLine.getText().length() == 0 && this.autosuggest.isVisible()) {
            this.autosuggest.setVisible(false);
         }
      }
   }

    void ProcessCommand() {
      if (this.CommandLine.internalText != nullptr) {
    std::string var1 = this.CommandLine.internalText;
         this.CommandLine.internalText = "";
         var1 = var1.trim();
         std::string[] var2 = var1.split(" ");
         var2[0] = var2[0].trim();
         if (this.Previous.empty() || !var1 == this.Previous.get(this.Previous.size() - 1))) {
            this.Previous.push_back(var1);
         }

         this.PreviousIndex = this.Previous.size();
         this.CommandLine.DoingTextEntry = true;
         Core.CurrentTextEntryBox = this.CommandLine;
         if ("clear" == var1)) {
            this.OutputLog.bTextChanged = true;
            this.OutputLog.clearInput();
         } else {
            if (DebugOptions.instance.UIDebugConsoleEchoCommand.getValue()) {
               this.SpoolText("[USER] - \"" + var1 + "\".");
            }

            try {
    LuaClosure var3 = LuaCompiler.loadstring(var1, "console", LuaManager.env);
    LuaReturn var4 = LuaManager.caller.protectedCall(LuaManager.thread, var3, new Object[0]);
            } catch (KahluaException var5) {
               this.SpoolText(var5.getMessage());
            } catch (Exception var6) {
               Logger.getLogger(UIDebugConsole.class.getName()).log(Level.SEVERE, nullptr, var6);
            }
         }
      }
   }

    void historyPrev() {
      this.PreviousIndex--;
      if (this.PreviousIndex < 0) {
         this.PreviousIndex = 0;
      }

      if (this.PreviousIndex >= 0 && this.PreviousIndex < this.Previous.size()) {
         this.CommandLine.SetText(this.Previous.get(this.PreviousIndex));
      }
   }

    void historyNext() {
      this.PreviousIndex++;
      if (this.PreviousIndex >= this.Previous.size()) {
         this.PreviousIndex = this.Previous.size() - 1;
      }

      if (this.PreviousIndex >= 0 && this.PreviousIndex < this.Previous.size()) {
         this.CommandLine.SetText(this.Previous.get(this.PreviousIndex));
      }
   }

    void onOtherKey(int var1) {
      switch (var1) {
         case 15:
            if (this.prevSuggestion != nullptr) {
               std::string[] var2 = this.CommandLine.getText().split(":");
    std::stringstream var3 = new std::stringstream();
               if (var2.length > 0) {
                  var2[var2.length - 1] = this.prevSuggestion.getName();

                  for (int var4 = 0; var4 < var2.length; var4++) {
                     var3.append(var2[var4]);
                     if (var4 != var2.length - 1) {
                        var3.append(":");
                     }
                  }
               }

               if (this.prevSuggestion.getParameterTypes().length == 0) {
                  this.CommandLine.SetText(var3 + "()");
               } else {
                  this.CommandLine.SetText(var3 + "(");
               }
            }
      }
   }

    void ClearConsole() {
      this.OutputLog.bTextChanged = true;
      this.OutputLog.SetText("");
      this.UpdateViewPos();
   }

    void UpdateViewPos() {
      this.OutputLog.TopLineIndex = this.OutputLog.Lines.size() - this.OutputLog.NumVisibleLines;
      if (this.OutputLog.TopLineIndex < 0) {
         this.OutputLog.TopLineIndex = 0;
      }

      this.ScrollBarV.scrollToBottom();
   }

    void SpoolText(const std::string& var1) {
      this.OutputLog.bTextChanged = true;
      this.OutputLog.SetText(this.OutputLog.Text + var1 + "\n");
      this.UpdateViewPos();
   }

    Method SuggestionEngine(const std::string& var1) {
      return this.SuggestionEngine(var1, this.globalLuaMethods);
   }

    Method SuggestionEngine(const std::string& var1, std::vector<Method> var2) {
    int var3 = 0;
    int var4 = 0;
    Method var5 = nullptr;

    for (auto& var7 : var2)         if (var5 == nullptr) {
            var5 = var7;
            var3 = this.levenshteinDistance(var1, var7.getName());
         } else {
            var4 = this.levenshteinDistance(var1, var7.getName());
            if (var4 < var3) {
               var3 = var4;
               var5 = var7;
            }
         }
      }

      this.prevSuggestion = var5;
    return var5;
   }

    void InitSuggestionEngine() {
      Class<GlobalObject> var1 = GlobalObject.class;
      this.globalLuaMethods.addAll(Arrays.asList(var1.getDeclaredMethods()));
   }

    int levenshteinDistance(CharSequence var1, CharSequence var2) {
    int var3 = var1.length() + 1;
    int var4 = var2.length() + 1;
      int[] var5 = new int[var3];
      int[] var6 = new int[var3];
    int var7 = 0;

      while (var7 < var3) {
         var5[var7] = var7++;
      }

      for (int var13 = 1; var13 < var4; var13++) {
         var6[0] = var13;

         for (int var8 = 1; var8 < var3; var8++) {
    int var9 = var1.charAt(var8 - 1) == var2.charAt(var13 - 1) ? 0 : 1;
    int var10 = var5[var8 - 1] + var9;
    int var11 = var5[var8] + 1;
    int var12 = var6[var8 - 1] + 1;
            var6[var8] = Math.min(Math.min(var11, var12), var10);
         }

         int[] var14 = var5;
         var5 = var6;
         var6 = var14;
      }

      return var5[var3 - 1];
   }

    void setSuggestWidth(int var1) {
      this.autosuggest.setWidth(var1);
      this.autosuggest.Frame.width = var1;
   }

    void addOutput(byte[] var1, int var2, int var3) {
      if (var3 >= 1) {
         /* synchronized - TODO: add std::mutex */ (outputLock) {
    int var5 = var3 - outputBB.capacity();
            if (var5 > 0) {
               var2 += var5;
               var3 -= var5;
            }

            if (outputBB.position() + var3 > outputBB.capacity()) {
               outputBB.clear();
            }

            outputBB.put(var1, var2, var3);
            if (var1[var2 + var3 - 1] == 10) {
               outputChanged = true;
            }
         }
      }
   }

    void handleOutput() {
      /* synchronized - TODO: add std::mutex */ (outputLock) {
         if (outputChanged) {
            outputChanged = false;

            try {
               if (outputDecoder == nullptr) {
                  outputDecoder = Charset.forName("UTF-8")
                     .newDecoder()
                     .onMalformedInput(CodingErrorAction.REPLACE)
                     .onUnmappableCharacter(CodingErrorAction.REPLACE);
               }

               outputDecoder.reset();
    int var2 = outputBB.position();
               outputBB.flip();
    int var3 = (int)((double)var2 * outputDecoder.maxCharsPerByte());
               if (outputChars == nullptr || outputChars.length < var3) {
    int var4 = (var3 + 128 - 1) / 128 * 128;
                  outputChars = new char[var4];
                  outputCharBuf = CharBuffer.wrap(outputChars);
               }

               outputCharBuf.clear();
    CoderResult var11 = outputDecoder.decode(outputBB, outputCharBuf, true);
               outputBB.clear();
    std::string var5 = new std::string(outputChars, 0, outputCharBuf.position());
               this.OutputLog.bTextChanged = true;
               this.OutputLog.SetText(this.OutputLog.Text + var5);
    short var6 = 8192;
               if (this.OutputLog.Text.length() > var6) {
    int var7 = this.OutputLog.Text.length() - var6;

                  while (var7 < this.OutputLog.Text.length() && this.OutputLog.Text.charAt(var7) != '\n') {
                     var7++;
                  }

                  this.OutputLog.bTextChanged = true;
                  this.OutputLog.SetText(this.OutputLog.Text.substr(var7 + 1));
               }
            } catch (Exception var9) {
            }

            this.UpdateViewPos();
         }
      }
   }
}
} // namespace ui
} // namespace zombie
