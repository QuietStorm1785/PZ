package zombie.core.booleanrectangles;

import java.util.ArrayList;
import java.util.Collections;
import org.lwjgl.util.Rectangle;
import zombie.core.booleanrectangles.BooleanRectangleCollection.1;
import zombie.core.booleanrectangles.BooleanRectangleCollection.Line;
import zombie.core.booleanrectangles.BooleanRectangleCollection.Point;

public class BooleanRectangleCollection extends ArrayList<Rectangle> {
   static boolean[][] donemap = new boolean[400][400];
   private static Point intersection = new Point();
   static int retWidth = 0;
   static int retHeight = 0;

   public void doIt(ArrayList<Rectangle> var1, Rectangle var2) {
      ArrayList var3 = new ArrayList();

      for (Rectangle var5 : var1) {
         ArrayList var6 = this.doIt(var5, var2);
         var3.addAll(var6);
      }

      this.clear();
      this.addAll(var3);
      this.optimize();
   }

   public void cutRectangle(Rectangle var1) {
      ArrayList var2 = new ArrayList();
      var2.addAll(this);
      this.doIt(var2, var1);
   }

   public ArrayList<Rectangle> doIt(Rectangle var1, Rectangle var2) {
      ArrayList var3 = new ArrayList();
      ArrayList var4 = new ArrayList();
      ArrayList var5 = new ArrayList();
      ArrayList var6 = new ArrayList();
      Rectangle var7 = var1;
      Rectangle var8 = var2;
      ArrayList var9 = new ArrayList();
      ArrayList var10 = new ArrayList();
      var9.add(new Line(this, new Point(var1.getX(), var1.getY()), new Point(var1.getX() + var1.getWidth(), var1.getY())));
      var9.add(new Line(this, new Point(var1.getX() + var1.getWidth(), var1.getY()), new Point(var1.getX() + var1.getWidth(), var1.getY() + var1.getHeight())));
      var9.add(new Line(this, new Point(var1.getX() + var1.getWidth(), var1.getY() + var1.getHeight()), new Point(var1.getX(), var1.getY() + var1.getHeight())));
      var9.add(new Line(this, new Point(var1.getX(), var1.getY() + var1.getHeight()), new Point(var1.getX(), var1.getY())));
      var10.add(new Line(this, new Point(var2.getX(), var2.getY()), new Point(var2.getX() + var2.getWidth(), var2.getY())));
      var10.add(new Line(this, new Point(var2.getX() + var2.getWidth(), var2.getY()), new Point(var2.getX() + var2.getWidth(), var2.getY() + var2.getHeight())));
      var10.add(
         new Line(this, new Point(var2.getX() + var2.getWidth(), var2.getY() + var2.getHeight()), new Point(var2.getX(), var2.getY() + var2.getHeight()))
      );
      var10.add(new Line(this, new Point(var2.getX(), var2.getY() + var2.getHeight()), new Point(var2.getX(), var2.getY())));

      for (int var11 = 0; var11 < var9.size(); var11++) {
         for (int var12 = 0; var12 < var10.size(); var12++) {
            if (this.IntesectsLine((Line)var9.get(var11), (Line)var10.get(var12)) != 0 && this.IsPointInRect(intersection.X, intersection.Y, var7)) {
               var4.add(new Point(intersection.X, intersection.Y));
            }
         }
      }

      if (this.IsPointInRect(var2.getX(), var2.getY(), var7)) {
         var4.add(new Point(var2.getX(), var2.getY()));
      }

      if (this.IsPointInRect(var2.getX() + var2.getWidth(), var2.getY(), var7)) {
         var4.add(new Point(var2.getX() + var2.getWidth(), var2.getY()));
      }

      if (this.IsPointInRect(var2.getX() + var2.getWidth(), var2.getY() + var2.getHeight(), var7)) {
         var4.add(new Point(var2.getX() + var2.getWidth(), var2.getY() + var2.getHeight()));
      }

      if (this.IsPointInRect(var2.getX(), var2.getY() + var2.getHeight(), var7)) {
         var4.add(new Point(var2.getX(), var2.getY() + var2.getHeight()));
      }

      var4.add(new Point(var7.getX(), var7.getY()));
      var4.add(new Point(var7.getX() + var7.getWidth(), var7.getY()));
      var4.add(new Point(var7.getX() + var7.getWidth(), var7.getY() + var7.getHeight()));
      var4.add(new Point(var7.getX(), var7.getY() + var7.getHeight()));
      Collections.sort(var4, new 1(this));
      int var20 = ((Point)var4.get(0)).X;
      int var21 = ((Point)var4.get(0)).Y;
      var5.add(var20);
      var6.add(var21);

      for (Point var14 : var4) {
         if (var14.X > var20) {
            var20 = var14.X;
            var5.add(var20);
         }

         if (var14.Y > var21) {
            var21 = var14.Y;
            var6.add(var21);
         }
      }

      for (int var22 = 0; var22 < var6.size() - 1; var22++) {
         for (int var23 = 0; var23 < var5.size() - 1; var23++) {
            int var15 = (Integer)var5.get(var23);
            int var16 = (Integer)var6.get(var22);
            int var17 = (Integer)var5.get(var23 + 1) - var15;
            int var18 = (Integer)var6.get(var22 + 1) - var16;
            Rectangle var19 = new Rectangle(var15, var16, var17, var18);
            if (!this.Intersects(var19, var8)) {
               var3.add(var19);
            }
         }
      }

      return var3;
   }

   public void optimize() {
      ArrayList var1 = new ArrayList();
      int var2 = 1000000;
      int var3 = 1000000;
      int var4 = -1000000;
      int var5 = -1000000;

      for (int var6 = 0; var6 < this.size(); var6++) {
         Rectangle var7 = this.get(var6);
         if (var7.getX() < var2) {
            var2 = var7.getX();
         }

         if (var7.getY() < var3) {
            var3 = var7.getY();
         }

         if (var7.getX() + var7.getWidth() > var4) {
            var4 = var7.getX() + var7.getWidth();
         }

         if (var7.getY() + var7.getHeight() > var5) {
            var5 = var7.getY() + var7.getHeight();
         }
      }

      int var14 = var4 - var2;
      int var15 = var5 - var3;

      for (int var8 = 0; var8 < var14; var8++) {
         for (int var9 = 0; var9 < var15; var9++) {
            donemap[var8][var9] = true;
         }
      }

      for (int var16 = 0; var16 < this.size(); var16++) {
         Rectangle var18 = this.get(var16);
         int var10 = var18.getX() - var2;
         int var11 = var18.getY() - var3;

         for (int var12 = 0; var12 < var18.getWidth(); var12++) {
            for (int var13 = 0; var13 < var18.getHeight(); var13++) {
               donemap[var12 + var10][var13 + var11] = false;
            }
         }
      }

      for (int var17 = 0; var17 < var14; var17++) {
         for (int var19 = 0; var19 < var15; var19++) {
            if (!donemap[var17][var19]) {
               int var20 = this.DoHeight(var17, var19, var15);
               int var21 = this.DoWidth(var17, var19, var20, var14);

               for (int var22 = 0; var22 < var21; var22++) {
                  for (int var23 = 0; var23 < var20; var23++) {
                     donemap[var22 + var17][var23 + var19] = true;
                  }
               }

               var1.add(new Rectangle(var17 + var2, var19 + var3, var21, var20));
            }
         }
      }

      this.clear();
      this.addAll(var1);
   }

   public boolean IsPointInRect(int var1, int var2, Rectangle var3) {
      return var1 >= var3.getX() && var1 <= var3.getX() + var3.getWidth() && var2 >= var3.getY() && var2 <= var3.getY() + var3.getHeight();
   }

   public int IntesectsLine(Line var1, Line var2) {
      intersection.X = 0;
      intersection.Y = 0;
      int var3 = var1.End.X - var1.Start.X;
      int var4 = var1.End.Y - var1.Start.Y;
      int var5 = var2.End.X - var2.Start.X;
      int var6 = var2.End.Y - var2.Start.Y;
      if (var3 == var5 || var4 == var6) {
         return 0;
      } else if (var4 == 0) {
         int var11 = Math.min(var1.Start.X, var1.End.X);
         int var12 = Math.max(var1.Start.X, var1.End.X);
         int var13 = Math.min(var2.Start.Y, var2.End.Y);
         int var14 = Math.max(var2.Start.Y, var2.End.Y);
         intersection.X = var2.Start.X;
         intersection.Y = var1.Start.Y;
         return 1;
      } else {
         int var7 = Math.min(var2.Start.X, var2.End.X);
         int var8 = Math.max(var2.Start.X, var2.End.X);
         int var9 = Math.min(var1.Start.Y, var1.End.Y);
         int var10 = Math.max(var1.Start.Y, var1.End.Y);
         intersection.X = var1.Start.X;
         intersection.Y = var2.Start.Y;
         return -1;
      }
   }

   public boolean Intersects(Rectangle var1, Rectangle var2) {
      int var3 = var1.getX() + var1.getWidth();
      int var4 = var1.getX();
      int var5 = var1.getY() + var1.getHeight();
      int var6 = var1.getY();
      int var7 = var2.getX() + var2.getWidth();
      int var8 = var2.getX();
      int var9 = var2.getY() + var2.getHeight();
      int var10 = var2.getY();
      return var3 > var8 && var5 > var10 && var4 < var7 && var6 < var9;
   }

   private int DoHeight(int var1, int var2, int var3) {
      int var4 = 0;

      for (int var5 = var2; var5 < var3; var5++) {
         if (donemap[var1][var5]) {
            return var4;
         }

         var4++;
      }

      return var4;
   }

   private int DoWidth(int var1, int var2, int var3, int var4) {
      int var5 = 0;

      for (int var6 = var1; var6 < var4; var6++) {
         for (int var7 = var2; var7 < var3; var7++) {
            if (donemap[var6][var7]) {
               return var5;
            }
         }

         var5++;
      }

      return var5;
   }

   private void DoRect(int var1, int var2) {
   }
}
