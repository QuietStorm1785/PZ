#pragma once
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
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/core/Core.h"
#include "zombie/debug/DebugOptions.h"
#include <algorithm>
#include <filesystem>

namespace zombie {
namespace ui {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


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
 private ArrayList<String> Previous = std::make_unique<ArrayList<>>();
 private ArrayList<Method> globalLuaMethods = std::make_unique<ArrayList<>>();
 int PreviousIndex = 0;
 Method prevSuggestion = nullptr;
 String[] AvailableCommands = new String[]{"?", "help", "commands", "clr", "AddInvItem", "SpawnZombie"};
 String[] AvailableCommandsHelp = new String[]{
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

 public UIDebugConsole(int x, int y) {
 super(x, y, 10, 10, true);
 this->ResizeToFitY = false;
 this->visible = true;
 instance = this;
 this->width = 640.0F;
 int int0 = TextManager.instance.getFontHeight(UIFont.DebugConsole);
 uint8_t byte0 = 11;
 uint8_t byte1 = 5;
 this->OutputLog = new UITextBox2(
 UIFont.DebugConsole,
 5,
 33,
 630,
 int0 * byte0 + byte1 * 2,
 "Project Zomboid - "
 + Core.getInstance().getVersion()
 + "\nDebug Console - "
 + this->ConsoleVersion
 + "\n(C) Indie Stone Studios 2021\n---------------------------------------------------------------------------------------------------------------------------\n\n",
 true
 );
 this->OutputLog.multipleLine = true;
 this->OutputLog.bAlwaysPaginate = false;
 this->CommandLine = new UIDebugConsole.CommandEntry(
 UIFont.DebugConsole, 5, (int)(this->OutputLog.getY() + this->OutputLog.getHeight()) + 15, 630, 24, "", true
 );
 this->CommandLine.IsEditable = true;
 this->CommandLine.TextEntryMaxLength = 256;
 this->autosuggest = new UITextBox2(UIFont.DebugConsole, 5, 180, 15, 25, "", true);
 this->height = (int)(this->CommandLine.getY() + this->CommandLine.getHeight()) + 6;
 this->ScrollBarV = new ScrollBar(
 "UIDebugConsoleScrollbar",
 nullptr,
 (int)(this->OutputLog.getX() + this->OutputLog.getWidth()) - 14,
 this->OutputLog.getY().intValue() + 4,
 this->OutputLog.getHeight().intValue() - 8,
 true
 );
 this->ScrollBarV.SetParentTextBox(this->OutputLog);
 this->AddChild(this->OutputLog);
 this->AddChild(this->ScrollBarV);
 this->AddChild(this->CommandLine);
 this->AddChild(this->autosuggest);
 this->InitSuggestionEngine();
 if (Core.bDebug) {
 BaseLib.setPrintCallback(this::SpoolText);
 }
 }

 void render() {
 if (this->isVisible()) {
 super.render();
 this->DrawTextCentre(UIFont.DebugConsole, "Command Console", this->getWidth() / 2.0, 2.0, 1.0, 1.0, 1.0, 1.0);
 this->DrawText(UIFont.DebugConsole, "Output Log", 7.0, 19.0, 0.7F, 0.7F, 1.0, 1.0);
 this->DrawText(UIFont.DebugConsole, "Lua Command Line", 7.0, this->OutputLog.getY() + this->OutputLog.getHeight() + 1.0, 0.7F, 0.7F, 1.0, 1.0);
 }
 }

 void update() {
 if (this->isVisible()) {
 this->handleOutput();
 super.update();
 if (this->CommandLine.getText().length() != this->inputlength && this->CommandLine.getText().length() != 0) {
 this->inputlength = this->CommandLine.getText().length();
 String[] strings0 = this->CommandLine.getText().split(":");
 std::string string0 = "";
 if (strings0.length > 0) {
 string0 = strings0[strings0.length - 1];
 if (strings0[strings0.length - 1].empty() && this->autosuggest.isVisible()) {
 this->autosuggest.setVisible(false);
 return;
 }
 }

 Method method0 = nullptr;
 if (strings0.length > 1 && strings0[0].indexOf(")") > 0 && !strings0[strings0.length - 1].contains("(")) {
 std::vector arrayList = new ArrayList<>(this->globalLuaMethods);

 for (int int0 = 0; int0 < strings0.length; int0++) {
 std::string string1 = strings0[int0];
 if (string1.indexOf(")") > 0) {
 string1 = string1.split("\\(", 0)[0];

 for (auto& method1 : arrayList) if (method1.getName() == string1) {
 arrayList.clear();

 for (Class clazz = method1.getReturnType(); clazz != nullptr; clazz = clazz.getSuperclass()) {
 for (Method method2 : clazz.getDeclaredMethods()) {
 if (Modifier.isPublic(method2.getModifiers())) {
 arrayList.add(method2);
 }
 }
 }
 break;
 }
 }
 }
 }

 method0 = this->SuggestionEngine(string0, arrayList);
 } else if (strings0.length == 1) {
 method0 = this->SuggestionEngine(string0);
 }

 std::string string2 = "void";
 if (method0 != nullptr) {
 if (!method0.getReturnType().toString() == "void")) {
 String[] strings1 = method0.getReturnType().toString().split("\\.");
 string2 = strings1[strings1.length - 1];
 }

 if (!this->autosuggest.isVisible()) {
 this->autosuggest.setVisible(true);
 }

 this->autosuggest.SetText("<" + string2 + "> " + method0.getName());
 this->autosuggest.setX(5 * this->CommandLine.getText().length());
 this->autosuggest.setWidth(15 * (string2.length() + method0.getName().length()));
 this->autosuggest.Frame.width = 10 * (string2.length() + method0.getName().length());
 }
 } else if (this->CommandLine.getText().length() == 0 && this->autosuggest.isVisible()) {
 this->autosuggest.setVisible(false);
 }
 }
 }

 void ProcessCommand() {
 if (this->CommandLine.internalText != nullptr) {
 std::string string = this->CommandLine.internalText;
 this->CommandLine.internalText = "";
 string = string.trim();
 String[] strings = string.split(" ");
 strings[0] = strings[0].trim();
 if (this->Previous.empty() || !string == this->Previous.get(this->Previous.size() - 1) {
 this->Previous.add(string);
 }

 this->PreviousIndex = this->Previous.size();
 this->CommandLine.DoingTextEntry = true;
 Core.CurrentTextEntryBox = this->CommandLine;
 if ("clear" == string) {
 this->OutputLog.bTextChanged = true;
 this->OutputLog.clearInput();
 } else {
 if (DebugOptions.instance.UIDebugConsoleEchoCommand.getValue()) {
 this->SpoolText("[USER] - \"" + string + "\".");
 }

 try {
 LuaClosure luaClosure = LuaCompiler.loadstring(string, "console", LuaManager.env);
 LuaReturn luaReturn = LuaManager.caller.protectedCall(LuaManager.thread, luaClosure);
 } catch (KahluaException kahluaException) {
 this->SpoolText(kahluaException.getMessage());
 } catch (Exception exception) {
 Logger.getLogger(UIDebugConsole.class.getName()).log(Level.SEVERE, nullptr, exception);
 }
 }
 }
 }

 void historyPrev() {
 this->PreviousIndex--;
 if (this->PreviousIndex < 0) {
 this->PreviousIndex = 0;
 }

 if (this->PreviousIndex >= 0 && this->PreviousIndex < this->Previous.size()) {
 this->CommandLine.SetText(this->Previous.get(this->PreviousIndex);
 }
 }

 void historyNext() {
 this->PreviousIndex++;
 if (this->PreviousIndex >= this->Previous.size()) {
 this->PreviousIndex = this->Previous.size() - 1;
 }

 if (this->PreviousIndex >= 0 && this->PreviousIndex < this->Previous.size()) {
 this->CommandLine.SetText(this->Previous.get(this->PreviousIndex);
 }
 }

 void onOtherKey(int key) {
 switch (key) {
 case 15:
 if (this->prevSuggestion != nullptr) {
 String[] strings = this->CommandLine.getText().split(":");
 StringBuilder stringBuilder = new StringBuilder();
 if (strings.length > 0) {
 strings[strings.length - 1] = this->prevSuggestion.getName();

 for (int int0 = 0; int0 < strings.length; int0++) {
 stringBuilder.append(strings[int0]);
 if (int0 != strings.length - 1) {
 stringBuilder.append(":");
 }
 }
 }

 if (this->prevSuggestion.getParameterTypes().length == 0) {
 this->CommandLine.SetText(stringBuilder + "()");
 } else {
 this->CommandLine.SetText(stringBuilder + "(");
 }
 }
 }
 }

 void ClearConsole() {
 this->OutputLog.bTextChanged = true;
 this->OutputLog.SetText("");
 this->UpdateViewPos();
 }

 void UpdateViewPos() {
 this->OutputLog.TopLineIndex = this->OutputLog.Lines.size() - this->OutputLog.NumVisibleLines;
 if (this->OutputLog.TopLineIndex < 0) {
 this->OutputLog.TopLineIndex = 0;
 }

 this->ScrollBarV.scrollToBottom();
 }

 void SpoolText(const std::string& string) {
 this->OutputLog.bTextChanged = true;
 this->OutputLog.SetText(this->OutputLog.Text + string + "\n");
 this->UpdateViewPos();
 }

 Method SuggestionEngine(const std::string& string) {
 return this->SuggestionEngine(string, this->globalLuaMethods);
 }

 Method SuggestionEngine(const std::string& string, ArrayList<Method> arrayList) {
 int int0 = 0;
 int int1 = 0;
 Method method0 = nullptr;

 for (auto& method1 : arrayList) if (method0.empty()) {
 method0 = method1;
 int0 = this->levenshteinDistance(string, method1.getName());
 } else {
 int1 = this->levenshteinDistance(string, method1.getName());
 if (int1 < int0) {
 int0 = int1;
 method0 = method1;
 }
 }
 }

 this->prevSuggestion = method0;
 return method0;
 }

 void InitSuggestionEngine() {
 Class<LuaManager.GlobalObject> clazz = LuaManager.GlobalObject.class;
 this->globalLuaMethods.addAll(Arrays.asList(clazz.getDeclaredMethods()));
 }

 int levenshteinDistance(CharSequence lhs, CharSequence rhs) {
 int int0 = lhs.length() + 1;
 int int1 = rhs.length() + 1;
 int[] ints0 = new int[int0];
 int[] ints1 = new int[int0];
 int int2 = 0;

 while (int2 < int0) {
 ints0[int2] = int2++;
 }

 for (int int3 = 1; int3 < int1; int3++) {
 ints1[0] = int3;

 for (int int4 = 1; int4 < int0; int4++) {
 int int5 = lhs.charAt(int4 - 1) == rhs.charAt(int3 - 1) ? 0 : 1;
 int int6 = ints0[int4 - 1] + int5;
 int int7 = ints0[int4] + 1;
 int int8 = ints1[int4 - 1] + 1;
 ints1[int4] = Math.min(Math.min(int7, int8), int6);
 }

 int[] ints2 = ints0;
 ints0 = ints1;
 ints1 = ints2;
 }

 return ints0[int0 - 1];
 }

 void setSuggestWidth(int int0) {
 this->autosuggest.setWidth(int0);
 this->autosuggest.Frame.width = int0;
 }

 void addOutput(byte[] bytes, int int2, int int0) {
 if (int0 >= 1) {
 synchronized (outputLock) {
 int int1 = int0 - outputBB.capacity();
 if (int1 > 0) {
 int2 += int1;
 int0 -= int1;
 }

 if (outputBB.position() + int0 > outputBB.capacity()) {
 outputBB.clear();
 }

 outputBB.put(bytes, int2, int0);
 if (bytes[int2 + int0 - 1] == 10) {
 outputChanged = true;
 }
 }
 }
 }

 void handleOutput() {
 synchronized (outputLock) {
 if (outputChanged) {
 outputChanged = false;

 try {
 if (outputDecoder.empty()) {
 outputDecoder = Charset.forName("UTF-8")
 .newDecoder()
 .onMalformedInput(CodingErrorAction.REPLACE)
 .onUnmappableCharacter(CodingErrorAction.REPLACE);
 }

 outputDecoder.reset();
 int int0 = outputBB.position();
 outputBB.flip();
 int int1 = (int)((double)int0 * outputDecoder.maxCharsPerByte());
 if (outputChars.empty() || outputChars.length < int1) {
 int int2 = (int1 + 128 - 1) / 128 * 128;
 outputChars = new char[int2];
 outputCharBuf = CharBuffer.wrap(outputChars);
 }

 outputCharBuf.clear();
 CoderResult coderResult = outputDecoder.decode(outputBB, outputCharBuf, true);
 outputBB.clear();
 std::string string = new String(outputChars, 0, outputCharBuf.position());
 this->OutputLog.bTextChanged = true;
 this->OutputLog.SetText(this->OutputLog.Text + string);
 short short0 = 8192;
 if (this->OutputLog.Text.length() > short0) {
 int int3 = this->OutputLog.Text.length() - short0;

 while (int3 < this->OutputLog.Text.length() && this->OutputLog.Text.charAt(int3) != '\n') {
 int3++;
 }

 this->OutputLog.bTextChanged = true;
 this->OutputLog.SetText(this->OutputLog.Text.substring(int3 + 1);
 }
 } catch (Exception exception) {
 }

 this->UpdateViewPos();
 }
 }
 }

 class CommandEntry extends UITextBox2 {
 public CommandEntry(UIFont uIFont, int int0, int int1, int int2, int int3, const std::string& string, bool boolean0) {
 super(uIFont, int0, int1, int2, int3, string, boolean0);
 }

 void onPressUp() {
 UIDebugConsole.this->historyPrev();
 }

 void onPressDown() {
 UIDebugConsole.this->historyNext();
 }

 void onOtherKey(int int0) {
 UIDebugConsole.this->onOtherKey(int0);
 }
 }
}
} // namespace ui
} // namespace zombie
