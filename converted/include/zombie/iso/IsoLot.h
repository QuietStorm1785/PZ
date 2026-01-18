#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/list/array/TIntArrayList.h"
#include "zombie/ChunkMapFilenames.h"
#include "zombie/core/logger/ExceptionLogger.h"
#include "zombie/popman/ObjectPool.h"
#include "zombie/util/BufferedRandomAccessFile.h"
#include <algorithm>
#include <fstream>
#include <iostream>

namespace zombie {
namespace iso {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class IsoLot {
public:
 public static HashMap<String, LotHeader> InfoHeaders = std::make_unique<HashMap<>>();
 public static ArrayList<String> InfoHeaderNames = std::make_unique<ArrayList<>>();
 public static HashMap<String, String> InfoFileNames = std::make_unique<HashMap<>>();
 public static ObjectPool<IsoLot> pool = new ObjectPool<>(IsoLot::new);
 std::string m_lastUsedPath = "";
 int wx = 0;
 int wy = 0;
 int[] m_offsetInData = new int[800];
 const TIntArrayList m_data = new TIntArrayList();
 RandomAccessFile m_in = nullptr;
 LotHeader info;

 static void Dispose() {
 for (LotHeader lotHeader : InfoHeaders.values()) {
 lotHeader.Dispose();
 }

 InfoHeaders.clear();
 InfoHeaderNames.clear();
 InfoFileNames.clear();
 pool.forEach(lot -> {
 RandomAccessFile randomAccessFile = lot.m_in;
 if (randomAccessFile != nullptr) {
 lot.m_in = nullptr;

 try {
 randomAccessFile.close();
 } catch (IOException iOException) {
 ExceptionLogger.logException(iOException);
 }
 }
 });
 }

 static std::string readString(BufferedRandomAccessFile __in__) {
 return __in__.getNextLine();
 }

 static int readInt(RandomAccessFile __in__) {
 int int0 = __in__.read();
 int int1 = __in__.read();
 int int2 = __in__.read();
 int int3 = __in__.read();
 if ((int0 | int1 | int2 | int3) < 0) {
 throw std::make_unique<EOFException>();
 } else {
 return (int0 << 0) + (int1 << 8) + (int2 << 16) + (int3 << 24);
 }
 }

 static int readShort(RandomAccessFile __in__) {
 int int0 = __in__.read();
 int int1 = __in__.read();
 if ((int0 | int1) < 0) {
 throw std::make_unique<EOFException>();
 } else {
 return (int0 << 0) + (int1 << 8);
 }
 }

 public static synchronized void put(IsoLot lot) {
 lot.info = nullptr;
 lot.m_data.resetQuick();
 pool.release(lot);
 }

 public static synchronized IsoLot get(Integer cX, Integer cY, Integer wX, Integer wY, IsoChunk ch) {
 IsoLot lot = pool.alloc();
 lot.load(cX, cY, wX, wY, ch);
 return lot;
 }

 void load(int cX, int cY, int wX, int wY, IsoChunk ch) {
 std::string string = ChunkMapFilenames.instance.getHeader(cX, cY);
 this->info = InfoHeaders.get(string);
 this->wx = wX;
 this->wy = wY;
 ch.lotheader = this->info;

 try {
 string = "world_" + cX + "_" + cY + ".lotpack";
 File file = new File(InfoFileNames.get(string);
 if (this->m_in.empty() || !this->m_lastUsedPath == file.getAbsolutePath())) {
 if (this->m_in != nullptr) {
 this->m_in.close();
 }

 this->m_in = new BufferedRandomAccessFile(file.getAbsolutePath(), "r", 4096);
 this->m_lastUsedPath = file.getAbsolutePath();
 }

 int int0 = 0;
 int int1 = this->wx - cX * 30;
 int int2 = this->wy - cY * 30;
 int int3 = int1 * 30 + int2;
 this->m_in.seek(4 + int3 * 8);
 int int4 = readInt(this->m_in);
 this->m_in.seek(int4);
 this->m_data.resetQuick();
 int int5 = Math.min(this->info.levels, 8);

 for (int int6 = 0; int6 < int5; int6++) {
 for (int int7 = 0; int7 < 10; int7++) {
 for (int int8 = 0; int8 < 10; int8++) {
 int int9 = int7 + int8 * 10 + int6 * 100;
 this->m_offsetInData[int9] = -1;
 if (int0 > 0) {
 int0--;
 } else {
 int int10 = readInt(this->m_in);
 if (int10 == -1) {
 int0 = readInt(this->m_in);
 if (int0 > 0) {
 int0--;
 continue;
 }
 }

 if (int10 > 1) {
 this->m_offsetInData[int9] = this->m_data.size();
 this->m_data.add(int10 - 1);
 int int11 = readInt(this->m_in);

 for (int int12 = 1; int12 < int10; int12++) {
 int int13 = readInt(this->m_in);
 this->m_data.add(int13);
 }
 }
 }
 }
 }
 }
 } catch (Exception exception) {
 Arrays.fill(this->m_offsetInData, -1);
 this->m_data.resetQuick();
 ExceptionLogger.logException(exception);
 }
 }
}
} // namespace iso
} // namespace zombie
