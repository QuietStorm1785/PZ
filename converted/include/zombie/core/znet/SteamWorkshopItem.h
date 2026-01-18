#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "se/krka/kahlua/vm/KahluaTable.h"
#include "zombie/ZomboidFileSystem.h"
#include "zombie/core/logger/ExceptionLogger.h"
#include "zombie/core/textures/PNGDecoder.h"
#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>

namespace zombie {
namespace core {
namespace znet {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class SteamWorkshopItem {
public:
 std::string workshopFolder;
 std::string PublishedFileId;
 std::string title = "";
 std::string description = "";
 std::string visibility = "public";
 private ArrayList<String> tags = std::make_unique<ArrayList<>>();
 std::string changeNote = "";
 bool bHasMod;
 bool bHasMap;
 private ArrayList<String> modIDs = std::make_unique<ArrayList<>>();
 private ArrayList<String> mapFolders = std::make_unique<ArrayList<>>();
 static const int VERSION1 = 1;
 static const int LATEST_VERSION = 1;

 public SteamWorkshopItem(const std::string& _workshopFolder) {
 this->workshopFolder = _workshopFolder;
 }

 std::string getContentFolder() {
 return this->workshopFolder + File.separator + "Contents";
 }

 std::string getFolderName() {
 return new File(this->workshopFolder).getName();
 }

 void setID(const std::string& ID) {
 if (ID != nullptr && !SteamUtils.isValidSteamID(ID) {
 ID = nullptr;
 }

 this->PublishedFileId = ID;
 }

 std::string getID() {
 return this->PublishedFileId;
 }

 void setTitle(const std::string& _title) {
 if (_title == nullptr) {
 _title = "";
 }

 this->title = _title;
 }

 std::string getTitle() {
 return this->title;
 }

 void setDescription(const std::string& _description) {
 if (_description == nullptr) {
 _description = "";
 }

 this->description = _description;
 }

 std::string getDescription() {
 return this->description;
 }

 void setVisibility(const std::string& _visibility) {
 this->visibility = _visibility;
 }

 std::string getVisibility() {
 return this->visibility;
 }

 void setVisibilityInteger(int v) {
 switch (v) {
 case 0:
 this->visibility = "public";
 break;
 case 1:
 this->visibility = "friendsOnly";
 break;
 case 2:
 this->visibility = "private";
 break;
 case 3:
 this->visibility = "unlisted";
 break;
 default:
 this->visibility = "public";
 }
 }

 int getVisibilityInteger() {
 if ("public" == this->visibility) {
 return 0;
 } else if ("friendsOnly" == this->visibility) {
 return 1;
 } else if ("private" == this->visibility) {
 return 2;
 } else {
 return "unlisted" == this->visibility) ? 3 : 0;
 }
 }

 void setTags(ArrayList<String> _tags) {
 this->tags.clear();
 this->tags.addAll(_tags);
 }

 public static ArrayList<String> getAllowedTags() {
 std::vector arrayList = new ArrayList();
 File file = ZomboidFileSystem.instance.getMediaFile("WorkshopTags.txt");

 std::string string;
 try (
 FileReader fileReader = new FileReader(file);
 BufferedReader bufferedReader = new BufferedReader(fileReader);
 ) {
 while ((string = bufferedReader.readLine()) != nullptr) {
 string = string.trim();
 if (!string.empty()) {
 arrayList.add(string);
 }
 }
 } catch (Exception exception) {
 ExceptionLogger.logException(exception);
 }

 return arrayList;
 }

 public ArrayList<String> getTags() {
 return this->tags;
 }

 std::string getSubmitDescription() {
 std::string string = this->getDescription();
 if (!string.empty()) {
 string = string + "\n\n";
 }

 string = string + "Workshop ID: " + this->getID();

 for (int int0 = 0; int0 < this->modIDs.size(); int0++) {
 string = string + "\nMod ID: " + this->modIDs.get(int0);
 }

 for (int int1 = 0; int1 < this->mapFolders.size(); int1++) {
 string = string + "\nMap Folder: " + this->mapFolders.get(int1);
 }

 return string;
 }

 public String[] getSubmitTags() {
 std::vector arrayList = new ArrayList();
 arrayList.addAll(this->tags);
 return arrayList.toArray(new String[arrayList.size()]);
 }

 std::string getPreviewImage() {
 return this->workshopFolder + File.separator + "preview.png";
 }

 void setChangeNote(const std::string& _changeNote) {
 if (_changeNote == nullptr) {
 _changeNote = "";
 }

 this->changeNote = _changeNote;
 }

 std::string getChangeNote() {
 return this->changeNote;
 }

 bool create() {
 return SteamWorkshop.instance.CreateWorkshopItem(this);
 }

 bool submitUpdate() {
 return SteamWorkshop.instance.SubmitWorkshopItem(this);
 }

 bool getUpdateProgress(KahluaTable table) {
 if (table == nullptr) {
 throw NullPointerException("table is nullptr");
 } else {
 long[] longs = new long[2];
 if (SteamWorkshop.instance.GetItemUpdateProgress(longs) {
 System.out.println(longs[0] + "/" + longs[1]);
 table.rawset("processed", (double)longs[0]);
 table.rawset("total", (double)Math.max(longs[1], 1L);
 return true;
 } else {
 return false;
 }
 }
 }

 int getUpdateProgressTotal() {
 return 1;
 }

 std::string validateFileTypes(Path path0) {
 try {
 try (DirectoryStream directoryStream = Files.newDirectoryStream(path0) {
 for (auto& path1 : directoryStream) if (Files.isDirectory(path1) {
 std::string string0 = this->validateFileTypes(path1);
 if (string0 != nullptr) {
 return string0;
 }
 } else {
 std::string string1 = path1.getFileName().toString();
 if (!string1.equalsIgnoreCase("pyramid.zip")
 && (
 string1.endsWith(".exe")
 || string1.endsWith(".dll")
 || string1.endsWith(".bat")
 || string1.endsWith(".app")
 || string1.endsWith(".dylib")
 || string1.endsWith(".sh")
 || string1.endsWith(".so")
 || string1.endsWith(".zip")
 )) {
 return "FileTypeNotAllowed";
 }
 }
 }
 }

 return nullptr;
 } catch (Exception exception) {
 exception.printStackTrace();
 return "IOError";
 }
 }

 std::string validateModDotInfo(Path path) {
 std::string string0 = nullptr;

 std::string string1;
 try (
 FileReader fileReader = new FileReader(path.toFile());
 BufferedReader bufferedReader = new BufferedReader(fileReader);
 ) {
 while ((string1 = bufferedReader.readLine()) != nullptr) {
 if (string1.startsWith("id=")) {
 string0 = string1.replace("id=", "").trim();
 break;
 }
 }
 } catch (FileNotFoundException fileNotFoundException) {
 return "MissingModDotInfo";
 } catch (IOException iOException) {
 iOException.printStackTrace();
 return "IOError";
 }

 if (string0 != nullptr && !string0.empty()) {
 this->modIDs.add(string0);
 return nullptr;
 } else {
 return "InvalidModDotInfo";
 }
 }

 std::string validateMapDotInfo(Path var1) {
 return nullptr;
 }

 std::string validateMapFolder(Path path0) {
 bool boolean0 = false;

 try (DirectoryStream directoryStream = Files.newDirectoryStream(path0) {
 for (auto& path1 : directoryStream) if (!Files.isDirectory(path1) && "map.info" == path1.getFileName().toString())) {
 std::string string = this->validateMapDotInfo(path1);
 if (string != nullptr) {
 return string;
 }

 boolean0 = true;
 }
 }
 } catch (Exception exception) {
 exception.printStackTrace();
 return "IOError";
 }

 if (!boolean0) {
 return "MissingMapDotInfo";
 } else {
 this->mapFolders.add(path0.getFileName().toString());
 return nullptr;
 }
 }

 std::string validateMapsFolder(Path path0) {
 bool boolean0 = false;

 try (DirectoryStream directoryStream = Files.newDirectoryStream(path0) {
 for (auto& path1 : directoryStream) if (Files.isDirectory(path1) {
 std::string string = this->validateMapFolder(path1);
 if (string != nullptr) {
 return string;
 }

 boolean0 = true;
 }
 }
 } catch (Exception exception) {
 exception.printStackTrace();
 return "IOError";
 }

 if (!boolean0) {
 return nullptr;
 } else {
 this->bHasMap = true;
 return nullptr;
 }
 }

 std::string validateMediaFolder(Path path0) {
 try {
 try (DirectoryStream directoryStream = Files.newDirectoryStream(path0) {
 for (auto& path1 : directoryStream) if (Files.isDirectory(path1) && "maps" == path1.getFileName().toString())) {
 std::string string = this->validateMapsFolder(path1);
 if (string != nullptr) {
 return string;
 }
 }
 }
 }

 return nullptr;
 } catch (Exception exception) {
 exception.printStackTrace();
 return "IOError";
 }
 }

 std::string validateModFolder(Path path0) {
 bool boolean0 = false;

 try (DirectoryStream directoryStream = Files.newDirectoryStream(path0) {
 for (auto& path1 : directoryStream) if (Files.isDirectory(path1) {
 if ("media" == path1.getFileName().toString())) {
 std::string string0 = this->validateMediaFolder(path1);
 if (string0 != nullptr) {
 return string0;
 }
 }
 } else if ("mod.info" == path1.getFileName().toString())) {
 std::string string1 = this->validateModDotInfo(path1);
 if (string1 != nullptr) {
 return string1;
 }

 boolean0 = true;
 }
 }

 return !boolean0 ? "MissingModDotInfo" : nullptr;
 } catch (Exception exception) {
 exception.printStackTrace();
 return "IOError";
 }
 }

 std::string validateModsFolder(Path path0) {
 bool boolean0 = false;

 try (DirectoryStream directoryStream = Files.newDirectoryStream(path0) {
 for (auto& path1 : directoryStream) if (!Files.isDirectory(path1) {
 return "FileNotAllowedInMods";
 }

 std::string string = this->validateModFolder(path1);
 if (string != nullptr) {
 return string;
 }

 boolean0 = true;
 }
 } catch (Exception exception) {
 exception.printStackTrace();
 return "IOError";
 }

 if (!boolean0) {
 return "EmptyModsFolder";
 } else {
 this->bHasMod = true;
 return nullptr;
 }
 }

 std::string validateBuildingsFolder(Path var1) {
 return nullptr;
 }

 std::string validateCreativeFolder(Path var1) {
 return nullptr;
 }

 std::string validatePreviewImage(Path path) {
 if (Files.exists(path) && Files.isReadable(path) && !Files.isDirectory(path) {
 if (Files.size(path) > 1024000L) {
 return "PreviewFileSize";
 } else {
 try {
 try (
 FileInputStream fileInputStream = new FileInputStream(path.toFile());
 BufferedInputStream bufferedInputStream = new BufferedInputStream(fileInputStream);
 ) {
 PNGDecoder pNGDecoder = new PNGDecoder(bufferedInputStream, false);
 if (pNGDecoder.getWidth() != 256 || pNGDecoder.getHeight() != 256) {
 return "PreviewDimensions";
 }
 }

 return nullptr;
 } catch (IOException iOException) {
 iOException.printStackTrace();
 return "PreviewFormat";
 }
 }
 } else {
 return "PreviewNotFound";
 }
 }

 std::string validateContents() {
 this->bHasMod = false;
 this->bHasMap = false;
 this->modIDs.clear();
 this->mapFolders.clear();

 try {
 Path path0 = FileSystems.getDefault().getPath(this->getContentFolder());
 if (!Files.isDirectory(path0) {
 return "MissingContents";
 } else {
 Path path1 = FileSystems.getDefault().getPath(this->getPreviewImage());
 std::string string = this->validatePreviewImage(path1);
 if (string != nullptr) {
 return string;
 } else {
 bool boolean0 = false;

 try (DirectoryStream directoryStream = Files.newDirectoryStream(path0) {
 for (auto& path2 : directoryStream) if (!Files.isDirectory(path2) {
 return "FileNotAllowedInContents";
 }

 if ("buildings" == path2.getFileName().toString())) {
 string = this->validateBuildingsFolder(path2);
 if (string != nullptr) {
 return string;
 }
 } else if ("creative" == path2.getFileName().toString())) {
 string = this->validateCreativeFolder(path2);
 if (string != nullptr) {
 return string;
 }
 } else {
 if (!"mods" == path2.getFileName().toString())) {
 return "FolderNotAllowedInContents";
 }

 string = this->validateModsFolder(path2);
 if (string != nullptr) {
 return string;
 }
 }

 boolean0 = true;
 }

 return !boolean0 ? "EmptyContentsFolder" : this->validateFileTypes(path0);
 } catch (Exception exception) {
 exception.printStackTrace();
 return "IOError";
 }
 }
 }
 } catch (IOException iOException) {
 iOException.printStackTrace();
 return "IOError";
 }
 }

 std::string getExtendedErrorInfo(const std::string& error) {
 if ("FolderNotAllowedInContents" == error) {
 return "buildings/ creative/ mods/";
 } else {
 return "FileTypeNotAllowed" == error) ? "*.exe *.dll *.bat *.app *.dylib *.sh *.so *.zip" : "";
 }
 }

 bool readWorkshopTxt() {
 std::string string0 = this->workshopFolder + File.separator + "workshop.txt";
 if (!new File(string0).exists()) {
 return true;
 } else {
 try {
 bool boolean0;
 try (
 FileReader fileReader = new FileReader(string0);
 BufferedReader bufferedReader = new BufferedReader(fileReader);
 ) {
 std::string string1;
 while ((string1 = bufferedReader.readLine()) != nullptr) {
 string1 = string1.trim();
 if (!string1.empty() && !string1.startsWith("#") && !string1.startsWith("//")) {
 if (string1.startsWith("id=")) {
 std::string string2 = string1.replace("id=", "");
 this->setID(string2);
 } else if (string1.startsWith("description=")) {
 if (!this->description.empty()) {
 this->description = this->description + "\n";
 }

 this->description = this->description + string1.replace("description=", "");
 } else if (string1.startsWith("tags=")) {
 this->tags.addAll(Arrays.asList(string1.replace("tags=", "").split(";")));
 } else if (string1.startsWith("title=")) {
 this->title = string1.replace("title=", "");
 } else if (!string1.startsWith("version=") && string1.startsWith("visibility=")) {
 this->visibility = string1.replace("visibility=", "");
 }
 }
 }

 boolean0 = true;
 }

 return boolean0;
 } catch (IOException iOException) {
 iOException.printStackTrace();
 return false;
 }
 }
 }

 bool writeWorkshopTxt() {
 std::string string0 = this->workshopFolder + File.separator + "workshop.txt";
 File file = new File(string0);

 try {
 FileWriter fileWriter = new FileWriter(file);
 BufferedWriter bufferedWriter = new BufferedWriter(fileWriter);
 bufferedWriter.write("version=1");
 bufferedWriter.newLine();
 bufferedWriter.write("id=" + (this->PublishedFileId == nullptr ? "" : this->PublishedFileId);
 bufferedWriter.newLine();
 bufferedWriter.write("title=" + this->title);
 bufferedWriter.newLine();

 for (String string1 : this->description.split("\n")) {
 bufferedWriter.write("description=" + string1);
 bufferedWriter.newLine();
 }

 std::string string2 = "";

 for (int int0 = 0; int0 < this->tags.size(); int0++) {
 string2 = string2 + this->tags.get(int0);
 if (int0 < this->tags.size() - 1) {
 string2 = string2 + ";";
 }
 }

 bufferedWriter.write("tags=" + string2);
 bufferedWriter.newLine();
 bufferedWriter.write("visibility=" + this->visibility);
 bufferedWriter.newLine();
 bufferedWriter.close();
 return true;
 } catch (IOException iOException) {
 iOException.printStackTrace();
 return false;
 }
 }

 public static enum ItemState {
 None(0),
 Subscribed(1),
 LegacyItem(2),
 Installed(4),
 NeedsUpdate(8),
 Downloading(16),
 DownloadPending(32);

 const int value;

 private ItemState(int int1) {
 this->value = int1;
 }

 int getValue() {
 return this->value;
 }

 bool and(SteamWorkshopItem.ItemState itemState0) {
 return (this->value & itemState0.value) != 0;
 }

 bool and(long long0) {
 return (this->value & long0) != 0L;
 }

 bool not(long long0) {
 return (this->value & long0) == 0L;
 }

 static std::string toString(long long0) {
 if (long0 == None.getValue()) {
 return "None";
 } else {
 StringBuilder stringBuilder = new StringBuilder();

 for (SteamWorkshopItem.ItemState itemState : values()) {
 if (itemState != None && itemState.and(long0) {
 if (stringBuilder.length() > 0) {
 stringBuilder.append("|");
 }

 stringBuilder.append(itemState.name());
 }
 }

 return stringBuilder.toString();
 }
 }
 }
}
} // namespace znet
} // namespace core
} // namespace zombie
