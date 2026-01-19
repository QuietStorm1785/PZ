package zombie.core.raknet;

import fmod.FMODSoundBuffer;
import fmod.SoundBuffer;
import java.awt.BasicStroke;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.GridLayout;
import java.awt.Point;
import java.awt.RenderingHints;
import java.awt.Stroke;
import java.util.ArrayList;
import java.util.List;
import javax.swing.JFrame;
import javax.swing.JPanel;

public class VoiceDebug extends JPanel {
   private static final int PREF_W = 400;
   private static final int PREF_H = 200;
   private static final int BORDER_GAP = 30;
   private static final Color LINE_CURRENT_COLOR = Color.blue;
   private static final Color LINE_LAST_COLOR = Color.red;
   private static final Color GRAPH_COLOR = Color.green;
   private static final Color GRAPH_POINT_COLOR = new Color(150, 50, 50, 180);
   private static final Stroke GRAPH_STROKE = new BasicStroke(3.0F);
   private static final int GRAPH_POINT_WIDTH = 12;
   private static final int Y_HATCH_CNT = 10;
   public List<Integer> scores;
   public int scores_max;
   public String title;
   public int psize;
   public int last;
   public int current;
   private static VoiceDebug mainPanel;
   private static VoiceDebug mainPanel2;
   private static VoiceDebug mainPanel3;
   private static VoiceDebug mainPanel4;
   private static JFrame frame;

   public VoiceDebug(List<Integer> var1, String var2) {
      this.scores = var1;
      this.title = var2;
      this.psize = var1.size();
      this.last = 5;
      this.current = 8;
      this.scores_max = 100;
   }

   @Override
   protected void paintComponent(Graphics var1) {
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

      ArrayList var9 = new ArrayList();

      for (int var10 = 0; var10 < this.scores.size(); var10 += var8) {
         int var11 = (int)(var10 * var3 + 30.0);
         int var12 = (int)((this.scores_max - this.scores.get(var10)) * var5 + 30.0 - var7);
         var9.add(new Point(var11, var12));
      }

      var2.setColor(Color.black);
      var2.drawLine(30, this.getHeight() - 30, 30, 30);
      var2.drawLine(30, this.getHeight() - 30, this.getWidth() - 30, this.getHeight() - 30);

      for (int var16 = 0; var16 < 10; var16++) {
         byte var18 = 30;
         byte var21 = 42;
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

   @Override
   public Dimension getPreferredSize() {
      return new Dimension(400, 200);
   }

   public static void createAndShowGui() {
      ArrayList var0 = new ArrayList();
      ArrayList var1 = new ArrayList();
      ArrayList var2 = new ArrayList();
      ArrayList var3 = new ArrayList();
      mainPanel = new VoiceDebug(var0, "SoundBuffer");
      mainPanel.scores_max = 32000;
      mainPanel2 = new VoiceDebug(var1, "SoundBuffer - first 100 sample");
      mainPanel2.scores_max = 32000;
      mainPanel3 = new VoiceDebug(var2, "FMODSoundBuffer");
      mainPanel3.scores_max = 32000;
      mainPanel4 = new VoiceDebug(var3, "FMODSoundBuffer - first 100 sample");
      mainPanel4.scores_max = 32000;
      frame = new JFrame("DrawGraph");
      frame.setDefaultCloseOperation(3);
      frame.setLayout(new GridLayout(2, 2));
      frame.getContentPane().add(mainPanel);
      frame.getContentPane().add(mainPanel2);
      frame.getContentPane().add(mainPanel3);
      frame.getContentPane().add(mainPanel4);
      frame.pack();
      frame.setLocationByPlatform(true);
      frame.setVisible(true);
   }

   public static void updateGui(SoundBuffer var0, FMODSoundBuffer var1) {
      mainPanel.scores.clear();
      if (var0 != null) {
         for (int var2 = 0; var2 < var0.buf().length; var2++) {
            mainPanel.scores.add(Integer.valueOf(var0.buf()[var2]));
         }

         mainPanel.current = var0.Buf_Write;
         mainPanel.last = var0.Buf_Read;
         mainPanel.psize = var0.Buf_Size;
         mainPanel2.scores.clear();

         for (int var3 = 0; var3 < 100; var3++) {
            mainPanel2.scores.add(Integer.valueOf(var0.buf()[var3]));
         }
      }

      mainPanel3.scores.clear();
      mainPanel4.scores.clear();

      for (byte var4 = 0; var4 < var1.buf().length / 2; var4 += 2) {
         mainPanel4.scores.add(var1.buf()[var4 + 1] * 256 + var1.buf()[var4]);
      }

      frame.repaint();
   }
}
