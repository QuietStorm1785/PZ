package zombie.core.skinnedmodel;

import java.util.ArrayList;
import zombie.characters.IsoGameCharacter;
import zombie.characters.AttachedItems.AttachedModels;
import zombie.core.skinnedmodel.model.ModelInstance;

public class ModelManager$ModelSlot {
   public int ID;
   public ModelInstance model;
   public IsoGameCharacter character;
   public final ArrayList<ModelInstance> sub = new ArrayList<>();
   protected final AttachedModels attachedModels = new AttachedModels();
   public boolean active;
   public boolean bRemove;
   public int renderRefCount = 0;
   public int framesSinceStart;

   public ModelManager$ModelSlot(int var1, ModelInstance var2, IsoGameCharacter var3) {
      this.ID = var1;
      this.model = var2;
      this.character = var3;
   }

   public void Update() {
      if (this.character != null && !this.bRemove) {
         this.framesSinceStart++;
         if (this != this.character.legsSprite.modelSlot) {
            boolean var1 = false;
         }

         if (this.model.AnimPlayer != this.character.getAnimationPlayer()) {
            this.model.AnimPlayer = this.character.getAnimationPlayer();
         }

         synchronized (this.model.m_lock) {
            this.model.UpdateDir();
            this.model.Update();

            for (int var2 = 0; var2 < this.sub.size(); var2++) {
               this.sub.get(var2).AnimPlayer = this.model.AnimPlayer;
            }
         }
      }
   }

   public boolean isRendering() {
      return this.renderRefCount > 0;
   }

   public void reset() {
      ModelManager.instance.resetModelInstanceRecurse(this.model, this);
      if (this.character != null) {
         this.character.primaryHandModel = null;
         this.character.secondaryHandModel = null;
         ModelManager.instance.derefModelInstances(this.character.getReadyModelData());
         this.character.getReadyModelData().clear();
      }

      this.active = false;
      this.character = null;
      this.bRemove = false;
      this.renderRefCount = 0;
      this.model = null;
      this.sub.clear();
      this.attachedModels.clear();
   }
}
