package zombie.ui;

import java.util.ArrayList;
import zombie.ui.TextDrawObject.DrawElement;

final class TextDrawObject$DrawLine {
   private final ArrayList<DrawElement> elements = new ArrayList<>();
   private int h = 0;
   private int w = 0;
   private int charW = 0;

   private TextDrawObject$DrawLine() {
   }

   private void addElement(DrawElement var1) {
      this.elements.add(var1);
   }
}
