package zombie.vehicles;

import java.io.IOException;
import java.io.InputStream;
import java.nio.BufferOverflowException;
import java.nio.ByteBuffer;
import zombie.debug.DebugLog;
import zombie.iso.IsoWorld;
import zombie.util.ByteBufferOutputStream;

final class VehiclesDB2$VehicleBuffer {
   int m_id = -1;
   int m_wx;
   int m_wy;
   float m_x;
   float m_y;
   int m_WorldVersion;
   ByteBuffer m_bb = ByteBuffer.allocate(32768);

   private VehiclesDB2$VehicleBuffer() {
   }

   void set(BaseVehicle var1) throws IOException {
      if (!$assertionsDisabled && var1.sqlID < 1) {
         throw new AssertionError();
      } else {
         synchronized (VehiclesDB2.instance.m_main.m_usedIDs) {
            if (!$assertionsDisabled && !VehiclesDB2.instance.m_main.m_usedIDs.contains(var1.sqlID)) {
               throw new AssertionError();
            }
         }

         this.m_id = var1.sqlID;
         this.m_wx = var1.chunk.wx;
         this.m_wy = var1.chunk.wy;
         this.m_x = var1.getX();
         this.m_y = var1.getY();
         this.m_WorldVersion = IsoWorld.getWorldVersion();
         ByteBuffer var6 = (ByteBuffer)VehiclesDB2.TL_SliceBuffer.get();
         var6.clear();

         while (true) {
            try {
               var1.save(var6);
               break;
            } catch (BufferOverflowException var4) {
               if (var6.capacity() >= 2097152) {
                  DebugLog.General.error("the vehicle %d cannot be saved", new Object[]{var1.sqlID});
                  throw var4;
               }

               var6 = ByteBuffer.allocate(var6.capacity() + 32768);
               VehiclesDB2.TL_SliceBuffer.set(var6);
            }
         }

         var6.flip();
         this.setBytes(var6);
      }
   }

   void setBytes(ByteBuffer var1) {
      var1.rewind();
      ByteBufferOutputStream var2 = new ByteBufferOutputStream(this.m_bb, true);
      var2.clear();
      byte[] var3 = (byte[])VehiclesDB2.TL_Bytes.get();
      int var4 = var1.limit();

      while (var4 > 0) {
         int var5 = Math.min(var3.length, var4);
         var1.get(var3, 0, var5);
         var2.write(var3, 0, var5);
         var4 -= var5;
      }

      var2.flip();
      this.m_bb = var2.getWrappedBuffer();
   }

   void setBytes(byte[] var1) {
      ByteBufferOutputStream var2 = new ByteBufferOutputStream(this.m_bb, true);
      var2.clear();
      var2.write(var1);
      var2.flip();
      this.m_bb = var2.getWrappedBuffer();
   }

   void setBytes(InputStream var1) throws IOException {
      ByteBufferOutputStream var2 = new ByteBufferOutputStream(this.m_bb, true);
      var2.clear();
      byte[] var3 = (byte[])VehiclesDB2.TL_Bytes.get();

      while (true) {
         int var4 = var1.read(var3);
         if (var4 < 1) {
            var2.flip();
            this.m_bb = var2.getWrappedBuffer();
            return;
         }

         var2.write(var3, 0, var4);
      }
   }
}
