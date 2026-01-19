package zombie.characters;

import gnu.trove.map.hash.THashMap;
import java.util.HashMap;
import zombie.characters.BodyDamage.BodyDamage;
import zombie.characters.BodyDamage.BodyPart;
import zombie.characters.BodyDamage.BodyPartLast;
import zombie.characters.BodyDamage.BodyPartType;
import zombie.characters.WornItems.WornItems;
import zombie.inventory.InventoryItem;
import zombie.inventory.InventoryItemFactory;
import zombie.inventory.types.Clothing;
import zombie.network.GameClient;
import zombie.network.GameServer;
import zombie.util.StringUtils;

final class IsoGameCharacter$Bandages {
   final HashMap<String, String> bandageTypeMap = new HashMap<>();
   final THashMap<String, InventoryItem> itemMap = new THashMap();

   private IsoGameCharacter$Bandages() {
   }

   String getBloodBandageType(String var1) {
      String var2 = this.bandageTypeMap.get(var1);
      if (var2 == null) {
         this.bandageTypeMap.put(var1, var2 = var1 + "_Blood");
      }

      return var2;
   }

   void update(IsoGameCharacter var1) {
      if (!GameServer.bServer) {
         BodyDamage var2 = var1.getBodyDamage();
         WornItems var3 = var1.getWornItems();
         if (var2 != null && var3 != null) {
            if (!$assertionsDisabled && var1 instanceof IsoZombie) {
               throw new AssertionError();
            } else {
               this.itemMap.clear();

               for (int var4 = 0; var4 < var3.size(); var4++) {
                  InventoryItem var5 = var3.getItemByIndex(var4);
                  if (var5 != null) {
                     this.itemMap.put(var5.getFullType(), var5);
                  }
               }

               for (int var10 = 0; var10 < BodyPartType.ToIndex(BodyPartType.MAX); var10++) {
                  BodyPart var11 = var2.getBodyPart(BodyPartType.FromIndex(var10));
                  BodyPartLast var6 = var2.getBodyPartsLastState(BodyPartType.FromIndex(var10));
                  String var7 = var11.getType().getBandageModel();
                  if (!StringUtils.isNullOrWhitespace(var7)) {
                     String var8 = this.getBloodBandageType(var7);
                     if (var11.bandaged() != var6.bandaged()) {
                        if (var11.bandaged()) {
                           if (var11.isBandageDirty()) {
                              this.removeBandageModel(var1, var7);
                              this.addBandageModel(var1, var8);
                           } else {
                              this.removeBandageModel(var1, var8);
                              this.addBandageModel(var1, var7);
                           }
                        } else {
                           this.removeBandageModel(var1, var7);
                           this.removeBandageModel(var1, var8);
                        }
                     }

                     if (var11.bitten() != var6.bitten()) {
                        if (var11.bitten()) {
                           String var9 = var11.getType().getBiteWoundModel(var1.isFemale());
                           if (StringUtils.isNullOrWhitespace(var9)) {
                              continue;
                           }

                           this.addBandageModel(var1, var9);
                        } else {
                           this.removeBandageModel(var1, var11.getType().getBiteWoundModel(var1.isFemale()));
                        }
                     }

                     if (var11.scratched() != var6.scratched()) {
                        if (var11.scratched()) {
                           String var12 = var11.getType().getScratchWoundModel(var1.isFemale());
                           if (StringUtils.isNullOrWhitespace(var12)) {
                              continue;
                           }

                           this.addBandageModel(var1, var12);
                        } else {
                           this.removeBandageModel(var1, var11.getType().getScratchWoundModel(var1.isFemale()));
                        }
                     }

                     if (var11.isCut() != var6.isCut()) {
                        if (var11.isCut()) {
                           String var13 = var11.getType().getCutWoundModel(var1.isFemale());
                           if (!StringUtils.isNullOrWhitespace(var13)) {
                              this.addBandageModel(var1, var13);
                           }
                        } else {
                           this.removeBandageModel(var1, var11.getType().getCutWoundModel(var1.isFemale()));
                        }
                     }
                  }
               }
            }
         }
      }
   }

   protected void addBandageModel(IsoGameCharacter var1, String var2) {
      if (!this.itemMap.containsKey(var2)) {
         if (InventoryItemFactory.CreateItem(var2) instanceof Clothing var4) {
            var1.getInventory().addItem(var4);
            var1.setWornItem(var4.getBodyLocation(), var4);
            var1.resetModelNextFrame();
         }
      }
   }

   protected void removeBandageModel(IsoGameCharacter var1, String var2) {
      InventoryItem var3 = (InventoryItem)this.itemMap.get(var2);
      if (var3 != null) {
         var1.getWornItems().remove(var3);
         var1.getInventory().Remove(var3);
         var1.resetModelNextFrame();
         var1.onWornItemsChanged();
         if (GameClient.bClient && var1 instanceof IsoPlayer && ((IsoPlayer)var1).isLocalPlayer()) {
            GameClient.instance.sendClothing((IsoPlayer)var1, var3.getBodyLocation(), var3);
         }
      }
   }
}
