#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "fmod/FMODSoundBuffer.h"
#include "fmod/SoundBuffer.h"
#include "java/awt/BasicStroke.h"
#include "java/awt/Color.h"
#include "java/awt/Dimension.h"
#include "java/awt/Graphics.h"
#include "java/awt/Graphics2D.h"
#include "java/awt/GridLayout.h"
#include "java/awt/Point.h"
#include "java/awt/RenderingHints.h"
#include "java/awt/Stroke.h"
#include "javax/swing/JFrame.h"
#include "javax/swing/JPanel.h"

namespace zombie {
namespace core {
namespace raknet {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class VoiceDebug : public JPanel {
public:
 static const int PREF_W = 400;
 static const int PREF_H = 200;
 static const int BORDER_GAP = 30;
 static const Color LINE_CURRENT_COLOR = Color.blue;
 static const Color LINE_LAST_COLOR = Color.red;
 static const Color GRAPH_COLOR = Color.green;
 static const Color GRAPH_POINT_COLOR = new Color(150, 50, 50, 180);
 static const Stroke GRAPH_STROKE = new BasicStroke(3.0F);
 static const int GRAPH_POINT_WIDTH = 12;
 static const int Y_HATCH_CNT = 10;
 public List<Integer> scores;
 int scores_max;
 std::string title;
 int psize;
 int last;
 int current;
 static VoiceDebug mainPanel;
 static VoiceDebug mainPanel2;
 static VoiceDebug mainPanel3;
 static VoiceDebug mainPanel4;
 static JFrame frame;

 public VoiceDebug(List<Integer> list, const std::string& string) {
 this->scores = list;
 this->title = string;
 this->psize = list.size();
 this->last = 5;
 this->current = 8;
 this->scores_max = 100;
 }

 void paintComponent(Graphics graphics) {
 super.paintComponent(graphics);
 Graphics2D graphics2D = (Graphics2D)graphics;
 graphics2D.setRenderingHint(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_ON);
 double double0 = (this->getWidth() - 60.0) / (this->scores.size() - 1);
 double double1 = (this->getHeight() - 60.0) / (this->scores_max - 1);
 int int0 = (int)((this->getHeight() - 60.0) / 2.0);
 int int1 = (int)(1.0 / double0);
 if (int1 == 0) {
 int1 = 1;
 }

 std::vector arrayList = new ArrayList();

 for (int int2 = 0; int2 < this->scores.size(); int2 += int1) {
 int int3 = (int)(int2 * double0 + 30.0);
 int int4 = (int)((this->scores_max - this->scores.get(int2) * double1 + 30.0 - int0);
 arrayList.add(new Point(int3, int4);
 }

 graphics2D.setColor(Color.black);
 graphics2D.drawLine(30, this->getHeight() - 30, 30, 30);
 graphics2D.drawLine(30, this->getHeight() - 30, this->getWidth() - 30, this->getHeight() - 30);

 for (int int5 = 0; int5 < 10; int5++) {
 uint8_t byte0 = 30;
 uint8_t byte1 = 42;
 int int6 = this->getHeight() - ((int5 + 1) * (this->getHeight() - 60) / 10 + 30);
 graphics2D.drawLine(byte0, int6, byte1, int6);
 }

 Stroke stroke = graphics2D.getStroke();
 graphics2D.setColor(GRAPH_COLOR);
 graphics2D.setStroke(GRAPH_STROKE);

 for (int int7 = 0; int7 < arrayList.size() - 1; int7++) {
 int int8 = ((Point)arrayList.get(int7).x;
 int int9 = ((Point)arrayList.get(int7).y;
 int int10 = ((Point)arrayList.get(int7 + 1).x;
 int int11 = ((Point)arrayList.get(int7 + 1).y;
 graphics2D.drawLine(int8, int9, int10, int11);
 }

 double double2 = (this->getWidth() - 60.0) / (this->psize - 1);
 graphics2D.setColor(LINE_CURRENT_COLOR);
 int int12 = (int)(this->current * double2 + 30.0);
 graphics2D.drawLine(int12, this->getHeight() - 30, int12, 30);
 graphics2D.drawString("Current", int12, this->getHeight() - 30);
 graphics2D.setColor(LINE_LAST_COLOR);
 int int13 = (int)(this->last * double2 + 30.0);
 graphics2D.drawLine(int13, this->getHeight() - 30, int13, 30);
 graphics2D.drawString("Last", int13, this->getHeight() - 30);
 graphics2D.setColor(Color.black);
 graphics2D.drawString(this->title, this->getWidth() / 2, 15);
 graphics2D.drawString("Size: " + this->scores.size(), 30, 15);
 graphics2D.drawString("Current/Write: " + this->current, 30, 30);
 graphics2D.drawString("Last/Read: " + this->last, 30, 45);
 }

 Dimension getPreferredSize() {
 return new Dimension(400, 200);
 }

 static void createAndShowGui() {
 std::vector arrayList0 = new ArrayList();
 std::vector arrayList1 = new ArrayList();
 std::vector arrayList2 = new ArrayList();
 std::vector arrayList3 = new ArrayList();
 mainPanel = new VoiceDebug(arrayList0, "SoundBuffer");
 mainPanel.scores_max = 32000;
 mainPanel2 = new VoiceDebug(arrayList1, "SoundBuffer - first 100 sample");
 mainPanel2.scores_max = 32000;
 mainPanel3 = new VoiceDebug(arrayList2, "FMODSoundBuffer");
 mainPanel3.scores_max = 32000;
 mainPanel4 = new VoiceDebug(arrayList3, "FMODSoundBuffer - first 100 sample");
 mainPanel4.scores_max = 32000;
 frame = new JFrame("DrawGraph");
 frame.setDefaultCloseOperation(3);
 frame.setLayout(new GridLayout(2, 2);
 frame.getContentPane().add(mainPanel);
 frame.getContentPane().add(mainPanel2);
 frame.getContentPane().add(mainPanel3);
 frame.getContentPane().add(mainPanel4);
 frame.pack();
 frame.setLocationByPlatform(true);
 frame.setVisible(true);
 }

 static void updateGui(SoundBuffer soundBuffer, FMODSoundBuffer fMODSoundBuffer) {
 mainPanel.scores.clear();
 if (soundBuffer != nullptr) {
 for (int int0 = 0; int0 < soundBuffer.buf().length; int0++) {
 mainPanel.scores.add(Integer.valueOf(soundBuffer.buf()[int0]));
 }

 mainPanel.current = soundBuffer.Buf_Write;
 mainPanel.last = soundBuffer.Buf_Read;
 mainPanel.psize = soundBuffer.Buf_Size;
 mainPanel2.scores.clear();

 for (int int1 = 0; int1 < 100; int1++) {
 mainPanel2.scores.add(Integer.valueOf(soundBuffer.buf()[int1]));
 }
 }

 mainPanel3.scores.clear();
 mainPanel4.scores.clear();

 for (byte byte0 = 0; byte0 < fMODSoundBuffer.buf().length / 2; byte0 += 2) {
 mainPanel4.scores.add(fMODSoundBuffer.buf()[byte0 + 1] * 256 + fMODSoundBuffer.buf()[byte0]);
 }

 frame.repaint();
 }
}
} // namespace raknet
} // namespace core
} // namespace zombie
