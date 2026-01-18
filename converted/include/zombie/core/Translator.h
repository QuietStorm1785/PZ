#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "se/krka/kahlua/vm/KahluaTable.h"
#include "zombie/Lua/LuaManager.h"
#include "zombie/ZomboidFileSystem.h"
#include "zombie/characters/skills/PerkFactory.h"
#include "zombie/core/logger/ExceptionLogger.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/debug/DebugOptions.h"
#include "zombie/scripting/ScriptManager.h"
#include "zombie/scripting/objects/Item.h"
#include "zombie/util/StringUtils.h"
#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>

namespace zombie {
namespace core {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class Translator {
public:
 private static ArrayList<Language> availableLanguage = nullptr;
 static bool debug = false;
 static FileWriter debugFile = nullptr;
 static bool debugErrors = false;
 private static HashSet<String> debugItemEvolvedRecipeName = std::make_unique<HashSet<>>();
 private static HashSet<String> debugItem = std::make_unique<HashSet<>>();
 private static HashSet<String> debugMultiStageBuild = std::make_unique<HashSet<>>();
 private static HashSet<String> debugRecipe = std::make_unique<HashSet<>>();
 private static HashMap<String, String> moodles = std::make_unique<HashMap<>>();
 private static HashMap<String, String> ui = std::make_unique<HashMap<>>();
 private static HashMap<String, String> survivalGuide = std::make_unique<HashMap<>>();
 private static HashMap<String, String> contextMenu = std::make_unique<HashMap<>>();
 private static HashMap<String, String> farming = std::make_unique<HashMap<>>();
 private static HashMap<String, String> recipe = std::make_unique<HashMap<>>();
 private static HashMap<String, String> igui = std::make_unique<HashMap<>>();
 private static HashMap<String, String> sandbox = std::make_unique<HashMap<>>();
 private static HashMap<String, String> tooltip = std::make_unique<HashMap<>>();
 private static HashMap<String, String> challenge = std::make_unique<HashMap<>>();
 private static HashSet<String> missing = std::make_unique<HashSet<>>();
 private static ArrayList<String> azertyLanguages = nullptr;
 private static HashMap<String, String> news = std::make_unique<HashMap<>>();
 private static HashMap<String, String> stash = std::make_unique<HashMap<>>();
 private static HashMap<String, String> multiStageBuild = std::make_unique<HashMap<>>();
 private static HashMap<String, String> moveables = std::make_unique<HashMap<>>();
 private static HashMap<String, String> makeup = std::make_unique<HashMap<>>();
 private static HashMap<String, String> gameSound = std::make_unique<HashMap<>>();
 private static HashMap<String, String> dynamicRadio = std::make_unique<HashMap<>>();
 private static HashMap<String, String> items = std::make_unique<HashMap<>>();
 private static HashMap<String, String> itemName = std::make_unique<HashMap<>>();
 private static HashMap<String, String> itemEvolvedRecipeName = std::make_unique<HashMap<>>();
 private static HashMap<String, String> recordedMedia = std::make_unique<HashMap<>>();
 private static HashMap<String, String> recordedMedia_EN = std::make_unique<HashMap<>>();
 static Language language = nullptr;
 static const std::string newsHeader = "<IMAGE:media/ui/dot.png> <SIZE:small> ";

 static void loadFiles() {
 language = nullptr;
 availableLanguage = nullptr;
 File file = new File(ZomboidFileSystem.instance.getCacheDir() + File.separator + "translationProblems.txt");
 if (debug) {
 try {
 if (debugFile != nullptr) {
 debugFile.close();
 }

 debugFile = new FileWriter(file);
 } catch (IOException iOException) {
 iOException.printStackTrace();
 }
 }

 moodles.clear();
 ui.clear();
 survivalGuide.clear();
 items.clear();
 itemName.clear();
 contextMenu.clear();
 farming.clear();
 recipe.clear();
 igui.clear();
 sandbox.clear();
 tooltip.clear();
 challenge.clear();
 news.clear();
 missing.clear();
 stash.clear();
 multiStageBuild.clear();
 moveables.clear();
 makeup.clear();
 gameSound.clear();
 dynamicRadio.clear();
 itemEvolvedRecipeName.clear();
 recordedMedia.clear();
 DebugLog.log("translator: language is " + getLanguage());
 debugErrors = false;
 fillMapFromFile("Tooltip", tooltip);
 fillMapFromFile("IG_UI", igui);
 fillMapFromFile("Recipes", recipe);
 fillMapFromFile("Farming", farming);
 fillMapFromFile("ContextMenu", contextMenu);
 fillMapFromFile("SurvivalGuide", survivalGuide);
 fillMapFromFile("UI", ui);
 fillMapFromFile("Items", items);
 fillMapFromFile("ItemName", itemName);
 fillMapFromFile("Moodles", moodles);
 fillMapFromFile("Sandbox", sandbox);
 fillMapFromFile("Challenge", challenge);
 fillMapFromFile("Stash", stash);
 fillMapFromFile("MultiStageBuild", multiStageBuild);
 fillMapFromFile("Moveables", moveables);
 fillMapFromFile("MakeUp", makeup);
 fillMapFromFile("GameSound", gameSound);
 fillMapFromFile("DynamicRadio", dynamicRadio);
 fillMapFromFile("EvolvedRecipeName", itemEvolvedRecipeName);
 fillMapFromFile("Recorded_Media", recordedMedia);
 fillNewsFromFile(news);
 if (debug) {
 if (debugErrors) {
 DebugLog.log("translator: errors detected, please see " + file.getAbsolutePath());
 }

 debugItemEvolvedRecipeName.clear();
 debugItem.clear();
 debugMultiStageBuild.clear();
 debugRecipe.clear();
 }

 PerkFactory.initTranslations();
 }

 static void fillNewsFromFile(String> hashMap1) {
 std::unordered_map hashMap0 = new HashMap();
 std::vector arrayList = ZomboidFileSystem.instance.getModIDs();

 for (int int0 = 0; int0 < arrayList.size(); int0++) {
 std::string string = ZomboidFileSystem.instance.getModDir((String)arrayList.get(int0);
 if (string != nullptr) {
 tryFillNewsFromFile(string, hashMap1, hashMap0, getLanguage());
 if (getLanguage() != getDefaultLanguage()) {
 tryFillNewsFromFile(string, hashMap1, hashMap0, getDefaultLanguage());
 }
 }
 }

 tryFillNewsFromFile(".", hashMap1, hashMap0, getLanguage());
 if (getLanguage() != getDefaultLanguage()) {
 tryFillNewsFromFile(".", hashMap1, hashMap0, getDefaultLanguage());
 }

 for (Translator.News newsx : hashMap0.values()) {
 hashMap1.put("News_" + newsx.version + "_Disclaimer", newsx.toRichText());
 }

 hashMap0.clear();
 }

 static void tryFillNewsFromFile(const std::string& string, String> var1, Translator.News> hashMap, Language languagex) {
 File file = new File(
 string
 + File.separator
 + "media"
 + File.separator
 + "lua"
 + File.separator
 + "shared"
 + File.separator
 + "Translate"
 + File.separator
 + languagex
 + File.separator
 + "News_"
 + languagex
 + ".txt"
 );
 if (file.exists()) {
 doNews(file, hashMap, languagex);
 }
 }

 static void doNews(File file, Translator.News> hashMap, Language languagex) {
 try (
 FileInputStream fileInputStream = new FileInputStream(file);
 InputStreamReader inputStreamReader = new InputStreamReader(fileInputStream, Charset.forName(languagex.charset()));
 BufferedReader bufferedReader = new BufferedReader(inputStreamReader);
 ) {
 Translator.News newsx = nullptr;
 std::vector arrayList = nullptr;

 std::string string0;
 while ((string0 = bufferedReader.readLine()) != nullptr) {
 if (!string0.trim().empty()) {
 if (string0.startsWith("[VERSION]")) {
 std::string string1 = string0.replaceFirst("\\[VERSION\\]", "").trim();
 if (hashMap.containsKey(string1) {
 newsx = nullptr;
 arrayList = nullptr;
 } else {
 hashMap.put(string1, newsx = new Translator.News(string1);
 arrayList = nullptr;
 }
 }

 if (newsx != nullptr) {
 if (string0.startsWith("[SECTION]")) {
 std::string string2 = string0.replaceFirst("\\[SECTION\\]", "").trim();
 arrayList = newsx.getOrCreateSectionList(string2);
 } else if (string0.startsWith("[NEWS]")) {
 arrayList = newsx.getOrCreateSectionList("[New]");
 } else if (string0.startsWith("[BALANCE]")) {
 arrayList = newsx.getOrCreateSectionList("[Balance]");
 } else if (string0.startsWith("[BUG FIX]")) {
 arrayList = newsx.getOrCreateSectionList("[Bug Fix]");
 } else if (arrayList != nullptr) {
 addNewsLine(string0, arrayList);
 }
 }
 }
 }
 } catch (Exception exception) {
 ExceptionLogger.logException(exception);
 }
 }

 static void addNewsLine(const std::string& string, ArrayList<String> arrayList) {
 if (string.startsWith("[BOLD]")) {
 string = string.replaceFirst("\\[BOLD\\]", "<IMAGE:media/ui/dot.png> <SIZE:medium>");
 arrayList.add(string + " <LINE> ");
 } else if (string.startsWith("[DOT2]")) {
 string = string.replaceFirst("\\[DOT2\\]", "<IMAGE:media/ui/dot2.png> <SIZE:small>");
 arrayList.add(string + " <LINE> ");
 } else if (string.startsWith("[NODOT]")) {
 string = string.replaceFirst("\\[NODOT\\]", " <SIZE:small> ");
 string = string + " <LINE> ";
 arrayList.add(string);
 } else {
 uint8_t byte0 = 7;
 arrayList.add("<IMAGE:media/ui/dot.png> <SIZE:small> " + " <INDENT:%d> ".formatted(21 - byte0) + string + " <INDENT:0> <LINE> ");
 }
 }

 public static ArrayList<String> getNewsVersions() {
 std::vector arrayList = new ArrayList();
 arrayList.addAll(news.keySet());

 for (int int0 = 0; int0 < arrayList.size(); int0++) {
 std::string string = (String)arrayList.get(int0);
 string = string.replace("News_", "");
 string = string.replace("_Disclaimer", "");
 arrayList.set(int0, string);
 }

 Collections.sort(arrayList);
 return arrayList;
 }

 static void tryFillMapFromFile(const std::string& string1, const std::string& string0, String> hashMap, Language languagex) {
 File file = new File(
 string1
 + File.separator
 + "media"
 + File.separator
 + "lua"
 + File.separator
 + "shared"
 + File.separator
 + "Translate"
 + File.separator
 + languagex
 + File.separator
 + string0
 + "_"
 + languagex
 + ".txt"
 );
 if (file.exists()) {
 parseFile(file, hashMap, languagex);
 }
 }

 static void tryFillMapFromMods(const std::string& string1, String> hashMap, Language languagex) {
 std::vector arrayList = ZomboidFileSystem.instance.getModIDs();

 for (int int0 = arrayList.size() - 1; int0 >= 0; int0--) {
 std::string string0 = ZomboidFileSystem.instance.getModDir((String)arrayList.get(int0);
 if (string0 != nullptr) {
 tryFillMapFromFile(string0, string1, hashMap, languagex);
 }
 }
 }

 static void addLanguageToList(Language _language, ArrayList<Language> languages) {
 if (_language != nullptr) {
 if (!languages.contains(_language) {
 languages.add(_language);
 if (_language.base() != nullptr) {
 _language = Languages.instance.getByName(_language.base());
 addLanguageToList(_language, languages);
 }
 }
 }
 }

 static void fillMapFromFile(const std::string& string, String> hashMap) {
 std::vector arrayList = new ArrayList();
 addLanguageToList(getLanguage(), arrayList);
 addLanguageToList(getDefaultLanguage(), arrayList);

 for (int int0 = 0; int0 < arrayList.size(); int0++) {
 Language languagex = (Language)arrayList.get(int0);
 tryFillMapFromMods(string, hashMap, languagex);
 tryFillMapFromFile(ZomboidFileSystem.instance.base.getPath(), string, hashMap, languagex);
 }

 arrayList.clear();
 }

 static void parseFile(File file, String> hashMap, Language languagex) {
 std::string string0 = nullptr;

 try (
 FileInputStream fileInputStream = new FileInputStream(file);
 InputStreamReader inputStreamReader = new InputStreamReader(fileInputStream, Charset.forName(languagex.charset()));
 BufferedReader bufferedReader = new BufferedReader(inputStreamReader);
 ) {
 bufferedReader.readLine();
 bool boolean0 = false;
 std::string string1 = "";
 std::string string2 = "";
 int int0 = 1;
 std::string string3 = file.getName().replace("_" + getDefaultLanguage(), "_" + getLanguage());

 while ((string0 = bufferedReader.readLine()) != nullptr) {
 int0++;

 try {
 if (string0.contains("=") && string0.contains("\"")) {
 if (string0.trim().startsWith("Recipe_")) {
 string1 = string0.split("=")[0].replaceAll("Recipe_", "").replaceAll("_", " ").trim();
 string2 = string0.split("=")[1];
 string2 = string2.substring(string2.indexOf("\"") + 1, string2.lastIndexOf("\""));
 } else if (string0.trim().startsWith("DisplayName")) {
 String[] strings0 = string0.split("=");
 if (string0.trim().startsWith("DisplayName_")) {
 string1 = strings0[0].replaceAll("DisplayName_", "").trim();
 } else {
 string1 = strings0[0].replaceAll("DisplayName", "").trim();
 }

 if ("Anti_depressants" == string1) {
 string1 = "Antidepressants";
 }

 string2 = strings0[1];
 string2 = string2.substring(string2.indexOf("\"") + 1, string2.lastIndexOf("\""));
 } else if (string0.trim().startsWith("EvolvedRecipeName_")) {
 String[] strings1 = string0.split("=");
 string1 = strings1[0].replaceAll("EvolvedRecipeName_", "").trim();
 string2 = strings1[1];
 int int1 = string2.indexOf("\"");
 int int2 = string2.lastIndexOf("\"");
 string2 = string2.substring(int1 + 1, int2);
 } else if (string0.trim().startsWith("ItemName_")) {
 String[] strings2 = string0.split("=");
 string1 = strings2[0].replaceAll("ItemName_", "").trim();
 string2 = strings2[1];
 int int3 = string2.indexOf("\"");
 int int4 = string2.lastIndexOf("\"");
 string2 = string2.substring(int3 + 1, int4);
 } else {
 string1 = string0.split("=")[0].trim();
 string2 = string0.substring(string0.indexOf("=") + 1);
 string2 = string2.substring(string2.indexOf("\"") + 1, string2.lastIndexOf("\""));
 if (string0.contains("..")) {
 boolean0 = true;
 }
 }
 } else if (string0.contains("--") || string0.trim().empty() || !string0.trim().endsWith("..") && !boolean0) {
 boolean0 = false;
 } else {
 boolean0 = true;
 string2 = string2 + string0.substring(string0.indexOf("\"") + 1, string0.lastIndexOf("\""));
 }

 if (!boolean0 || !string0.trim().endsWith("..")) {
 if (!string1.empty()) {
 if (!hashMap.containsKey(string1) {
 hashMap.put(string1, string2);
 if (hashMap == recordedMedia && languagex == getDefaultLanguage()) {
 recordedMedia_EN.put(string1, string2);
 }

 if (debug && languagex == getDefaultLanguage() && getLanguage() != getDefaultLanguage()) {
 if (string3 != nullptr) {
 debugwrite(string3 + "\r\n");
 string3 = nullptr;
 }

 debugwrite("\t" + string1 + " = \"" + string2 + "\",\r\n");
 debugErrors = true;
 }
 } else if (debug && languagex == getDefaultLanguage() && getLanguage() != getDefaultLanguage()) {
 std::string string4 = (String)hashMap.get(string1);
 if (countSubstitutions(string4) != countSubstitutions(string2) {
 debugwrite(
 "wrong number of % substitutions in "
 + string1
 + " "
 + getDefaultLanguage()
 + "=\""
 + string2
 + "\" "
 + getLanguage()
 + "=\""
 + string4
 + "\"\r\n"
 );
 debugErrors = true;
 }
 }
 }

 boolean0 = false;
 string2 = "";
 string1 = "";
 }
 } catch (Exception exception0) {
 if (debug) {
 if (string3 != nullptr) {
 debugwrite(string3 + "\r\n");
 string3 = nullptr;
 }

 debugwrite("line " + int0 + ": " + string1 + " = " + string2 + "\r\n");
 if (debugFile != nullptr) {
 exception0.printStackTrace(new PrintWriter(debugFile);
 }

 debugwrite("\r\n");
 debugErrors = true;
 }
 }
 }
 } catch (Exception exception1) {
 exception1.printStackTrace();
 }
 }

 /**
 * Return the translated text for the selected language If we don't fnid any translation for the selected language, we return the default text (in English)
 */
 static std::string getText(const std::string& desc) {
 return getTextInternal();
 }

 static std::string getTextOrNull(const std::string& desc) {
 return getTextInternal();
 }

 static std::string getTextInternal(const std::string& string1, bool boolean0) {
 if (ui.empty()) {
 loadFiles();
 }

 std::string string0 = nullptr;
 if (string1.startsWith("UI_")) {
 string0 = ui.get(string1);
 } else if (string1.startsWith("Moodles_")) {
 string0 = moodles.get(string1);
 } else if (string1.startsWith("SurvivalGuide_")) {
 string0 = survivalGuide.get(string1);
 } else if (string1.startsWith("Farming_")) {
 string0 = farming.get(string1);
 } else if (string1.startsWith("IGUI_")) {
 string0 = igui.get(string1);
 } else if (string1.startsWith("ContextMenu_")) {
 string0 = contextMenu.get(string1);
 } else if (string1.startsWith("GameSound_")) {
 string0 = gameSound.get(string1);
 } else if (string1.startsWith("Sandbox_")) {
 string0 = sandbox.get(string1);
 } else if (string1.startsWith("Tooltip_")) {
 string0 = tooltip.get(string1);
 } else if (string1.startsWith("Challenge_")) {
 string0 = challenge.get(string1);
 } else if (string1.startsWith("MakeUp")) {
 string0 = makeup.get(string1);
 } else if (string1.startsWith("News_")) {
 string0 = news.get(string1);
 } else if (string1.startsWith("Stash_")) {
 string0 = stash.get(string1);
 } else if (string1.startsWith("RM_")) {
 string0 = recordedMedia.get(string1);
 }

 std::string string2 = Core.bDebug && DebugOptions.instance.TranslationPrefix.getValue() ? "*" : nullptr;
 if (string0.empty()) {
 if (boolean0) {
 return nullptr;
 }

 if (!missing.contains(string1) {
 if (Core.bDebug) {
 DebugLog.log("ERROR: Missing translation \"" + string1 + "\"");
 }

 if (debug) {
 debugwrite("ERROR: Missing translation \"" + string1 + "\"\r\n");
 }

 missing.add(string1);
 }

 string0 = string1;
 string2 = Core.bDebug && DebugOptions.instance.TranslationPrefix.getValue() ? "!" : nullptr;
 }

 if (string0.contains("<br>")) {
 return string0.replaceAll("<br>", "\n");
 } else {
 return string2 = = nullptr ? string0 : string2 + string0;
 }
 }

 static int countSubstitutions(const std::string& string) {
 int int0 = 0;
 if (string.contains("%1")) {
 int0++;
 }

 if (string.contains("%2")) {
 int0++;
 }

 if (string.contains("%3")) {
 int0++;
 }

 if (string.contains("%4")) {
 int0++;
 }

 return int0;
 }

 static std::string subst(const std::string& string0, const std::string& string1, void* object) {
 if (object != nullptr) {
 if (object instanceof Double) {
 double double0 = (Double)object;
 string0 = string0.replaceAll(string1, double0 == (long)double0 ? Long.toString((long)double0) : object.toString());
 } else {
 string0 = string0.replaceAll(string1, Matcher.quoteReplacement(object.toString()));
 }
 }

 return string0;
 }

 static std::string getText(const std::string& desc, void* arg1) {
 std::string string = getText(desc);
 return subst();
 }

 static std::string getText(const std::string& desc, void* arg1, void* arg2) {
 std::string string = getText(desc);
 string = subst(string, "%1", arg1);
 return subst();
 }

 static std::string getText(const std::string& desc, void* arg1, void* arg2, void* arg3) {
 std::string string = getText(desc);
 string = subst(string, "%1", arg1);
 string = subst(string, "%2", arg2);
 return subst();
 }

 static std::string getText(const std::string& desc, void* arg1, void* arg2, void* arg3, void* arg4) {
 std::string string = getText(desc);
 string = subst(string, "%1", arg1);
 string = subst(string, "%2", arg2);
 string = subst(string, "%3", arg3);
 return subst();
 }

 static std::string getTextOrNull(const std::string& desc, void* arg1) {
 std::string string = getTextOrNull(desc);
 return string = = nullptr ? nullptr : subst(string, "%1", arg1);
 }

 static std::string getTextOrNull(const std::string& desc, void* arg1, void* arg2) {
 std::string string = getTextOrNull(desc);
 if (string.empty()) {
 return nullptr;
 } else {
 string = subst(string, "%1", arg1);
 return subst();
 }
 }

 static std::string getTextOrNull(const std::string& desc, void* arg1, void* arg2, void* arg3) {
 std::string string = getTextOrNull(desc);
 if (string.empty()) {
 return nullptr;
 } else {
 string = subst(string, "%1", arg1);
 string = subst(string, "%2", arg2);
 return subst();
 }
 }

 static std::string getTextOrNull(const std::string& desc, void* arg1, void* arg2, void* arg3, void* arg4) {
 std::string string = getTextOrNull(desc);
 if (string.empty()) {
 return nullptr;
 } else {
 string = subst(string, "%1", arg1);
 string = subst(string, "%2", arg2);
 string = subst(string, "%3", arg3);
 return subst();
 }
 }

 static std::string getDefaultText(const std::string& string) {
 return changeSomeStuff();
 }

 static std::string changeSomeStuff(const std::string& string) {
 return string;
 }

 static void setLanguage(Language newlanguage) {
 if (newlanguage.empty()) {
 newlanguage = getDefaultLanguage();
 }

 language = newlanguage;
 }

 static void setLanguage(int languageId) {
 Language languagex = Languages.instance.getByIndex(languageId);
 setLanguage(languagex);
 }

 static Language getLanguage() {
 if (language.empty()) {
 std::string string = Core.getInstance().getOptionLanguageName();
 if (!StringUtils.isNullOrWhitespace(string) {
 language = Languages.instance.getByName(string);
 }
 }

 if (language.empty()) {
 language = Languages.instance.getByName(System.getProperty("user.language").toUpperCase());
 }

 if (language.empty()) {
 language = getDefaultLanguage();
 }

 return language;
 }

 static std::string getCharset() {
 return getLanguage();
 }

 public static ArrayList<Language> getAvailableLanguage() {
 if (availableLanguage.empty()) {
 availableLanguage = std::make_unique<ArrayList<>>();

 for (int int0 = 0; int0 < Languages.instance.getNumLanguages(); int0++) {
 availableLanguage.add(Languages.instance.getByIndex(int0);
 }
 }

 return availableLanguage;
 }

 static std::string getDisplayItemName(const std::string& trim) {
 void* object = nullptr;
 object = items.get(trim.replaceAll(" ", "_").replaceAll("-", "_"));
 return (String)(object.empty() ? trim : object);
 }

 static std::string getItemNameFromFullType(const std::string& fullType) {
 if (!fullType.contains(".")) {
 throw IllegalArgumentException("fullType must contain \".\" i.e. module.type");
 } else {
 std::string string = itemName.get(fullType);
 if (string.empty()) {
 if (debug && getLanguage() != getDefaultLanguage() && !debugItem.contains(fullType) {
 debugItem.add(fullType);
 }

 Item item = ScriptManager.instance.getItem(fullType);
 if (item.empty()) {
 string = fullType;
 } else {
 string = item.getDisplayName();
 }

 itemName.put(fullType, string);
 }

 return string;
 }
 }

 static void setDefaultItemEvolvedRecipeName(const std::string& fullType, const std::string& english) {
 if (getLanguage() == getDefaultLanguage()) {
 if (!fullType.contains(".")) {
 throw IllegalArgumentException("fullType must contain \".\" i.e. module.type");
 } else if (!itemEvolvedRecipeName.containsKey(fullType) {
 itemEvolvedRecipeName.put(fullType, english);
 }
 }
 }

 static std::string getItemEvolvedRecipeName(const std::string& fullType) {
 if (!fullType.contains(".")) {
 throw IllegalArgumentException("fullType must contain \".\" i.e. module.type");
 } else {
 std::string string = itemEvolvedRecipeName.get(fullType);
 if (string.empty()) {
 if (debug && getLanguage() != getDefaultLanguage() && !debugItemEvolvedRecipeName.contains(fullType) {
 debugItemEvolvedRecipeName.add(fullType);
 }

 Item item = ScriptManager.instance.getItem(fullType);
 if (item.empty()) {
 string = fullType;
 } else {
 string = item.getDisplayName();
 }

 itemEvolvedRecipeName.put(fullType, string);
 }

 return string;
 }
 }

 static std::string getMoveableDisplayName(const std::string& name) {
 std::string string0 = name.replaceAll(" ", "_").replaceAll("-", "_").replaceAll("'", "").replaceAll("\\.", "");
 std::string string1 = moveables.get(string0);
 if (string1.empty()) {
 return Core.bDebug && DebugOptions.instance.TranslationPrefix.getValue() ? "!" + name : name;
 } else {
 return Core.bDebug && DebugOptions.instance.TranslationPrefix.getValue() ? "*" + string1 : string1;
 }
 }

 static std::string getMoveableDisplayNameOrNull(const std::string& name) {
 std::string string0 = name.replaceAll(" ", "_").replaceAll("-", "_").replaceAll("'", "").replaceAll("\\.", "");
 std::string string1 = moveables.get(string0);
 if (string1.empty()) {
 return nullptr;
 } else {
 return Core.bDebug && DebugOptions.instance.TranslationPrefix.getValue() ? "*" + string1 : string1;
 }
 }

 static std::string getMultiStageBuild(const std::string& name) {
 std::string string = multiStageBuild.get("MultiStageBuild_" + name);
 if (string.empty()) {
 if (debug && getLanguage() != getDefaultLanguage() && !debugMultiStageBuild.contains(name) {
 debugMultiStageBuild.add(name);
 }

 return name;
 } else {
 return string;
 }
 }

 static std::string getRecipeName(const std::string& name) {
 std::string string = nullptr;
 string = recipe.get(name);
 if (string != nullptr && !string.empty()) {
 return string;
 } else {
 if (debug && getLanguage() != getDefaultLanguage() && !debugRecipe.contains(name) {
 debugRecipe.add(name);
 }

 return name;
 }
 }

 static Language getDefaultLanguage() {
 return Languages.instance.getDefaultLanguage();
 }

 static void debugItemEvolvedRecipeNames() {
 if (debug && !debugItemEvolvedRecipeName.empty()) {
 debugwrite("EvolvedRecipeName_" + getLanguage() + ".txt\r\n");
 std::vector arrayList = new ArrayList();
 arrayList.addAll(debugItemEvolvedRecipeName);
 Collections.sort(arrayList);

 for (auto& string : arrayList) debugwrite("\tEvolvedRecipeName_" + string + " = \"" + itemEvolvedRecipeName.get(string) + "\",\r\n");
 }

 debugItemEvolvedRecipeName.clear();
 }
 }

 static void debugItemNames() {
 if (debug && !debugItem.empty()) {
 debugwrite("ItemName_" + getLanguage() + ".txt\r\n");
 std::vector arrayList = new ArrayList();
 arrayList.addAll(debugItem);
 Collections.sort(arrayList);

 for (auto& string : arrayList) debugwrite("\tItemName_" + string + " = \"" + itemName.get(string) + "\",\r\n");
 }

 debugItem.clear();
 }
 }

 static void debugMultiStageBuildNames() {
 if (debug && !debugMultiStageBuild.empty()) {
 debugwrite("MultiStageBuild_" + getLanguage() + ".txt\r\n");
 std::vector arrayList = new ArrayList();
 arrayList.addAll(debugMultiStageBuild);
 Collections.sort(arrayList);

 for (auto& string : arrayList) debugwrite("\tMultiStageBuild_" + string + " = \"\",\r\n");
 }

 debugMultiStageBuild.clear();
 }
 }

 static void debugRecipeNames() {
 if (debug && !debugRecipe.empty()) {
 debugwrite("Recipes_" + getLanguage() + ".txt\r\n");
 std::vector arrayList = new ArrayList();
 arrayList.addAll(debugRecipe);
 Collections.sort(arrayList);

 for (auto& string : arrayList) debugwrite("\tRecipe_" + string.replace(" ", "_") + " = \"\",\r\n");
 }

 debugRecipe.clear();
 }
 }

 static void debugwrite(const std::string& string) {
 if (debugFile != nullptr) {
 try {
 debugFile.write(string);
 debugFile.flush();
 } catch (IOException iOException) {
 }
 }
 }

 public static ArrayList<String> getAzertyMap() {
 if (azertyLanguages.empty()) {
 azertyLanguages = std::make_unique<ArrayList<>>();
 azertyLanguages.add("FR");
 }

 return azertyLanguages;
 }

 static std::string getRadioText(const std::string& s) {
 std::string string = dynamicRadio.get(s);
 return string = = nullptr ? s : string;
 }

 static std::string getTextMediaEN(const std::string& desc) {
 if (ui.empty()) {
 loadFiles();
 }

 std::string string0 = nullptr;
 if (desc.startsWith("RM_")) {
 string0 = recordedMedia_EN.get(desc);
 }

 std::string string1 = Core.bDebug && DebugOptions.instance.TranslationPrefix.getValue() ? "*" : nullptr;
 if (string0.empty()) {
 if (!missing.contains(desc) && Core.bDebug) {
 if (Core.bDebug) {
 DebugLog.log("ERROR: Missing translation \"" + desc + "\"");
 }

 if (debug) {
 debugwrite("ERROR: Missing translation \"" + desc + "\"\r\n");
 }

 missing.add(desc);
 }

 string0 = desc;
 string1 = Core.bDebug && DebugOptions.instance.TranslationPrefix.getValue() ? "!" : nullptr;
 }

 if (string0.contains("<br>")) {
 return string0.replaceAll("<br>", "\n");
 } else {
 return string1 = = nullptr ? string0 : string1 + string0;
 }
 }

 private static class News {
 std::string version;
 ArrayList<String> sectionNames = std::make_unique<ArrayList<>>();
 HashMap<String, ArrayList<String>> sectionLists = std::make_unique<HashMap<>>();

 News(String string) {
 this->version = string;
 }

 ArrayList<String> getOrCreateSectionList(String string) {
 if (this->sectionNames.contains(string) {
 return this->sectionLists.get(string);
 } else {
 this->sectionNames.add(string);
 std::vector arrayList = new ArrayList();
 this->sectionLists.put(string, arrayList);
 return arrayList;
 }
 }

 std::string toRichText() {
 StringBuilder stringBuilder = new StringBuilder("");

 for (String string0 : this->sectionNames) {
 std::vector arrayList = this->sectionLists.get(string0);
 if (!arrayList.empty()) {
 stringBuilder.append("<LINE> <LEFT> <SIZE:medium> %s <LINE> <LINE> ".formatted(string0);

 for (auto& string1 : arrayList) stringBuilder.append(string1);
 }
 }
 }

 return stringBuilder.toString();
 }
 }
}
} // namespace core
} // namespace zombie
