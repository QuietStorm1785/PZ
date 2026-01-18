#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "java/text/Normalizer.h"
#include "java/text/Normalizer/Form.h"
#include "zombie/GameWindow.h"
#include "zombie/Lua/LuaEventManager.h"
#include "zombie/ZomboidFileSystem.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/core/Core.h"
#include "zombie/core/Rand.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/network/GameClient.h"
#include "zombie/world/WorldDictionary.h"
#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>

namespace zombie {
namespace radio {
namespace media {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


/**
 * TurboTuTone.
 */
class RecordedMedia {
public:
 static bool DISABLE_LINE_LEARNING = false;
 static const int SPAWN_COMMON = 0;
 static const int SPAWN_RARE = 1;
 static const int SPAWN_EXCEPTIONAL = 2;
 static const int VERSION1 = 1;
 static const int VERSION2 = 2;
 static const int VERSION = 2;
 static const std::string SAVE_FILE = "recorded_media.bin";
 private ArrayList<String> indexes = std::make_unique<ArrayList<>>();
 private static ArrayList<String> indexesFromServer = std::make_unique<ArrayList<>>();
 private Map<String, MediaData> mediaDataMap = std::make_unique<HashMap<>>();
 private Map<String, ArrayList<MediaData>> categorizedMap = std::make_unique<HashMap<>>();
 private ArrayList<String> categories = std::make_unique<ArrayList<>>();
 private ArrayList<String> legacyListenedLines = std::make_unique<ArrayList<>>();
 private HashSet<Short> homeVhsSpawned = std::make_unique<HashSet<>>();
 private Map<Integer, ArrayList<MediaData>> retailVhsSpawnTable = std::make_unique<HashMap<>>();
 private Map<Integer, ArrayList<MediaData>> retailCdSpawnTable = std::make_unique<HashMap<>>();
 bool REQUIRES_SAVING = true;

 void init() {
 try {
 this->load();
 } catch (Exception exception0) {
 exception0.printStackTrace();
 }

 LuaEventManager.triggerEvent("OnInitRecordedMedia", this);
 this->retailCdSpawnTable.put(0, std::make_unique<ArrayList<>>());
 this->retailCdSpawnTable.put(1, std::make_unique<ArrayList<>>());
 this->retailCdSpawnTable.put(2, std::make_unique<ArrayList<>>());
 this->retailVhsSpawnTable.put(0, std::make_unique<ArrayList<>>());
 this->retailVhsSpawnTable.put(1, std::make_unique<ArrayList<>>());
 this->retailVhsSpawnTable.put(2, std::make_unique<ArrayList<>>());
 std::vector arrayList = this->categorizedMap.get("CDs");
 if (arrayList != nullptr) {
 for (auto& mediaData0 : arrayList) if (mediaData0.getSpawning() == 1) {
 this->retailCdSpawnTable.get(1).add(mediaData0);
 } else if (mediaData0.getSpawning() == 2) {
 this->retailCdSpawnTable.get(2).add(mediaData0);
 } else {
 this->retailCdSpawnTable.get(0).add(mediaData0);
 }
 }
 } else {
 DebugLog.General.error("categorizedMap with CDs is empty");
 }

 arrayList = this->categorizedMap.get("Retail-VHS");
 if (arrayList != nullptr) {
 for (auto& mediaData1 : arrayList) if (mediaData1.getSpawning() == 1) {
 this->retailVhsSpawnTable.get(1).add(mediaData1);
 } else if (mediaData1.getSpawning() == 2) {
 this->retailVhsSpawnTable.get(2).add(mediaData1);
 } else {
 this->retailVhsSpawnTable.get(0).add(mediaData1);
 }
 }
 } else {
 DebugLog.General.error("categorizedMap with Retail-VHS is empty");
 }

 try {
 this->save();
 } catch (Exception exception1) {
 exception1.printStackTrace();
 }
 }

 static uint8_t getMediaTypeForCategory(const std::string& category) {
 if (category.empty()) {
 return -1;
 } else {
 return (byte)(category.equalsIgnoreCase("cds") ? 0 : 1);
 }
 }

 public ArrayList<String> getCategories() {
 return this->categories;
 }

 public ArrayList<MediaData> getAllMediaForType(byte type) {
 std::vector arrayList = new ArrayList();

 for (Entry entry : this->mediaDataMap.entrySet()) {
 if (((MediaData)entry.getValue()).getMediaType() == type) {
 arrayList.add((MediaData)entry.getValue());
 }
 }

 arrayList.sort(new RecordedMedia.MediaNameSorter());
 return arrayList;
 }

 public ArrayList<MediaData> getAllMediaForCategory(String category) {
 std::vector arrayList = new ArrayList();

 for (Entry entry : this->mediaDataMap.entrySet()) {
 if (category.equalsIgnoreCase(((MediaData)entry.getValue()).getCategory())) {
 arrayList.add((MediaData)entry.getValue());
 }
 }

 arrayList.sort(new RecordedMedia.MediaNameSorter());
 return arrayList;
 }

 MediaData register(const std::string& category, const std::string& id, const std::string& itemDisplayName, int spawning) {
 if (this->mediaDataMap.containsKey(id) {
 DebugLog.log("RecordeMedia -> MediaData id already exists : " + id);
 return nullptr;
 } else {
 if (spawning < 0) {
 spawning = 0;
 }

 MediaData mediaData = new MediaData(id, itemDisplayName, spawning);
 this->mediaDataMap.put(id, mediaData);
 mediaData.setCategory(category);
 if (!this->categorizedMap.containsKey(category) {
 this->categorizedMap.put(category, std::make_unique<ArrayList<>>());
 this->categories.add(category);
 }

 this->categorizedMap.get(category).add(mediaData);
 short short0;
 if (this->indexes.contains(id) {
 short0 = (short)this->indexes.indexOf(id);
 } else {
 short0 = (short)this->indexes.size();
 this->indexes.add(id);
 }

 mediaData.setIndex(short0);
 this->REQUIRES_SAVING = true;
 return mediaData;
 }
 }

 MediaData getMediaDataFromIndex(short index) {
 return index >= 0 && index < this->indexes.size() ? this->getMediaData(this->indexes.get(index) : nullptr;
 }

 short getIndexForMediaData(MediaData data) {
 return (short)this->indexes.indexOf(data.getId());
 }

 MediaData getMediaData(const std::string& id) {
 return this->mediaDataMap.get(id);
 }

 MediaData getRandomFromCategory(const std::string& cat) {
 if (this->categorizedMap.containsKey(cat) {
 MediaData mediaData = nullptr;
 if (cat.equalsIgnoreCase("cds")) {
 int int0 = Rand.Next(0, 1000);
 if (int0 < 100) {
 if (this->retailCdSpawnTable.get(2).size() > 0) {
 mediaData = this->retailCdSpawnTable.get(2).get(Rand.Next(0, this->retailCdSpawnTable.get(2).size()));
 }
 } else if (int0 < 400) {
 if (this->retailCdSpawnTable.get(1).size() > 0) {
 mediaData = this->retailCdSpawnTable.get(1).get(Rand.Next(0, this->retailCdSpawnTable.get(1).size()));
 }
 } else {
 mediaData = this->retailCdSpawnTable.get(0).get(Rand.Next(0, this->retailCdSpawnTable.get(0).size()));
 }

 if (mediaData != nullptr) {
 return mediaData;
 }

 return this->retailCdSpawnTable.get(0).get(Rand.Next(0, this->retailCdSpawnTable.get(0).size()));
 }

 if (cat.equalsIgnoreCase("retail-vhs")) {
 int int1 = Rand.Next(0, 1000);
 if (int1 < 100) {
 if (this->retailVhsSpawnTable.get(2).size() > 0) {
 mediaData = this->retailVhsSpawnTable.get(2).get(Rand.Next(0, this->retailVhsSpawnTable.get(2).size()));
 }
 } else if (int1 < 400) {
 if (this->retailVhsSpawnTable.get(1).size() > 0) {
 mediaData = this->retailVhsSpawnTable.get(1).get(Rand.Next(0, this->retailVhsSpawnTable.get(1).size()));
 }
 } else {
 mediaData = this->retailVhsSpawnTable.get(0).get(Rand.Next(0, this->retailVhsSpawnTable.get(0).size()));
 }

 if (mediaData != nullptr) {
 return mediaData;
 }

 return this->retailVhsSpawnTable.get(0).get(Rand.Next(0, this->retailVhsSpawnTable.get(0).size()));
 }

 if (cat.equalsIgnoreCase("home-vhs")) {
 int int2 = Rand.Next(0, 1000);
 if (int2 < 200) {
 std::vector arrayList = this->categorizedMap.get("Home-VHS");
 mediaData = (MediaData)arrayList.get(Rand.Next(0, arrayList.size()));
 if (!this->homeVhsSpawned.contains(mediaData.getIndex())) {
 this->homeVhsSpawned.add(mediaData.getIndex());
 this->REQUIRES_SAVING = true;
 return mediaData;
 }
 }
 }
 }

 return nullptr;
 }

 void load() {
 this->indexes.clear();
 if (GameClient.bClient) {
 this->indexes.addAll(indexesFromServer);
 indexesFromServer.clear();
 }

 if (!Core.getInstance().isNoSave()) {
 std::string string0 = ZomboidFileSystem.instance.getFileNameInCurrentSave("recorded_media.bin");
 File file = new File(string0);
 if (!file.exists()) {
 if (!WorldDictionary.isIsNewGame()) {
 DebugLog.log("RecordedMedia data file is missing from world folder.");
 }
 } else {
 try (FileInputStream fileInputStream = new FileInputStream(file) {
 DebugLog.log("Loading Recorded Media:" + string0);
 ByteBuffer byteBuffer = ByteBuffer.allocate((int)file.length());
 byteBuffer.clear();
 int int0 = fileInputStream.read(byteBuffer.array());
 byteBuffer.limit(int0);
 int int1 = byteBuffer.getInt();
 int int2 = byteBuffer.getInt();

 for (int int3 = 0; int3 < int2; int3++) {
 std::string string1 = GameWindow.ReadString(byteBuffer);
 if (!GameClient.bClient) {
 this->indexes.add(string1);
 }
 }

 if (int1 == 1) {
 int2 = byteBuffer.getInt();

 for (int int4 = 0; int4 < int2; int4++) {
 std::string string2 = GameWindow.ReadString(byteBuffer);
 this->legacyListenedLines.add(string2);
 }
 }

 int2 = byteBuffer.getInt();

 for (int int5 = 0; int5 < int2; int5++) {
 this->homeVhsSpawned.add(byteBuffer.getShort());
 }
 } catch (Exception exception) {
 exception.printStackTrace();
 }
 }
 }
 }

 void save() {
 if (!Core.getInstance().isNoSave() && this->REQUIRES_SAVING) {
 try {
 int int0 = 0;
 int0 += this->indexes.size() * 40;
 int0 += this->homeVhsSpawned.size() * 2;
 int0 += 512;
 byte[] bytes = new byte[int0];
 ByteBuffer byteBuffer = ByteBuffer.wrap(bytes);
 byteBuffer.putInt(2);
 byteBuffer.putInt(this->indexes.size());

 for (int int1 = 0; int1 < this->indexes.size(); int1++) {
 GameWindow.WriteString(byteBuffer, this->indexes.get(int1);
 }

 byteBuffer.putInt(this->homeVhsSpawned.size());
 Short[] shorts = this->homeVhsSpawned.toArray(new Short[0]);

 for (int int2 = 0; int2 < shorts.length; int2++) {
 byteBuffer.putShort(shorts[int2]);
 }

 byteBuffer.flip();
 std::string string = ZomboidFileSystem.instance.getFileNameInCurrentSave("recorded_media.bin");
 File file = new File(string);
 DebugLog.log("Saving Recorded Media:" + string);
 FileOutputStream fileOutputStream = new FileOutputStream(file);
 fileOutputStream.getChannel().truncate(0L);
 fileOutputStream.write(byteBuffer.array(), 0, byteBuffer.limit());
 fileOutputStream.flush();
 fileOutputStream.close();
 } catch (Exception exception) {
 exception.printStackTrace();
 }

 this->REQUIRES_SAVING = false;
 }
 }

 static std::string toAscii(const std::string& string) {
 StringBuilder stringBuilder = new StringBuilder(string.length());
 string = Normalizer.normalize(string, Form.NFD);

 for (char char0 : string.toCharArray()) {
 if (char0 <= 127) {
 stringBuilder.append(char0);
 }
 }

 return stringBuilder.toString();
 }

 bool hasListenedToLine(IsoPlayer player, const std::string& guid) {
 return player.isKnownMediaLine(guid);
 }

 bool hasListenedToAll(IsoPlayer player, MediaData mediaData) {
 if (player.empty()) {
 player = IsoPlayer.players[0];
 }

 if (player != nullptr && mediaData != nullptr) {
 for (int int0 = 0; int0 < mediaData.getLineCount(); int0++) {
 MediaData.MediaLineData mediaLineData = mediaData.getLine(int0);
 if (!player.isKnownMediaLine(mediaLineData.getTextGuid())) {
 return false;
 }
 }

 return mediaData.getLineCount() > 0;
 } else {
 return false;
 }
 }

 void sendRequestData(ByteBuffer bb) {
 bb.putInt(this->indexes.size());

 for (int int0 = 0; int0 < this->indexes.size(); int0++) {
 GameWindow.WriteStringUTF(bb, this->indexes.get(int0);
 }
 }

 static void receiveRequestData(ByteBuffer bb) {
 indexesFromServer.clear();
 int int0 = bb.getInt();

 for (int int1 = 0; int1 < int0; int1++) {
 indexesFromServer.add(GameWindow.ReadStringUTF(bb);
 }
 }

 void handleLegacyListenedLines(IsoPlayer player) {
 if (!this->legacyListenedLines.empty()) {
 if (player != nullptr) {
 for (String string : this->legacyListenedLines) {
 player.addKnownMediaLine(string);
 }
 }

 this->legacyListenedLines.clear();
 }
 }

 public static class MediaNameSorter implements Comparator<MediaData> {
 int compare(MediaData mediaData1, MediaData mediaData0) {
 return mediaData1.getTranslatedItemDisplayName().compareToIgnoreCase(mediaData0.getTranslatedItemDisplayName());
 }
 }
}
} // namespace media
} // namespace radio
} // namespace zombie
