package zombie.inventory;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.FileWriter;
import java.nio.file.DirectoryStream;
import java.nio.file.FileSystems;
import java.nio.file.Files;
import java.nio.file.Path;
import zombie.ZomboidFileSystem;
import zombie.core.logger.ExceptionLogger;
import zombie.inventory.ClothingItemsDotTxt.Block;
import zombie.inventory.ClothingItemsDotTxt.Value;
import zombie.util.StringUtils;

public final class ClothingItemsDotTxt {
   public static final ClothingItemsDotTxt instance = new ClothingItemsDotTxt();
   private final StringBuilder buf = new StringBuilder();

   private int readBlock(String var1, int var2, Block var3) {
      int var4;
      for (var4 = var2; var4 < var1.length(); var4++) {
         if (var1.charAt(var4) == '{') {
            Block var5 = new Block();
            var3.children.add(var5);
            var3.elements.add(var5);
            String var6 = var1.substring(var2, var4).trim();
            int var7 = var6.indexOf(32);
            int var8 = var6.indexOf(9);
            int var9 = Math.max(var7, var8);
            if (var9 == -1) {
               var5.type = var6;
            } else {
               var5.type = var6.substring(0, var9);
               var5.id = var6.substring(var9).trim();
            }

            var4 = this.readBlock(var1, var4 + 1, var5);
            var2 = var4;
         } else {
            if (var1.charAt(var4) == '}') {
               String var11 = var1.substring(var2, var4).trim();
               if (!var11.isEmpty()) {
                  Value var12 = new Value();
                  var12.string = var1.substring(var2, var4).trim();
                  var3.values.add(var12.string);
                  var3.elements.add(var12);
               }

               return var4 + 1;
            }

            if (var1.charAt(var4) == ',') {
               Value var10 = new Value();
               var10.string = var1.substring(var2, var4).trim();
               var3.values.add(var10.string);
               var3.elements.add(var10);
               var2 = var4 + 1;
            }
         }
      }

      return var4;
   }

   public void LoadFile() {
      String var1 = ZomboidFileSystem.instance.getString("media/scripts/clothingItems.txt");
      File var2 = new File(var1);
      if (var2.exists()) {
         try (
            FileReader var3 = new FileReader(var1);
            BufferedReader var4 = new BufferedReader(var3);
         ) {
            this.buf.setLength(0);

            String var5;
            while ((var5 = var4.readLine()) != null) {
               this.buf.append(var5);
            }
         } catch (Throwable var21) {
            ExceptionLogger.logException(var21);
            return;
         }

         int var22 = this.buf.lastIndexOf("*/");

         while (var22 != -1) {
            int var23 = this.buf.lastIndexOf("/*", var22 - 1);
            if (var23 == -1) {
               break;
            }

            int var25 = this.buf.lastIndexOf("*/", var22 - 1);

            while (var25 > var23) {
               int var6 = var23;
               String var7 = this.buf.substring(var23, var25 + 2);
               var23 = this.buf.lastIndexOf("/*", var23 - 2);
               if (var23 == -1) {
                  break;
               }

               var25 = this.buf.lastIndexOf("*/", var6 - 2);
            }

            if (var23 == -1) {
               break;
            }

            String var27 = this.buf.substring(var23, var22 + 2);
            this.buf.replace(var23, var22 + 2, "");
            var22 = this.buf.lastIndexOf("*/", var23);
         }

         Block var24 = new Block();
         this.readBlock(this.buf.toString(), 0, var24);
         Path var26 = FileSystems.getDefault().getPath("media/clothing/clothingItems");

         try (DirectoryStream var28 = Files.newDirectoryStream(var26)) {
            for (Path var8 : var28) {
               if (!Files.isDirectory(var8)) {
                  String var9 = var8.getFileName().toString();
                  if (var9.endsWith(".xml")) {
                     String var10 = StringUtils.trimSuffix(var9, ".xml");
                     System.out.println(var9 + " -> " + var10);
                     this.addClothingItem(var10, (Block)var24.children.get(0));
                  }
               }
            }
         } catch (Exception var18) {
            var18.printStackTrace();
         }

         try (FileWriter var29 = new FileWriter(var2)) {
            var29.write(((Block)var24.children.get(0)).toString());
         } catch (Throwable var15) {
            ExceptionLogger.logException(var15);
         }

         System.out.println(var24.children.get(0));
      }
   }

   private void addClothingItem(String var1, Block var2) {
      if (!var1.startsWith("FemaleHair_")) {
         if (!var1.startsWith("MaleBeard_")) {
            if (!var1.startsWith("MaleHair_")) {
               if (!var1.startsWith("ZedDmg_")) {
                  if (!var1.startsWith("Bandage_")) {
                     if (!var1.startsWith("Zed_Skin")) {
                        for (Block var4 : var2.children) {
                           if ("item".equals(var4.type) && var1.equals(var4.id)) {
                              return;
                           }
                        }

                        Block var5 = new Block();
                        var5.type = "item";
                        var5.id = var1;
                        Value var6 = new Value();
                        var6.string = "Type = Clothing";
                        var5.elements.add(var6);
                        var5.values.add(var6.string);
                        var6 = new Value();
                        var6.string = "DisplayName = " + var1;
                        var5.elements.add(var6);
                        var5.values.add(var6.string);
                        var6 = new Value();
                        var6.string = "ClothingItem = " + var1;
                        var5.elements.add(var6);
                        var5.values.add(var6.string);
                        var2.elements.add(var5);
                        var2.children.add(var5);
                     }
                  }
               }
            }
         }
      }
   }
}
