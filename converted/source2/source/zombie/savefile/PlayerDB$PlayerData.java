package zombie.savefile;

import java.io.IOException;
import java.io.InputStream;
import java.nio.BufferOverflowException;
import java.nio.ByteBuffer;
import zombie.characters.IsoPlayer;
import zombie.debug.DebugLog;
import zombie.iso.IsoWorld;
import zombie.util.ByteBufferOutputStream;

final class PlayerDB$PlayerData {
   int m_sqlID = -1;
   float m_x;
   float m_y;
   float m_z;
   boolean m_isDead;
   String m_name;
   int m_WorldVersion;
   ByteBuffer m_byteBuffer = ByteBuffer.allocate(32768);

   private PlayerDB$PlayerData() {
   }

   PlayerDB$PlayerData set(IsoPlayer var1) throws IOException {
      if (!$assertionsDisabled && var1.sqlID < 1) {
         throw new AssertionError();
      } else {
         this.m_sqlID = var1.sqlID;
         this.m_x = var1.getX();
         this.m_y = var1.getY();
         this.m_z = var1.getZ();
         this.m_isDead = var1.isDead();
         this.m_name = var1.getDescriptor().getForename() + " " + var1.getDescriptor().getSurname();
         this.m_WorldVersion = IsoWorld.getWorldVersion();
         ByteBuffer var2 = (ByteBuffer)PlayerDB.TL_SliceBuffer.get();
         var2.clear();

         while (true) {
            try {
               var1.save(var2);
               break;
            } catch (BufferOverflowException var4) {
               if (var2.capacity() >= 2097152) {
                  DebugLog.General.error("the player %s cannot be saved", new Object[]{var1.getUsername()});
                  throw var4;
               }

               var2 = ByteBuffer.allocate(var2.capacity() + 32768);
               PlayerDB.TL_SliceBuffer.set(var2);
            }
         }

         var2.flip();
         this.setBytes(var2);
         return this;
      }
   }

   void setBytes(ByteBuffer var1) {
      var1.rewind();
      ByteBufferOutputStream var2 = new ByteBufferOutputStream(this.m_byteBuffer, true);
      var2.clear();
      byte[] var3 = (byte[])PlayerDB.TL_Bytes.get();
      int var4 = var1.limit();

      while (var4 > 0) {
         int var5 = Math.min(var3.length, var4);
         var1.get(var3, 0, var5);
         var2.write(var3, 0, var5);
         var4 -= var5;
      }

      var2.flip();
      this.m_byteBuffer = var2.getWrappedBuffer();
   }

   void setBytes(byte[] var1) {
      ByteBufferOutputStream var2 = new ByteBufferOutputStream(this.m_byteBuffer, true);
      var2.clear();
      var2.write(var1);
      var2.flip();
      this.m_byteBuffer = var2.getWrappedBuffer();
   }

   void setBytes(InputStream var1) throws IOException {
      ByteBufferOutputStream var2 = new ByteBufferOutputStream(this.m_byteBuffer, true);
      var2.clear();
      byte[] var3 = (byte[])PlayerDB.TL_Bytes.get();

      while (true) {
         int var4 = var1.read(var3);
         if (var4 < 1) {
            var2.flip();
            this.m_byteBuffer = var2.getWrappedBuffer();
            return;
         }

         var2.write(var3, 0, var4);
      }
   }
}
