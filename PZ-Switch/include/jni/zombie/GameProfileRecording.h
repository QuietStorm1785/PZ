#pragma once
#include <string>
#include <string_view>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/GameProfileRecording/Row.h"
#include "zombie/GameProfileRecording/Span.h"
#include "zombie/GameProfiler/ProfileArea.h"
#include "zombie/core/skinnedmodel/animation/debug/AnimationPlayerRecorder.h"
#include "zombie/core/skinnedmodel/animation/debug/GenericNameValueRecordingFrame.h"
#include "zombie/util/list/PZArrayUtil.h"
#include <algorithm>
#include <fstream>
#include <iostream>

namespace zombie {


class GameProfileRecording :  GenericNameValueRecordingFrame {
:
    long m_startTime;
    const Row m_rootRow = new Row();
   private HashMap<String, Integer> m_keyValueTable = std::make_unique<HashMap<>>();
    PrintStream m_outSegment = nullptr;
    long m_firstFrameNo = -1L;
   private List<String> m_segmentFilePaths = std::make_unique<ArrayList<>>();
    int m_numFramesPerFile = 60;
    int m_currentSegmentFrameCount = 0;

     GameProfileRecording(std::string_view var1) {
      super(var1, "_times");
      this.addColumnInternal("StartTime");
      this.addColumnInternal("EndTime");
      this.addColumnInternal("SegmentNo");
      this.addColumnInternal("Spans");
      this.addColumnInternal("key");
      this.addColumnInternal("Depth");
      this.addColumnInternal("StartTime");
      this.addColumnInternal("EndTime");
      this.addColumnInternal("Time Format");
      this.addColumnInternal("x * 100ns");
   }

    void setNumFramesPerSegment(int var1) {
      this.m_numFramesPerFile = var1;
   }

    void setStartTime(long var1) {
      this.m_startTime = var1;
   }

    void logTimeSpan(ProfileArea var1) {
      if (this.m_firstFrameNo == -1L) {
         this.m_firstFrameNo = this.m_frameNumber;
      }

    Span var2 = this.allocSpan(var1);
    Row var3 = this.m_rootRow;
      if (var3.Spans.isEmpty()) {
         var3.StartTime = var2.StartTime;
      }

      var3.EndTime = var2.EndTime;
      var3.Spans.add(var2);
   }

    Span allocSpan(ProfileArea var1) {
    int var2 = this.getOrCreateKey(var1.Key);
    long var3 = var1.StartTime - this.m_startTime;
    long var5 = var1.EndTime - this.m_startTime;
    Span var7 = Span.alloc();
      var7.key = var2;
      var7.Depth = var1.Depth;
      var7.StartTime = var3;
      var7.EndTime = var5;
    int var8 = 0;

      for (int var9 = var1.Children.size(); var8 < var9; var8++) {
    ProfileArea var10 = (ProfileArea)var1.Children.get(var8);
    Span var11 = this.allocSpan(var10);
         var7.Children.add(var11);
      }

    return var7;
   }

    int getOrCreateKey(std::string_view var1) {
    int var2 = this.m_keyValueTable.get(var1);
      if (var2 == nullptr) {
         var2 = this.m_keyValueTable.size();
         this.m_keyValueTable.put(var1, var2);
         this.m_headerDirty = true;
      }

    return var2;
   }

    std::string getValueAt(int var1) {
      throw RuntimeException("Not implemented. Use getValueAt(row, col)");
   }

    void onColumnAdded() {
   }

    void reset() {
      this.m_rootRow.reset();
   }

    void openSegmentFile(bool var1) {
      if (this.m_outSegment != nullptr) {
         this.m_outSegment.flush();
         this.m_outSegment.close();
      }

    std::string var2 = String.format("%s%s_%04d", this.m_fileKey, this.m_valuesFileNameSuffix, this.m_segmentFilePaths.size());
      this.m_outSegment = AnimationPlayerRecorder.openFileStream(var2, var1, this.m_segmentFilePaths::add);
      this.m_currentSegmentFrameCount = 0;
      this.m_headerDirty = true;
   }

    void close() {
      if (this.m_outSegment != nullptr) {
         this.m_outSegment.close();
         this.m_outSegment = nullptr;
      }
   }

    void closeAndDiscard() {
      super.closeAndDiscard();
      PZArrayUtil.forEach(this.m_segmentFilePaths, ZomboidFileSystem.instance::tryDeleteFile);
      this.m_segmentFilePaths.clear();
   }

    void writeData() {
      if (this.m_outValues == nullptr) {
         this.openValuesFile(false);
      }

    StringBuilder var1 = this.m_lineBuffer;
      var1.setLength(0);
      this.m_currentSegmentFrameCount++;
      if (this.m_outSegment == nullptr || this.m_currentSegmentFrameCount >= this.m_numFramesPerFile) {
         this.openSegmentFile(false);
      }

      this.writeDataRow(var1, this.m_rootRow);
      this.m_outSegment.print(this.m_frameNumber);
      this.m_outSegment.println(var1);
      var1 = this.m_lineBuffer;
      var1.setLength(0);
      this.writeFrameTimeRow(var1, this.m_rootRow, this.m_segmentFilePaths.size() - 1);
      this.m_outValues.print(this.m_frameNumber);
      this.m_outValues.println(var1);
   }

    void writeDataRow(StringBuilder var1, Row var2) {
    int var3 = 0;

      for (int var4 = var2.Spans.size(); var3 < var4; var3++) {
    Span var5 = (Span)var2.Spans.get(var3);
         this.writeSpan(var1, var2, var5);
      }
   }

    void writeFrameTimeRow(StringBuilder var1, Row var2, int var3) {
      appendCell(var1, var2.StartTime / 100L);
      appendCell(var1, var2.EndTime / 100L);
      appendCell(var1, var3);
   }

    void writeSpan(StringBuilder var1, Row var2, Span var3) {
    long var4 = (var3.StartTime - var2.StartTime) / 100L;
    long var6 = (var3.EndTime - var3.StartTime) / 100L;
      appendCell(var1, var3.key);
      appendCell(var1, var3.Depth);
      appendCell(var1, var4);
      appendCell(var1, var6);
    int var8 = 0;

      for (int var9 = var3.Children.size(); var8 < var9; var8++) {
    Span var10 = (Span)var3.Children.get(var8);
         this.writeSpan(var1, var2, var10);
      }
   }

    void writeHeader() {
      super.writeHeader();
      this.m_outHeader.println();
      this.m_outHeader.println("Segmentation Info");
      this.m_outHeader.println("FirstFrame," + this.m_firstFrameNo);
      this.m_outHeader.println("NumFramesPerFile," + this.m_numFramesPerFile);
      this.m_outHeader.println("NumFiles," + this.m_segmentFilePaths.size());
      this.m_outHeader.println();
      this.m_outHeader.println("KeyNamesTable");
      this.m_outHeader.println("Index,Name");
    StringBuilder var1 = new StringBuilder();

      for (Entry var3 : this.m_keyValueTable.entrySet()) {
         var1.setLength(0);
         var1.append(var3.getValue());
         var1.append(",");
         var1.append((String)var3.getKey());
         this.m_outHeader.println(var1);
      }
   }
}
} // namespace zombie
