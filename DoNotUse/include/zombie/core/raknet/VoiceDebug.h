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


class VoiceDebug : public JPanel {
public:
    static const int PREF_W = 400;
    static const int PREF_H = 200;
    static const int BORDER_GAP = 30;
    static const Color LINE_CURRENT_COLOR = Color.blue;
    static const Color LINE_LAST_COLOR = Color.red;
    static const Color GRAPH_COLOR = Color.green;
    static const Color GRAPH_POINT_COLOR = std::make_shared<Color>(150, 50, 50, 180);
    static const Stroke GRAPH_STROKE = std::make_shared<BasicStroke>(3.0F);
    static const int GRAPH_POINT_WIDTH = 12;
    static const int Y_HATCH_CNT = 10;
   public List<int> scores;
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

    public VoiceDebug(List<int> var1, const std::string& var2) {
      this.scores = var1;
      this.title = var2;
      this.psize = var1.size();
      this.last = 5;
      this.current = 8;
      this.scores_max = 100;
   }

    void paintComponent(Graphics var1) {
      super.paintComponent(var1);
    Graphics2D var2 = (Graphics2D)var1;
      var2.setRenderingHint(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_ON);
    double var3 = (this.getWidth() - 60.0) / (this.scores.size() - 1);
    double var5 = (this.getHeight() - 60.0) / (this.scores_max - 1);
    int var7 = (int)((this.getHeight() - 60.0) / 2.0);
    int var8 = (int)(1.0 / var3);
      if (var8 == 0) {
         var8 = 1;
      }

    std::vector var9 = new std::vector();

      for (int var10 = 0; var10 < this.scores.size(); var10 += var8) {
    int var11 = (int)(var10 * var3 + 30.0);
    int var12 = (int)((this.scores_max - this.scores.get(var10)) * var5 + 30.0 - var7);
         var9.push_back(std::make_shared<Point>(var11, var12));
      }

      var2.setColor(Color.black);
      var2.drawLine(30, this.getHeight() - 30, 30, 30);
      var2.drawLine(30, this.getHeight() - 30, this.getWidth() - 30, this.getHeight() - 30);

      for (int var16 = 0; var16 < 10; var16++) {
    uint8_t var18 = 30;
    uint8_t var21 = 42;
    int var13 = this.getHeight() - ((var16 + 1) * (this.getHeight() - 60) / 10 + 30);
         var2.drawLine(var18, var13, var21, var13);
      }

    Stroke var17 = var2.getStroke();
      var2.setColor(GRAPH_COLOR);
      var2.setStroke(GRAPH_STROKE);

      for (int var19 = 0; var19 < var9.size() - 1; var19++) {
    int var22 = ((Point)var9.get(var19)).x;
    int var23 = ((Point)var9.get(var19)).y;
    int var14 = ((Point)var9.get(var19 + 1)).x;
    int var15 = ((Point)var9.get(var19 + 1)).y;
         var2.drawLine(var22, var23, var14, var15);
      }

    double var20 = (this.getWidth() - 60.0) / (this.psize - 1);
      var2.setColor(LINE_CURRENT_COLOR);
    int var24 = (int)(this.current * var20 + 30.0);
      var2.drawLine(var24, this.getHeight() - 30, var24, 30);
      var2.drawString("Current", var24, this.getHeight() - 30);
      var2.setColor(LINE_LAST_COLOR);
    int var25 = (int)(this.last * var20 + 30.0);
      var2.drawLine(var25, this.getHeight() - 30, var25, 30);
      var2.drawString("Last", var25, this.getHeight() - 30);
      var2.setColor(Color.black);
      var2.drawString(this.title, this.getWidth() / 2, 15);
      var2.drawString("Size: " + this.scores.size(), 30, 15);
      var2.drawString("Current/Write: " + this.current, 30, 30);
      var2.drawString("Last/Read: " + this.last, 30, 45);
   }

    Dimension getPreferredSize() {
      return std::make_shared<Dimension>(400, 200);
   }

    static void createAndShowGui() {
    std::vector var0 = new std::vector();
    std::vector var1 = new std::vector();
    std::vector var2 = new std::vector();
    std::vector var3 = new std::vector();
      mainPanel = std::make_shared<VoiceDebug>(var0, "SoundBuffer");
      mainPanel.scores_max = 32000;
      mainPanel2 = std::make_shared<VoiceDebug>(var1, "SoundBuffer - first 100 sample");
      mainPanel2.scores_max = 32000;
      mainPanel3 = std::make_shared<VoiceDebug>(var2, "FMODSoundBuffer");
      mainPanel3.scores_max = 32000;
      mainPanel4 = std::make_shared<VoiceDebug>(var3, "FMODSoundBuffer - first 100 sample");
      mainPanel4.scores_max = 32000;
      frame = std::make_shared<JFrame>("DrawGraph");
      frame.setDefaultCloseOperation(3);
      frame.setLayout(std::make_shared<GridLayout>(2, 2));
      frame.getContentPane().push_back(mainPanel);
      frame.getContentPane().push_back(mainPanel2);
      frame.getContentPane().push_back(mainPanel3);
      frame.getContentPane().push_back(mainPanel4);
      frame.pack();
      frame.setLocationByPlatform(true);
      frame.setVisible(true);
   }

    static void updateGui(SoundBuffer var0, FMODSoundBuffer var1) {
      mainPanel.scores.clear();
      if (var0 != nullptr) {
         for (int var2 = 0; var2 < var0.buf().length; var2++) {
            mainPanel.scores.push_back(int.valueOf(var0.buf()[var2]));
         }

         mainPanel.current = var0.Buf_Write;
         mainPanel.last = var0.Buf_Read;
         mainPanel.psize = var0.Buf_Size;
         mainPanel2.scores.clear();

         for (int var3 = 0; var3 < 100; var3++) {
            mainPanel2.scores.push_back(int.valueOf(var0.buf()[var3]));
         }
      }

      mainPanel3.scores.clear();
      mainPanel4.scores.clear();

      for (byte var4 = 0; var4 < var1.buf().length / 2; var4 += 2) {
         mainPanel4.scores.push_back(var1.buf()[var4 + 1] * 256 + var1.buf()[var4]);
      }

      frame.repaint();
   }
}
} // namespace raknet
} // namespace core
} // namespace zombie
