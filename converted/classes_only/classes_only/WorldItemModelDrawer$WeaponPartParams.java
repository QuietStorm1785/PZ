package zombie.core.skinnedmodel.model;

import org.joml.Matrix4f;
import zombie.scripting.objects.ModelAttachment;
import zombie.scripting.objects.ModelScript;

final class WorldItemModelDrawer$WeaponPartParams {
   Model m_model;
   String m_attachmentNameSelf;
   String m_attachmentNameParent;
   final Matrix4f m_transform = new Matrix4f();

   private WorldItemModelDrawer$WeaponPartParams() {
   }

   void initTransform(ModelScript var1, ModelScript var2) {
      this.m_transform.identity();
      Matrix4f var3 = WorldItemModelDrawer.s_attachmentXfrm;
      ModelAttachment var4 = var1.getAttachmentById(this.m_attachmentNameParent);
      if (var4 != null) {
         ModelInstanceRenderData.makeAttachmentTransform(var4, var3);
         this.m_transform.mul(var3);
      }

      ModelAttachment var5 = var2.getAttachmentById(this.m_attachmentNameSelf);
      if (var5 != null) {
         ModelInstanceRenderData.makeAttachmentTransform(var5, var3);
         var3.invert();
         this.m_transform.mul(var3);
      }
   }
}
